#include <gtest/gtest.h>
#include "1-two-sum.cpp"

static Solution solution;

TEST(TwoSumTest, Example1) {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> expected = {0, 1};
    auto result = solution.twoSum(nums, target);
    EXPECT_EQ(result, expected);
}

TEST(TwoSumTest, Example2) {
    std::vector<int> nums = {3, 2, 4};
    int target = 6;
    std::vector<int> expected = {1, 2};
    auto result = solution.twoSum(nums, target);
    EXPECT_EQ(result, expected);
}

TEST(TwoSumTest, Example3) {
    std::vector<int> nums = {3, 3};
    int target = 6;
    std::vector<int> expected = {0, 1};
    auto result = solution.twoSum(nums, target);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}