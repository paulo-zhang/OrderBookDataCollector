#pragma once

#include <CPPServiceLocator/ServiceLocator.hpp>

#include <Common/IDataFeed.h>
#include <DataFeeds/Binance/BinanceDataFeed.h>

namespace Start{
    namespace Services{
        class DataFeedModule : public ServiceLocator::Module {
            public:
            void load() override {
                bind<Common::IDataFeed>("Binance").to<DataFeeds::Binance::BinanceDataFeed>([] (SLContext_sptr slc) {
                    return new DataFeeds::Binance::BinanceDataFeed();
                });
                // More datafeeds can be bound in here ...
            }
        };
    }
}