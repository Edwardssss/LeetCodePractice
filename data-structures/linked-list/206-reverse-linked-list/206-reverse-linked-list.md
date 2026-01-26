# 206. Reverse Linked List

## 题目描述

206. 反转链表

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

示例 1：

>  **输入**
>
> head = [1,2,3,4,5]
>
>  **输出**
>
> [5,4,3,2,1]

示例 2：

>  **输入**
>
> head = [1,2]
>
>  **输出**
>
> [2,1]

示例 3：

>  **输入**
>
> head = []
>
>  **输出**
>
> []

提示：

- 链表中节点的数目范围是 `[0, 5000]`
- `-5000 <= Node.val <= 5000`

进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？

## 思路分析

这道题难度是easy，我很快就想到了迭代法，然后AC了。但是我递归练习很少，写了一个版本的递归算法然后失败了，再看了答案之后发现还不是挺难的，可以当作一个蓝本来复习。

LeetCode官方给出的递归算法的解法如下所示：
``` c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
```

然后我看了一眼题解评论区，发现还有一种使用LIFO思想的解法，即使用栈来存储链表，也很有意思：

```c++
class Solution {
    public ListNode reverseList(ListNode head) {
        Deque<ListNode> stack = new LinkedList<>();
        // 哑节点，解决返回头节点为空的边界问题
        ListNode dump = new ListNode(-1);
        ListNode res = dump;
        while (null != head) {
            stack.push(head);
            head = head.next;
        }
        while (!stack.isEmpty()) {
            ListNode node = stack.pop();
            // 避免形成环
            node.next = null;
            dump.next = node;
            dump = dump.next;
        }
        return res.next;
    }
}
```

> 其实我一开始有用栈的想法，但是我看到这个最大链表长度为5000的时候有点退缩了，担心栈溢出的问题。目前看来是多想了。

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr){
            return nullptr;
        }
        ListNode* pre_node = nullptr;
        ListNode* cur_node = head;
        ListNode* next_node = head->next;
        while (next_node != nullptr) {
            cur_node->next = pre_node;
            pre_node = cur_node;
            cur_node = next_node;
            next_node = next_node->next;
        }
        cur_node->next = pre_node;
        return cur_node;
    }
};
```

## 复杂度分析

- 迭代法
    - 时间复杂度：$O(n)$，其中 $n$ 为链表长度。每个节点只遍历一次。
    - 空间复杂度：$O(1)$，只使用了常数级别的指针变量。

- 递归法
    - 时间复杂度：$O(n)$，每个节点只遍历一次。
    - 空间复杂度：$O(n)$，递归调用的栈空间，最坏情况下递归深度为链表长度。

- LIFO法（使用栈）
    - 时间复杂度：$O(n)$，每个节点入栈和出栈各一次。
    - 空间复杂度：$O(n)$，需要一个栈存储所有节点。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "206-reverse-linked-list.cpp"
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

TEST(ReverseListTest, EmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    ListNode* reversed = sol.reverseList(head);
    EXPECT_EQ(reversed, nullptr);
}

TEST(ReverseListTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* reversed = sol.reverseList(head);
    std::vector<int> expected = {1};
    EXPECT_EQ(listToVector(reversed), expected);
    freeList(reversed);
}

TEST(ReverseListTest, MultipleNodes) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* reversed = sol.reverseList(head);
    std::vector<int> expected = {5,4,3,2,1};
    EXPECT_EQ(listToVector(reversed), expected);
    freeList(reversed);
}

TEST(ReverseListTest, CustomNodes) {
    Solution sol;
    ListNode* head = createList({10,20,30});
    ListNode* reversed = sol.reverseList(head);
    std::vector<int> expected = {30,20,10};
    EXPECT_EQ(listToVector(reversed), expected);
    freeList(reversed);
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
[----------] 4 tests from ReverseListTest
[ RUN      ] ReverseListTest.EmptyList
[       OK ] ReverseListTest.EmptyList (0 ms)
[ RUN      ] ReverseListTest.SingleNode
[       OK ] ReverseListTest.SingleNode (0 ms)
[ RUN      ] ReverseListTest.MultipleNodes
[       OK ] ReverseListTest.MultipleNodes (0 ms)
[ RUN      ] ReverseListTest.CustomNodes
[       OK ] ReverseListTest.CustomNodes (0 ms)
[----------] 4 tests from ReverseListTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```