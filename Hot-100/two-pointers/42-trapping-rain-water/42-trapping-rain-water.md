# 42. Trapping Rain Water

## 题目描述

42. 接雨水

给定 `n` 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

![](./1.png)

示例 1：

>  **输入**
>
> height = [0,1,0,2,1,0,1,3,2,1,2,1]
>
>  **输出**
>
> 6
>
>  **解释**
>
> 上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。

示例 2：

>  **输入**
>
> height = [4,2,0,3,2,5]
>
> **输出**
>
> 9

提示：

- `n == height.length`
- `1 <= n <= 2 * 104`
- `0 <= height[i] <= 105`

## 思路分析

本题是最经典的算法面试题：接雨水。但是很遗憾，至少这一次我没写出来。动态规划、单调栈、双指针三种方法我一种也没想出来，后面还是需要多多复盘。

代码实现里面写的是双指针法。

**方法一：动态规划法**

对于下标 $i$，下雨后水能到达的最大高度等于下标 $i$ 两边的最大高度的最小值，下标 $i$ 处能接的雨水量等于下标 $i$ 处的水能到达的最大高度减去 `height[i]`。

朴素的做法是对于数组 `height` 中的每个元素，分别向左和向右扫描并记录左边和右边的最大高度，然后计算每个下标位置能接的雨水量。假设数组 `height` 的长度为 $n$，该做法需要对每个下标位置使用 $O(n)$ 的时间向两边扫描并得到最大高度，因此总时间复杂度是 $O(n^2)$。

上述做法的时间复杂度较高是因为需要对每个下标位置都向两边扫描。如果已经知道每个位置两边的最大高度，则可以在 $O(n)$ 的时间内得到能接的雨水总量。使用动态规划的方法，可以在 $O(n)$ 的时间内预处理得到每个位置两边的最大高度。

创建两个长度为 $n$ 的数组 `leftMax` 和 `rightMax`。对于 $0≤i<n$，`leftMax[i]` 表示下标 $i$ 及其左边的位置中，`height` 的最大高度，`rightMax[i]` 表示下标 $i$ 及其右边的位置中，`height` 的最大高度。

显然，`leftMax[0]=height[0]，rightMax[n−1]=height[n−1]`。两个数组的其余元素的计算如下：

当 $1≤i≤n−1$ 时，`leftMax[i]=max(leftMax[i−1],height[i])`；

当 $0≤i≤n−2$ 时，`rightMax[i]=max(rightMax[i+1],height[i])`。

因此可以正向遍历数组 `height` 得到数组 `leftMax` 的每个元素值，反向遍历数组 `height` 得到数组 `rightMax` 的每个元素值。

在得到数组 `leftMax` 和 `rightMax` 的每个元素值之后，对于 $0≤i<n$，下标 $i$ 处能接的雨水量等于 `min(leftMax[i],rightMax[i])−height[i]`。遍历每个下标位置即可得到能接的雨水总量。

动态规划做法可以由下图体现。

![](./dynamic.png)

官方代码示例如下：

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        vector<int> leftMax(n);
        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        vector<int> rightMax(n);
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};
```

**方法二：单调栈法**

除了计算并存储每个位置两边的最大高度以外，也可以用单调栈计算能接的雨水总量。

维护一个单调栈，单调栈存储的是下标，满足从栈底到栈顶的下标对应的数组 `height` 中的元素递减。

从左到右遍历数组，遍历到下标 $i$ 时，如果栈内至少有两个元素，记栈顶元素为 `top`，`top` 的下面一个元素是 `left`，则一定有 `height[left]≥height[top]`。如果 `height[i]>height[top]`，则得到一个可以接雨水的区域，该区域的宽度是 `i−left−1`，高度是 `min(height[left],height[i])−height[top]`，根据宽度和高度即可计算得到该区域能接的雨水量。

为了得到 `left`，需要将 `top` 出栈。在对 `top` 计算能接的雨水量之后，`left` 变成新的 `top`，重复上述操作，直到栈变为空，或者栈顶下标对应的 `height` 中的元素大于或等于 `height[i]`。

在对下标 $i$ 处计算能接的雨水量之后，将 $i$ 入栈，继续遍历后面的下标，计算能接的雨水量。遍历结束之后即可得到能接的雨水总量。

官方代码如下：

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }
                int left = stk.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }
};
```

**方法三：双指针法**

动态规划的做法中，需要维护两个数组 `leftMax` 和 `rightMax`，因此空间复杂度是 $O(n)$。是否可以将空间复杂度降到 $O(1)$？

注意到下标 $i$ 处能接的雨水量由 `leftMax[i]` 和 `rightMax[i]` 中的最小值决定。由于数组 `leftMax` 是从左往右计算，数组 `rightMax` 是从右往左计算，因此可以使用双指针和两个变量代替两个数组。

维护两个指针 `left` 和 `right`，以及两个变量 `leftMax` 和 `rightMax`，初始时 `left=0`,`right=n−1`,`leftMax=0`,`rightMax=0`。指针 `left` 只会向右移动，指针 `right` 只会向左移动，在移动指针的过程中维护两个变量 `leftMax` 和 `rightMax` 的值。

当两个指针没有相遇时，进行如下操作：

使用 `height[left]` 和 `height[right]` 的值更新 `leftMax` 和 `rightMax` 的值；

如果 `height[left]<height[right]`，则必有 `leftMax<rightMax`，下标 `left` 处能接的雨水量等于 `leftMax−height[left]`，将下标 `left` 处能接的雨水量加到能接的雨水总量，然后将 `left` 加 1（即向右移动一位）；

如果 `height[left]≥height[right]`，则必有 `leftMax≥rightMax`，下标 `right` 处能接的雨水量等于 `rightMax−height[right]`，将下标 `right` 处能接的雨水量加到能接的雨水总量，然后将 `right` 减 1（即向左移动一位）。

当两个指针相遇时，即可得到能接的雨水总量。

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += leftMax - height[left];
                ++left;
            } else {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};
```

## 复杂度分析

- 动态规划

    - 时间复杂度：$O(n)$，其中 $n$ 为数组长度。需要三次遍历：两次预处理最大值，一次计算总水量。
    - 空间复杂度：$O(n)$，需要两个长度为 $n$ 的辅助数组。

- 单调栈法

    - 时间复杂度：$O(n)$，每个元素最多入栈和出栈各一次。
    - 空间复杂度：$O(n)$，栈的空间最多为 $n$。

- 双指针法

    - 时间复杂度：$O(n)$，只需一次遍历。
    - 空间复杂度：$O(1)$，只用常数级别的变量。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "42-trapping-rain-water.cpp"
#include <vector>

TEST(TrappingRainWaterTest, Example1) {
    Solution sol;
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ(sol.trap(height), 6);
}

TEST(TrappingRainWaterTest, Example2) {
    Solution sol;
    std::vector<int> height = {4,2,0,3,2,5};
    EXPECT_EQ(sol.trap(height), 9);
}

TEST(TrappingRainWaterTest, AllZero) {
    Solution sol;
    std::vector<int> height = {0,0,0,0};
    EXPECT_EQ(sol.trap(height), 0);
}

TEST(TrappingRainWaterTest, NoTrap) {
    Solution sol;
    std::vector<int> height = {1,2,3,4,5};
    EXPECT_EQ(sol.trap(height), 0);
}

TEST(TrappingRainWaterTest, SingleBar) {
    Solution sol;
    std::vector<int> height = {7};
    EXPECT_EQ(sol.trap(height), 0);
}

TEST(TrappingRainWaterTest, Empty) {
    Solution sol;
    std::vector<int> height = {};
    EXPECT_EQ(sol.trap(height), 0);
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
[----------] 6 tests from TrappingRainWaterTest
[ RUN      ] TrappingRainWaterTest.Example1
[       OK ] TrappingRainWaterTest.Example1 (0 ms)
[ RUN      ] TrappingRainWaterTest.Example2
[       OK ] TrappingRainWaterTest.Example2 (0 ms)
[ RUN      ] TrappingRainWaterTest.AllZero
[       OK ] TrappingRainWaterTest.AllZero (0 ms)
[ RUN      ] TrappingRainWaterTest.NoTrap
[       OK ] TrappingRainWaterTest.NoTrap (0 ms)
[ RUN      ] TrappingRainWaterTest.SingleBar
[       OK ] TrappingRainWaterTest.SingleBar (0 ms)
[ RUN      ] TrappingRainWaterTest.Empty
[       OK ] TrappingRainWaterTest.Empty (0 ms)
[----------] 6 tests from TrappingRainWaterTest (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 6 tests.
```