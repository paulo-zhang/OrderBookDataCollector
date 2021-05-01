#include <iostream>
#include <DataFeeds/Binance/BinanceDataFeed.h>
#include <Storages/MongoDB/MongoDBStorage.h>
#include <Storages/Redis/RedisStorage.h>
#include "Platform.h"

using namespace DataFeeds::Binance;
using namespace Storages::MongoDB;
using namespace Storages::Redis;
using namespace std;

namespace Start{
    Platform::Platform(){
        feed = new BinanceDataFeed();
        redis = new RedisStorage();
        mongoDB = new MongoDBStorage();
    }

    void Platform::Start(){
        cout <<"Platform::Start()" << endl;
        
        feed->Start("Server from Platform.");

        redis->Start("Server from Platform.");

        mongoDB->Start("Server from Platform.");
    }

    void Platform::Stop(){
        cout <<"Platform::Stop()" << endl;
        feed->Stop();
        redis->Stop();
        mongoDB->Stop();
    }
}