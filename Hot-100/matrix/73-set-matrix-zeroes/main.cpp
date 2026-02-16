#include <gtest/gtest.h>
#include "73-set-matrix-zeroes.cpp"
#include <vector>

static Solution solution;

void expectMatrixEq(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(SetMatrixZeroesTest, Example1) {
    std::vector<std::vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
    std::vector<std::vector<int>> expected = {{1,0,1},{0,0,0},{1,0,1}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, Example2) {
    std::vector<std::vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    std::vector<std::vector<int>> expected = {{0,0,0,0},{0,4,5,0},{0,3,1,0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, NoZero) {
    std::vector<std::vector<int>> matrix = {{1,2},{3,4}};
    std::vector<std::vector<int>> expected = {{1,2},{3,4}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, AllZero) {
    std::vector<std::vector<int>> matrix = {{0,0},{0,0}};
    std::vector<std::vector<int>> expected = {{0,0},{0,0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, SingleRow) {
    std::vector<std::vector<int>> matrix = {{1,0,3}};
    std::vector<std::vector<int>> expected = {{0,0,0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, SingleCol) {
    std::vector<std::vector<int>> matrix = {{1},{0},{3}};
    std::vector<std::vector<int>> expected = {{0},{0},{0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}