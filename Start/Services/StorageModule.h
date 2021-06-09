#pragma once

#include <CPPServiceLocator/ServiceLocator.hpp>

#include <Common/IStorage.h>
#include <Storages/Redis/RedisStorage.h>
#include <Storages/MongoDB/MongoDBStorage.h>

namespace Start{
    namespace Services{
        class StorageModule : public ServiceLocator::Module {
            public:
            void load() override {
                bind<Common::IStorage>("Redis").to<Storages::Redis::RedisStorage>([] (SLContext_sptr slc) {
                    return new Storages::Redis::RedisStorage();
                });
                bind<Common::IStorage>("MongoDB").to<Storages::MongoDB::MongoDBStorage>([] (SLContext_sptr slc) {
                    return new Storages::MongoDB::MongoDBStorage();
                });
            }
        };
    }
}