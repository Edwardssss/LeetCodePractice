#include <gtest/gtest.h>
#include "31-next-permutation.cpp"
#include <vector>

TEST(NextPermutationTest, Example1) {
    Solution sol;
    std::vector<int> nums = {1,2,3};
    std::vector<int> expected = {1,3,2};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, Example2) {
    Solution sol;
    std::vector<int> nums = {3,2,1};
    std::vector<int> expected = {1,2,3};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, Example3) {
    Solution sol;
    std::vector<int> nums = {1,1,5};
    std::vector<int> expected = {1,5,1};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, SingleElement) {
    Solution sol;
    std::vector<int> nums = {1};
    std::vector<int> expected = {1};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, TwoElements) {
    Solution sol;
    std::vector<int> nums = {1,2};
    std::vector<int> expected = {2,1};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}