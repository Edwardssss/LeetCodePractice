# 41. 缺失的第一个正数

## 题目描述

41. 缺失的第一个正数

给你一个未排序的整数数组 `nums` ，请你找出其中没有出现的最小的正整数。

请你实现时间复杂度为 $O(n)$ 并且只使用常数级别额外空间的解决方案。

示例 1：

>  **输入**
>
> nums = [1,2,0]
>
>  **输出**
>
> 3
>
>  **解释**
>
> 范围 [1,2] 中的数字都在数组中。

示例 2：

>  **输入**
>
> nums = [3,4,-1,1]
>
>  **输出**
>
> 2
>
>  **解释**
>
> 1 在数组中，但 2 没有。

示例 3：

>  **输入**
>
> nums = [7,8,9,11,12]
>
>  **输出**
>
> 1
>
>  **解释**
>
> 最小的正数 1 没有出现。

提示：

- `1 <= nums.length <= 105`
- `-231 <= nums[i] <= 231 - 1`

## 思路分析

这道题我最早的想法是用无序哈希表去做一个索引表，然后依次遍历进行查找。但是题目限制了空间复杂度是$O(1)$，所以我想半天也没想出来，就用了sort排序之后再遍历。

官方的解法比较巧妙，真的是没见过就真的写不出来的那种。

**哈希表**

对于一个长度为 $N$ 的数组，其中没有出现的最小正整数只能在 $[1,N+1]$ 中。这是因为如果 $[1,N]$ 都出现了，那么答案是 $N+1$，否则答案是 $[1,N]$ 中没有出现的最小正整数。这样一来，我们将所有在 $[1,N]$ 范围内的数放入哈希表，也可以得到最终的答案。而给定的数组恰好长度为 $N$，这让我们有了一种将数组设计成哈希表的思路：

我们对数组进行遍历，对于遍历到的数 $x$，如果它在 $[1,N]$ 的范围内，那么就将数组中的第 $x−1$ 个位置（注意：数组下标从 $0$ 开始）打上「标记」。在遍历结束之后，如果所有的位置都被打上了标记，那么答案是 $N+1$，否则答案是最小的没有打上标记的位置加 $1$。

那么如何设计这个「标记」呢？由于数组中的数没有任何限制，因此这并不是一件容易的事情。但我们可以继续利用上面的提到的性质：由于我们只在意 $[1,N]$ 中的数，因此我们可以先对数组进行遍历，把不在 $[1,N]$ 范围内的数修改成任意一个大于 $N$ 的数（例如 $N+1$）。这样一来，数组中的所有数就都是正数了，因此我们就可以将「标记」表示为「负号」。算法的流程如下：

我们将数组中所有小于等于 $0$ 的数修改为 $N+1$；

我们遍历数组中的每一个数 $x$，它可能已经被打了标记，因此原本对应的数为 $∣x∣$，其中 $∣∣$ 为绝对值符号。如果 $∣x∣∈[1,N]$，那么我们给数组中的第 $∣x∣−1$ 个位置的数添加一个负号。注意如果它已经有负号，不需要重复添加；

在遍历完成之后，如果数组中的每一个数都是负数，那么答案是 $N+1$，否则答案是第一个正数的位置加 $1$。

![](./1.png)

官方代码实现如下所示：

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int& num: nums) {
            if (num <= 0) {
                num = n + 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};
```

**置换**

除了打标记以外，我们还可以使用置换的方法，将给定的数组「恢复」成下面的形式：

如果数组中包含 $x∈[1,N]$，那么恢复后，数组的第 $x−1$ 个元素为 $x$。

在恢复后，数组应当有 $[1, 2, ..., N]$ 的形式，但其中有若干个位置上的数是错误的，每一个错误的位置就代表了一个缺失的正数。以题目中的示例二 $[3, 4, -1, 1]$ 为例，恢复后的数组应当为 $[1, -1, 3, 4]$，我们就可以知道缺失的数为 $2$。

那么我们如何将数组进行恢复呢？我们可以对数组进行一次遍历，对于遍历到的数 $x=nums[i]$，如果 $x∈[1,N]$，我们就知道 $x$ 应当出现在数组中的 $x−1$ 的位置，因此交换 $nums[i]$ 和 $nums[x−1]$，这样 $x$ 就出现在了正确的位置。在完成交换后，新的 $nums[i]$ 可能还在 $[1,N]$ 的范围内，我们需要继续进行交换操作，直到 $x\notin [1,N]$。

> 注意到上面的方法可能会陷入死循环。如果 $nums[i]$ 恰好与 $nums[x−1]$ 相等，那么就会无限交换下去。此时我们有 $nums[i]=x=nums[x−1]$，说明 $x$ 已经出现在了正确的位置。因此我们可以跳出循环，开始遍历下一个数

官方代码实现如下所示：

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
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
    int firstMissingPositive(vector<int>& nums) {
        int minimum_num = 1;
        sort(nums.begin(),nums.end());
        for(int i = 0;i < nums.size();++i){
            if (nums[i] == minimum_num) {
                ++minimum_num;
            }
            else if(nums[i] > minimum_num){
                return minimum_num;
            }
            else if (nums[i] < minimum_num) {
                continue;
            }
        }
        return minimum_num;
    }
};
```

## 复杂度分析

- 哈希表

    - 时间复杂度：$O(N)$
    - 空间复杂度：$O(1)$

- 置换

    - 时间复杂度：$O(N)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "41-first-missing-positive.cpp"

static Solution solution;

TEST(FirstMissingPositiveTest, Example1) {
    std::vector<int> nums = {1,2,0};
    EXPECT_EQ(solution.firstMissingPositive(nums), 3);
}

TEST(FirstMissingPositiveTest, Example2) {
    std::vector<int> nums = {3,4,-1,1};
    EXPECT_EQ(solution.firstMissingPositive(nums), 2);
}

TEST(FirstMissingPositiveTest, Example3) {
    std::vector<int> nums = {7,8,9,11,12};
    EXPECT_EQ(solution.firstMissingPositive(nums), 1);
}

TEST(FirstMissingPositiveTest, AllNegative) {
    std::vector<int> nums = {-1,-2,-3};
    EXPECT_EQ(solution.firstMissingPositive(nums), 1);
}

TEST(FirstMissingPositiveTest, ContinuousPositive) {
    std::vector<int> nums = {1,2,3,4,5};
    EXPECT_EQ(solution.firstMissingPositive(nums), 6);
}

TEST(FirstMissingPositiveTest, Unordered) {
    std::vector<int> nums = {2,1};
    EXPECT_EQ(solution.firstMissingPositive(nums), 3);
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
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from FirstMissingPositiveTest
[ RUN      ] FirstMissingPositiveTest.Example1
[ RUN      ] FirstMissingPositiveTest.Example1
[       OK ] FirstMissingPositiveTest.Example1 (0 ms)
[ RUN      ] FirstMissingPositiveTest.Example2
[       OK ] FirstMissingPositiveTest.Example2 (0 ms)
[ RUN      ] FirstMissingPositiveTest.Example3
[       OK ] FirstMissingPositiveTest.Example3 (0 ms)
[ RUN      ] FirstMissingPositiveTest.AllNegative
[       OK ] FirstMissingPositiveTest.AllNegative (0 ms)
[ RUN      ] FirstMissingPositiveTest.ContinuousPositive
[       OK ] FirstMissingPositiveTest.ContinuousPositive (0 ms)
[ RUN      ] FirstMissingPositiveTest.Unordered
[       OK ] FirstMissingPositiveTest.Unordered (0 ms)
[----------] 6 tests from FirstMissingPositiveTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 6 tests.
```
