#pragma once

// #define ASIO_STANDALONE

#include <string>
#include <thread>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <Common/IDataFeed.h>
#include <Common/OrderBook.h>
#include <Common/IDataFeedContext.h>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using namespace Common;

namespace DataFeeds
{
    namespace Binance
    {
        class BinanceDataFeed;

        class WebSocketClient : public client {
            public:
                BinanceDataFeed * feed;
                ~WebSocketClient(){}
        };

        class BinanceDataFeed : public IDataFeed
        {
        private:
            // Create a client endpoint
            WebSocketClient c;
            client::connection_ptr connection;
            thread *pReconnectThread = NULL;
            string server;
            bool stopped = false;
            IDataFeedContext *context;
            bool initialized = false;

            void OnMessage(string msg);
            void Reconnection();
            friend void Reconnect(BinanceDataFeed *that);
            friend void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg);
            void TryInitClient();
        public:
            BinanceDataFeed(IDataFeedContext *context);
            ~BinanceDataFeed() override;
            void Start(string server) override;
            void Stop() override;
        };
    }
}