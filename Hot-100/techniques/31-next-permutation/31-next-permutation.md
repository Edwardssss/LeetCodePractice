# 31. 下一个排列

## 题目描述

31. 下一个排列

整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

例如，`arr = [1,2,3]` ，以下这些都可以视作 `arr` 的排列：`[1,2,3]`、`[1,3,2]`、`[3,1,2]`、`[2,3,1]` 。

整数数组的 **下一个排列** 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 **下一个排列** 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

例如，`arr = [1,2,3]` 的下一个排列是 `[1,3,2]` 。

类似地，`arr = [2,3,1]` 的下一个排列是 `[3,1,2]` 。

而 `arr = [3,2,1]` 的下一个排列是 `[1,2,3]` ，因为 `[3,2,1]` 不存在一个字典序更大的排列。

给你一个整数数组 `nums` ，找出 `nums` 的下一个排列。

必须 **原地** 修改，只允许使用额外常数空间。

示例 1：

>  **输入**
>
> nums = [1,2,3]
>
>  **输出**
>
> [1,3,2]

示例 2：

>  **输入**
>
> nums = [3,2,1]
>
>  **输出**
>
> [1,2,3]

示例 3：

>  **输入**
>
> nums = [1,1,5]
>
>  **输出**
>
> [1,5,1]

提示：

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 100`

## 思路分析

这道题看半天没看懂要干什么，所以没写出来。

LeetCode官方给出的题解是进行两遍扫描。

我们需要将一个左边的「较小数」与一个右边的「较大数」交换，以能够让当前排列变大，从而得到下一个排列。

同时我们要让这个「较小数」尽量靠右，而「较大数」尽可能小。当交换完成后，「较大数」右边的数需要按照升序重新排列。这样可以在保证新排列大于原来排列的情况下，使变大的幅度尽可能小。

以排列 `[4,5,2,6,3,1]` 为例：

我们能找到的符合条件的一对「较小数」与「较大数」的组合为 `2` 与 `3`，满足「较小数」尽量靠右，而「较大数」尽可能小。

当我们完成交换后排列变为 `[4,5,3,6,2,1]`，此时我们可以重排「较小数」右边的序列，序列变为 `[4,5,3,1,2,6]`。

具体地，我们这样描述该算法，对于长度为 `n` 的排列 `a`：

首先从后向前查找第一个顺序对 `(i,i+1)`，满足 `a[i]<a[i+1]`。这样「较小数」即为 `a[i]`。此时 `[i+1,n)` 必然是下降序列。

如果找到了顺序对，那么在区间 `[i+1,n)` 中从后向前查找第一个元素 `j` 满足 `a[i]<a[j]`。这样「较大数」即为 `a[j]`。

交换 `a[i]` 与 `a[j]`，此时可以证明区间 `[i+1,n)` 必为降序。我们可以直接使用双指针反转区间 `[i+1,n)` 使其变为升序，而无需对该区间进行排序。

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        if (i >= 0) {
            int j = nums.size() - 1;
            while (j >= 0 && nums[i] >= nums[j]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```

## 复杂度分析

- 时间复杂度：$O(N)$，其中 $N$ 为给定序列的长度。我们至多只需要扫描两次序列，以及进行一次反转操作。

- 空间复杂度：$O(1)$，只需要常数的空间存放若干变量。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "31-next-permutation.cpp"
#include <vector>

TEST(NextPermutationTest, Example1) {
    Solution sol;
    std::vector<int> nums = {1,2,3};
    std::vector<int> expected = {1,3,2};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, Example2) {
    Solution sol;
    std::vector<int> nums = {3,2,1};
    std::vector<int> expected = {1,2,3};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, Example3) {
    Solution sol;
    std::vector<int> nums = {1,1,5};
    std::vector<int> expected = {1,5,1};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, SingleElement) {
    Solution sol;
    std::vector<int> nums = {1};
    std::vector<int> expected = {1};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
}

TEST(NextPermutationTest, TwoElements) {
    Solution sol;
    std::vector<int> nums = {1,2};
    std::vector<int> expected = {2,1};
    sol.nextPermutation(nums);
    EXPECT_EQ(nums, expected);
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
[----------] 5 tests from NextPermutationTest
[ RUN      ] NextPermutationTest.Example1
[       OK ] NextPermutationTest.Example1 (0 ms)
[ RUN      ] NextPermutationTest.Example2
[       OK ] NextPermutationTest.Example2 (0 ms)
[ RUN      ] NextPermutationTest.Example3
[       OK ] NextPermutationTest.Example3 (0 ms)
[ RUN      ] NextPermutationTest.SingleElement
[       OK ] NextPermutationTest.SingleElement (0 ms)
[ RUN      ] NextPermutationTest.TwoElements
[       OK ] NextPermutationTest.TwoElements (0 ms)
[----------] 5 tests from NextPermutationTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```