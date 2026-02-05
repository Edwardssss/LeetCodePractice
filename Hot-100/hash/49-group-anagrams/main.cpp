#include <gtest/gtest.h>
#include "49-group-anagrams.cpp"

static Solution solution;

void sortInner(std::vector<std::vector<std::string>>& v) {
    for (auto& group : v) {
        std::sort(group.begin(), group.end());
    }
    std::sort(v.begin(), v.end());
}

TEST(GroupAnagramsTest, Example1) {
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<std::vector<std::string>> expected = {
        {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}
    };
    auto result = solution.groupAnagrams(strs);
    sortInner(result);
    sortInner(expected);
    EXPECT_EQ(result, expected);
}

TEST(GroupAnagramsTest, Example2) {
    std::vector<std::string> strs = {""};
    std::vector<std::vector<std::string>> expected = {{""}};
    auto result = solution.groupAnagrams(strs);
    sortInner(result);
    sortInner(expected);
    EXPECT_EQ(result, expected);
}

TEST(GroupAnagramsTest, Example3) {
    std::vector<std::string> strs = {"a"};
    std::vector<std::vector<std::string>> expected = {{"a"}};
    auto result = solution.groupAnagrams(strs);
    sortInner(result);
    sortInner(expected);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
