#include <gtest/gtest.h>
#include "167-two-sum-ii-input-array-is-sorted.cpp"

static Solution solution;

TEST(TwoSumIITest, Example1) {
    std::vector<int> numbers{2, 7, 11, 15};
    int target = 9;
    std::vector<int> expected{1, 2};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, Example2) {
    std::vector<int> numbers{2, 3, 4};
    int target = 6;
    std::vector<int> expected{1, 3};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, Example3) {
    std::vector<int> numbers{-1, 0};
    int target = -1;
    std::vector<int> expected{1, 2};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, NoSolution) {
    std::vector<int> numbers{1, 2, 3, 4, 5};
    int target = 10;
    std::vector<int> expected{};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, DuplicateNumbers) {
    std::vector<int> numbers{1, 2, 2, 3, 4};
    int target = 4;
    std::vector<int> expected{1, 4};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}