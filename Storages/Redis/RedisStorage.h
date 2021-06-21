#pragma once

#include <Common/IStorage.h>
#include <Common/OrderBook.h>
// https://github.com/sewenew/redis-plus-plus
#include <sw/redis++/redis++.h>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

using namespace Common;
using namespace std;

namespace Storages
{
    namespace Redis{
        class RedisStorage : public IStorage{
            private:
                string server;
                unique_ptr<sw::redis::Redis> pRedis = nullptr;
                unordered_map<string, OrderBook> cache;
                mutex mtxChache;
                condition_variable cvNotifyCache;
                bool stopped = false;
                unique_ptr<thread> pSaveDataThread = nullptr;
                void TryConnectRedis();
                void SaveDataToRedis();
                friend void ThreadSaveDataToRedis(RedisStorage *that);
            public:
                void Start(const Configuration &config) override;
                void Stop() override;
                void SaveOrderBook(const OrderBook &orderBook) override;
        };
    }
}