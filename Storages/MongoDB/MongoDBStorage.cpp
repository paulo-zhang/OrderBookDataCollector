#include <iostream>
#include "MongoDBStorage.h"

using namespace std;

namespace Storages
{
    namespace MongoDB{
        MongoDBStorage::MongoDBStorage(){

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