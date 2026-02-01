#include <gtest/gtest.h>
#include "496-next-greater-element-i.cpp"
#include <vector>

TEST(NextGreaterElementTest, Example1) {
    Solution sol;
    std::vector<int> nums1 = {4,1,2};
    std::vector<int> nums2 = {1,3,4,2};
    std::vector<int> expected = {-1,3,-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, Example2) {
    Solution sol;
    std::vector<int> nums1 = {2,4};
    std::vector<int> nums2 = {1,2,3,4};
    std::vector<int> expected = {3,-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, AllNoGreater) {
    Solution sol;
    std::vector<int> nums1 = {5,6};
    std::vector<int> nums2 = {6,5,4,3,2,1};
    std::vector<int> expected = {-1,-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, AllGreater) {
    Solution sol;
    std::vector<int> nums1 = {1,2,3};
    std::vector<int> nums2 = {1,2,3,4};
    std::vector<int> expected = {2,3,4};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, SingleElement) {
    Solution sol;
    std::vector<int> nums1 = {1};
    std::vector<int> nums2 = {1};
    std::vector<int> expected = {-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
