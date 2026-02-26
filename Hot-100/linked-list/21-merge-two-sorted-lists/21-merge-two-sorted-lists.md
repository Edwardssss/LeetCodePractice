# 21. 合并两个有序链表

## 题目描述

21. 合并两个有序链表

将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

![](./1.jpg)

示例 1：

>  **输入**
>
> l1 = [1,2,4], l2 = [1,3,4]
>
>  **输出**
>
> [1,1,2,3,4,4]

示例 2：

>  **输入**
>
> l1 = [], l2 = []
>
>  **输出**
>
> []

示例 3：

>  **输入**
>
> l1 = [], l2 = [0]
>
>  **输出**
>
> [0]

提示：

- 两个链表的节点数目范围是 `[0, 50]`
- `-100 <= Node.val <= 100`
- `l1` 和 `l2` 均按 **非递减顺序** 排列

## 思路分析

这道题最先想到的就是逐个比较值即可，如果有一个链表被比较完了就可以把另一个链表的剩下部分全部接过来即可。LeetCode官方给出了另一种基于递归的实现。

官方示例代码如下：

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        } else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        ListNode* ptr1 = list1;
        ListNode* ptr2 = list2;
        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->val < ptr2->val) {
                tail->next = ptr1;
                ptr1 = ptr1->next;
            } else {
                tail->next = ptr2;
                ptr2 = ptr2->next;
            }
            tail = tail->next;
        }
        if (ptr1 != nullptr) {
            tail->next = ptr1;
        } else {
            tail->next = ptr2;
        }
        return dummy.next;
    }
};
```

## 复杂度分析

- 递归法

    - 时间复杂度：$O(m+n)$
    - 空间复杂度：$O(m+n)$

- 迭代法

    - 时间复杂度：$O(m+n)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "21-merge-two-sorted-lists.cpp"
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

// 辅助函数：释放链表内存
void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

TEST(MergeTwoListsTest, Example1) {
    Solution sol;
    ListNode* l1 = createList({1,2,4});
    ListNode* l2 = createList({1,3,4});
    ListNode* res = sol.mergeTwoLists(l1, l2);
    std::vector<int> expected = {1,1,2,3,4,4};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(MergeTwoListsTest, OneEmpty) {
    Solution sol;
    ListNode* l1 = nullptr;
    ListNode* l2 = createList({0});
    ListNode* res = sol.mergeTwoLists(l1, l2);
    std::vector<int> expected = {0};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(MergeTwoListsTest, BothEmpty) {
    Solution sol;
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;
    ListNode* res = sol.mergeTwoLists(l1, l2);
    EXPECT_EQ(res, nullptr);
}

TEST(MergeTwoListsTest, DifferentLength) {
    Solution sol;
    ListNode* l1 = createList({2,5,7});
    ListNode* l2 = createList({1,3,4,6,8});
    ListNode* res = sol.mergeTwoLists(l1, l2);
    std::vector<int> expected = {1,2,3,4,5,6,7,8};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
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
[----------] 4 tests from MergeTwoListsTest
[ RUN      ] MergeTwoListsTest.Example1
[       OK ] MergeTwoListsTest.Example1 (0 ms)
[ RUN      ] MergeTwoListsTest.OneEmpty
[       OK ] MergeTwoListsTest.OneEmpty (0 ms)
[ RUN      ] MergeTwoListsTest.BothEmpty
[       OK ] MergeTwoListsTest.BothEmpty (0 ms)
[ RUN      ] MergeTwoListsTest.DifferentLength
[       OK ] MergeTwoListsTest.DifferentLength (0 ms)
[----------] 4 tests from MergeTwoListsTest (2 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 4 tests.
```
