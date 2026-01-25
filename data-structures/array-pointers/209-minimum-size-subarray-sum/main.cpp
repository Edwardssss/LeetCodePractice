#include <gtest/gtest.h>
#include "209-minimum-size-subarray-sum.cpp"

static Solution solution;

TEST(MinSubArrayLenTest, Example1) {
    std::vector<int> nums{2,3,1,2,4,3};
    int target = 7;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 2);
}

TEST(MinSubArrayLenTest, Example2) {
    std::vector<int> nums{1,4,4};
    int target = 4;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 1);
}

TEST(MinSubArrayLenTest, Example3) {
    std::vector<int> nums{1,1,1,1,1,1,1,1};
    int target = 11;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 0);
}

TEST(MinSubArrayLenTest, SingleElement) {
    std::vector<int> nums{10};
    int target = 10;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 1);
}

TEST(MinSubArrayLenTest, NoSolution) {
    std::vector<int> nums{1,2,3};
    int target = 7;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(MinSubArrayLenTest, AdditionalTest) {
    std::vector<int> nums{12,28,83,4,25,26,25,2,25,25,25,12};
    int target = 213;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 8);
}
