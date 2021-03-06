#include <iostream>
#include "RedisStorage.h"
#include <chrono>

using namespace std;

namespace Storages
{
    namespace Redis{
        void ThreadSaveDataToRedis(RedisStorage *that){
            that->SaveDataToRedis();
        }

        void RedisStorage::TryConnectRedis(){
            try
            {
                if(pRedis != nullptr)return;

                pRedis = make_unique<sw::redis::Redis>(server);
                pSaveDataThread = make_unique<thread>(ThreadSaveDataToRedis, this);
            }
            catch(const sw::redis::Error &e) {
                cout << "RedisStorage::Start() error: " << e.what() << std::endl;
            }
        }

        void RedisStorage::Start(const Configuration &config){
            this->server = config.RedisServer;
            cout << "RedisStorage::Start(" << server << ")\n";
            TryConnectRedis();
        }

        void RedisStorage::Stop(){
            cout << "RedisStorage::Stop()\n";
            stopped = true;
            cvNotifyCache.notify_all();

            if(pSaveDataThread != nullptr){
                if(pSaveDataThread->joinable()){
                    pSaveDataThread->join();
                }
            }
        }

        void RedisStorage::SaveOrderBook(const OrderBook &orderBook){
            lock_guard<mutex> lk(mtxChache);
            cache[orderBook.Symbol] = orderBook;
            cvNotifyCache.notify_all();
        }

        void RedisStorage::SaveDataToRedis(){
            while(!stopped){
                try{
                    unordered_map<string, OrderBook> newMap;
                    {
                        lock_guard<mutex> lk(mtxChache);
                        newMap.swap(cache);
                    }

                    if(newMap.size() == 0){
                        unique_lock<std::mutex> lck(mtxChache);
                        cvNotifyCache.wait(lck);
                        continue;
                    }

                    unordered_map<string, string> hash;
                    for(auto &b : newMap){
                        hash[b.first] = b.second.Serialize();
                    }

                    pRedis->hmset("OrderBooks", hash.begin(), hash.end());
                    cout << "SaveDataToRedis, count: " << hash.size() << "\n";
                }
                catch(const std::exception& e)
                {
                    std::cerr << "RedisStorage::SaveDataToRedis(), error: " << e.what() << '\n';
                }
            }
        }
    }
}