# 76. Minimum Window Substring

## 题目描述

76. 最小覆盖子串

给定两个字符串 s 和 t，长度分别是 m 和 n，返回 s 中的 最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。如果没有这样的子串，返回空字符串 ""。

测试用例保证答案唯一。

示例 1：

>  **输入**
>
> s = "ADOBECODEBANC", t = "ABC"
>
>  **输出**
>
> "BANC"
>
>  **解释**
>
> 最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。

示例 2：

>  **输入**
>
> s = "a", t = "a"
>
>  **输出**
>
> "a"
>
>  **解释**
>
> 整个字符串 s 是最小覆盖子串。

示例 3:

>  **输入**
>
> s = "a", t = "aa"
>
>  **输出**
>
> ""
>
>  **解释**
>
> t 中两个字符 'a' 均应包含在 s 的子串中，因此没有符合条件的子字符串，返回空字符串。

提示：

- `m == s.length`
- `n == t.length`
- `1 <= m, n <= 105`
- `s 和 t 由英文字母组成`

进阶：你能设计一个在 $O(m + n)$ 时间内解决此问题的算法吗？

## 思路分析

这道题是很典型的滑动窗口，虽然我很快想到了是滑动窗口法，但是我写代码写了一堆bug，卡了很久，还是太菜了。

## 代码实现

代码实现如下：
```c++
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.size() < t.size()) return "";
        map<char, int> need;
        for (char c : t) need[c]++;
        int required = need.size();
        int formed = 0;
        map<char, int> window;
        int left = 0, right = 0;
        int min_len = s.size() + 1, min_left = 0;
        while (right < s.size()) {
            char c = s[right];
            window[c]++;
            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }
            while (left <= right && formed == required) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    min_left = left;
                }
                char d = s[left];
                window[d]--;
                if (need.count(d) && window[d] < need[d]) {
                    formed--;
                }
                left++;
            }
            right++;
        }
        return min_len > s.size() ? "" : s.substr(min_left, min_len);
    }
};
```

## 复杂度分析

- 时间复杂度：$O(m + n)$
- 空间复杂度：$O(1)$，空间消耗在哈希表上了，是常数级空间

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "76-minimum-window-substring.cpp"

static Solution solution;

TEST(MinWindowTest, Example1) {
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";
    EXPECT_EQ(solution.minWindow(s, t), "BANC");
}

TEST(MinWindowTest, Example2) {
    std::string s = "a";
    std::string t = "a";
    EXPECT_EQ(solution.minWindow(s, t), "a");
}

TEST(MinWindowTest, Example3) {
    std::string s = "a";
    std::string t = "aa";
    EXPECT_EQ(solution.minWindow(s, t), "");
}

TEST(MinWindowTest, NoMatch) {
    std::string s = "abcdefg";
    std::string t = "xyz";
    EXPECT_EQ(solution.minWindow(s, t), "");
}

TEST(MinWindowTest, AllMatch) {
    std::string s = "abc";
    std::string t = "abc";
    EXPECT_EQ(solution.minWindow(s, t), "abc");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from MinWindowTest
[ RUN      ] MinWindowTest.Example1
[       OK ] MinWindowTest.Example1 (0 ms)
[ RUN      ] MinWindowTest.Example2
[       OK ] MinWindowTest.Example2 (0 ms)
[ RUN      ] MinWindowTest.Example3
[       OK ] MinWindowTest.Example3 (0 ms)
[ RUN      ] MinWindowTest.NoMatch
[       OK ] MinWindowTest.NoMatch (0 ms)
[ RUN      ] MinWindowTest.AllMatch
[       OK ] MinWindowTest.AllMatch (0 ms)
[----------] 5 tests from MinWindowTest (1 ms total)    

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 5 tests.
```