# 189. Rotate Array

## 题目描述

189. 轮转数组

给定一个整数数组 `nums`，将数组中的元素向右轮转 `k` 个位置，其中 `k` 是非负数。

示例 1:

>  **输入**
>
> nums = [1,2,3,4,5,6,7], k = 3
>
>  **输出**
>
> [5,6,7,1,2,3,4]
>
>  **解释**
>
> 向右轮转 1 步: [7,1,2,3,4,5,6]
>
> 向右轮转 2 步: [6,7,1,2,3,4,5]
>
> 向右轮转 3 步: [5,6,7,1,2,3,4]

示例 2:

>  **输入**
>
> nums = [-1,-100,3,99], k = 2
>
>  **输出**
>
> [3,99,-1,-100]
>
>  **解释**
>
> 向右轮转 1 步: [99,-1,-100,3]
>
> 向右轮转 2 步: [3,99,-1,-100]


提示：

- `1 <= nums.length <= 105`
- `-231 <= nums[i] <= 231 - 1`
- `0 <= k <= 105`

进阶：

尽可能想出更多的解决方案，至少有**三种**不同的方法可以解决这个问题。

你可以使用空间复杂度为$O(1)$的 原地算法解决这个问题吗？

## 思路分析

对于这个问题，我第一反应肯定是暴力解法啊，所以我的方法一是创建一个新的数组对原数组进行存储，处理好之后再复制回去。

> 当然我又想到了拷贝开销，所以我这里没有用`assign`而是用了`swap`，移动完了之后`temp`数组就直接空了，但是可以节省拷贝开销。

然后我想了想，移动过程中移动了`k`位，那必然会丢失`k % nums.size()`个元素啊，所以我的方法二新设置了一个数组，然后仅存储那些会被覆盖的值，在全部搬移完成之后再加回去。LeetCode上叫这个叫环状替换，我也是用的环状队列的思想。

然后我尝试想一个空间复杂度为$O(1)$的解法，然后我想到可以逐个搬运啊。比如`k = 3`，我就逐个移动3次，每次固定移动1位即可，这就是我的方法三的思路。但是很可惜，触发了`time limit exceed`，所以应该是不可行的。

LeetCode官方给出的解法技巧性比较强：使用了3次`reverse`来实现部分替换：

```c++
class Solution {
public:
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start += 1;
            end -= 1;
        }
    }

    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
    }
};
```

有老哥整理了一下思路就是这样的：

```
nums = "----->-->"; k =3
result = "-->----->";

reverse "----->-->" we can get "<--<-----"
reverse "<--" we can get "--><-----"
reverse "<-----" we can get "-->----->"
this visualization help me figure it out :)
```

比较巧妙，临场发挥完全想不到，我选择死记硬背了（bushi）。

## 代码实现

代码实现如下：
```c++
#include <vector>

using namespace std;

class Solution {
public:
    //暴力解法
    /*
    void rotate(vector<int>& nums, int k) {
        vector<int> temp;
        int step = k % nums.size();
        for(int i = 0;i < nums.size();++i){
            temp.push_back(nums[(nums.size() + i - step) % nums.size()]);
        }
        nums.swap(temp);
    }
    */
    //暂存法
    void rotate(vector<int>& nums, int k){
        vector<int> temp;
        int step = k % nums.size();
        for(int i = nums.size() - step;i < nums.size();++i){
            temp.push_back(nums[i]);
        }
        for (int j = nums.size() - 1; j > step - 1; --j) {
            nums[j] = nums[j - step];
        }
        for(int p = 0;p < step;++p){
            nums[p] = temp[p];
        }
    }
    //单步轮转法
    /*
    void rotate(vector<int>& nums, int k){
        int temp = nums[nums.size() - 1];
        int step = k % nums.size();
        while (step > 0) {
            for(int i = nums.size() - 1;i > 0;--i){
                nums[i] = nums[i - 1];
            }
            nums[0] = temp;
            temp = nums[nums.size() - 1];
            --step;
        }
    }
    */
};
```

## 复杂度分析

- 暴力解法
    - 时间复杂度：$O(n)$，每个元素都只被访问和赋值一次。
    - 空间复杂度：$O(n)$，需要一个与原数组等长的临时数组。

- 暂存法
    - 时间复杂度：$O(n + k)$，需要遍历两次数组（一次暂存，一次搬移）。
    - 空间复杂度：$O(n)$，只需要额外存储$k$个元素。

- 单步轮转法
    - 时间复杂度：$O(nk)$，每次右移都要遍历整个数组，重复$k$次，最坏时$k\approx n$，总复杂度$O(n^2)$。
    - 空间复杂度：$O(1)$，只用到常数级别的临时变量。

- LeetCode官方解法
    - 时间复杂度：只需三次遍历（每次$O(n)$）。
    - 空间复杂度：只用到常数级别的临时变量，原地操作。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "189-rotate-array.cpp"

TEST(RotateArrayTest, Example1) {
    std::vector<int> nums = {1,2,3,4,5,6,7};
    Solution solution;
    solution.rotate(nums, 3);
    EXPECT_EQ(nums, (std::vector<int>{5,6,7,1,2,3,4}));
}

TEST(RotateArrayTest, Example2) {
    std::vector<int> nums = {-1,-100,3,99};
    Solution solution;
    solution.rotate(nums, 2);
    EXPECT_EQ(nums, (std::vector<int>{3,99,-1,-100}));
}

TEST(RotateArrayTest, KZero) {
    std::vector<int> nums = {1,2,3};
    Solution solution;
    solution.rotate(nums, 0);
    EXPECT_EQ(nums, (std::vector<int>{1,2,3}));
}

TEST(RotateArrayTest, KEqualToSize) {
    std::vector<int> nums = {1,2,3};
    Solution solution;
    solution.rotate(nums, 3);
    EXPECT_EQ(nums, (std::vector<int>{1,2,3}));
}

TEST(RotateArrayTest, KGreaterThanSize) {
    std::vector<int> nums = {1,2,3};
    Solution solution;
    solution.rotate(nums, 4);
    EXPECT_EQ(nums, (std::vector<int>{3,1,2}));
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
[----------] 5 tests from RotateArrayTest
[ RUN      ] RotateArrayTest.Example1
[       OK ] RotateArrayTest.Example1 (0 ms)
[ RUN      ] RotateArrayTest.Example2
[       OK ] RotateArrayTest.Example2 (0 ms)
[ RUN      ] RotateArrayTest.KZero
[       OK ] RotateArrayTest.KZero (0 ms)
[ RUN      ] RotateArrayTest.KEqualToSize
[       OK ] RotateArrayTest.KEqualToSize (0 ms)
[ RUN      ] RotateArrayTest.KGreaterThanSize
[       OK ] RotateArrayTest.KGreaterThanSize (0 ms)
[----------] 5 tests from RotateArrayTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```
