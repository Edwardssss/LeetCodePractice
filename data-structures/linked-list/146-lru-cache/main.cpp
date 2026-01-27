#include <gtest/gtest.h>
#include "146-lru-cache.cpp"

TEST(LRUCacheTest, BasicPutGet) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    EXPECT_EQ(cache.get(1), 1);
    cache.put(3, 3);
    EXPECT_EQ(cache.get(2), -1);
    cache.put(4, 4);
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(3), 3);
    EXPECT_EQ(cache.get(4), 4);
}

TEST(LRUCacheTest, OverwriteValue) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), 10);
}

TEST(LRUCacheTest, CapacityOne) {
    LRUCache cache(1);
    cache.put(1, 1);
    EXPECT_EQ(cache.get(1), 1);
    cache.put(2, 2);
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 2);
}

TEST(LRUCacheTest, GetNonExist) {
    LRUCache cache(2);
    EXPECT_EQ(cache.get(100), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
