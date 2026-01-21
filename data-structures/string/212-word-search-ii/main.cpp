#include <algorithm>
#include <gtest/gtest.h>
#include "212-word-search-ii.cpp"

static Solution solution;

TEST(WordSearchIITest, Example1) {
    std::vector<std::vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    std::vector<std::string> words = {"oath","pea","eat","rain"};
    std::vector<std::string> expected = {"oath","eat"};
    auto result = solution.findWords(board, words);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(result, expected);
}

TEST(WordSearchIITest, Example2) {
    std::vector<std::vector<char>> board = {
        {'a','b'},
        {'c','d'}
    };
    std::vector<std::string> words = {"abcb"};
    std::vector<std::string> expected = {};
    auto result = solution.findWords(board, words);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
