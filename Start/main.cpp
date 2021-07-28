#include <iostream>
#include <fstream>

#include <DataFeeds/Binance/BinanceDataFeed.h>
#include <Storages/MongoDB/MongoDBStorage.h>
#include <Storages/Redis/RedisStorage.h>
#include <Platform/PlatformService.h>
#include <Common/Configuration.h>
#include "Services/DataFeedModule.h"
#include "Services/StorageModule.h"

#include <CPPServiceLocator/ServiceLocator.hpp>

using namespace std;
using namespace Common;
using namespace Start::Services;
using namespace Platform;

int main()
{
    cout <<"Starting service ..." << endl;

    Configuration config;
    ifstream fin("configuration.json");
    stringstream strStream;
    strStream << fin.rdbuf();//read the file
    config.Deserialize(strStream.str());

    // DataFeed service.
    auto dataFeedLocator = ServiceLocator::create();
    dataFeedLocator->modules().add<DataFeedModule>();

    // Storage service
    auto storageLocator = ServiceLocator::create();
    storageLocator->modules().add<StorageModule>();

    PlatformService p(dataFeedLocator, storageLocator);
    p.Start(config);

    cout <<"Service Started." << endl;
    cout << "Press Esc Enter to exit.\n";
    while(cin.get() != '\e');

    p.Stop();
   return 0;
}