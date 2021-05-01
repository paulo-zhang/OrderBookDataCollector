#pragma once

#include <Common/IStorage.h>

using namespace Common;
namespace Storages
{
    namespace Redis{
        class RedisStorage : public IStorage{
            private:
            // Data.
            public:
            RedisStorage();
            virtual ~RedisStorage();
            void Start(string server);
            void Stop();
        };
    }
}