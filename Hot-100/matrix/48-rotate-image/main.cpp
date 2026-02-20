#include <gtest/gtest.h>
#include "48-rotate-image.cpp"
#include <vector>

static Solution solution;

void assertMatrixEq(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        ASSERT_EQ(a[i], b[i]);
    }
}

TEST(RotateImageTest, Example1) {
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    std::vector<std::vector<int>> expected = {{7,4,1},{8,5,2},{9,6,3}};
    solution.rotate(matrix);
    assertMatrixEq(matrix, expected);
}

TEST(RotateImageTest, Example2) {
    std::vector<std::vector<int>> matrix = {{1,2},{3,4}};
    std::vector<std::vector<int>> expected = {{3,1},{4,2}};
    solution.rotate(matrix);
    assertMatrixEq(matrix, expected);
}

TEST(RotateImageTest, SingleRowCol) {
    std::vector<std::vector<int>> matrix = {{1}};
    std::vector<std::vector<int>> expected = {{1}};
    solution.rotate(matrix);
    assertMatrixEq(matrix, expected);
}

TEST(RotateImageTest, FourByFour) {
    std::vector<std::vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    std::vector<std::vector<int>> expected = {{13,9,5,1},{14,10,6,2},{15,11,7,3},{16,12,8,4}};
    solution.rotate(matrix);
    assertMatrixEq(matrix, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}