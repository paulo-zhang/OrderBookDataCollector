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

        void MongoDBStorage::Start(string server){
            cout << "MongoDBStorage::Start(" << server << ")" << endl;
        }

        void MongoDBStorage::Stop(){
            cout << "MongoDBStorage::Stop()" << endl;;
        }

        void MongoDBStorage::SaveOrderBook(OrderBook orderBook){
            
        }
    }
}