#include <gtest/gtest.h>
#include <Storages/Redis/RedisStorage.h>

using namespace Storages::Redis;

// Demonstrate some basic assertions.
TEST(RedisStorage_Contructor_Test, BasicAssertions) {
  IStorage *p = new RedisStorage();
  // "tcp://127.0.0.1:6379"
  EXPECT_TRUE(p != NULL);
}