#include <gtest/gtest.h>
#include "560-subarray-sum-equals-k.cpp"
#include <vector>

static Solution solution;

TEST(SubarraySumTest, Example1) {
    std::vector<int> nums{1,1,1};
    int k = 2;
    EXPECT_EQ(solution.subarraySum(nums, k), 2);
}

TEST(SubarraySumTest, Example2) {
    std::vector<int> nums{1,2,3};
    int k = 3;
    EXPECT_EQ(solution.subarraySum(nums, k), 2);
}

TEST(SubarraySumTest, NegativeNumbers) {
    std::vector<int> nums{1,-1,0};
    int k = 0;
    EXPECT_EQ(solution.subarraySum(nums, k), 3);
}

TEST(SubarraySumTest, SingleElement) {
    std::vector<int> nums{5};
    int k = 5;
    EXPECT_EQ(solution.subarraySum(nums, k), 1);
}

TEST(SubarraySumTest, NoSolution) {
    std::vector<int> nums{1,2,3};
    int k = 7;
    EXPECT_EQ(solution.subarraySum(nums, k), 0);
}

TEST(SubarraySumTest, AllZero) {
    std::vector<int> nums{0,0,0,0};
    int k = 0;
    EXPECT_EQ(solution.subarraySum(nums, k), 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}