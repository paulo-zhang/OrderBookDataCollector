#pragma once

#include <string>
#include <Common/OrderBook.h>
#include "Configuration.h"

using namespace std;

namespace Common
{
    class IStorage {
        public:
        virtual void Start(const Configuration &config) = 0;
        virtual void Stop() = 0;
        virtual void SaveOrderBook(const OrderBook &orderBook) = 0;
        IStorage() = default;
        IStorage(const IStorage&) = delete;
        IStorage& operator = (const IStorage&) = delete;
        IStorage(IStorage &&) = delete;
        IStorage& operator = (IStorage&&) = delete;
        virtual ~IStorage() = default;
    };
}