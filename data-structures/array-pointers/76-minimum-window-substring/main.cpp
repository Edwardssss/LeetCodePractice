#include <gtest/gtest.h>
#include "76-minimum-window-substring.cpp"

static Solution solution;

TEST(MinWindowTest, Example1) {
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";
    EXPECT_EQ(solution.minWindow(s, t), "BANC");
}

TEST(MinWindowTest, Example2) {
    std::string s = "a";
    std::string t = "a";
    EXPECT_EQ(solution.minWindow(s, t), "a");
}

TEST(MinWindowTest, Example3) {
    std::string s = "a";
    std::string t = "aa";
    EXPECT_EQ(solution.minWindow(s, t), "");
}

TEST(MinWindowTest, NoMatch) {
    std::string s = "abcdefg";
    std::string t = "xyz";
    EXPECT_EQ(solution.minWindow(s, t), "");
}

TEST(MinWindowTest, AllMatch) {
    std::string s = "abc";
    std::string t = "abc";
    EXPECT_EQ(solution.minWindow(s, t), "abc");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
