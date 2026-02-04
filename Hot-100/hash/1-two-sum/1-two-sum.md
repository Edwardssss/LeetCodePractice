# 1. Two Sum

## 题目描述

1. 两数之和

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那**两个**整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。

示例 1：

>  **输入**
>
> nums = [2,7,11,15], target = 9
>
>  **输出**
>
> [0,1]

解释：因为 `nums[0] + nums[1] == 9`，返回 `[0, 1]`。

示例 2：

>  **输入**
>
> nums = [3,2,4], target = 6
>
>  **输出**
>
> [1,2]

示例 3：

>  **输入**
>
> nums = [3,3], target = 6
>
>  **输出**
>
> [0,1]

提示：

- `2 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`
- **只会存在一个有效答案**


进阶：你可以想出一个时间复杂度小于$O(n^2)$的算法吗？

## 思路分析

这道题我采用的是暴力搜索，这个没什么好讲的。官方给出的最优解法是哈希表，在给出确定值`x`之后，在vector中索引`target - x`，并返回索引。

示例代码如下：
```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
```

使用哈希表，可以将寻找 `target - x` 的时间复杂度降低到从$O(N)$ 降低到 $O(1)$。

## 代码实现

代码实现如下：
```c++
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for(int i = 0;i < nums.size() - 1;++i){
            for(int j = i + 1;j < nums.size();++j){
                if (nums[i] + nums[j] == target) {
                    return {i,j};
                }
            }
        }
        return {};
    }
};
```

## 复杂度分析

- 时间复杂度：$O(N^2)$，其中 $N$ 是数组中的元素数量。最坏情况下数组中任意两个数都要被匹配一次。

- 空间复杂度：$O(1)$。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "1-two-sum.cpp"

static Solution solution;

TEST(TwoSumTest, Example1) {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> expected = {0, 1};
    auto result = solution.twoSum(nums, target);
    EXPECT_EQ(result, expected);
}

TEST(TwoSumTest, Example2) {
    std::vector<int> nums = {3, 2, 4};
    int target = 6;
    std::vector<int> expected = {1, 2};
    auto result = solution.twoSum(nums, target);
    EXPECT_EQ(result, expected);
}

TEST(TwoSumTest, Example3) {
    std::vector<int> nums = {3, 3};
    int target = 6;
    std::vector<int> expected = {0, 1};
    auto result = solution.twoSum(nums, target);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from TwoSumTest
[ RUN      ] TwoSumTest.Example1
[       OK ] TwoSumTest.Example1 (0 ms)
[ RUN      ] TwoSumTest.Example2
[       OK ] TwoSumTest.Example2 (0 ms)
[ RUN      ] TwoSumTest.Example3
[       OK ] TwoSumTest.Example3 (0 ms)
[----------] 3 tests from TwoSumTest (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 3 tests.
```