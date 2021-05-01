#include <gtest/gtest.h>
#include <DataFeeds/Binance/BinanceDataFeed.h>

using namespace DataFeeds::Binance;

// Demonstrate some basic assertions.
TEST(BinanceDataFeed_Contructor_Test, BasicAssertions) {
  IDataFeed *p = new BinanceDataFeed();

  EXPECT_TRUE(p != NULL);
}