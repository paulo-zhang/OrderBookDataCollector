#include <gtest/gtest.h>
#include <Storages/MongoDB/MongoDBStorage.h>

using namespace Storages::MongoDB;

// Demonstrate some basic assertions.
TEST(MongoDBStorage_Contructor_Test, BasicAssertions) {
  IStorage* p = new MongoDBStorage();

  EXPECT_TRUE(p != NULL);
}