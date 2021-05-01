#include <iostream>
#include "RedisStorage.h"

using namespace std;

namespace Storages
{
    namespace Redis{
        RedisStorage::RedisStorage(){

        }

        RedisStorage::~RedisStorage(){

        }

        void RedisStorage::Start(string server){
            cout << "RedisStorage::Start(" << server << ")" << endl;
        }

        void RedisStorage::Stop(){
            cout << "RedisStorage::Stop()" << endl;;
        }
    }
}