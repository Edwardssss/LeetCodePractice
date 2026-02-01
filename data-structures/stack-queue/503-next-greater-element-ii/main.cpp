#include <gtest/gtest.h>
#include "503-next-greater-element-ii.cpp"
#include <vector>

TEST(NextGreaterElementsTest, Example1) {
	Solution sol;
	std::vector<int> nums = {1,2,1};
	std::vector<int> expected = {2,-1,2};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, AllIncreasing) {
	Solution sol;
	std::vector<int> nums = {1,2,3,4};
	std::vector<int> expected = {2,3,4,-1};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, AllDecreasing) {
	Solution sol;
	std::vector<int> nums = {4,3,2,1};
	std::vector<int> expected = {-1,4,4,4};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, AllSame) {
	Solution sol;
	std::vector<int> nums = {5,5,5,5};
	std::vector<int> expected = {-1,-1,-1,-1};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, SingleElement) {
	Solution sol;
	std::vector<int> nums = {7};
	std::vector<int> expected = {-1};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
