#include <iostream>
#include "DataFeeds/DataFeedContext.h"
#include "PlatformService.h"
#include <Common/Configuration.h>

using namespace std;
using namespace Common;

namespace Platform{
    PlatformService::PlatformService(const shared_ptr<ServiceLocator> &dataFeedServieLocator, const shared_ptr<ServiceLocator> &storageServiceLocator){
        this->dataFeedServieLocator = dataFeedServieLocator;
        this->storageServiceLocator = storageServiceLocator;
    }

    void PlatformService::Start(const Configuration &config){
        cout <<"Platform::Start()" << endl;

        dataFeedServieLocator->getContext()->resolveAll<IDataFeed>(&feeds);
        storageServiceLocator->getContext()->resolveAll<IStorage>(&storages);

        for(const auto &storage : storages){
            storage->Start(config);
        }

        for(const auto &feed: feeds){
            feed->Start(config.BinanceServer, new Platform::DataFeeds::DataFeedContext([this](OrderBook& orderBook){
                for(const auto &storage : storages){
                    storage->SaveOrderBook(orderBook);
                }
            }));
        }
    }

    void PlatformService::Stop(){
        cout <<"Platform::Stop()" << endl;
        for(const auto &feed: feeds){
            feed->Stop();
        }

        for(const auto &storage : storages){
            storage->Stop();
        }
    }
}