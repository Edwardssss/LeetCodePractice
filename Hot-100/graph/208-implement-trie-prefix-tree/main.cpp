#include <gtest/gtest.h>
#include "208-implement-trie-prefix-tree.cpp"

static Trie trie;

TEST(TrieTest, InsertApple) {
    trie.insert("apple");
    SUCCEED();
}

TEST(TrieTest, SearchApple) {
    EXPECT_TRUE(trie.search("apple"));
}

TEST(TrieTest, SearchApp) {
    EXPECT_FALSE(trie.search("app"));
}

TEST(TrieTest, StartsWithApp) {
    EXPECT_TRUE(trie.startsWith("app"));
}

TEST(TrieTest, InsertApp) {
    trie.insert("app");
    SUCCEED();
}

TEST(TrieTest, SearchAppAfterInsert) {
    EXPECT_TRUE(trie.search("app"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
