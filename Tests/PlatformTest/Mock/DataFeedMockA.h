#pragma once

#include <memory>

#include <Common/IDataFeed.h>
#include <Common/OrderBook.h>
#include <Common/IDataFeedContext.h>

using namespace Common;
using namespace std;

namespace PlatformTest{
    namespace Mock{
        class DataFeedMockA : public IDataFeed{
            private:
            unique_ptr<IDataFeedContext> context;
            public:
            void Start(string server, unique_ptr<IDataFeedContext> &&context) override;
            void Stop() override;
        };

        void DataFeedMockA::Start(string server, unique_ptr<IDataFeedContext> &&context){
            this->context = move(context);
        }

        void DataFeedMockA::Stop(){

        }
    }
}