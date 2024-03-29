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
        class BinanceDataFeed : public IDataFeed
        {
        private:
            // Create a client endpoint
            client c;
            client::connection_ptr connection;
            unique_ptr<thread> pReconnectThread = nullptr;
            string server;
            bool stopped = false;
            unique_ptr<IDataFeedContext> context;
            bool initialized = false;

            void OnMessage(const string &msg);
            void Reconnection();
            friend void Reconnect(BinanceDataFeed *that);
            friend void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg);
            void TryInitClient();
        public:
            void Start(string server, unique_ptr<IDataFeedContext> &&context) override;
            void Stop() override;
        };
    }
}