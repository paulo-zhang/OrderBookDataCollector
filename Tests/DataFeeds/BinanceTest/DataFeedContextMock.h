#include <Common/IDataFeedContext.h>

class DataFeedContextMock : public IDataFeedContext{
    private:
        void (*callback)(OrderBook& orderBook, int count);
        int count = 0;
    public:
        DataFeedContextMock(void (*callback)(OrderBook& orderBook, int count)){
            this->callback = callback;
        }
        ~DataFeedContextMock(){}
        void NewOrderBook(OrderBook& orderBook){
            callback(orderBook, ++ count);
        }
};