#include <gtest/gtest.h>
#include "438-find-all-anagrams-in-a-string.cpp"
#include <vector>

static Solution solution;

TEST(FindAnagramsTest, Example1) {
    std::string s = "cbaebabacd";
    std::string p = "abc";
    std::vector<int> expected{0, 6};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, Example2) {
    std::string s = "abab";
    std::string p = "ab";
    std::vector<int> expected{0, 1, 2};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, NoAnagrams) {
    std::string s = "abcdefg";
    std::string p = "xyz";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, EmptyString) {
    std::string s = "";
    std::string p = "a";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, EmptyPattern) {
    std::string s = "abc";
    std::string p = "";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, PatternLongerThanString) {
    std::string s = "a";
    std::string p = "aa";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}