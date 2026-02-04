#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "15-3sum.cpp"

static std::vector<std::vector<int>> Normalize(std::vector<std::vector<int>> result) {
    for (auto &triplet : result) {
        std::sort(triplet.begin(), triplet.end());
    }
    std::sort(result.begin(), result.end());
    return result;
}

TEST(ThreeSumTest, Example1) {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    Solution solution;
    auto result = Normalize(solution.threeSum(nums));
    std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
    expected = Normalize(expected);
    EXPECT_EQ(result, expected);
}

TEST(ThreeSumTest, Example2) {
    std::vector<int> nums = {0, 1, 1};
    Solution solution;
    auto result = Normalize(solution.threeSum(nums));
    std::vector<std::vector<int>> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(ThreeSumTest, Example3) {
    std::vector<int> nums = {0, 0, 0};
    Solution solution;
    auto result = Normalize(solution.threeSum(nums));
    std::vector<std::vector<int>> expected = {{0, 0, 0}};
    expected = Normalize(expected);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
