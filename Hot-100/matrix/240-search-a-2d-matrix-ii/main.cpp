#include <gtest/gtest.h>
#include "240-search-a-2d-matrix-ii.cpp"
#include <vector>

static Solution solution;

TEST(SearchMatrixIITest, Example1) {
    std::vector<std::vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    EXPECT_TRUE(solution.searchMatrix(matrix, 5));
    EXPECT_FALSE(solution.searchMatrix(matrix, 20));
}

TEST(SearchMatrixIITest, SingleRow) {
    std::vector<std::vector<int>> matrix = {{1, 2, 3, 4, 5}};
    EXPECT_TRUE(solution.searchMatrix(matrix, 3));
    EXPECT_FALSE(solution.searchMatrix(matrix, 6));
}

TEST(SearchMatrixIITest, SingleCol) {
    std::vector<std::vector<int>> matrix = {{1}, {2}, {3}, {4}, {5}};
    EXPECT_TRUE(solution.searchMatrix(matrix, 4));
    EXPECT_FALSE(solution.searchMatrix(matrix, 0));
}

TEST(SearchMatrixIITest, Empty) {
    std::vector<std::vector<int>> matrix = {};
    EXPECT_FALSE(solution.searchMatrix(matrix, 1));
}

TEST(SearchMatrixIITest, OneElement) {
    std::vector<std::vector<int>> matrix = {{7}};
    EXPECT_TRUE(solution.searchMatrix(matrix, 7));
    EXPECT_FALSE(solution.searchMatrix(matrix, 8));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}