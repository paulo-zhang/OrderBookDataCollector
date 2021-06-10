#pragma once

#include <string>
#include "IDataFeedContext.h"

using namespace std;

namespace Common
{
    class IDataFeed {
        public:
        virtual void Start(const string &server, const shared_ptr<IDataFeedContext> &context) = 0;
        virtual void Stop() = 0;
    };
}