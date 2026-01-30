# 287. Find the Duplicate Number

## 题目描述

287. 寻找重复数

给定一个包含 `n + 1` 个整数的数组 `nums` ，其数字都在 `[1, n]` 范围内（包括 `1` 和 `n`），可知至少存在一个重复的整数。

假设 `nums` 只有一个重复的整数 ，返回这个重复的数 。

你设计的解决方案必须 **不修改** 数组 `nums` 且只用常量级 $O(1)$ 的额外空间。

示例 1：

>  **输入**
>
> nums = [1,3,4,2,2]
>
>  **输出**
>
> 2

示例 2：

>  **输入**
>
> nums = [3,1,3,4,2]
>
>  **输出**
>
> 3

示例 3 :

>  **输入**
>
> nums = [3,3,3,3,3]
>
>  **输出**
>
> 3

提示：

- `1 <= n <= 105`
- `nums.length == n + 1`
- `1 <= nums[i] <= n`
- `nums` 中 **只有一个整数** 出现 **两次或多次** ，其余整数均只出现 **一次**

进阶：

- 如何证明 `nums` 中至少存在一个重复的数字?
- 你可以设计一个线性级时间复杂度 $O(n)$ 的解决方案吗？

## 思路分析

这道题只知道是抽屉原理，但是想不到怎么写，看的官方题解的。

第一种方法是二分查找：我们定义 `cnt[i]` 表示 `nums` 数组中小于等于 `i` 的数有多少个，假设我们重复的数是 `target`，那么 `[1,target−1]`里的所有数满足 `cnt[i]≤i`，`[target,n]` 里的所有数满足 `cnt[i]>i`，具有单调性。

代码实现如下所示：

```c++
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 1, r = n - 1, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                cnt += nums[i] <= mid;
            }
            if (cnt <= mid) {
                l = mid + 1;
            } else {
                r = mid - 1;
                ans = mid;
            }
        }
        return ans;
    }
};
```

方法二是将所有的值都转换为二进制，然后通过比较不同位的个数来推断重复数字的值。

代码实现如下所示：

```c++
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        // 确定二进制下最高位是多少
        int bit_max = 31;
        while (!((n - 1) >> bit_max)) {
            bit_max -= 1;
        }
        for (int bit = 0; bit <= bit_max; ++bit) {
            int x = 0, y = 0;
            for (int i = 0; i < n; ++i) {
                if (nums[i] & (1 << bit)) {
                    x += 1;
                }
                if (i >= 1 && (i & (1 << bit))) {
                    y += 1;
                }
            }
            if (x > y) {
                ans |= 1 << bit;
            }
        }
        return ans;
    }
};
```

方法三为快慢指针，我们对 `nums` 数组建图，每个位置 `i` 连一条 `i→nums[i]` 的边。由于存在的重复的数字 `target`，因此 `target` 这个位置一定有起码两条指向它的边，因此整张图一定存在环，且我们要找到的 `target` 就是这个环的入口，那么整个问题就等价于142题。

我们先设置慢指针 `slow` 和快指针 `fast` ，慢指针每次走一步，快指针每次走两步，根据「Floyd 判圈算法」两个指针在有环的情况下一定会相遇，此时我们再将 `slow` 放置起点 0，两个指针每次同时移动一步，相遇的点就是答案。

## 代码实现

代码实现如下：
```c++
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
```

## 复杂度分析

- 二分查找法

    - 时间复杂度：$O(n\log n)$
    - 空间复杂度：$O(1)$

- 位运算法

    - 时间复杂度：$O(n\log n)$
    - 空间复杂度：$O(1)$

- 快慢指针法

    - 时间复杂度：$O(n)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "287-find-the-duplicate-number.cpp"
#include <vector>

TEST(FindDuplicateTest, Example1) {
    Solution sol;
    std::vector<int> nums = {1,3,4,2,2};
    EXPECT_EQ(sol.findDuplicate(nums), 2);
}

TEST(FindDuplicateTest, Example2) {
    Solution sol;
    std::vector<int> nums = {3,1,3,4,2};
    EXPECT_EQ(sol.findDuplicate(nums), 3);
}

TEST(FindDuplicateTest, DuplicateAtStart) {
    Solution sol;
    std::vector<int> nums = {2,2,2,2,2};
    EXPECT_EQ(sol.findDuplicate(nums), 2);
}

TEST(FindDuplicateTest, DuplicateAtEnd) {
    Solution sol;
    std::vector<int> nums = {1,4,6,2,5,3,6};
    EXPECT_EQ(sol.findDuplicate(nums), 6);
}

TEST(FindDuplicateTest, LargeCase) {
    Solution sol;
    std::vector<int> nums(10001);
    for (int i = 0; i < 10000; ++i) nums[i] = i+1;
    nums[10000] = 9999;
    EXPECT_EQ(sol.findDuplicate(nums), 9999);
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
[----------] 5 tests from FindDuplicateTest
[ RUN      ] FindDuplicateTest.Example1
[       OK ] FindDuplicateTest.Example1 (0 ms)
[ RUN      ] FindDuplicateTest.Example2
[       OK ] FindDuplicateTest.Example2 (0 ms)
[ RUN      ] FindDuplicateTest.DuplicateAtStart
[       OK ] FindDuplicateTest.DuplicateAtStart (0 ms)
[ RUN      ] FindDuplicateTest.DuplicateAtEnd
[       OK ] FindDuplicateTest.DuplicateAtEnd (0 ms)
[ RUN      ] FindDuplicateTest.LargeCase
[       OK ] FindDuplicateTest.LargeCase (0 ms)
[----------] 5 tests from FindDuplicateTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```