#pragma once

#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/types.hpp>

#include <Common/IStorage.h>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using namespace Common;
namespace Storages
{
    namespace MongoDB{
        class MongoDBStorage : public IStorage{
            private:
                static bool initialized;
                string server;
                unique_ptr<mongocxx::client> pClient = nullptr;
                vector<OrderBook> cache;
                mutex mtxChache;
                condition_variable cvNotifyCache;
                bool stopped = false;
                unique_ptr<thread> pSaveDataThread = nullptr;
                void TryConnectMongoDB();
                void SaveDataToMongoDB();
                friend void ThreadSaveDataToMongoDB(MongoDBStorage *that);
            public:
                MongoDBStorage();
                void Start(const Configuration &config) override;
                void Stop() override;
                void SaveOrderBook(const OrderBook &orderBook) override;
        };
    }
}