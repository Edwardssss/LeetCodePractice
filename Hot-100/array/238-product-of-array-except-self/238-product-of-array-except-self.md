# 238. 除了自身以外数组的乘积

## 题目描述

238. 除了自身以外数组的乘积

给你一个整数数组 `nums`，返回数组 `answer` ，其中 `answer[i]` 等于 `nums` 中除了 `nums[i]` 之外其余各元素的乘积 。

题目数据 **保证** 数组 `nums`之中任意元素的全部前缀元素和后缀的乘积都在 **32 位** 整数范围内。

请 **不要使用除法**，且在 $O(n)$ 时间复杂度内完成此题。

示例 1:

>  **输入**
>
> nums = [1,2,3,4]
>
>  **输出**
>
> [24,12,8,6]

示例 2:

>  **输入**
>
> nums = [-1,1,0,-3,3]
>
>  **输出**
>
> [0,0,9,0,0]

提示：

- `2 <= nums.length <= 105`
- `-30 <= nums[i] <= 30`
- 输入**保证**数组 `answer[i]` 在**32 位**整数范围内

进阶：你可以在 $O(1)$ 的额外空间复杂度内完成这个题目吗？（出于对空间复杂度分析的目的，输出数组 **不被视为** 额外空间。）

## 思路分析

这道题让我想到了之前学习概率因子图的计算方法：即全部乘起来之后除以需要的那个数字即可避免重复计算。但是这道题不让用这种方法，而且需要保证$O(n)$复杂度，那么我就想到了分组相乘，即分成前缀之积和后缀之积，只需遍历一次即可得到两个积，然后翻转相乘就是答案了。

我看了下官方答案，方法一就是我这种方法，但是空间复杂度是$O(n)$，所以此处贴一下官方的方法二。

方法二就是在方法一的基础上，先把输出数组当作前缀数组来计算，然后再动态构造后缀数组得到结果。

- 初始化 `answer` 数组，对于给定索引 `i`，`answer[i]` 代表的是 `i` 左侧所有数字的乘积。
- 构造方式与之前相同，只是我们试图节省空间，先把 `answer` 作为方法一的前缀数组。
- 这种方法的唯一变化就是我们没有构造后缀数组。而是用一个遍历来跟踪右边元素的乘积。并更新数组 `answer[i]=answer[i]∗R`。然后 `R` 更新为 `R=R∗nums[i]`，其中变量 `R` 表示的就是索引右侧数字的乘积。

官方代码实现如下：

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();
        vector<int> answer(length);

        // answer[i] 表示索引 i 左侧所有元素的乘积
        // 因为索引为 '0' 的元素左侧没有元素， 所以 answer[0] = 1
        answer[0] = 1;
        for (int i = 1; i < length; i++) {
            answer[i] = nums[i - 1] * answer[i - 1];
        }

        // R 为右侧所有元素的乘积
        // 刚开始右边没有元素，所以 R = 1
        int R = 1;
        for (int i = length - 1; i >= 0; i--) {
            // 对于索引 i，左边的乘积为 answer[i]，右边的乘积为 R
            answer[i] = answer[i] * R;
            // R 需要包含右边所有的乘积，所以计算下一个结果时需要将当前值乘到 R 上
            R *= nums[i];
        }
        return answer;
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
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> preffix,suffix,result;
        int length = nums.size();
        preffix.push_back(1);
        suffix.push_back(1);
        for(int i = 0;i < length;++i){
            preffix.push_back(preffix[i] * nums[i]);
            suffix.push_back(suffix[i] * nums[length - i - 1]);
        }
        for(int j = 0;j < length;++j){
            result.push_back(preffix[j] * suffix[length - j - 1]);
        }
        return result;
    }
};
```

## 复杂度分析


- 前缀后缀列表
    - 时间复杂度：$O(n)$。需要三次遍历数组，分别计算前缀积、后缀积和最终结果。
    - 空间复杂度：$O(n)$。需要额外的前缀和后缀数组，各为 $O(n)$。

- 前缀后缀列表（优化）
    - 时间复杂度：$O(n)$。同样只需两次遍历数组。
    - 空间复杂度：$O(1)$（不计输出数组）。只用常数级变量存储右侧乘积。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "238-product-of-array-except-self.cpp"

static Solution solution;

TEST(ProductExceptSelfTest, Example1) {
    std::vector<int> nums = {1,2,3,4};
    std::vector<int> expected = {24,12,8,6};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, ContainsZero) {
    std::vector<int> nums = {0,1,2,3};
    std::vector<int> expected = {6,0,0,0};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, AllOnes) {
    std::vector<int> nums = {1,1,1,1};
    std::vector<int> expected = {1,1,1,1};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, NegativeNumbers) {
    std::vector<int> nums = {-1,2,-3,4};
    std::vector<int> expected = {-24,12,-8,6};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(ProductExceptSelfTest, SingleElement) {
    std::vector<int> nums = {5};
    std::vector<int> expected = {1};
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：

```
[ RUN      ] ProductExceptSelfTest.Example1
[       OK ] ProductExceptSelfTest.Example1 (0 ms)
[ RUN      ] ProductExceptSelfTest.ContainsZero
[       OK ] ProductExceptSelfTest.ContainsZero (0 ms)
[ RUN      ] ProductExceptSelfTest.AllOnes
[       OK ] ProductExceptSelfTest.AllOnes (0 ms)
[ RUN      ] ProductExceptSelfTest.NegativeNumbers
[       OK ] ProductExceptSelfTest.NegativeNumbers (0 ms)
[ RUN      ] ProductExceptSelfTest.SingleElement
[       OK ] ProductExceptSelfTest.SingleElement (0 ms)
[----------] 5 tests from ProductExceptSelfTest (1 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 5 tests.
```
