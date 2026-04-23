# 75. Sort Colors

## 题目描述

75. 颜色分类

给定一个包含红色、白色和蓝色、共 $n$ 个元素的数组 $nums$ ，**原地** 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 `0`、 `1` 和 `2` 分别表示红色、白色和蓝色。

必须在不使用库内置的 `sort` 函数的情况下解决这个问题。

示例 1：

>  **输入**
>
> nums = [2,0,2,1,1,0]
>
>  **输出**
>
> [0,0,1,1,2,2]

示例 2：

>  **输入**
>
> nums = [2,0,1]
>
>  **输出**
>
> [0,1,2]

提示：

- `n == nums.length`
- `1 <= n <= 300`
- `nums[i]` 为 `0`、`1` 或 `2`

进阶：

你能想出一个仅使用常数空间的一趟扫描算法吗？

## 思路分析

这道题是很明显的排序，但是我没想到怎么排序，所以就写了个冒泡排序，效果看上去还不错。

LeetCode官方有好几种方法去做这个题目，首先是单指针法。我们可以考虑对数组进行两次遍历。在第一次遍历中，我们将数组中所有的 0 交换到数组的头部。在第二次遍历中，我们将数组中所有的 1 交换到头部的 0 之后。此时，所有的 2 都出现在数组的尾部，这样我们就完成了排序。

代码实现示例如下：

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int ptr = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                swap(nums[i], nums[ptr]);
                ++ptr;
            }
        }
        for (int i = ptr; i < n; ++i) {
            if (nums[i] == 1) {
                swap(nums[i], nums[ptr]);
                ++ptr;
            }
        }
    }
};
```

基于前面的单指针方法，我们也可以额外使用一个指针，即使用两个指针分别用来交换 0 和 1。

代码实现示例如下：

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int p0 = 0, p1 = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                swap(nums[i], nums[p1]);
                ++p1;
            } else if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                if (p0 < p1) {
                    swap(nums[i], nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};
```

也可以换一个角度，类似，我们也可以考虑使用一个指针来交换 0，另一个指针来交换 2。在遍历的过程中，我们需要找出所有的 0 交换至数组的头部，并且找出所有的 2 交换至数组的尾部。

代码实现示例如下：

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int p0 = 0, p2 = n - 1;
        for (int i = 0; i <= p2; ++i) {
            while (i <= p2 && nums[i] == 2) {
                swap(nums[i], nums[p2]);
                --p2;
            }
            if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                ++p0;
            }
        }
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        for(int i = 0;i < nums.size() - 1;++i){
            for(int j = 0;j < nums.size() - 1 - i;++j){
                if(nums[j + 1] < nums[j]) swap(nums[j],nums[j + 1]);
            }
        }
    }
};
```

## 复杂度分析

- 冒泡排序

    - 时间复杂度：$O(n^2)$。冒泡排序需要两层循环，最坏情况下每一对元素都要比较和交换一次。
    - 空间复杂度：$O(1)$。只使用了常数级别的额外空间，排序在原数组上进行。

- 单指针法

    - 时间复杂度：$O(n)$。需要遍历数组两次，每次$O(n)$，总共$O(n)$。
    - 空间复杂度：$O(1)$。只使用了常数级别的指针变量。

- 双指针法

    - 时间复杂度：$O(n)$。只需遍历一遍数组，每个元素最多被操作两次。
    - 空间复杂度：$O(1)$。只使用了常数级别的指针变量。

- 头尾指针

    - 时间复杂度：$O(n)$。只需遍历一遍数组，每个元素最多被操作一次。
    - 空间复杂度：$O(1)$。只使用了常数级别的指针变量。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "75-sort-colors.cpp"
#include <vector>

TEST(SortColorsTest, Example1) {
    Solution sol;
    std::vector<int> nums = {2,0,2,1,1,0};
    std::vector<int> expected = {0,0,1,1,2,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, Example2) {
    Solution sol;
    std::vector<int> nums = {2,0,1};
    std::vector<int> expected = {0,1,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, AllZeros) {
    Solution sol;
    std::vector<int> nums = {0,0,0};
    std::vector<int> expected = {0,0,0};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, AllOnes) {
    Solution sol;
    std::vector<int> nums = {1,1,1};
    std::vector<int> expected = {1,1,1};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, AllTwos) {
    Solution sol;
    std::vector<int> nums = {2,2,2};
    std::vector<int> expected = {2,2,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, Mixed) {
    Solution sol;
    std::vector<int> nums = {1,2,0,2,1,0,1,2,0};
    std::vector<int> expected = {0,0,0,1,1,1,2,2,2};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, SingleElement) {
    Solution sol;
    std::vector<int> nums = {1};
    std::vector<int> expected = {1};
    sol.sortColors(nums);
    EXPECT_EQ(nums, expected);
}

TEST(SortColorsTest, TwoElements) {
    Solution sol;
    std::vector<int> nums = {2,0};
    std::vector<int> expected = {0,2};
    sol.sortColors(nums);
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
[==========] Running 8 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 8 tests from SortColorsTest
[ RUN      ] SortColorsTest.Example1
[       OK ] SortColorsTest.Example1 (0 ms)
[ RUN      ] SortColorsTest.Example2
[       OK ] SortColorsTest.Example2 (0 ms)
[ RUN      ] SortColorsTest.AllZeros
[       OK ] SortColorsTest.AllZeros (0 ms)
[ RUN      ] SortColorsTest.AllOnes
[       OK ] SortColorsTest.AllOnes (0 ms)
[ RUN      ] SortColorsTest.AllTwos
[       OK ] SortColorsTest.AllTwos (0 ms)
[ RUN      ] SortColorsTest.Mixed
[       OK ] SortColorsTest.Mixed (0 ms)
[ RUN      ] SortColorsTest.SingleElement
[       OK ] SortColorsTest.SingleElement (0 ms)
[ RUN      ] SortColorsTest.TwoElements
[       OK ] SortColorsTest.TwoElements (0 ms)
[----------] 8 tests from SortColorsTest (0 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 8 tests.
```
