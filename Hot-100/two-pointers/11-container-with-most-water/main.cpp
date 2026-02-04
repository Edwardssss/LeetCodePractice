#include <gtest/gtest.h>
#include "11-container-with-most-water.cpp"

static Solution solution;

TEST(MaxAreaTest, Example1) {
    std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    EXPECT_EQ(solution.maxArea(height), 49);
}

TEST(MaxAreaTest, Example2) {
    std::vector<int> height{1, 1};
    EXPECT_EQ(solution.maxArea(height), 1);
}

TEST(MaxAreaTest, Increasing) {
    std::vector<int> height{1, 2, 3, 4, 5};
    EXPECT_EQ(solution.maxArea(height), 6);
}

TEST(MaxAreaTest, Decreasing) {
    std::vector<int> height{5, 4, 3, 2, 1};
    EXPECT_EQ(solution.maxArea(height), 6);
}

TEST(MaxAreaTest, WithZeros) {
    std::vector<int> height{0, 2, 0, 4, 0, 3};
    EXPECT_EQ(solution.maxArea(height), 8);
}

TEST(MaxAreaTest, TwoBars) {
    std::vector<int> height{2, 3};
    EXPECT_EQ(solution.maxArea(height), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
