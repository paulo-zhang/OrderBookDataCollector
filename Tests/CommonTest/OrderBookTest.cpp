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