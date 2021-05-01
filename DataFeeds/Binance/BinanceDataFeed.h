#pragma once

#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <Common/IDataFeed.h>

using namespace Common;

namespace DataFeeds
{
    namespace Binance
    {
        class BinanceDataFeed : public IDataFeed
        {
        private:
            /* data */
        public:
            BinanceDataFeed();
            virtual ~BinanceDataFeed();
            virtual void Start(string server);
            virtual void Stop();
        };
    }
}