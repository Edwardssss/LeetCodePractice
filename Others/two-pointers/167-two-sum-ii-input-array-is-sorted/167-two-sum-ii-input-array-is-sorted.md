# 167. Two Sum II - Input Array Is Sorted

## 题目描述

167. 两数之和 II - 输入有序数组

给你一个下标从 1 开始的整数数组 `numbers` ，该数组已按**非递减顺序排列**  ，请你从数组中找出满足相加之和等于目标数 `target` 的两个数。如果设这两个数分别是 `numbers[index1]` 和 `numbers[index2]` ，则 `1 <= index1 < index2 <= numbers.length` 。

以长度为 2 的整数数组 `[index1, index2]` 的形式返回这两个整数的下标 `index1` 和 `index2`。

你可以假设每个输入**只对应唯一的答案** ，而且你**不可以**重复使用相同的元素。

你所设计的解决方案必须只使用**常量级的额外空间**。


示例 1：

>  **输入**
>
> numbers = [2,7,11,15], target = 9
>
>  **输出**
>
> [1,2]
>
>  **解释**
>
> 2 与 7 之和等于目标数 9 。因此 `index1 = 1`, `index2 = 2` 。返回 `[1, 2]` 。

示例 2：

>  **输入**
>
> numbers = [2,3,4], target = 6
>
>  **输出**
>
> [1,3]
>
>  **解释**
>
> 2 与 4 之和等于目标数 6 。因此 `index1 = 1`, `index2 = 3` 。返回 `[1, 3]` 。

示例 3：

>  **输入**
>
> numbers = [-1,0], target = -1
>
>  **输出**
>
> [1,2]
>
>  **解释**
>
> -1 与 0 之和等于目标数 -1 。因此 `index1 = 1`, `index2 = 2` 。返回 `[1, 2]` 。

提示：

- `2 <= numbers.length <= 3 * 104`
- `-1000 <= numbers[i] <= 1000`
- `numbers` 按**非递减顺序**排列
- `-1000 <= target <= 1000`
- 仅存在一个有效答案

## 思路分析

这道题是非常典型的双指针法，甚至人家连排序都排好了，直接用就完事。此处不多做赘述双指针法了。

## 代码实现

代码实现如下：
```c++
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int p = 0,q = numbers.size() - 1;
        while(p != q){
            if(numbers[p] + numbers[q] < target){
                ++p;
            }
            else if(numbers[p] + numbers[q] > target){
                --q;
            }
            else {
                return {p + 1,q + 1};
            }
        }
        return {};
    }
};
```

## 复杂度分析

- 时间复杂度：$O(n)$，一次遍历
- 空间复杂度：$O(1)$，常量级额外空间（双指针）

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "167-two-sum-ii-input-array-is-sorted.cpp"

static Solution solution;

TEST(TwoSumIITest, Example1) {
    std::vector<int> numbers{2, 7, 11, 15};
    int target = 9;
    std::vector<int> expected{1, 2};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, Example2) {
    std::vector<int> numbers{2, 3, 4};
    int target = 6;
    std::vector<int> expected{1, 3};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, Example3) {
    std::vector<int> numbers{-1, 0};
    int target = -1;
    std::vector<int> expected{1, 2};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, NoSolution) {
    std::vector<int> numbers{1, 2, 3, 4, 5};
    int target = 10;
    std::vector<int> expected{};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
}

TEST(TwoSumIITest, DuplicateNumbers) {
    std::vector<int> numbers{1, 2, 2, 3, 4};
    int target = 4;
    std::vector<int> expected{1, 4};
    EXPECT_EQ(solution.twoSum(numbers, target), expected);
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
[----------] 5 tests from TwoSumIITest
[ RUN      ] TwoSumIITest.Example1
[       OK ] TwoSumIITest.Example1 (0 ms)
[ RUN      ] TwoSumIITest.Example2
[       OK ] TwoSumIITest.Example2 (0 ms)
[ RUN      ] TwoSumIITest.Example3
[       OK ] TwoSumIITest.Example3 (0 ms)
[ RUN      ] TwoSumIITest.NoSolution
[       OK ] TwoSumIITest.NoSolution (0 ms)
[ RUN      ] TwoSumIITest.DuplicateNumbers
[       OK ] TwoSumIITest.DuplicateNumbers (0 ms)
[----------] 5 tests from TwoSumIITest (1 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 5 tests.
```