#include <iostream>
#include <chrono>
#include "BinanceDataFeed.h"

using namespace std;

typedef std::shared_ptr<boost::asio::ssl::context> context_ptr;

namespace DataFeeds
{
    namespace Binance
    {
        void BinanceDataFeed::TryInitClient(){
            try{
                if(initialized) return;

                // Set logging to be pretty verbose (everything except message payloads)
                c.set_access_channels(websocketpp::log::alevel::all);
                c.clear_access_channels(websocketpp::log::alevel::frame_payload);

                // Initialize ASIO
                c.init_asio();
                c.set_tls_init_handler([](auto connection_hdl){
                    // establishes a SSL connection
                    context_ptr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);

                    try {
                        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                                        boost::asio::ssl::context::no_sslv2 |
                                        boost::asio::ssl::context::no_sslv3 |
                                        boost::asio::ssl::context::single_dh_use);
                    } catch (std::exception &e) {
                        cout << "Error in context pointer: " << e.what() << endl;
                    }

                    return ctx;
                });
                //c.set_tls_init_handler(bind(&BinanceDataFeed::on_tls_init, this, server.c_str(), ::_1));

                // Register our message handler
                c.set_message_handler([this](websocketpp::connection_hdl hdl, message_ptr msg){
                    this->OnMessage(msg->get_payload());
                });
                initialized = true;
            }
            catch (const websocketpp::exception& e) {
                cout << "BinanceDataFeed::TryInitClient() error: " << e.what() << std::endl;
            }
        }

        void BinanceDataFeed::Reconnection(){
            while(!stopped){
                try {
                    TryInitClient();
                    websocketpp::lib::error_code ec;
                    connection = c.get_connection(server, ec);
                    if (ec) {
                        std::cout << "could not create connection because: " << ec.message() << endl;
                        std::this_thread::sleep_for (std::chrono::seconds(3));
                        continue;
                    }

                    // Note that connect here only requests a connection. No network messages are
                    // exchanged until the event loop starts running in the next line.
                    c.connect(connection);

                    // Start the ASIO io_service run loop
                    // this will cause a single connection to be made to the server. c.run()
                    // will exit when this connection is closed.
                    c.run();
                } catch (websocketpp::exception const & e) {
                    cout << "BinanceDataFeed::Reconnection() error: " << e.what() << std::endl;
                    this_thread::sleep_for (std::chrono::seconds(3));
                }
            }
        }

        void BinanceDataFeed::OnMessage(const string &msg){
            // We should queue the msg in the case of high frequent data.
            OrderBook orderBook;
            orderBook.Deserialize(msg);
            context->NewOrderBook(move(orderBook));
        }
        
        void BinanceDataFeed::Start(string server, unique_ptr<IDataFeedContext> &&context){
            cout << "BinanceDataFeed::Start(" << server << ")\n";
            this->server = move(server);
            this->context = move(context);
            pReconnectThread = make_unique<thread>(&BinanceDataFeed::Reconnection, this);
        }

        void BinanceDataFeed::Stop(){
            cout << "BinanceDataFeed::Stop()\n";
            stopped = true;

            websocketpp::close::status::value v = 0;
            string reason = "Intentionally close connection.";
            connection->close(v, reason);

            if(pReconnectThread != nullptr){
                if(pReconnectThread->joinable()){
                    pReconnectThread->join();
                }
            }
        }
    }
}