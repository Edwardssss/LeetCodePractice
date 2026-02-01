# 496. Next Greater Element I

## 题目描述

496. 下一个更大元素 I

`nums1` 中数字 `x` 的 **下一个更大元素** 是指 `x` 在 `nums2` 中对应位置 **右侧** 的 **第一个** 比 `x` 大的元素。

给你两个 `没有重复元素` 的数组 `nums1` 和 `nums2` ，下标从 `0` 开始计数，其中`nums1` 是 `nums2` 的子集。

对于每个 `0 <= i < nums1.length` ，找出满足 `nums1[i] == nums2[j]` 的下标 `j` ，并且在 `nums2` 确定 `nums2[j]` 的 下一个更大元素 。如果不存在下一个更大元素，那么本次查询的答案是 `-1` 。

返回一个长度为 `nums1.length` 的数组 `ans` 作为答案，满足 `ans[i]` 是如上所述的 **下一个更大元素** 。

示例 1：

>  **输入**
>
> nums1 = [4,1,2], nums2 = [1,3,4,2].
>
>  **输出**
>
> [-1,3,-1]
>
>  **解释**
>
> nums1 中每个值的下一个更大元素如下所述：
>
> - 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
>
> - 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
>
> - 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。

示例 2：

>  **输入**
>
> nums1 = [2,4], nums2 = [1,2,3,4].
>
>  **输出**
>
> [3,-1]
>
>  **解释**
>
> nums1 中每个值的下一个更大元素如下所述：
>
> - 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
>
> - 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。

提示：

- `1 <= nums1.length <= nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 104`
- `nums1`和`nums2`中所有整数 **互不相同**
- `nums1` 中的所有整数同样出现在 `nums2` 中

进阶：你可以设计一个时间复杂度为 $O(nums1.length + nums2.length)$ 的解决方案吗？

## 思路分析

这道题我只想到了暴力解法，官方给的解法是使用单调栈做的。

1. 栈的含义： 栈中存放的是按序排列且暂时没有求出结果的元素的 下标 。
2. 维护单调性： 栈内元素严格递减，新来到的元素只需要和栈顶元素进行比较。
3. 新元素的处理： 当一个新元素到来时，先与栈顶元素进行比较。若比栈顶元素小，则直接压栈保存；若比栈顶元素大，则需要弹出栈顶元素，直到栈空或比栈顶元素小后压栈。
4. 弹出时更新信息： 当弹出栈顶元素时，此时次栈顶元素和新来元素就是所求的左右两侧距离最近的且大于该元素的值，记录其下标等信息 。
5. 时间复杂度： 时间复杂度为$O(n)$，因为每个元素最多被压入和弹出栈一次。

有个网友总结的：一旦要求下一个更大的元素，就是用单调栈解。

官方给出的答案如下所示：

```c++
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> hashmap;
        stack<int> st;
        for (int i = nums2.size() - 1; i >= 0; --i) {
            int num = nums2[i];
            while (!st.empty() && num >= st.top()) {
                st.pop();
            }
            hashmap[num] = st.empty() ? -1 : st.top();
            st.push(num);
        }
        vector<int> res(nums1.size());
        for (int i = 0; i < nums1.size(); ++i) {
            res[i] = hashmap[nums1[i]];
        }
        return res;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        for(auto raw_num:nums1){
            auto find_index = find(nums2.begin(),nums2.end(),raw_num);
            int dis = distance(nums2.begin(),find_index);
            for(auto i = nums2.begin() + dis;i != nums2.end();++i){
                if(*i > raw_num){
                    result.push_back(*i);
                    goto next;
                }
            }
            result.push_back(-1);
            next:continue;
        }
        return result;
```

## 复杂度分析

- 暴力解法

    - 时间复杂度：$O(mn)$，其中 `m` 是`nums1`的长度，`n` 是 `nums2`的长度。
    - 空间复杂度：$O(1)$

- 单调栈

    - 时间复杂度：$O(m+n)$，其中 `m` 是 `nums1`的长度，`n` 是 `nums2`的长度。
    - 空间复杂度：$O(n)$，用于存储哈希表。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "496-next-greater-element-i.cpp"
#include <vector>

TEST(NextGreaterElementTest, Example1) {
    Solution sol;
    std::vector<int> nums1 = {4,1,2};
    std::vector<int> nums2 = {1,3,4,2};
    std::vector<int> expected = {-1,3,-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, Example2) {
    Solution sol;
    std::vector<int> nums1 = {2,4};
    std::vector<int> nums2 = {1,2,3,4};
    std::vector<int> expected = {3,-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, AllNoGreater) {
    Solution sol;
    std::vector<int> nums1 = {5,6};
    std::vector<int> nums2 = {6,5,4,3,2,1};
    std::vector<int> expected = {-1,-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, AllGreater) {
    Solution sol;
    std::vector<int> nums1 = {1,2,3};
    std::vector<int> nums2 = {1,2,3,4};
    std::vector<int> expected = {2,3,4};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
}

TEST(NextGreaterElementTest, SingleElement) {
    Solution sol;
    std::vector<int> nums1 = {1};
    std::vector<int> nums2 = {1};
    std::vector<int> expected = {-1};
    EXPECT_EQ(sol.nextGreaterElement(nums1, nums2), expected);
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
[----------] 5 tests from NextGreaterElementTest
[ RUN      ] NextGreaterElementTest.Example1
[       OK ] NextGreaterElementTest.Example1 (0 ms)
[ RUN      ] NextGreaterElementTest.Example2
[       OK ] NextGreaterElementTest.Example2 (0 ms)
[ RUN      ] NextGreaterElementTest.AllNoGreater
[       OK ] NextGreaterElementTest.AllNoGreater (0 ms)
[ RUN      ] NextGreaterElementTest.AllGreater
[       OK ] NextGreaterElementTest.AllGreater (0 ms)
[ RUN      ] NextGreaterElementTest.SingleElement
[       OK ] NextGreaterElementTest.SingleElement (0 ms)
[----------] 5 tests from NextGreaterElementTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```