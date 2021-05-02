#pragma once

#include <string>
#include <Common/OrderBook.h>

using namespace std;

namespace Common
{
    class IStorage {
        public:
        IStorage(){};
        virtual ~IStorage(){};
        virtual void Start(string server) = 0;
        virtual void Stop() = 0;
        virtual void SaveOrderBook(OrderBook orderBook) = 0;
    };
}