#include <gtest/gtest.h>
#include "3-longest-substring-without-repeating-characters.cpp"

static Solution solution;

TEST(LongestSubstringTest, Example1) {
    std::string s = "abcabcbb";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 3);
}

TEST(LongestSubstringTest, Example2) {
    std::string s = "bbbbb";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 1);
}

TEST(LongestSubstringTest, Example3) {
    std::string s = "pwwkew";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 3);
}

TEST(LongestSubstringTest, EmptyString) {
    std::string s = "";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 0);
}

TEST(LongestSubstringTest, AllUnique) {
    std::string s = "abcdefg";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 7);
}

TEST(LongestSubstringTest, SingleChar) {
    std::string s = "a";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
