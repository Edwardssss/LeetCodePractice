# 20. Valid Parentheses

## 题目描述

20. 有效的括号

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：

- 左括号必须用相同类型的右括号闭合。
- 左括号必须以正确的顺序闭合。
- 每个右括号都有一个对应的相同类型的左括号。

示例 1：

>  **输入**
>
> s = "()"
>
>  **输出**
>
> true

示例 2：

>  **输入**
>
> s = "()[]{}"
>
>  **输出**
>
> true

示例 3：

>  **输入**
>
> s = "(]"
>
>  **输出**
>
> false

示例 4：

>  **输入**
>
> s = "([])"
>
>  **输出**：
>
> true

示例 5：

>  **输入**
>
> s = "([)]"
>
>  **输出**
>
> false

提示：

- `1 <= s.length <= 104`
- `s` 仅由括号 `'()[]{}'` 组成

## 思路分析

这道题就是一个括号匹配的问题，我们很容易想到：在最里面的括号需要先进行匹配，外面的括号可以最后匹配。这就是一个很典型的LIFO数据结构，所以我们很容易想到用栈来实现这个算法。

我的结果是对的，但是我觉得还是有必要借鉴一下LeetCode官方题解的写法，我的那种写法很容易造出屎山。

```c++
class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n % 2 == 1) {
            return false;
        }

        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        stack<char> stk;
        for (char ch: s) {
            if (pairs.count(ch)) {
                if (stk.empty() || stk.top() != pairs[ch]) {
                    return false;
                }
                stk.pop();
            }
            else {
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> string_stack;
        if(s.size() <= 1) return false;
        for(auto i:s){
            if((i == '(') || (i == '[') || (i == '{')){
                string_stack.push(i);
            }
            else {
                if(string_stack.empty()) return false;
                switch (string_stack.top()) {
                    case '(':if(i == ')') break;else return false;
                    case '[':if(i == ']') break;else return false;
                    case '{':if(i == '}') break;else return false;
                    default: return false;
                }
                string_stack.pop();
            }
        }
        if(string_stack.empty()) return true;else return false;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "20-valid-parentheses.cpp"
#include <string>

TEST(ValidParenthesesTest, Example1) {
    Solution sol;
    EXPECT_TRUE(sol.isValid("()"));
}

TEST(ValidParenthesesTest, Example2) {
    Solution sol;
    EXPECT_TRUE(sol.isValid("()[]{}"));
}

TEST(ValidParenthesesTest, Example3) {
    Solution sol;
    EXPECT_FALSE(sol.isValid("(]"));
}

TEST(ValidParenthesesTest, Example4) {
    Solution sol;
    EXPECT_FALSE(sol.isValid("([)]"));
}

TEST(ValidParenthesesTest, Example5) {
    Solution sol;
    EXPECT_TRUE(sol.isValid("{[]}"));
}

TEST(ValidParenthesesTest, OnlyOpen) {
    Solution sol;
    EXPECT_FALSE(sol.isValid("((({{{"));
}

TEST(ValidParenthesesTest, OnlyClose) {
    Solution sol;
    EXPECT_FALSE(sol.isValid(")]]}}"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[----------] Global test environment set-up.
[----------] 7 tests from ValidParenthesesTest
[ RUN      ] ValidParenthesesTest.Example1
[       OK ] ValidParenthesesTest.Example1 (0 ms)
[ RUN      ] ValidParenthesesTest.Example2
[       OK ] ValidParenthesesTest.Example2 (0 ms)
[ RUN      ] ValidParenthesesTest.Example3
[       OK ] ValidParenthesesTest.Example3 (0 ms)
[ RUN      ] ValidParenthesesTest.Example4
[       OK ] ValidParenthesesTest.Example4 (0 ms)
[ RUN      ] ValidParenthesesTest.Example5
[       OK ] ValidParenthesesTest.Example5 (0 ms)
[ RUN      ] ValidParenthesesTest.OnlyOpen
[       OK ] ValidParenthesesTest.OnlyOpen (0 ms)
[ RUN      ] ValidParenthesesTest.OnlyClose
[       OK ] ValidParenthesesTest.OnlyClose (0 ms)
[----------] 7 tests from ValidParenthesesTest (0 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 7 tests.
```