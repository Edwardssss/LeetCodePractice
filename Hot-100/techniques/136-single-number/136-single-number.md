# 136. Single Number

## 题目描述

136. 只出现一次的数字

给你一个 **非空** 整数数组 `nums` ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。

示例 1 ：

>  **输入**
>
> nums = [2,2,1]
>
>  **输出**
>
> 1

示例 2 ：

>  **输入**
>
> nums = [4,1,2,1,2]
>
>  **输出**
>
> 4

示例 3 ：

>  **输入**
>
> nums = [1]
>
>  **输出**
>
> 1

提示：

- `1 <= nums.length <= 3 * 104`
- `-3 * 104 <= nums[i] <= 3 * 104`
- 除了某个元素只出现一次以外，其余每个元素均出现两次。

## 思路分析

这道题我一开始很想用无序哈希表查找做的，然后发现他要求常数级的内存占用和线性计算复杂度，这就明显不好用哈希了。然后看了提示之后用异或做出来了，但是这个还是需要复习一下。

## 代码实现

代码实现如下：

```c++
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (auto i : nums) {
            result ^= i;
        }
        return result;
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
#include "136-single-number.cpp"
#include <vector>

static Solution solution;

TEST(SingleNumberTest, Example1) {
    std::vector<int> nums{2, 2, 1};
    EXPECT_EQ(solution.singleNumber(nums), 1);
}

TEST(SingleNumberTest, Example2) {
    std::vector<int> nums{4, 1, 2, 1, 2};
    EXPECT_EQ(solution.singleNumber(nums), 4);
}

TEST(SingleNumberTest, NegativeNumbers) {
    std::vector<int> nums{-1, -1, -2};
    EXPECT_EQ(solution.singleNumber(nums), -2);
}

TEST(SingleNumberTest, SingleElement) {
    std::vector<int> nums{99};
    EXPECT_EQ(solution.singleNumber(nums), 99);
}

TEST(SingleNumberTest, LargeNumbers) {
    std::vector<int> nums{100000, 100000, 123456};
    EXPECT_EQ(solution.singleNumber(nums), 123456);
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
[----------] 5 tests from SingleNumberTest
[ RUN      ] SingleNumberTest.Example1
[       OK ] SingleNumberTest.Example1 (0 ms)
[ RUN      ] SingleNumberTest.Example2
[       OK ] SingleNumberTest.Example2 (0 ms)
[ RUN      ] SingleNumberTest.NegativeNumbers
[       OK ] SingleNumberTest.NegativeNumbers (0 ms)    
[ RUN      ] SingleNumberTest.SingleElement
[       OK ] SingleNumberTest.SingleElement (0 ms)      
[ RUN      ] SingleNumberTest.LargeNumbers
[       OK ] SingleNumberTest.LargeNumbers (0 ms)       
[----------] 5 tests from SingleNumberTest (1 ms total) 

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 5 tests.
```