# 503. Next Greater Element II

## 题目描述

503. 下一个更大元素 II

给定一个循环数组 `nums` （ `nums[nums.length - 1]` 的下一个元素是 `nums[0]` ），返回 `nums` 中每个元素的 **下一个更大元素** 。

数字 `x` 的 **下一个更大的元素** 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 `-1` 。

示例 1:

>  **输入**
>
> nums = [1,2,1]
>
>  **输出**
>
> [2,-1,2]
>
>  **解释**
>
> 第一个 1 的下一个更大的数是 2；
>
> 数字 2 找不到下一个更大的数；
>
> 第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

示例 2:

>  **输入**
>
> nums = [1,2,3,4,3]
>
>  **输出**
>
> [2,3,4,-1,4]

提示:

- `1 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`

## 思路分析

今天又是只会暴力解法的一天。只想到了循环数组的实现，也知道是单调栈做的，和496题差不多，但是我还是没写出来。

可以使用单调栈解决本题。单调栈中保存的是下标，从栈底到栈顶的下标在数组 `nums` 中对应的值是单调不升的。

每次我们移动到数组中的一个新的位置 `i`，我们就将当前单调栈中所有对应值小于 `nums[i]` 的下标弹出单调栈，这些值的下一个更大元素即为 `nums[i]`（证明很简单：如果有更靠前的更大元素，那么这些位置将被提前弹出栈）。随后我们将位置 `i` 入栈。

但是注意到只遍历一次序列是不够的，例如序列 `[2,3,1]`，最后单调栈中将剩余 `[3,1]`，其中元素 `[1]` 的下一个更大元素还是不知道的。

一个朴素的思想是，我们可以把这个循环数组「拉直」，即复制该序列的前 `n−1` 个元素拼接在原序列的后面。这样我们就可以将这个新序列当作普通序列，用上文的方法来处理。

LeetCode官方解答如下：

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int> stk;
        for (int i = 0; i < n * 2 - 1; i++) {
            while (!stk.empty() && nums[stk.top()] < nums[i % n]) {
                ret[stk.top()] = nums[i % n];
                stk.pop();
            }
            stk.push(i % n);
        }
        return ret;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <cmath>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result;
        float length = nums.size();
        for(int i = 0;i < nums.size();++i){
            int index = i + 1;
            int temp_index = index - nums.size() * floor(index / nums.size());
            while (temp_index % nums.size() != i) {
                if(nums[temp_index] > nums[i]){
                    result.push_back(nums[temp_index]);
                    goto next_loop;
                }
                ++index;
                temp_index = index - nums.size() * floor(index / nums.size());
            }
            result.push_back(-1);
            next_loop:continue;
        }
        return result;
    }
};
```

## 复杂度分析

- 暴力搜索

    - 时间复杂度：$O(n^2)$，其中 `n` 是序列的长度。对于每个元素，都可能需要遍历整个数组一次来寻找下一个更大元素。

    - 空间复杂度：$O(1)$，只使用了常数级别的额外空间（不包括返回结果）。

- 单调栈

    - 时间复杂度: $O(n)$，其中 `n` 是序列的长度。我们需要遍历该数组中每个元素最多 2 次，每个元素出栈与入栈的总次数也不超过 4 次。

    - 空间复杂度: $O(n)$，其中 `n` 是序列的长度。空间复杂度主要取决于栈的大小，栈的大小至多为 `2n−1`。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "503-next-greater-element-ii.cpp"
#include <vector>

TEST(NextGreaterElementsTest, Example1) {
	Solution sol;
	std::vector<int> nums = {1,2,1};
	std::vector<int> expected = {2,-1,2};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, AllIncreasing) {
	Solution sol;
	std::vector<int> nums = {1,2,3,4};
	std::vector<int> expected = {2,3,4,-1};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, AllDecreasing) {
	Solution sol;
	std::vector<int> nums = {4,3,2,1};
	std::vector<int> expected = {-1,4,4,4};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, AllSame) {
	Solution sol;
	std::vector<int> nums = {5,5,5,5};
	std::vector<int> expected = {-1,-1,-1,-1};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
}

TEST(NextGreaterElementsTest, SingleElement) {
	Solution sol;
	std::vector<int> nums = {7};
	std::vector<int> expected = {-1};
	EXPECT_EQ(sol.nextGreaterElements(nums), expected);
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
[----------] 5 tests from NextGreaterElementsTest
[ RUN      ] NextGreaterElementsTest.Example1
[       OK ] NextGreaterElementsTest.Example1 (0 ms)
[ RUN      ] NextGreaterElementsTest.AllIncreasing
[       OK ] NextGreaterElementsTest.AllIncreasing (0 ms)
[ RUN      ] NextGreaterElementsTest.AllDecreasing
[       OK ] NextGreaterElementsTest.AllDecreasing (0 ms)
[ RUN      ] NextGreaterElementsTest.AllSame
[       OK ] NextGreaterElementsTest.AllSame (0 ms)
[ RUN      ] NextGreaterElementsTest.SingleElement
[       OK ] NextGreaterElementsTest.SingleElement (0 ms)
[----------] 5 tests from NextGreaterElementsTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```
