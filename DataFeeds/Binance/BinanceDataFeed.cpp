#include <iostream>
#include <chrono>
#include "BinanceDataFeed.h"

using namespace std;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace DataFeeds
{
    namespace Binance
    {
        BinanceDataFeed::BinanceDataFeed(IDataFeedContext *context) {
            this->context = context;
        }

        BinanceDataFeed::~BinanceDataFeed() {

        }

        void Reconnect(BinanceDataFeed *that){
            that->Reconnection();
        }

        void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg){
            ((WebSocketClient*)c)->feed->OnMessage((WebSocketClient*)c, hdl, msg);
        }

        void BinanceDataFeed::Reconnection(){
            while(!stopped){
                try {
                    if(pClient != NULL){
                        auto p = pClient;
                        pClient = NULL;
                        delete p;
                    }

                    pClient = new WebSocketClient();
                    pClient->feed = this;
                    
                    // Set logging to be pretty verbose (everything except message payloads)
                    pClient->set_access_channels(websocketpp::log::alevel::all);
                    pClient->clear_access_channels(websocketpp::log::alevel::frame_payload);

                    // Initialize ASIO
                    pClient->init_asio();

                    // Register our message handler
                    pClient->set_message_handler(bind(&on_message, pClient,::_1,::_2));

                    websocketpp::lib::error_code ec;
                    client::connection_ptr con = pClient->get_connection(server, ec);
                    if (ec) {
                        std::cout << "could not create connection because: " << ec.message() << std::endl;
                        std::this_thread::sleep_for (std::chrono::seconds(3));
                        continue;
                    }

                    // Note that connect here only requests a connection. No network messages are
                    // exchanged until the event loop starts running in the next line.
                    pClient->connect(con);

                    // Start the ASIO io_service run loop
                    // this will cause a single connection to be made to the server. pClient->run()
                    // will exit when this connection is closed.
                    pClient->run();
                } catch (websocketpp::exception const & e) {
                    std::cout << e.what() << std::endl;
                    std::this_thread::sleep_for (std::chrono::seconds(3));
                }
            }
        }

        void BinanceDataFeed::OnMessage(WebSocketClient* c, websocketpp::connection_hdl hdl, message_ptr msg){
            // We should queue the msg in the case of high frequent data.
            OrderBook orderBook;
            orderBook.Deserialize(msg->get_payload());
            context->NewOrderBook(orderBook);
        }
        
        void BinanceDataFeed::Start(string server){
            cout << "BinanceDataFeed::Start(" << server << ")" << endl;
            this->server = server;
            pReconnectThread = new thread(Reconnect, this);
        }

        void BinanceDataFeed::Stop(){
            cout << "BinanceDataFeed::Stop()"<<endl;
            stopped = true;
            if(pReconnectThread != NULL && pReconnectThread->joinable()){
                pReconnectThread->join();
            }
        }
    }
}