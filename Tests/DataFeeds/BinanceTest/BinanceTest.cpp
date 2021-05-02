#include <gtest/gtest.h>
#include <DataFeeds/Binance/BinanceDataFeed.h>
#include "DataFeedContextMock.h"
#include <thread>
#include <chrono>

using namespace DataFeeds::Binance;

// Demonstrate some basic assertions.
TEST(BinanceDataFeed_Connection_Test, BasicAssertions) {
  DataFeedContextMock contextMock([](auto &orderBook){
      cout << orderBook.Symbol;
  });

  IDataFeed *p = new BinanceDataFeed(&contextMock);
  p->Start("wss://stream.binance.com:9443/ws/bnbbtc@depth");
  std::this_thread::sleep_for (std::chrono::seconds(30));
  p->Stop();
  EXPECT_TRUE(p != NULL);
}