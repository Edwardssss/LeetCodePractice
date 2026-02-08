# 438. 找到字符串中所有字母异位词

## 题目描述

438. 找到字符串中所有字母异位词

给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

示例 1:

>  **输入**
>
> s = "cbaebabacd", p = "abc"
>
>  **输出**
>
> [0,6]
>
>  **解释**
>
> 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
>
> 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。

示例 2:

>  **输入**
>
> s = "abab", p = "ab"
>
>  **输出**
>
> [0,1,2]
>
>  **解释**
>
> 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
>
> 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
>
> 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

提示:

- `1 <= s.length, p.length <= 3 * 104`
- `s` 和 `p` 仅包含小写字母

## 思路分析

本题很明显是一个滑动窗口问题。我首先想到的是定长窗口滑动，使用无序哈希表进行存储，最后喜提34ms的AC。然后我去看了下官方题解，还是需要再次学习一下的。

滑动窗口（字符计数）代码实现如下：

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};
```

官方还对滑动窗口进行了一个优化：只需要维护一个存储窗口内字符和目标字符的差异计数器即可。

滑动窗口（差异计数）代码实现如下：

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> count(26);
        for (int i = 0; i < pLen; ++i) {
            ++count[s[i] - 'a'];
            --count[p[i] - 'a'];
        }

        int differ = 0;
        for (int j = 0; j < 26; ++j) {
            if (count[j] != 0) {
                ++differ;
            }
        }

        if (differ == 0) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            if (count[s[i] - 'a'] == 1) {  // 窗口中字母 s[i] 的数量与字符串 p 中的数量从不同变得相同
                --differ;
            } else if (count[s[i] - 'a'] == 0) {  // 窗口中字母 s[i] 的数量与字符串 p 中的数量从相同变得不同
                ++differ;
            }
            --count[s[i] - 'a'];

            if (count[s[i + pLen] - 'a'] == -1) {  // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从不同变得相同
                --differ;
            } else if (count[s[i + pLen] - 'a'] == 0) {  // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从相同变得不同
                ++differ;
            }
            ++count[s[i + pLen] - 'a'];
            
            if (differ == 0) {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(s.length() < p.length()) return {};
        vector<int> result;
        unordered_map<char, int> p_char;
        unordered_map<char, int> win_char;
        int begin = 0,end = p.length() - 1;
        for (int i = 0;i < p.length();++i) {
            if(win_char.count(s[i])){
                ++win_char[s[i]];
            }
            else {
                win_char[s[i]] = 1;
            }
            if (p_char.count(p[i])) {
                ++p_char[p[i]];
            }
            else {
                p_char[p[i]] = 1;
            }
        }
        while (end < s.length()) {
            if (win_char == p_char) {
                result.push_back(begin);
            }
            ++end;
            if (end < s.length()) {
                win_char[s[end]]++;
                win_char[s[begin]]--;
                if (win_char[s[begin]] == 0) {
                    win_char.erase(s[begin]);
                }
                ++begin;
            }
        }
        return result;
    }
};
```


## 复杂度分析

- 滑动窗口（无序哈希）
    - 时间复杂度：$O((|s| - |p| + 1) \cdot |p|)$，每次窗口比较哈希表，最坏情况下每次都要遍历 $|p|$ 个字符。
    - 空间复杂度：$O(|p|)$，哈希表存储窗口和目标字符计数。

- 滑动窗口（字符计数）
    - 时间复杂度：$O(|s| + |p|)$，窗口内计数数组比较是 $O(26)$，整体为线性。
    - 空间复杂度：$O(1)$，计数数组固定大小。

- 滑动窗口（差异计数）
    - 时间复杂度：$O(|s| + |p|)$，每次窗口移动只需常数时间维护差异计数。
    - 空间复杂度：$O(1)$，计数数组固定大小。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "438-find-all-anagrams-in-a-string.cpp"
#include <vector>

static Solution solution;

TEST(FindAnagramsTest, Example1) {
    std::string s = "cbaebabacd";
    std::string p = "abc";
    std::vector<int> expected{0, 6};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, Example2) {
    std::string s = "abab";
    std::string p = "ab";
    std::vector<int> expected{0, 1, 2};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, NoAnagrams) {
    std::string s = "abcdefg";
    std::string p = "xyz";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, EmptyString) {
    std::string s = "";
    std::string p = "a";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, EmptyPattern) {
    std::string s = "abc";
    std::string p = "";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

TEST(FindAnagramsTest, PatternLongerThanString) {
    std::string s = "a";
    std::string p = "aa";
    std::vector<int> expected{};
    EXPECT_EQ(solution.findAnagrams(s, p), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：

```
[==========] Running 6 tests from 1 test suite.      
[----------] Global test environment set-up.
[----------] 6 tests from FindAnagramsTest
[ RUN      ] FindAnagramsTest.Example1
[       OK ] FindAnagramsTest.Example1 (0 ms)        
[ RUN      ] FindAnagramsTest.Example2
[       OK ] FindAnagramsTest.Example2 (0 ms)
[ RUN      ] FindAnagramsTest.NoAnagrams
[       OK ] FindAnagramsTest.NoAnagrams (0 ms)
[ RUN      ] FindAnagramsTest.EmptyString
[       OK ] FindAnagramsTest.EmptyString (0 ms)
[ RUN      ] FindAnagramsTest.EmptyPattern
[       OK ] FindAnagramsTest.EmptyPattern (0 ms)
[ RUN      ] FindAnagramsTest.PatternLongerThanString
[       OK ] FindAnagramsTest.PatternLongerThanString (0 ms)
[----------] 6 tests from FindAnagramsTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (6 ms total)
[  PASSED  ] 6 tests.
```
