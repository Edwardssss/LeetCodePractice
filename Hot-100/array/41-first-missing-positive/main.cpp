#include <gtest/gtest.h>
#include "41-first-missing-positive.cpp"

static Solution solution;

TEST(FirstMissingPositiveTest, Example1) {
    std::vector<int> nums = {1,2,0};
    EXPECT_EQ(solution.firstMissingPositive(nums), 3);
}

TEST(FirstMissingPositiveTest, Example2) {
    std::vector<int> nums = {3,4,-1,1};
    EXPECT_EQ(solution.firstMissingPositive(nums), 2);
}

TEST(FirstMissingPositiveTest, Example3) {
    std::vector<int> nums = {7,8,9,11,12};
    EXPECT_EQ(solution.firstMissingPositive(nums), 1);
}

TEST(FirstMissingPositiveTest, AllNegative) {
    std::vector<int> nums = {-1,-2,-3};
    EXPECT_EQ(solution.firstMissingPositive(nums), 1);
}

TEST(FirstMissingPositiveTest, ContinuousPositive) {
    std::vector<int> nums = {1,2,3,4,5};
    EXPECT_EQ(solution.firstMissingPositive(nums), 6);
}

TEST(FirstMissingPositiveTest, Unordered) {
    std::vector<int> nums = {2,1};
    EXPECT_EQ(solution.firstMissingPositive(nums), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}