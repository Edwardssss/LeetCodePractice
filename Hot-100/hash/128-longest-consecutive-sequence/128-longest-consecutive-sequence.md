# 128. Longest Consecutive Sequence

## 题目描述

128. 最长连续序列

给定一个未排序的整数数组 `nums` ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 $O(n)$ 的算法解决此问题。

示例 1：

>  **输入**
>
> nums = [100,4,200,1,3,2]
>
>  **输出**
>
> 4
>
>  **解释**
>
> 最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

示例 2：

>  **输入**
>
> nums = [0,3,7,2,5,8,4,6,0,1]
>
>  **输出**
>
> 9

示例 3：

>  **输入**
>
> nums = [1,0,1,2]
>
>  **输出**
>
> 3

提示：

- `0 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`

## 思路分析

这道题我首先就是想到先用$O(n\log n)$的`sort`排序一下，然后用双指针看看排序也行啊。然后发现官方解是哈希表做的，使用集合来去除重复元素。

官方代码实现如下：

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
};
```

## 代码实现

代码实现如下：
```c++
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return 1;
        sort(nums.begin(), nums.end());
        int max_length = 1;
        int cur_length = 1;
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1]) {
                continue;
            } else if (nums[i] == nums[i - 1] + 1) {
                ++cur_length;
            } else {
                cur_length = 1;
            }
            if (cur_length > max_length) {
                max_length = cur_length;
            }
        }
        return max_length;
    }
};
```


## 复杂度分析

- 排序法
    - 时间复杂度：$O(n \log n)$，主要耗时在排序，后续遍历一次数组是 $O(n)$。
    - 空间复杂度：$O(1)$（原地排序）或 $O(n)$（如果排序算法不是原地排序）。

- 哈希表
    - 时间复杂度：$O(n)$，每个元素插入哈希表和查找都是常数时间，整体为线性。
    - 空间复杂度：$O(n)$，哈希表需要存储所有元素。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "128-longest-consecutive-sequence.cpp"

static Solution solution;

TEST(LongestConsecutiveTest, Example1) {
    std::vector<int> nums{100, 4, 200, 1, 3, 2};
    EXPECT_EQ(solution.longestConsecutive(nums), 4);
}

TEST(LongestConsecutiveTest, Example2) {
    std::vector<int> nums{0,3,7,2,5,8,4,6,0,1};
    EXPECT_EQ(solution.longestConsecutive(nums), 9);
}

TEST(LongestConsecutiveTest, Empty) {
    std::vector<int> nums{};
    EXPECT_EQ(solution.longestConsecutive(nums), 0);
}

TEST(LongestConsecutiveTest, Single) {
    std::vector<int> nums{42};
    EXPECT_EQ(solution.longestConsecutive(nums), 1);
}

TEST(LongestConsecutiveTest, Duplicates) {
    std::vector<int> nums{1,2,0,1};
    EXPECT_EQ(solution.longestConsecutive(nums), 3);
}

TEST(LongestConsecutiveTest, NoConsecutive) {
    std::vector<int> nums{10, 30, 20};
    EXPECT_EQ(solution.longestConsecutive(nums), 1);
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
[----------] 6 tests from LongestConsecutiveTest
[ RUN      ] LongestConsecutiveTest.Example1
[       OK ] LongestConsecutiveTest.Example1 (0 ms)
[ RUN      ] LongestConsecutiveTest.Example2
[       OK ] LongestConsecutiveTest.Example2 (0 ms)
[ RUN      ] LongestConsecutiveTest.Empty
[       OK ] LongestConsecutiveTest.Empty (0 ms)
[ RUN      ] LongestConsecutiveTest.Single
[       OK ] LongestConsecutiveTest.Single (0 ms)
[ RUN      ] LongestConsecutiveTest.Duplicates
[       OK ] LongestConsecutiveTest.Duplicates (0 ms)
[ RUN      ] LongestConsecutiveTest.NoConsecutive
[       OK ] LongestConsecutiveTest.NoConsecutive (0 ms)
[----------] 6 tests from LongestConsecutiveTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 6 tests.
```