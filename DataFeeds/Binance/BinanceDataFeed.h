#include <Common/IDataFeed.h>

using namespace Common;

namespace DataFeeds
{
    namespace Binance
    {
        class BinanceDataFeed : IDataFeed
        {
        private:
            /* data */
        public:
            void Start(string server);
            void Stop();
        };
    }
}