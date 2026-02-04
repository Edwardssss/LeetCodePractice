#include <gtest/gtest.h>
#include "20-valid-parentheses.cpp"
#include <string>

TEST(ValidParenthesesTest, Example1) {
    Solution sol;
    EXPECT_TRUE(sol.isValid("()"));
}

TEST(ValidParenthesesTest, Example2) {
    Solution sol;
    EXPECT_TRUE(sol.isValid("()[]{}"));
}

TEST(ValidParenthesesTest, Example3) {
    Solution sol;
    EXPECT_FALSE(sol.isValid("(]"));
}

TEST(ValidParenthesesTest, Example4) {
    Solution sol;
    EXPECT_FALSE(sol.isValid("([)]"));
}

TEST(ValidParenthesesTest, Example5) {
    Solution sol;
    EXPECT_TRUE(sol.isValid("{[]}"));
}

TEST(ValidParenthesesTest, OnlyOpen) {
    Solution sol;
    EXPECT_FALSE(sol.isValid("((({{{"));
}

TEST(ValidParenthesesTest, OnlyClose) {
    Solution sol;
    EXPECT_FALSE(sol.isValid(")]]}}"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
