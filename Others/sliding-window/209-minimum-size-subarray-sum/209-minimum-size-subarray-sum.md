# 209. Minimum Size Subarray Sum

## 题目描述

209. 长度最小的子数组

给定一个含有 `n` 个正整数的数组和一个正整数 `target` 。

找出该数组中满足其总和大于等于 `target` 的长度最小的 子数组 `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

示例 1：

>  **输入**
>
> target = 7, nums = [2,3,1,2,4,3]
>
>  **输出**
>
> 2
>
>  **解释**
>
> 子数组 [4,3] 是该条件下的长度最小的子数组。

示例 2：

>  **输入**
>
> target = 4, nums = [1,4,4]
>
>  **输出**
>
> 1

示例 3：

>  **输入**
>
> target = 11, nums = [1,1,1,1,1,1,1,1]
>
>  **输出**
>
> 0

提示：

- `1 <= target <= 109`
- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 104`

进阶：

如果你已经实现 $O(n)$ 时间复杂度的解法, 请尝试设计一个 $O(n log(n))$ 时间复杂度的解法。

> 怎么是反向优化？这个错误有点绷不住

## 思路分析

LeetCode官方给出了三种解法：暴力法、前缀和 + 二分查找法和滑动窗口法。我就是使用的双指针的滑动窗口法，当窗口满足条件就缩短，不满足就拉长，最后找到最小的窗口。

## 代码实现

代码实现如下：
```c++
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int min_len = 10e5;
        int left = 0, sum = 0;
        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                min_len = min(min_len, right - left + 1);
                sum -= nums[left++];
            }
        }
        return min_len == 10e5 ? 0 : min_len;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(n)$
- 空间复杂度：$O(1)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "209-minimum-size-subarray-sum.cpp"

static Solution solution;

TEST(MinSubArrayLenTest, Example1) {
    std::vector<int> nums{2,3,1,2,4,3};
    int target = 7;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 2);
}

TEST(MinSubArrayLenTest, Example2) {
    std::vector<int> nums{1,4,4};
    int target = 4;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 1);
}

TEST(MinSubArrayLenTest, Example3) {
    std::vector<int> nums{1,1,1,1,1,1,1,1};
    int target = 11;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 0);
}

TEST(MinSubArrayLenTest, SingleElement) {
    std::vector<int> nums{10};
    int target = 10;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 1);
}

TEST(MinSubArrayLenTest, NoSolution) {
    std::vector<int> nums{1,2,3};
    int target = 7;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(MinSubArrayLenTest, AdditionalTest) {
    std::vector<int> nums{12,28,83,4,25,26,25,2,25,25,25,12};
    int target = 213;
    EXPECT_EQ(solution.minSubArrayLen(target, nums), 8);
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from MinSubArrayLenTest
[ RUN      ] MinSubArrayLenTest.Example1
[       OK ] MinSubArrayLenTest.Example1 (0 ms)
[ RUN      ] MinSubArrayLenTest.Example2
[       OK ] MinSubArrayLenTest.Example2 (0 ms)
[ RUN      ] MinSubArrayLenTest.Example3
[       OK ] MinSubArrayLenTest.Example3 (0 ms)
[ RUN      ] MinSubArrayLenTest.SingleElement
```