#include <gtest/gtest.h>
#include "287-find-the-duplicate-number.cpp"
#include <vector>

TEST(FindDuplicateTest, Example1) {
    Solution sol;
    std::vector<int> nums = {1,3,4,2,2};
    EXPECT_EQ(sol.findDuplicate(nums), 2);
}

TEST(FindDuplicateTest, Example2) {
    Solution sol;
    std::vector<int> nums = {3,1,3,4,2};
    EXPECT_EQ(sol.findDuplicate(nums), 3);
}

TEST(FindDuplicateTest, DuplicateAtStart) {
    Solution sol;
    std::vector<int> nums = {2,2,2,2,2};
    EXPECT_EQ(sol.findDuplicate(nums), 2);
}

TEST(FindDuplicateTest, DuplicateAtEnd) {
    Solution sol;
    std::vector<int> nums = {1,4,6,2,5,3,6};
    EXPECT_EQ(sol.findDuplicate(nums), 6);
}

TEST(FindDuplicateTest, LargeCase) {
    Solution sol;
    std::vector<int> nums(10001);
    for (int i = 0; i < 10000; ++i) nums[i] = i+1;
    nums[10000] = 9999;
    EXPECT_EQ(sol.findDuplicate(nums), 9999);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
