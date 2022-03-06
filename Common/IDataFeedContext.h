#pragma once

#include <string>
#include "OrderBook.h"

using namespace std;

namespace Common
{
    class IDataFeedContext {
        public:
        virtual void NewOrderBook(OrderBook&& orderBook) = 0;
        IDataFeedContext() = default;
        IDataFeedContext(IDataFeedContext &&) = default;
        IDataFeedContext& operator = (IDataFeedContext&&) = default;
        virtual ~IDataFeedContext(){}
    };
}