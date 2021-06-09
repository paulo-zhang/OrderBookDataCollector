#pragma once

#include <Common/IStorage.h>
#include <Common/OrderBook.h>
// https://github.com/sewenew/redis-plus-plus
#include <sw/redis++/redis++.h>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace Common;
using namespace std;

namespace Storages
{
    namespace Redis{
        class RedisStorage : public IStorage{
            private:
                string server;
                sw::redis::Redis *pRedis;
                unordered_map<string, OrderBook> cache;
                mutex mtxChache;
                condition_variable cvNotifyCache;
                bool stopped = false;
                thread *pSaveDataThread = NULL;
                void TryConnectRedis();
                void SaveDataToRedis();
                friend void ThreadSaveDataToRedis(RedisStorage *that);
            public:
                RedisStorage();
                ~RedisStorage() override;
                void Start(string server) override;
                void Stop() override;
                void SaveOrderBook(OrderBook orderBook) override;
        };
    }
}