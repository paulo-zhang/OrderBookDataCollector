#include <Common/IDataFeedContext.h>

class DataFeedContextMock : public IDataFeedContext{
    public:
    DataFeedContextMock(void (*func)(OrderBook& orderBook)){}
    ~DataFeedContextMock(){}
    void NewOrderBook(OrderBook& orderBook){
        
    }
};