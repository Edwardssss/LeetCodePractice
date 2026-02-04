#include <gtest/gtest.h>
#include "189-rotate-array.cpp"

TEST(RotateArrayTest, Example1) {
    std::vector<int> nums = {1,2,3,4,5,6,7};
    Solution solution;
    solution.rotate(nums, 3);
    EXPECT_EQ(nums, (std::vector<int>{5,6,7,1,2,3,4}));
}

TEST(RotateArrayTest, Example2) {
    std::vector<int> nums = {-1,-100,3,99};
    Solution solution;
    solution.rotate(nums, 2);
    EXPECT_EQ(nums, (std::vector<int>{3,99,-1,-100}));
}

TEST(RotateArrayTest, KZero) {
    std::vector<int> nums = {1,2,3};
    Solution solution;
    solution.rotate(nums, 0);
    EXPECT_EQ(nums, (std::vector<int>{1,2,3}));
}

TEST(RotateArrayTest, KEqualToSize) {
    std::vector<int> nums = {1,2,3};
    Solution solution;
    solution.rotate(nums, 3);
    EXPECT_EQ(nums, (std::vector<int>{1,2,3}));
}

TEST(RotateArrayTest, KGreaterThanSize) {
    std::vector<int> nums = {1,2,3};
    Solution solution;
    solution.rotate(nums, 4);
    EXPECT_EQ(nums, (std::vector<int>{3,1,2}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
