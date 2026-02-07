#include <gtest/gtest.h>
#include "128-longest-consecutive-sequence.cpp"

static Solution solution;

TEST(LongestConsecutiveTest, Example1) {
    std::vector<int> nums{100, 4, 200, 1, 3, 2};
    EXPECT_EQ(solution.longestConsecutive(nums), 4);
}

TEST(LongestConsecutiveTest, Example2) {
    std::vector<int> nums{0,3,7,2,5,8,4,6,0,1};
    EXPECT_EQ(solution.longestConsecutive(nums), 9);
}

TEST(LongestConsecutiveTest, Empty) {
    std::vector<int> nums{};
    EXPECT_EQ(solution.longestConsecutive(nums), 0);
}

TEST(LongestConsecutiveTest, Single) {
    std::vector<int> nums{42};
    EXPECT_EQ(solution.longestConsecutive(nums), 1);
}

TEST(LongestConsecutiveTest, Duplicates) {
    std::vector<int> nums{1,2,0,1};
    EXPECT_EQ(solution.longestConsecutive(nums), 3);
}

TEST(LongestConsecutiveTest, NoConsecutive) {
    std::vector<int> nums{10, 30, 20};
    EXPECT_EQ(solution.longestConsecutive(nums), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
