# 19. 删除链表的倒数第 N 个结点

## 题目描述

19. 删除链表的倒数第 N 个结点

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

![](./1.jpg)

示例 1：

>  **输入**
>
> head = [1,2,3,4,5], n = 2
>
>  **输出**
>
> [1,2,3,5]

示例 2：

>  **输入**
>
> head = [1], n = 1
>
>  **输出**
>
> []

示例 3：

>  **输入**
>
> head = [1,2], n = 1
>
> **输出**
>
> [1]

提示：

- 链表中结点的数目为 `sz`
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

进阶：你能尝试使用一趟扫描实现吗？

## 思路分析

这道题一眼双指针，双指针一个在前面一个在后面就可以了，到了链表尾部就断开对应节点。但是我当时卡在了头节点等特殊情况的判断上了。后面经过提示才发现可以使用一个虚拟的头节点指向头节点，这样就可以避免判定特殊情况。

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;
        for (int i = 0; i < n + 1; ++i) {
            fast = fast->next;
        }
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* toDelete = slow->next;
        slow->next = toDelete->next;
        delete toDelete;
        return dummy.next;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(L)$，其中 $L$ 是链表的长度。
- 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "19-remove-nth-node-from-end-of-list.cpp"
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

TEST(RemoveNthFromEndTest, Example1) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.removeNthFromEnd(head, 2);
    std::vector<int> expected = {1,2,3,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(RemoveNthFromEndTest, RemoveHead) {
    Solution sol;
    ListNode* head = createList({1,2});
    ListNode* res = sol.removeNthFromEnd(head, 2);
    std::vector<int> expected = {2};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(RemoveNthFromEndTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* res = sol.removeNthFromEnd(head, 1);
    EXPECT_EQ(res, nullptr);
}

TEST(RemoveNthFromEndTest, RemoveLast) {
    Solution sol;
    ListNode* head = createList({1,2,3});
    ListNode* res = sol.removeNthFromEnd(head, 1);
    std::vector<int> expected = {1,2};
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
[----------] 4 tests from RemoveNthFromEndTest
[ RUN      ] RemoveNthFromEndTest.Example1
[       OK ] RemoveNthFromEndTest.Example1 (0 ms)
[ RUN      ] RemoveNthFromEndTest.RemoveHead
[       OK ] RemoveNthFromEndTest.RemoveHead (0 ms)
[ RUN      ] RemoveNthFromEndTest.SingleNode
[       OK ] RemoveNthFromEndTest.SingleNode (0 ms)
[ RUN      ] RemoveNthFromEndTest.RemoveLast
[       OK ] RemoveNthFromEndTest.RemoveLast (0 ms)
[----------] 4 tests from RemoveNthFromEndTest (2 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 4 tests.
```