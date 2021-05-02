#include <iostream>
#include <DataFeeds/Binance/BinanceDataFeed.h>
#include <Storages/MongoDB/MongoDBStorage.h>
#include <Storages/Redis/RedisStorage.h>
#include "DataFeeds/DataFeedContext.h"
#include "Platform.h"

using namespace DataFeeds::Binance;
using namespace Storages::MongoDB;
using namespace Storages::Redis;
using namespace Start::DataFeeds;
using namespace std;

namespace Start{
    Platform::Platform(){
        
    }

    void Platform::Start(){
        feed = new BinanceDataFeed(new DataFeedContext());
        redis = new RedisStorage();
        mongoDB = new MongoDBStorage();

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