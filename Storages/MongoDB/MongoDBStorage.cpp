#include <iostream>
#include "MongoDBStorage.h"

using namespace std;

namespace Storages
{
    namespace MongoDB{
        bool MongoDBStorage::initialized = false;

        MongoDBStorage::MongoDBStorage(){
            if(!initialized){
                mongocxx::instance instance{}; // This should be done only once.
                initialized = true;
            }
        }

        MongoDBStorage::~MongoDBStorage(){

        }

        void ThreadSaveDataToMongoDB(MongoDBStorage *that){
                that->SaveDataToMongoDB();
        }

        void MongoDBStorage::TryConnectMongoDB() {
            if(pClient != NULL)return;
            
            try {
                mongocxx::uri uri(server);
                pClient = new mongocxx::client(uri);
                pSaveDataThread = new thread(ThreadSaveDataToMongoDB, this);
            }
            catch(const std::exception& e)
            {
                std::cerr << "MongoDBStorage::TryConnectMongoDB(), error: " << e.what() << '\n';
            }
        }

        void MongoDBStorage::Start(string server){
            cout << "MongoDBStorage::Start(" << server << ")\n";
            this->server = server;
            TryConnectMongoDB();
        }

        void MongoDBStorage::Stop(){
            cout << "MongoDBStorage::Stop()" << endl;;
            stopped = true;
            cvNotifyCache.notify_all();

            if(pSaveDataThread != NULL){
                if(pSaveDataThread->joinable()){
                    pSaveDataThread->join();
                }

                delete pSaveDataThread;
                pSaveDataThread = NULL;
            }
        }

        void MongoDBStorage::SaveOrderBook(OrderBook orderBook){
            lock_guard<mutex> lk(mtxChache);
            cache.push_back(orderBook);
            cvNotifyCache.notify_all();
        }

        void MongoDBStorage::SaveDataToMongoDB(){
            while(!stopped){
                try
                {
                    vector<OrderBook> newContainer;
                    {
                        lock_guard<mutex> lk(mtxChache);
                        newContainer.swap(cache);
                        cache.clear();
                    }

                    if(newContainer.size() == 0){
                        unique_lock<std::mutex> lck(mtxChache);
                        cvNotifyCache.wait(lck);
                        continue;
                    }

                    std::vector<bsoncxx::document::value> documents;
                    for(auto &b : newContainer){
                        auto builder = bsoncxx::builder::stream::document{};
                        builder << "e" << b.EventType
                        << "E" << b.EventTime 
                        << "s" << b.Symbol
                        << "U" << b.FirstId
                        << "u" << b.FinalId
                        << "b" << bsoncxx::builder::stream::open_array;
                        for(auto &q : b.Bids){
                            builder << bsoncxx::builder::stream::open_array
                            << q.Price << q.Quantity
                            << close_array;
                        }
                        builder << close_array
                        << "a" << bsoncxx::builder::stream::open_array;
                        for(auto &q : b.Asks){
                            builder << bsoncxx::builder::stream::open_array
                            << q.Price << q.Quantity
                            << close_array;
                        }
                        builder << close_array
                        << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;
                        
                        documents.push_back(builder);
                    }

                    mongocxx::database db = (*pClient)["TradeDB"];
                    mongocxx::collection coll = db["OrderBooks"];
                    coll.insert_many(documents);
                    cout << "SaveDataToMongoDB, count: " << documents.size() << "\n";
                }
                catch(const std::exception& e)
                {
                    std::cerr << "MongoDBStorage::SaveDataToMongoDB(), error: " << e.what() << '\n';
                }
            }
        }
    }
}