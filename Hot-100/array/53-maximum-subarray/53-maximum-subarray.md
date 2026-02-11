# 53. 最大子数组和

## 题目描述

53. 最大子数组和

给你一个整数数组 `nums` ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组是数组中的一个连续部分。


示例 1：

>  **输入**
>
> nums = [-2,1,-3,4,-1,2,1,-5,4]
>
>  **输出**
>
> 6
>
>  **解释**
>
> 连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2：

>  **输入**
>
> nums = [1]
>
>  **输出**
>
> 1

示例 3：

>  **输入**
>
> nums = [5,4,-1,7,8]
>
>  **输出**
>
> 23

提示：

- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

进阶：如果你已经实现复杂度为 $O(n)$ 的解法，尝试使用更为精妙的 `分治法` 求解。

## 思路分析

这道题我一看就想到前缀和了，然后很快就写出来了。但是官方提示的分治法我没想出来，不过我联想到了之前某道题的按$k$个一组，然后分组计算前缀和的方法，然而答案和这个没啥关系。

官方有以下两种方法：

**动态规划**

动态规划其实是Kadane 算法。

假设 $nums$ 数组的长度是 $n$，下标从 $0$ 到 $n−1$。

我们用 $f(i)$ 代表以第 $i$ 个数结尾的「连续子数组的最大和」，那么很显然我们要求的答案就是：

$$\max_{0≤i≤n−1}​\{f(i)\}$$

因此我们只需要求出每个位置的 $f(i)$，然后返回 $f$ 数组中的最大值即可。那么我们如何求 $f(i)$ 呢？我们可以考虑 $nums[i]$ 单独成为一段还是加入 $f(i−1)$ 对应的那一段，这取决于 $nums[i]$ 和 $f(i−1)+nums[i]$ 的大小，我们希望获得一个比较大的，于是可以写出这样的动态规划转移方程：

$$f(i)=\max\{f(i−1)+nums[i],nums[i]\}$$

不难给出一个时间复杂度 $O(n)$、空间复杂度 $O(n)$ 的实现，即用一个 $f$ 数组来保存 $f(i)$ 的值，用一个循环求出所有 $f(i)$。考虑到 $f(i)$ 只和 $f(i−1)$ 相关，于是我们可以只用一个变量 $pre$ 来维护对于当前 $f(i)$的 $f(i−1)$ 的值是多少，从而让空间复杂度降低到 $O(1)$，这有点类似「滚动数组」的思想。

官方代码实现如下：

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
```

**分治**

这个分治方法类似于「线段树求解最长公共上升子序列问题」的 `pushUp` 操作。 也许读者还没有接触过线段树，没有关系，方法二的内容假设你没有任何线段树的基础。当然，如果读者有兴趣的话，推荐阅读线段树区间合并法解决多次询问的「区间最长连续上升序列问题」和「区间最大子段和问题」，还是非常有趣的。

我们定义一个操作 `get(a, l, r)` 表示查询 $a$ 序列 $[l,r]$ 区间内的最大子段和，那么最终我们要求的答案就是 `get(nums, 0, nums.size() - 1)`。如何分治实现这个操作呢？对于一个区间 $[l,r]$，我们取 $m=⌊\frac{l+r}{2}⌋$，对区间 $[l,m]$ 和 $[m+1,r]$ 分治求解。当递归逐层深入直到区间长度缩小为 $1$ 的时候，递归「开始回升」。这个时候我们考虑如何通过 $[l,m]$ 区间的信息和 $[m+1,r]$ 区间的信息合并成区间 $[l,r]$ 的信息。最关键的两个问题是：

- 我们要维护区间的哪些信息呢？
- 我们如何合并这些信息呢？

对于一个区间 $[l,r]$，我们可以维护四个量：

- $lSum$ 表示 $[l,r]$ 内以 $l$ 为左端点的最大子段和
- $rSum$ 表示 $[l,r]$ 内以 $r$ 为右端点的最大子段和
- $mSum$ 表示 $[l,r]$ 内的最大子段和
- $iSum$ 表示 $[l,r]$ 的区间和

以下简称 $[l,m]$ 为 $[l,r]$ 的「左子区间」，$[m+1,r]$ 为 $[l,r]$ 的「右子区间」。我们考虑如何维护这些量呢（如何通过左右子区间的信息合并得到 $[l,r]$ 的信息）？对于长度为 $1$ 的区间 $[i,i]$，四个量的值都和 $nums[i]$ 相等。对于长度大于 $1$ 的区间：

- 首先最好维护的是 $iSum$，区间 $[l,r]$ 的 $iSum$ 就等于「左子区间」的 $iSum$ 加上「右子区间」的 $iSum$。

- 对于 $[l,r]$ 的 $lSum$，存在两种可能，它要么等于「左子区间」的 $lSum$，要么等于「左子区间」的 $iSum$ 加上「右子区间」的 $lSum$，二者取大。

- 对于 $[l,r]$ 的 $rSum$，同理，它要么等于「右子区间」的 $rSum$，要么等于「右子区间」的 $iSum$ 加上「左子区间」的 $rSum$，二者取大。

- 当计算好上面的三个量之后，就很好计算 $[l,r]$ 的 $mSum$ 了。我们可以考虑 $[l,r]$ 的 $mSum$ 对应的区间是否跨越 $m$——它可能不跨越 $m$，也就是说 $[l,r]$ 的 $mSum$ 可能是「左子区间」的 $mSum$ 和 「右子区间」的 $mSum$ 中的一个；它也可能跨越 $m$，可能是「左子区间」的 $rSum$ 和 「右子区间」的 $lSum$ 求和。三者取大。

## 代码实现

代码实现如下：

```c++
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int maxSum = nums[0];
        int minSum = 0;
        int currentSum = 0;
        for (int num : nums) {
            currentSum += num;
            maxSum = max(maxSum, currentSum - minSum);
            minSum = min(minSum, currentSum);
        }
        return maxSum;
    }
};
```

## 复杂度分析

- 前缀和

    - 时间复杂度：$O(n)$。只需一次遍历即可完成前缀和及最大子数组和的计算。
    - 空间复杂度：$O(1)$（只用变量记录当前和和最小前缀和），或$O(n)$（如果存储所有前缀和）。

- 动态规划（Kadane 算法）

    - 时间复杂度：$O(n)$。每个元素只遍历一次。
    - 空间复杂度：$O(1)$。只需两个变量记录当前最大和和当前dp值。

- 分治

    - 时间复杂度：$O(n)$。每次递归合并区间，整体复杂度为线性。
    - 空间复杂度：$O(\log n)$。递归栈深度为$\log n$，每次只存储常量级信息。

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "53-maximum-subarray.cpp"

static Solution solution;

TEST(MaxSubArrayTest, Example1) {
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    EXPECT_EQ(solution.maxSubArray(nums), 6);
}

TEST(MaxSubArrayTest, Example2) {
    std::vector<int> nums = {1};
    EXPECT_EQ(solution.maxSubArray(nums), 1);
}

TEST(MaxSubArrayTest, Example3) {
    std::vector<int> nums = {5, 4, -1, 7, 8};
    EXPECT_EQ(solution.maxSubArray(nums), 23);
}

TEST(MaxSubArrayTest, AllNegative) {
    std::vector<int> nums = {-3, -1, -2};
    EXPECT_EQ(solution.maxSubArray(nums), -1);
}

TEST(MaxSubArrayTest, SingleNegative) {
    std::vector<int> nums = {-7};
    EXPECT_EQ(solution.maxSubArray(nums), -7);
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
[----------] 5 tests from MaxSubArrayTest
[ RUN      ] MaxSubArrayTest.Example1
[       OK ] MaxSubArrayTest.Example1 (0 ms)
[ RUN      ] MaxSubArrayTest.Example2
[       OK ] MaxSubArrayTest.Example2 (0 ms)
[ RUN      ] MaxSubArrayTest.Example3
[       OK ] MaxSubArrayTest.Example3 (0 ms)
[ RUN      ] MaxSubArrayTest.AllNegative
[       OK ] MaxSubArrayTest.AllNegative (0 ms)
[ RUN      ] MaxSubArrayTest.SingleNegative
[       OK ] MaxSubArrayTest.SingleNegative (0 ms)
[----------] 5 tests from MaxSubArrayTest (2 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 5 tests.
```