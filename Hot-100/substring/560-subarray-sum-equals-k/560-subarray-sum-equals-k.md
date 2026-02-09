# 560. 和为 K 的子数组

## 题目描述

560. 和为 K 的子数组

给你一个整数数组 `nums` 和一个整数 `k` ，请你统计并返回 该数组中和为 `k` 的子数组的个数。

子数组是数组中元素的连续非空序列。

示例 1：

>  **输入**
>
> nums = [1,1,1], k = 2
>
>  **输出**
>
> 2

示例 2：

>  **输入**
>
> nums = [1,2,3], k = 3
>
>  **输出**
>
> 2

提示：

- `1 <= nums.length <= 2 * 104`
- `-1000 <= nums[i] <= 1000`
- `-107 <= k <= 107`

## 思路分析

本道题我最开始想到的是滑动窗口，但是后面发现数组内的值可以是负数。这就代表了窗口内的值的变化并不一定是单调的，所以我就没思路了。最后想到的是双重for循环暴力搜索，仍然是没有想到官方答案。官方使用的是前缀和 + 哈希表。

官方题解代码实现如下：

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x:nums) {
            pre += x;
            if (mp.find(pre - k) != mp.end()) {
                count += mp[pre - k];
            }
            mp[pre]++;
        }
        return count;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int result_cnt = 0;
        for (int start = 0; start < n; ++start) {
            int sum = 0;
            for (int end = start; end < n; ++end) {
                sum += nums[end];
                if (sum == k) {
                    ++result_cnt;
                }
            }
        }
        return result_cnt;
    }
};
```

## 复杂度分析

- 暴力法
    - 时间复杂度：$O(n^2)$，外层循环 $O(n)$，内层循环 $O(n)$，总共 $O(n^2)$。
    - 空间复杂度：$O(1)$，只用常数级别的辅助变量。

- 前缀和 + 哈希表
    - 时间复杂度：$O(n)$，只需遍历一遍数组，每次哈希表操作均为常数时间。
    - 空间复杂度：$O(n)$，哈希表最多存储 $n$ 个不同的前缀和。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "560-subarray-sum-equals-k.cpp"
#include <vector>

static Solution solution;

TEST(SubarraySumTest, Example1) {
    std::vector<int> nums{1,1,1};
    int k = 2;
    EXPECT_EQ(solution.subarraySum(nums, k), 2);
}

TEST(SubarraySumTest, Example2) {
    std::vector<int> nums{1,2,3};
    int k = 3;
    EXPECT_EQ(solution.subarraySum(nums, k), 2);
}

TEST(SubarraySumTest, NegativeNumbers) {
    std::vector<int> nums{1,-1,0};
    int k = 0;
    EXPECT_EQ(solution.subarraySum(nums, k), 3);
}

TEST(SubarraySumTest, SingleElement) {
    std::vector<int> nums{5};
    int k = 5;
    EXPECT_EQ(solution.subarraySum(nums, k), 1);
}

TEST(SubarraySumTest, NoSolution) {
    std::vector<int> nums{1,2,3};
    int k = 7;
    EXPECT_EQ(solution.subarraySum(nums, k), 0);
}

TEST(SubarraySumTest, AllZero) {
    std::vector<int> nums{0,0,0,0};
    int k = 0;
    EXPECT_EQ(solution.subarraySum(nums, k), 10);
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
[----------] 6 tests from SubarraySumTest
[ RUN      ] SubarraySumTest.Example1
[       OK ] SubarraySumTest.Example1 (0 ms)       
[ RUN      ] SubarraySumTest.Example2
[       OK ] SubarraySumTest.Example2 (0 ms)       
[ RUN      ] SubarraySumTest.NegativeNumbers       
[       OK ] SubarraySumTest.NegativeNumbers (0 ms)
[ RUN      ] SubarraySumTest.SingleElement
[       OK ] SubarraySumTest.SingleElement (0 ms)  
[ RUN      ] SubarraySumTest.NoSolution
[       OK ] SubarraySumTest.NoSolution (0 ms)
[ RUN      ] SubarraySumTest.AllZero
[       OK ] SubarraySumTest.AllZero (0 ms)
[----------] 6 tests from SubarraySumTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 6 tests.
```