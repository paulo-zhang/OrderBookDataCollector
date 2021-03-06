#include <gtest/gtest.h>
#include <DataFeeds/Binance/BinanceDataFeed.h>
#include "DataFeedContextMock.h"
#include <thread>
#include <chrono>

using namespace DataFeeds::Binance;

// Demonstrate some basic assertions.
TEST(BinanceDataFeed_Connection_Test, BasicAssertions) {
  unique_ptr<DataFeedContextMock> contextMock = make_unique<DataFeedContextMock>([](auto &&orderBook, int count){
      cout << "Receive orderBook(" << count << "): Symbol: " << orderBook.Symbol << ", EventType: " << orderBook.EventType << ", EventTime: " << orderBook.EventTime << endl;
  });

  IDataFeed *p = new BinanceDataFeed();
  // https://github.com/binance/binance-spot-api-docs/blob/master/web-socket-streams.md#how-to-manage-a-local-order-book-correctly
  p->Start("wss://stream.binance.com:9443/ws/btcusdt@depth", move(contextMock));
  std::this_thread::sleep_for (std::chrono::seconds(10));
  p->Stop();
  EXPECT_TRUE(p != NULL); // Just a dummy test.
  delete p;
}