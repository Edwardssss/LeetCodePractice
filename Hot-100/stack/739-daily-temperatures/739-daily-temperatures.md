# 739. Daily Temperatures

## 题目描述

739. 每日温度

给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。

示例 1:

>  **输入**
>
> temperatures = [73,74,75,71,69,72,76,73]
>
>  **输出**
>
> [1,1,4,2,1,1,0,0]

示例 2:

>  **输入**
>
> temperatures = [30,40,50,60]
>
>  **输出**
>
> [1,1,1,0]

示例 3:

>  **输入**
>
> temperatures = [30,60,90]
>
>  **输出**
>
> [1,1,0]

提示：

- `1 <= temperatures.length <= 105`
- `30 <= temperatures[i] <= 100`

## 思路分析

这道题也是非常经典的单调栈问题，就维护一个从栈顶到栈底的单调递增栈即可，存储温度的下标。不过我写的时候还是不熟练，后面需要再次复习一下。

## 代码实现

代码实现如下：

```c++
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        stack<int> st;
        for (int i = 0; i < temperatures.size(); ++i) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int idx = st.top();
                st.pop();
                result[idx] = i - idx;
            }
            st.push(i);
        }
        return result;
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
```

## 测试结果

测试结果如下所示：
```
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from DailyTemperaturesTest
[ RUN      ] DailyTemperaturesTest.Example1
[       OK ] DailyTemperaturesTest.Example1 (0 ms)
[ RUN      ] DailyTemperaturesTest.AllIncreasing
[       OK ] DailyTemperaturesTest.AllIncreasing (0 ms)
[ RUN      ] DailyTemperaturesTest.AllDecreasing
[       OK ] DailyTemperaturesTest.AllDecreasing (0 ms)
[ RUN      ] DailyTemperaturesTest.AllSame
[       OK ] DailyTemperaturesTest.AllSame (0 ms)
[ RUN      ] DailyTemperaturesTest.SingleElement
[       OK ] DailyTemperaturesTest.SingleElement (0 ms)
[----------] 5 tests from DailyTemperaturesTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```
