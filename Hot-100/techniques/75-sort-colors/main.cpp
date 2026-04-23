#include <gtest/gtest.h>
#include "75-sort-colors.cpp"
#include <vector>

TEST(SortColorsTest, Example1) {
    Solution sol;
    std::vector<int> nums = {2,0,2,1,1,0};
    std::vector<int> expected = {0,0,1,1,2,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, Example2) {
    Solution sol;
    std::vector<int> nums = {2,0,1};
    std::vector<int> expected = {0,1,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, AllZeros) {
    Solution sol;
    std::vector<int> nums = {0,0,0};
    std::vector<int> expected = {0,0,0};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, AllOnes) {
    Solution sol;
    std::vector<int> nums = {1,1,1};
    std::vector<int> expected = {1,1,1};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, AllTwos) {
    Solution sol;
    std::vector<int> nums = {2,2,2};
    std::vector<int> expected = {2,2,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, Mixed) {
    Solution sol;
    std::vector<int> nums = {1,2,0,2,1,0,1,2,0};
    std::vector<int> expected = {0,0,0,1,1,1,2,2,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, SingleElement) {
    Solution sol;
    std::vector<int> nums = {1};
    std::vector<int> expected = {1};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, TwoElements) {
    Solution sol;
    std::vector<int> nums = {2,0};
    std::vector<int> expected = {0,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
