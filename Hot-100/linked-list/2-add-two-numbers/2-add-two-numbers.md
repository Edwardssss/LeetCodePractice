# 2. Add Two Numbers

## 题目描述

2. 两数相加

给你两个**非空**的链表，表示两个非负的整数。它们每位数字都是按照 **逆序** 的方式存储的，并且每个节点只能存储 **一位** 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

![](./1.jpg)

示例 1：

>  **输入**
>
> l1 = [2,4,3], l2 = [5,6,4]
>
>  **输出**
>
> [7,0,8]
>
>  **解释**
>
> 342 + 465 = 807.

示例 2：

>  **输入**
>
> l1 = [0], l2 = [0]
>
>  **输出**
>
> [0]

示例 3：

>  **输入**
>
> l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
>
>  **输出**
>
> [8,9,9,9,0,0,0,1]

提示：

- 每个链表中的节点数在范围 `[1, 100]` 内
- `0 <= Node.val <= 9`
- 题目数据保证列表表示的数字不含前导零

## 思路分析

很简单的一道题，按照数学直觉去做就好了。但是由于我的代码水平低下，所以写的很臃肿，看了下LeetCode官方的题解，感觉写的真是清爽干净。

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr, *tail = nullptr;
        int carry = 0;
        while (l1 || l2) {
            int n1 = l1 ? l1->val: 0;
            int n2 = l2 ? l2->val: 0;
            int sum = n1 + n2 + carry;
            if (!head) {
                head = tail = new ListNode(sum % 10);
            } else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!(l1->val || l2->val) && !((l1->next) || (l2->next))) return new ListNode(0,nullptr);
        if(!(l1->val) && !(l1->next)) return l2;
        if(!(l2->val) && !(l2->next)) return l1;
        bool add_flag = false;
        ListNode* result_head = new ListNode();
        ListNode* result = result_head;
        ListNode* l1_cur = l1;
        ListNode* l2_cur = l2;
        int l1_value;
        int l2_value;
        while(l1_cur || l2_cur || add_flag){
            if(!l1_cur){
                l1_value = 0;
            }
            else{
                l1_value = l1_cur->val;
                l1_cur = l1_cur->next;
            }
            if(!l2_cur){
                l2_value = 0;
            }
            else{
                l2_value = l2_cur->val;
                l2_cur = l2_cur->next;
            }
            if(l1_value + l2_value + add_flag > 9){
                result->val = l1_value + l2_value + add_flag - 10;
                add_flag = true;
            }
            else{
                result->val = l1_value + l2_value + add_flag;
                add_flag = false;
            }
            if(l1_cur || l2_cur || add_flag){
                result->next = new ListNode();
                result = result->next;
            }
        }
        return result_head;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(\max(m,n))$，其中 `m` 和 `n` 分别为两个链表的长度。我们要遍历两个链表的全部位置，而处理每个位置只需要 $O(1)$ 的时间

- 空间复杂度：$O(1)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "2-add-two-numbers.cpp"
#include <vector>

// 辅助函数：根据数组创建链表
ListNode* createList(const std::vector<int>& vals) {
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    for (int v : vals) {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    ListNode* head = dummy->next;
    delete dummy;
    return head;
}

// 辅助函数：链表转vector
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> res;
    while (head) {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

TEST(AddTwoNumbersTest, Example1) {
    Solution sol;
    ListNode* l1 = createList({2,4,3});
    ListNode* l2 = createList({5,6,4});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {7,0,8};
    EXPECT_EQ(listToVector(res), expected);
}

TEST(AddTwoNumbersTest, CarryOver) {
    Solution sol;
    ListNode* l1 = createList({9,9,9,9,9,9,9});
    ListNode* l2 = createList({9,9,9,9});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {8,9,9,9,0,0,0,1};
    EXPECT_EQ(listToVector(res), expected);
}

TEST(AddTwoNumbersTest, SingleNode) {
    Solution sol;
    ListNode* l1 = createList({0});
    ListNode* l2 = createList({0});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {0};
    EXPECT_EQ(listToVector(res), expected);
}

TEST(AddTwoNumbersTest, DifferentLength) {
    Solution sol;
    ListNode* l1 = createList({1,8});
    ListNode* l2 = createList({0});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {1,8};
    EXPECT_EQ(listToVector(res), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from AddTwoNumbersTest
[ RUN      ] AddTwoNumbersTest.Example1
[       OK ] AddTwoNumbersTest.Example1 (0 ms)
[ RUN      ] AddTwoNumbersTest.CarryOver
[       OK ] AddTwoNumbersTest.CarryOver (0 ms)
[ RUN      ] AddTwoNumbersTest.SingleNode
[       OK ] AddTwoNumbersTest.SingleNode (0 ms)
[ RUN      ] AddTwoNumbersTest.DifferentLength
[       OK ] AddTwoNumbersTest.DifferentLength (0 ms)
[----------] 4 tests from AddTwoNumbersTest (1 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 4 tests.
```
