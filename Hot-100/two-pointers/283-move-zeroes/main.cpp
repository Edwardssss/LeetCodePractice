#include <gtest/gtest.h>
#include "283-move-zeroes.cpp"
#include <vector>

static Solution solution;

TEST(MoveZeroesTest, Example1) {
    std::vector<int> nums{0,1,0,3,12};
    std::vector<int> expected{1,3,12,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, Example2) {
    std::vector<int> nums{0,0,1};
    std::vector<int> expected{1,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, AllZero) {
    std::vector<int> nums{0,0,0,0};
    std::vector<int> expected{0,0,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, NoZero) {
    std::vector<int> nums{1,2,3,4};
    std::vector<int> expected{1,2,3,4};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, SingleZero) {
    std::vector<int> nums{0};
    std::vector<int> expected{0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, SingleNonZero) {
    std::vector<int> nums{5};
    std::vector<int> expected{5};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, ZerosAtEnd) {
    std::vector<int> nums{1,2,3,0,0};
    std::vector<int> expected{1,2,3,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}