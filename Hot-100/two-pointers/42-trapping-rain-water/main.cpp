#include <gtest/gtest.h>
#include "42-trapping-rain-water.cpp"
#include <vector>

TEST(TrappingRainWaterTest, Example1) {
    Solution sol;
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ(sol.trap(height), 6);
}

TEST(TrappingRainWaterTest, Example2) {
    Solution sol;
    std::vector<int> height = {4,2,0,3,2,5};
    EXPECT_EQ(sol.trap(height), 9);
}

TEST(TrappingRainWaterTest, AllZero) {
    Solution sol;
    std::vector<int> height = {0,0,0,0};
    EXPECT_EQ(sol.trap(height), 0);
}

TEST(TrappingRainWaterTest, NoTrap) {
    Solution sol;
    std::vector<int> height = {1,2,3,4,5};
    EXPECT_EQ(sol.trap(height), 0);
}

TEST(TrappingRainWaterTest, SingleBar) {
    Solution sol;
    std::vector<int> height = {7};
    EXPECT_EQ(sol.trap(height), 0);
}

TEST(TrappingRainWaterTest, Empty) {
    Solution sol;
    std::vector<int> height = {};
    EXPECT_EQ(sol.trap(height), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
