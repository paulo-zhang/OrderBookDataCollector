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
            shared_ptr<IDataFeedContext> context;
            public:
            void Start(const string &server, const shared_ptr<IDataFeedContext> &context) override;
            void Stop() override;
        };

        void DataFeedMockA::Start(const string &server, const shared_ptr<IDataFeedContext> &context){
            this->context = context;
        }

        void DataFeedMockA::Stop(){

        }
    }
}