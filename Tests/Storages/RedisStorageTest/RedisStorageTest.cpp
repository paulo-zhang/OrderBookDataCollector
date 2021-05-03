#include <thread>
#include <chrono>
#include <gtest/gtest.h>
#include <Storages/Redis/RedisStorage.h>

using namespace Storages::Redis;

// Demonstrate some basic assertions.
TEST(RedisStorage_SaveOrderBook_Test, BasicAssertions) {
  IStorage *p = new RedisStorage();

  // "tcp://127.0.0.1:6379"
  p->Start("tcp://127.0.0.1:63790,password=");
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