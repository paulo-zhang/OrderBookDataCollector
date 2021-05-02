#include <gtest/gtest.h>
#include <Common/OrderBook.h>

using namespace Common;

// Demonstrate some basic assertions.
TEST(OrderBookTest_Deserialize_Test, BasicAssertions) {
    string str = "{\"e\":\"depthUpdate\",\"E\":1619922115877,\"s\":\"BNBBTC\",\"U\":1833997158,\"u\":1833997167,\"b\":[[\"0.01074900\",\"5.18000000\"],[\"0.01073100\",\"1.45000000\"],[\"0.01073000\",\"31.73000000\"]],\"a\":[[\"0.01075500\",\"3.20000000\"],[\"0.01075600\",\"5.23000000\"],[\"0.01075700\",\"5.20000000\"],[\"0.01075800\",\"11.78000000\"],[\"0.01077700\",\"14.97000000\"],[\"0.01077900\",\"48.48000000\"]]}";
    OrderBook orderBook;
    orderBook.Deserialize(str);

    EXPECT_EQ(orderBook.EventType, "depthUpdate");
    EXPECT_EQ(orderBook.EventTime, 1619922115877);
    EXPECT_EQ(orderBook.Symbol, "BNBBTC");
    EXPECT_EQ(orderBook.FirstId, 1833997158);
    EXPECT_EQ(orderBook.FinalId, 1833997167);

    EXPECT_EQ(orderBook.Bids.size(), 3);
    EXPECT_EQ(orderBook.Asks.size(), 6);

    EXPECT_EQ(orderBook.Bids[0].Price, "0.01074900");
    EXPECT_EQ(orderBook.Bids[0].Quantity, "5.18000000");
    EXPECT_EQ(orderBook.Bids[1].Price, "0.01073100");
    EXPECT_EQ(orderBook.Bids[1].Quantity, "1.45000000");
    EXPECT_EQ(orderBook.Bids[2].Price, "0.01073000");
    EXPECT_EQ(orderBook.Bids[2].Quantity, "31.73000000");

    EXPECT_EQ(orderBook.Asks[0].Price, "0.01075500");
    EXPECT_EQ(orderBook.Asks[0].Quantity, "3.20000000");
    EXPECT_EQ(orderBook.Asks[1].Price, "0.01075600");
    EXPECT_EQ(orderBook.Asks[1].Quantity, "5.23000000");
    EXPECT_EQ(orderBook.Asks[2].Price, "0.01075700");
    EXPECT_EQ(orderBook.Asks[2].Quantity, "5.20000000");
    EXPECT_EQ(orderBook.Asks[5].Price, "0.01077900");
    EXPECT_EQ(orderBook.Asks[5].Quantity, "48.48000000");
}

TEST(OrderBookTest_Serialize_Deserialize_Test, BasicAssertions) {
    OrderBook orderBook = {.EventType = "depthUpdate", .EventTime = 1619922115877, .Symbol = "BNBBTC", .FirstId = 1833997158, .FinalId = 1833997167};
    orderBook.Asks.push_back(Quote() = {.Price = "0.01077900", .Quantity = "5.01075500"});
    orderBook.Asks.push_back(Quote() = {.Price = "0.01075600", .Quantity = "5.23000000"});
    orderBook.Bids.push_back(Quote() = {.Price = "0.01074900", .Quantity = "5.18000000"});
    orderBook.Bids.push_back(Quote() = {.Price = "0.01075700", .Quantity = "5.20000000"});

    string str = orderBook.Serialize();
    OrderBook orderBook2;
    orderBook2.Deserialize(str);

    EXPECT_EQ(orderBook.EventType, orderBook2.EventType);
    EXPECT_EQ(orderBook.EventTime, orderBook2.EventTime);
    EXPECT_EQ(orderBook.Symbol, orderBook2.Symbol);
    EXPECT_EQ(orderBook.FirstId, orderBook2.FirstId);
    EXPECT_EQ(orderBook.FinalId, orderBook2.FinalId);

    EXPECT_EQ(orderBook.Bids.size(), orderBook2.Bids.size());
    EXPECT_EQ(orderBook.Asks.size(), orderBook2.Asks.size());

    EXPECT_EQ(orderBook.Bids[0].Price, orderBook2.Bids[0].Price);
    EXPECT_EQ(orderBook.Bids[0].Quantity, orderBook2.Bids[0].Quantity);
    EXPECT_EQ(orderBook.Bids[1].Price, orderBook.Bids[1].Price);
    EXPECT_EQ(orderBook.Bids[1].Quantity, orderBook.Bids[1].Quantity);

    EXPECT_EQ(orderBook.Asks[0].Price, orderBook2.Asks[0].Price);
    EXPECT_EQ(orderBook.Asks[0].Quantity, orderBook2.Asks[0].Quantity);
    EXPECT_EQ(orderBook.Asks[1].Price, orderBook.Asks[1].Price);
    EXPECT_EQ(orderBook.Asks[1].Quantity, orderBook.Asks[1].Quantity);
}