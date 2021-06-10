#pragma once

#include <iostream>
#include <CPPServiceLocator/ServiceLocator.hpp>

#include <Common/IStorage.h>
#include "../Mock/StorageMockA.h"
#include "../Mock/StorageMockB.h"

namespace PlatformTest{
    namespace Services{
        class StorageModule : public ServiceLocator::Module {
            public:
            void load() override {
                bind<Common::IStorage>("StorageMockA").to<PlatformTest::Mock::StorageMockA>([] (SLContext_sptr slc) {
                    return new PlatformTest::Mock::StorageMockA();
                }).asSingleton();

                bind<Common::IStorage>("StorageMockB").to<PlatformTest::Mock::StorageMockB>([] (SLContext_sptr slc) {
                    return new PlatformTest::Mock::StorageMockB();
                }).asSingleton();
            }
        };
    }
}