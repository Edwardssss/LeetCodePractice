# 3. Longest Substring Without Repeating Characters

## 题目描述

3. 无重复字符的最长子串

给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

示例 1:

>  **输入**
>
> s = "abcabcbb"
>
>  **输出**
>
> 3
>
>  **解释**
>
> 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。

示例 2:

>  **输入**
>
> s = "bbbbb"
>
>  **输出**
>
> 1
>
>  **解释**
>
> 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:

>  **输入**
>
> s = "pwwkew"
>
>  **输出**
>
> 3
>
>  **解释**
>
> 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
>
> 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


提示：

- `0 <= s.length <= 5 * 104`
- `s` 由英文字母、数字、符号和空格组成

## 思路分析

这道题是双指针的滑动窗口。基本思想就是满足条件时，进行贪心扩张；不满足条件时就收缩窗口直到满足条件。但是由于我的代码水平稀烂，所以我写的方法看上去惨不忍睹（虽然是对的）。相比于官方题解，我的解法的好处是可能用的空间会更少？（因为我的解法是直接遍历，官方解法是使用哈希表来空间换时间）

LeetCode官方解法如下所示：
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 哈希集合，记录每个字符是否出现过
        unordered_set<char> occ;
        int n = s.size();
        // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
        int rk = -1, ans = 0;
        // 枚举左指针的位置，初始值隐性地表示为 -1
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                // 左指针向右移动一格，移除一个字符
                occ.erase(s[i - 1]);
            }
            while (rk + 1 < n && !occ.count(s[rk + 1])) {
                // 不断地移动右指针
                occ.insert(s[rk + 1]);
                ++rk;
            }
            // 第 i 到 rk 个字符是一个极长的无重复字符子串
            ans = max(ans, rk - i + 1);
        }
        return ans;
    }
};
```

## 代码实现

代码实现如下：
```c++
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0){
            return 0;
        }
        else if(s.length() == 1){
            return 1;
        }
        int window_length = 1;
        int begin = 0,end = 1;
        bool enlarge_window_flag;
        bool exit_flag = false;
        while(end != s.length()){
            enlarge_window_flag = true;
            for (int i = begin; i < end; ++i) {
                if(s[end] == s[i]){
                    ++begin;
                    exit_flag = false; // 重置
                    while (!exit_flag) {
                        exit_flag = true;
                        for (int j = begin; j < end; ++j) {
                            if(s[end] == s[j]){
                                begin++;
                                exit_flag = false;
                                break;
                            }
                        }
                    }
                    ++end;
                    window_length = max(window_length, end - begin); // 补更新
                    enlarge_window_flag = false;
                    break;
                }
            }
            if(enlarge_window_flag){
                ++end;
                window_length = max(window_length,end - begin);
            }
        }
        return window_length;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(n^2)$，最坏情况下每次移动窗口都需要遍历窗口内的所有字符
- 空间复杂度：$O(1)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "3-longest-substring-without-repeating-characters.cpp"

static Solution solution;

TEST(LongestSubstringTest, Example1) {
    std::string s = "abcabcbb";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 3);
}

TEST(LongestSubstringTest, Example2) {
    std::string s = "bbbbb";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 1);
}

TEST(LongestSubstringTest, Example3) {
    std::string s = "pwwkew";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 3);
}

TEST(LongestSubstringTest, EmptyString) {
    std::string s = "";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 0);
}

TEST(LongestSubstringTest, AllUnique) {
    std::string s = "abcdefg";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 7);
}

TEST(LongestSubstringTest, SingleChar) {
    std::string s = "a";
    EXPECT_EQ(solution.lengthOfLongestSubstring(s), 1);
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
[----------] 6 tests from LongestSubstringTest      
[ RUN      ] LongestSubstringTest.Example1
[       OK ] LongestSubstringTest.Example1 (0 ms)   
[ RUN      ] LongestSubstringTest.Example2
[       OK ] LongestSubstringTest.Example2 (0 ms)   
[ RUN      ] LongestSubstringTest.Example3
[       OK ] LongestSubstringTest.Example3 (0 ms)   
[ RUN      ] LongestSubstringTest.EmptyString       
[       OK ] LongestSubstringTest.EmptyString (0 ms)
[ RUN      ] LongestSubstringTest.AllUnique
[       OK ] LongestSubstringTest.AllUnique (0 ms)
[ RUN      ] LongestSubstringTest.SingleChar
[       OK ] LongestSubstringTest.SingleChar (0 ms)
[----------] 6 tests from LongestSubstringTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 6 tests.
```
