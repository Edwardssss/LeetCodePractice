#include <gtest/gtest.h>
#include "238-product-of-array-except-self.cpp"

static Solution solution;

TEST(ProductExceptSelfTest, Example1) {
    std::vector<int> nums = {1,2,3,4};
    std::vector<int> expected = {24,12,8,6};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, ContainsZero) {
    std::vector<int> nums = {0,1,2,3};
    std::vector<int> expected = {6,0,0,0};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, AllOnes) {
    std::vector<int> nums = {1,1,1,1};
    std::vector<int> expected = {1,1,1,1};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, NegativeNumbers) {
    std::vector<int> nums = {-1,2,-3,4};
    std::vector<int> expected = {-24,12,-8,6};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, SingleElement) {
    std::vector<int> nums = {5};
    std::vector<int> expected = {1};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}