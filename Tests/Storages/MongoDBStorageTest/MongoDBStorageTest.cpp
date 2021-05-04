#include <gtest/gtest.h>
#include <Storages/MongoDB/MongoDBStorage.h>

using namespace Storages::MongoDB;

// Demonstrate some basic assertions.
TEST(MongoDBStorage_SaveOrderBook_Test, BasicAssertions) {
  IStorage *p = new MongoDBStorage();

  // "tcp://127.0.0.1:6379"
  p->Start("mongodb://localhost:27170");
  OrderBook orderBook = {.EventType = "depthUpdate", .EventTime = 1619922115877, .Symbol = "BNBBTC", .FirstId = 1833997158, .FinalId = 1833997167};
  orderBook.Asks.push_back(Quote() = {.Price = "0.01077900", .Quantity = "5.01075500"});
  orderBook.Asks.push_back(Quote() = {.Price = "0.01075600", .Quantity = "5.23000000"});
  orderBook.Bids.push_back(Quote() = {.Price = "0.01074900", .Quantity = "5.18000000"});
  orderBook.Bids.push_back(Quote() = {.Price = "0.01075700", .Quantity = "5.20000000"});

  p->SaveOrderBook(orderBook);
  this_thread::sleep_for (std::chrono::seconds(1)); // Make sure it's asynchronously saved.
  p->Stop();
  
  EXPECT_TRUE(p != NULL);
}