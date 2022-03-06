#pragma once

#include <string>
#include "Library.h"
#include "IDataFeedContext.h"

using namespace std;

namespace Common
{
    class IDataFeed {
        public:
        virtual void Start(string server, unique_ptr<IDataFeedContext> &&context) = 0;
        virtual void Stop() = 0;
        IDataFeed() = default;
        IDataFeed(IDataFeed &&) = default;
        IDataFeed& operator = (IDataFeed&&) = default;
        virtual ~IDataFeed(){}
    };
}

extern EXPORT void* create();