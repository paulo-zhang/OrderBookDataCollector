#pragma once

#include <Common/IStorage.h>

using namespace Common;
namespace Storages
{
    namespace MongoDB{
        class MongoDBStorage : public IStorage{
            public:
            MongoDBStorage();
            virtual ~MongoDBStorage();
            virtual void Start(string server);
            virtual void Stop();
            virtual void SaveOrderBook(OrderBook orderBook);
        };
    }
}