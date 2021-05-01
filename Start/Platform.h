#pragma once

#include <Common/IDataFeed.h>
#include <Common/IStorage.h>

using namespace Common;

namespace Start{
    class Platform{
        private:
        IDataFeed *feed;
        IStorage *redis;
        IStorage *mongoDB;
        public:
        Platform();
        void Start();
        void Stop();
    };
}