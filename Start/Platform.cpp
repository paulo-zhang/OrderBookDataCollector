#include <iostream>
#include <fstream>
#include <DataFeeds/Binance/BinanceDataFeed.h>
#include <Storages/MongoDB/MongoDBStorage.h>
#include <Storages/Redis/RedisStorage.h>
#include "DataFeeds/DataFeedContext.h"
#include "Platform.h"
#include "Configuration.h"

using namespace DataFeeds::Binance;
using namespace Storages::MongoDB;
using namespace Storages::Redis;
using namespace Start::DataFeeds;
using namespace std;

namespace Start{
    Platform::Platform(){
        
    }

    void Platform::Start(){
        cout <<"Platform::Start()" << endl;

        redis = new RedisStorage();
        mongoDB = new MongoDBStorage();

        feed = new BinanceDataFeed(new DataFeedContext([this](OrderBook& orderBook){
            redis->SaveOrderBook(orderBook);
            mongoDB->SaveOrderBook(orderBook);
        }));
        
        Configuration config;
        ifstream fin("configuration.json");
        stringstream strStream;
        strStream << fin.rdbuf();//read the file
        config.Deserialize(strStream.str());

        feed->Start(config.BinanceServer);
        redis->Start(config.RedisServer);
        mongoDB->Start(config.MongoDBServer);
    }

    void Platform::Stop(){
        cout <<"Platform::Stop()" << endl;
        feed->Stop();
        redis->Stop();
        mongoDB->Stop();
    }
}