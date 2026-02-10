#include <gtest/gtest.h>
#include "239-sliding-window-maximum.cpp"

static Solution solution;

TEST(MaxSlidingWindowTest, Example1) {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    std::vector<int> expected = {3, 3, 5, 5, 6, 7};
    EXPECT_EQ(solution.maxSlidingWindow(nums, k), expected);
}

TEST(MaxSlidingWindowTest, Example2) {
    std::vector<int> nums = {1};
    int k = 1;
    std::vector<int> expected = {1};
    EXPECT_EQ(solution.maxSlidingWindow(nums, k), expected);
}

TEST(MaxSlidingWindowTest, AllSame) {
    std::vector<int> nums = {4, 4, 4, 4, 4, 4};
    int k = 4;
    std::vector<int> expected = {4, 4, 4};
    EXPECT_EQ(solution.maxSlidingWindow(nums, k), expected);
}

TEST(MaxSlidingWindowTest, NegativeNumbers) {
    std::vector<int> nums = {-7, -8, -9, -1, -2, -3};
    int k = 2;
    std::vector<int> expected = {-7, -8, -1, -1, -2};
    EXPECT_EQ(solution.maxSlidingWindow(nums, k), expected);
}

TEST(MaxSlidingWindowTest, Empty) {
    std::vector<int> nums = {};
    int k = 1;
    std::vector<int> expected = {};
    EXPECT_EQ(solution.maxSlidingWindow(nums, k), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
