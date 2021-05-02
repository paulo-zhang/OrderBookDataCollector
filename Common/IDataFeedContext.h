#pragma once

#include <string>
#include "OrderBook.h"

using namespace std;

namespace Common
{
    class IDataFeedContext {
        public:
        IDataFeedContext() {};
        virtual ~IDataFeedContext(){};
        virtual void NewOrderBook(OrderBook& orderBook) = 0;
    };
}