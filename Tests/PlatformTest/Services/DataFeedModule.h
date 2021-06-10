#pragma once

#include <CPPServiceLocator/ServiceLocator.hpp>

#include <Common/IDataFeed.h>
#include "../Mock/DataFeedMockA.h"
#include "../Mock/DataFeedMockB.h"

namespace PlatformTest{
    namespace Services{
        class DataFeedModule : public ServiceLocator::Module {
            public:
            void load() override {
                bind<Common::IDataFeed>("DataFeedMockA").to<PlatformTest::Mock::DataFeedMockA>([] (SLContext_sptr slc) {
                    return new PlatformTest::Mock::DataFeedMockA();
                }).asSingleton();

                bind<Common::IDataFeed>("DataFeedMockB").to<PlatformTest::Mock::DataFeedMockB>([] (SLContext_sptr slc) {
                    return new PlatformTest::Mock::DataFeedMockB();
                }).asSingleton();
            }
        };
    }
}