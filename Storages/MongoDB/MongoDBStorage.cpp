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
                    using bsoncxx::builder::basic::kvp;
                    using bsoncxx::builder::basic::sub_array;

                    // https://github.com/mongodb/mongo-cxx-driver/blob/master/examples/bsoncxx/builder_basic.cpp
                    // http://mongocxx.org/mongocxx-v3/working-with-bson/
                    for(auto &b : newContainer){
                        auto doc = bsoncxx::builder::basic::document{};
                        doc.append(kvp("e", b.EventType));
                        doc.append(kvp("E", bsoncxx::types::b_int64() = {b.EventTime}));
                        doc.append(kvp("s", b.Symbol));
                        doc.append(kvp("U", bsoncxx::types::b_int64() = {b.FirstId}));
                        doc.append(kvp("U", bsoncxx::types::b_int64() = {b.FinalId}));
                        doc.append(kvp("a", [&b](sub_array child) {
                            for (const auto& q : b.Asks) {
                                child.append([&q](sub_array nestChild){
                                    nestChild.append(q.Price);
                                    nestChild.append(q.Quantity);
                                });
                            }
                        }));

                        doc.append(kvp("b", [&b](sub_array child) {
                            for (const auto& q : b.Bids) {
                                child.append([&q](sub_array nestChild){
                                    nestChild.append(q.Price);
                                    nestChild.append(q.Quantity);
                                });
                            }
                        }));

                        documents.push_back(doc.extract());
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