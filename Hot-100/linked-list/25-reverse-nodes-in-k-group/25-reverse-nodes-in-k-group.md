# 25. Reverse Nodes in k-Group

## 题目描述

25. K 个一组翻转链表

给你链表的头节点 `head` ，每 `k` 个节点一组进行翻转，请你返回修改后的链表。

`k` 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 `k` 的整数倍，那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

![](./1.jpg)

示例 1：

>  **输入**
>
> head = [1,2,3,4,5], k = 2
>
>  **输出**
>
> [2,1,4,3,5]

![](./2.jpg)

示例 2：

>  **输入**
>
> head = [1,2,3,4,5], k = 3
>
>  **输出**
>
> [3,2,1,4,5]

提示：
- 链表中的节点数目为 `n`
- `1 <= k <= n <= 5000`
- `0 <= Node.val <= 1000`

进阶：你可以设计一个只用$O(1)$额外内存空间的算法解决此问题吗？

## 思路描述

这个题其实是206题的plus版，就是再加一层while处理每`k`组的循环，然后我再加入了一下几个特殊逻辑即可，主要是比较麻烦。

## 代码实现

代码实现如下：
```c++
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode* pre = &dummy;
        ListNode* end = &dummy;
        while (true) {
            for (int i = 0; i < k && end; ++i) end = end->next;
            if (!end) break;
            ListNode* start = pre->next;
            ListNode* next = end->next;
            end->next = nullptr;
            pre->next = reverse(start);
            start->next = next;
            pre = start;
            end = pre;
        }
        return dummy.next;
    }
private:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(n)$，其中 $n$ 为链表长度。每个节点最多只会被遍历两次（一次查找分组，一次反转）
- 空间复杂度：$O(1)$，只使用了常数级别的指针变量，反转过程为原地操作，没有使用额外的数据结构

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "25-reverse-nodes-in-k-group.cpp"
#include <vector>

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

std::vector<int> listToVector(ListNode* head) {
    std::vector<int> res;
    while (head) {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

TEST(ReverseKGroupTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* res = sol.reverseKGroup(head, 2);
    std::vector<int> expected = {1};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KEquals1) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.reverseKGroup(head, 1);
    std::vector<int> expected = {1,2,3,4,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KEquals2) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.reverseKGroup(head, 2);
    std::vector<int> expected = {2,1,4,3,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KEquals3) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.reverseKGroup(head, 3);
    std::vector<int> expected = {3,2,1,4,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KGreaterThanLength) {
    Solution sol;
    ListNode* head = createList({1,2});
    ListNode* res = sol.reverseKGroup(head, 3);
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
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from ReverseKGroupTest
[ RUN      ] ReverseKGroupTest.SingleNode
[       OK ] ReverseKGroupTest.SingleNode (0 ms)
[ RUN      ] ReverseKGroupTest.KEquals1
[       OK ] ReverseKGroupTest.KEquals1 (0 ms)
[ RUN      ] ReverseKGroupTest.KEquals2
[       OK ] ReverseKGroupTest.KEquals2 (0 ms)
[ RUN      ] ReverseKGroupTest.KEquals3
[       OK ] ReverseKGroupTest.KEquals3 (0 ms)
[ RUN      ] ReverseKGroupTest.KGreaterThanLength
[       OK ] ReverseKGroupTest.KGreaterThanLength (0 ms)
[----------] 5 tests from ReverseKGroupTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```
