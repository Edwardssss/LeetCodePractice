#include <gtest/gtest.h>
#include "56-merge-intervals.cpp"

static Solution solution;

TEST(MergeIntervalsTest, Example1) {
    std::vector<std::vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    std::vector<std::vector<int>> expected = {{1,6},{8,10},{15,18}};
    EXPECT_EQ(solution.merge(intervals), expected);
}

TEST(MergeIntervalsTest, Example2) {
    std::vector<std::vector<int>> intervals = {{1,4},{4,5}};
    std::vector<std::vector<int>> expected = {{1,5}};
    EXPECT_EQ(solution.merge(intervals), expected);
}

TEST(MergeIntervalsTest, NoMergeNeeded) {
    std::vector<std::vector<int>> intervals = {{1,2},{3,4},{5,6}};
    std::vector<std::vector<int>> expected = {{1,2},{3,4},{5,6}};
    EXPECT_EQ(solution.merge(intervals), expected);
}

TEST(MergeIntervalsTest, AllOverlap) {
    std::vector<std::vector<int>> intervals = {{1,10},{2,6},{3,5},{7,9}};
    std::vector<std::vector<int>> expected = {{1,10}};
    EXPECT_EQ(solution.merge(intervals), expected);
}

TEST(MergeIntervalsTest, SingleInterval) {
    std::vector<std::vector<int>> intervals = {{1,2}};
    std::vector<std::vector<int>> expected = {{1,2}};
    EXPECT_EQ(solution.merge(intervals), expected);
}

TEST(MergeIntervalsTest, Empty) {
    std::vector<std::vector<int>> intervals = {};
    std::vector<std::vector<int>> expected = {};
    EXPECT_EQ(solution.merge(intervals), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}