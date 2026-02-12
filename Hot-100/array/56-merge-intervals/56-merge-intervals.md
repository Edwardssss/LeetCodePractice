# 56. 合并区间

## 题目描述

56. 合并区间

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 **一个不重叠的区间数组**，该数组需恰好覆盖输入中的所有区间 。

示例 1：

>  **输入**
>
> intervals = [[1,3],[2,6],[8,10],[15,18]]
>
>  **输出**
>
> [[1,6],[8,10],[15,18]]
>
>  **解释**
>
> 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：

>  **输入**
>
> intervals = [[1,4],[4,5]]
>
>  **输出**
>
> [[1,5]]
>
>  **解释**
>
> 区间 [1,4] 和 [4,5] 可被视为重叠区间。

示例 3：

>  **输入**
>
> intervals = [[4,7],[1,4]]
>
>  **输出**
>
> [[1,7]]
>
>  **解释**
>
> 区间 [1,4] 和 [4,7] 可被视为重叠区间。

提示：

- `1 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 104`

## 思路分析

这道题没有想出来，看了提示还是没有想法。LeetCode官方是使用排序法做的这道题：

如果我们按照区间的左端点排序，那么在排完序的列表中，可以合并的区间一定是连续的。如下图所示，标记为蓝色、黄色和绿色的区间分别可以合并成一个大区间，它们在排完序的列表中是连续的：

![](./1.png)

我们用数组 `merged` 存储最终的答案。

首先，我们将列表中的区间按照左端点升序排序。然后我们将第一个区间加入 `merged` 数组中，并按顺序依次考虑之后的每个区间：

- 如果当前区间的左端点在数组 `merged` 中最后一个区间的右端点之后，那么它们不会重合，我们可以直接将这个区间加入数组 `merged` 的末尾；

- 否则，它们重合，我们需要用当前区间的右端点更新数组 `merged` 中最后一个区间的右端点，将其置为二者的较大值。

## 代码实现

代码实现如下：

```c++
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) {
            return {};
        }
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for (int i = 0; i < intervals.size(); ++i) {
            int L = intervals[i][0], R = intervals[i][1];
            if (!merged.size() || merged.back()[1] < L) {
                merged.push_back({L, R});
            }
            else {
                merged.back()[1] = max(merged.back()[1], R);
            }
        }
        return merged;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(n\log n)$，其中 $n$ 为区间的数量。除去排序的开销，我们只需要一次线性扫描，所以主要的时间开销是排序的 $O(n\log n)$

- 空间复杂度：$O(\log n)$，其中 $n$ 为区间的数量。这里计算的是存储答案之外，使用的额外空间。

## 测试用例

测试用例如下：

```c++
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
```

## 测试结果

测试结果如下所示：

```
[==========] Running 6 tests from 1 test suite.      
[----------] Global test environment set-up.
[----------] 6 tests from MergeIntervalsTest
[ RUN      ] MergeIntervalsTest.Example1
[       OK ] MergeIntervalsTest.Example1 (0 ms)      
[ RUN      ] MergeIntervalsTest.Example2
[       OK ] MergeIntervalsTest.Example2 (0 ms)      
[ RUN      ] MergeIntervalsTest.NoMergeNeeded        
[       OK ] MergeIntervalsTest.NoMergeNeeded (0 ms) 
[ RUN      ] MergeIntervalsTest.AllOverlap
[       OK ] MergeIntervalsTest.AllOverlap (0 ms)    
[ RUN      ] MergeIntervalsTest.SingleInterval       
[       OK ] MergeIntervalsTest.SingleInterval (0 ms)
[ RUN      ] MergeIntervalsTest.Empty
[       OK ] MergeIntervalsTest.Empty (0 ms)
[----------] 6 tests from MergeIntervalsTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (5 ms total)
[  PASSED  ] 6 tests.
```