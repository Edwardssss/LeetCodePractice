#include <gtest/gtest.h>
#include "54-spiral-matrix.cpp"
#include <vector>

static Solution solution;

TEST(SpiralMatrixTest, Example1) {
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    std::vector<int> expected = {1,2,3,6,9,8,7,4,5};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, Example2) {
    std::vector<std::vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    std::vector<int> expected = {1,2,3,4,8,12,11,10,9,5,6,7};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, SingleRow) {
    std::vector<std::vector<int>> matrix = {{1,2,3,4}};
    std::vector<int> expected = {1,2,3,4};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, SingleCol) {
    std::vector<std::vector<int>> matrix = {{1},{2},{3},{4}};
    std::vector<int> expected = {1,2,3,4};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, Empty) {
    std::vector<std::vector<int>> matrix = {};
    std::vector<int> expected = {};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}