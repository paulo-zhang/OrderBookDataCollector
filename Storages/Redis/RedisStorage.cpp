#include <iostream>
#include "RedisStorage.h"
#include <chrono>

using namespace std;

namespace Storages
{
    namespace Redis{
        RedisStorage::RedisStorage(){

        }

        RedisStorage::~RedisStorage(){

        }
        
        void ThreadSaveDataToRedis(RedisStorage *that){
            that->SaveDataToRedis();
        }

        void RedisStorage::TryConnectRedis(){
            try
            {
                if(pRedis != NULL)return;

                pRedis = new sw::redis::Redis(server);
                pSaveDataThread = new thread(ThreadSaveDataToRedis, this);
            }
            catch(const sw::redis::Error &e) {
                cout << "RedisStorage::Start() error: " << e.what() << std::endl;
            }
        }

        void RedisStorage::Start(string server){
            this->server = server;
            cout << "RedisStorage::Start(" << server << ")\n";
            TryConnectRedis();
        }

        void RedisStorage::Stop(){
            cout << "RedisStorage::Stop()\n";
            stopped = true;

            if(pSaveDataThread != NULL){
                if(pSaveDataThread->joinable()){
                    pSaveDataThread->join();
                }

                delete pSaveDataThread;
                pSaveDataThread = NULL;
            }
        }

        void RedisStorage::SaveOrderBook(OrderBook orderBook){
            lock_guard<mutex> lk(mtxChache);
            cache[orderBook.Symbol] = orderBook;
            cvNotifyCache.notify_all();
        }

        void RedisStorage::SaveDataToRedis(){
            while(!stopped){
                unordered_map<string, OrderBook> newMap;
                {
                    lock_guard<mutex> lk(mtxChache);
                    newMap.swap(cache);
                    cache.clear();
                }

                if(newMap.size() == 0){
                    unique_lock<std::mutex> lck(mtxChache);
                    cvNotifyCache.wait(lck);
                }

                unordered_map<string, string> hash;
                for(auto &b : newMap){
                    hash[b.first] = b.second.Serialize();
                }

                pRedis->hgetall("OrderBooks", std::inserter(hash, hash.end()));
            }
        }
    }
}