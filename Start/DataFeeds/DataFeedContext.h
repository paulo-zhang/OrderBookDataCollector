#include<functional>

#include <Common/IDataFeedContext.h>
#include <Common/IStorage.h>

using namespace Common;

namespace Start{
    namespace DataFeeds{
        class DataFeedContext: public IDataFeedContext{
            private:
                std::function<void (OrderBook& orderBook)> callback;
            public:
                DataFeedContext(std::function<void (OrderBook& orderBook)> callback){this->callback = callback;}
                ~DataFeedContext(){}
                void NewOrderBook(OrderBook& orderBook) override {
                    callback(orderBook);
                }
        };
    }
}