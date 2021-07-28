#pragma once

#include <memory>
#include <Common/IDataFeed.h>
#include <Common/IStorage.h>
#include <CPPServiceLocator/ServiceLocator.hpp>

using namespace Common;

namespace Platform{
    class PlatformService{
        private:
        vector<shared_ptr<IDataFeed>> feeds;
        vector<shared_ptr<IStorage>> storages;

        shared_ptr<ServiceLocator> dataFeedServieLocator;
        shared_ptr<ServiceLocator> storageServiceLocator;
        
        public:
        PlatformService(shared_ptr<ServiceLocator> dataFeedServieLocator, shared_ptr<ServiceLocator> storageServiceLocator);
        void Start(const Configuration &config);
        void Stop();
    };
}