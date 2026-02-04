#include <gtest/gtest.h>
#include "739-daily-temperatures.cpp"
#include <vector>

TEST(DailyTemperaturesTest, Example1) {
	Solution sol;
	std::vector<int> temperatures = {73,74,75,71,69,72,76,73};
	std::vector<int> expected = {1,1,4,2,1,1,0,0};
	EXPECT_EQ(sol.dailyTemperatures(temperatures), expected);
}

TEST(DailyTemperaturesTest, AllIncreasing) {
	Solution sol;
	std::vector<int> temperatures = {60,61,62,63};
	std::vector<int> expected = {1,1,1,0};
	EXPECT_EQ(sol.dailyTemperatures(temperatures), expected);
}

TEST(DailyTemperaturesTest, AllDecreasing) {
	Solution sol;
	std::vector<int> temperatures = {80,79,78,77};
	std::vector<int> expected = {0,0,0,0};
	EXPECT_EQ(sol.dailyTemperatures(temperatures), expected);
}

TEST(DailyTemperaturesTest, AllSame) {
	Solution sol;
	std::vector<int> temperatures = {70,70,70,70};
	std::vector<int> expected = {0,0,0,0};
	EXPECT_EQ(sol.dailyTemperatures(temperatures), expected);
}

TEST(DailyTemperaturesTest, SingleElement) {
	Solution sol;
	std::vector<int> temperatures = {100};
	std::vector<int> expected = {0};
	EXPECT_EQ(sol.dailyTemperatures(temperatures), expected);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
