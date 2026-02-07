# 283. 移动零

## 题目描述

283. 移动零

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。

示例 1:

>  **输入**
>
> nums = [0,1,0,3,12]
>
>  **输出**
>
> [1,3,12,0,0]

示例 2:

>  **输入**
>
> nums = [0]
>
>  **输出**
>
> [0]

提示:

- `1 <= nums.length <= 104`
- `-231 <= nums[i] <= 231 - 1`

## 思路分析

这道题我使用了`push_back`去做，然后发现官方都是用的`swap`，我都忘掉了还有这个用法，果然是刷少了啊。

官方题解是双指针（快慢指针）的思路，代码实现如下：

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0;
        while (right < n) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
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
    void moveZeroes(vector<int>& nums) {
        if (nums.size() == 1) return;
        for (int i = 0,cnt = 0; cnt < nums.size(); ++i,++cnt) {
            while (nums[i] == 0){
                nums.erase(nums.begin() + i);
                nums.push_back(0);
                if(++cnt >= nums.size()) break;
            }
        }
        return;
    }
};
```

## 复杂度分析

- 增删法

    - 时间复杂度：
    - 空间复杂度：

- 交换法

    - 时间复杂度：
    - 空间复杂度：

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "283-move-zeroes.cpp"
#include <vector>

static Solution solution;

TEST(MoveZeroesTest, Example1) {
    std::vector<int> nums{0,1,0,3,12};
    std::vector<int> expected{1,3,12,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, Example2) {
    std::vector<int> nums{0,0,1};
    std::vector<int> expected{1,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, AllZero) {
    std::vector<int> nums{0,0,0,0};
    std::vector<int> expected{0,0,0,0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, NoZero) {
    std::vector<int> nums{1,2,3,4};
    std::vector<int> expected{1,2,3,4};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, SingleZero) {
    std::vector<int> nums{0};
    std::vector<int> expected{0};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, SingleNonZero) {
    std::vector<int> nums{5};
    std::vector<int> expected{5};
    solution.moveZeroes(nums);
    EXPECT_EQ(nums, expected);
}

TEST(MoveZeroesTest, ZerosAtEnd) {
    std::vector<int> nums{1,2,3,0,0};
    std::vector<int> expected{1,2,3,0,0};
    solution.moveZeroes(nums);
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
[==========] Running 7 tests from 1 test suite. 
[----------] Global test environment set-up.    
[----------] 7 tests from MoveZeroesTest        
[ RUN      ] MoveZeroesTest.Example1
[       OK ] MoveZeroesTest.Example1 (0 ms)     
[ RUN      ] MoveZeroesTest.Example2
[       OK ] MoveZeroesTest.Example2 (0 ms)     
[ RUN      ] MoveZeroesTest.AllZero
[       OK ] MoveZeroesTest.AllZero (0 ms)      
[ RUN      ] MoveZeroesTest.NoZero
[       OK ] MoveZeroesTest.NoZero (0 ms)       
[ RUN      ] MoveZeroesTest.SingleZero
[       OK ] MoveZeroesTest.SingleZero (0 ms)   
[ RUN      ] MoveZeroesTest.SingleNonZero       
[       OK ] MoveZeroesTest.SingleNonZero (0 ms)
[ RUN      ] MoveZeroesTest.ZerosAtEnd
[       OK ] MoveZeroesTest.ZerosAtEnd (0 ms)
[----------] 7 tests from MoveZeroesTest (2 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 7 tests.
```