#include <gtest/gtest.h>
#include "136-single-number.cpp"
#include <vector>

static Solution solution;

TEST(SingleNumberTest, Example1) {
    std::vector<int> nums{2, 2, 1};
    EXPECT_EQ(solution.singleNumber(nums), 1);
}

TEST(SingleNumberTest, Example2) {
    std::vector<int> nums{4, 1, 2, 1, 2};
    EXPECT_EQ(solution.singleNumber(nums), 4);
}

TEST(SingleNumberTest, NegativeNumbers) {
    std::vector<int> nums{-1, -1, -2};
    EXPECT_EQ(solution.singleNumber(nums), -2);
}

TEST(SingleNumberTest, SingleElement) {
    std::vector<int> nums{99};
    EXPECT_EQ(solution.singleNumber(nums), 99);
}

TEST(SingleNumberTest, LargeNumbers) {
    std::vector<int> nums{100000, 100000, 123456};
    EXPECT_EQ(solution.singleNumber(nums), 123456);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
