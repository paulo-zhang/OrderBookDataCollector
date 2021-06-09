#pragma once

#include <string>
#include "IDataFeedContext.h"

using namespace std;

namespace Common
{
    class IDataFeed {
        public:
        IDataFeed() {};
        virtual ~IDataFeed(){};
        virtual void Start(string server, IDataFeedContext *context) = 0;
        virtual void Stop() = 0;
    };
}