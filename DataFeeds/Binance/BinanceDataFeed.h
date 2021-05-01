#pragma once

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