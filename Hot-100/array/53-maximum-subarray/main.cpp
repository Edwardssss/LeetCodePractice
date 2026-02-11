#include <gtest/gtest.h>
#include "53-maximum-subarray.cpp"

static Solution solution;

TEST(MaxSubArrayTest, Example1) {
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    EXPECT_EQ(solution.maxSubArray(nums), 6);
}

TEST(MaxSubArrayTest, Example2) {
    std::vector<int> nums = {1};
    EXPECT_EQ(solution.maxSubArray(nums), 1);
}

TEST(MaxSubArrayTest, Example3) {
    std::vector<int> nums = {5, 4, -1, 7, 8};
    EXPECT_EQ(solution.maxSubArray(nums), 23);
}

TEST(MaxSubArrayTest, AllNegative) {
    std::vector<int> nums = {-3, -1, -2};
    EXPECT_EQ(solution.maxSubArray(nums), -1);
}

TEST(MaxSubArrayTest, SingleNegative) {
    std::vector<int> nums = {-7};
    EXPECT_EQ(solution.maxSubArray(nums), -7);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}