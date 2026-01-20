#include <gtest/gtest.h>
#include "211-design-add-and-search-words-data-structure.cpp"

static WordDictionary dict;

TEST(WordDictionaryTest, AddBad) {
    dict.addWord("bad");
    SUCCEED();
}

TEST(WordDictionaryTest, AddDad) {
    dict.addWord("dad");
    SUCCEED();
}

TEST(WordDictionaryTest, AddMad) {
    dict.addWord("mad");
    SUCCEED();
}

TEST(WordDictionaryTest, SearchPad) {
    EXPECT_FALSE(dict.search("pad"));
}

TEST(WordDictionaryTest, SearchBad) {
    EXPECT_TRUE(dict.search("bad"));
}

TEST(WordDictionaryTest, SearchDotAd) {
    EXPECT_TRUE(dict.search(".ad"));
}

TEST(WordDictionaryTest, SearchBDotDot) {
    EXPECT_TRUE(dict.search("b.."));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
