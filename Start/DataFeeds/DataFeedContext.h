#include <Common/IDataFeedContext.h>

namespace Start{
    namespace DataFeeds{
        class DataFeedContext: public IDataFeedContext{
            public:
            DataFeedContext(){}
            ~DataFeedContext(){}
            void NewOrderBook(OrderBook& orderBook){

            }
        };
    }
}