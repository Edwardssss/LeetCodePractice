# 141. Linked List Cycle

## 题目描述

141. 环形链表

给你一个链表的头节点 `head` ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：`pos` 不作为参数进行传递 。仅仅是为了标识链表的实际情况。

如果链表中存在环 ，则返回 `true` 。 否则，返回 `false` 。

![](./1.png)

示例 1：

>  **输入**
>
> head = [3,2,0,-4], pos = 1
>
>  **输出**
>
> true
>
>  **解释**
>
> 链表中有一个环，其尾部连接到第二个节点。

![](./2.png)

示例 2：

>  **输入**
>
> head = [1,2], pos = 0
>
>  **输出**
>
> true
>
>  **解释**
>
> 链表中有一个环，其尾部连接到第一个节点。

![](./3.png)

示例 3：

>  **输入**
>
> head = [1], pos = -1
>
>  **输出**
>
> false
>
>  **解释**
>
> 链表中没有环。

提示：

- 链表中节点的数目范围是 `[0, 104]`
- `-105 <= Node.val <= 105`
- `pos` 为 `-1` 或者链表中的一个**有效索引** 。

进阶：你能用 $O(1)$（即，常量）内存解决此问题吗？

## 思路分析

这个题目的官方解法是快慢指针。我一开始想到了，但是我当时觉得时间复杂度是不是有点高，想着哈希表的搜索也就$O(1)$，所以用了哈希表的方法。

LeetCode官方题解如下所示：

```c++
class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
```

## 代码实现

代码实现如下：
```c++
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_map<ListNode*, int> list_map;
        ListNode* cur = head;
        while (cur) {
            if(!list_map.count(cur)){
                list_map[cur] = cur->val;
            }
            else {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};
```

## 复杂度分析

- 哈希表法：
    - 时间复杂度：$O(n)$，其中 $n$ 为链表长度。每个节点最多被访问一次。
    - 空间复杂度：$O(n)$，需要一个哈希表存储所有访问过的节点。

- 快慢指针：
    - 时间复杂度：$O(n)$，快慢指针最多遍历链表两遍。
    - 空间复杂度：$O(1)$，只使用了常数级别的指针。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "141-linked-list-cycle.cpp"
#include <vector>

// 辅助函数：根据数组和环位置创建链表
ListNode* createList(const std::vector<int>& vals, int pos, ListNode** cycleEntry = nullptr) {
    if (vals.empty()) return nullptr;
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    ListNode* entry = nullptr;
    for (int i = 0; i < vals.size(); ++i) {
        cur->next = new ListNode(vals[i]);
        cur = cur->next;
        if (i == pos) entry = cur;
    }
    if (pos >= 0) cur->next = entry;
    ListNode* head = dummy->next;
    delete dummy;
    if (cycleEntry) *cycleEntry = entry;
    return head;
}

// 辅助函数：释放链表（仅用于无环链表）
void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

TEST(HasCycleTest, EmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    EXPECT_FALSE(sol.hasCycle(head));
}

TEST(HasCycleTest, SingleNodeNoCycle) {
    Solution sol;
    ListNode* head = createList({1}, -1);
    EXPECT_FALSE(sol.hasCycle(head));
    freeList(head);
}

TEST(HasCycleTest, SingleNodeWithCycle) {
    Solution sol;
    ListNode* entry = nullptr;
    ListNode* head = createList({1}, 0, &entry);
    EXPECT_TRUE(sol.hasCycle(head));
    // 不能释放有环链表
}

TEST(HasCycleTest, NoCycle) {
    Solution sol;
    ListNode* head = createList({3,2,0,-4}, -1);
    EXPECT_FALSE(sol.hasCycle(head));
    freeList(head);
}

TEST(HasCycleTest, WithCycle) {
    Solution sol;
    ListNode* entry = nullptr;
    ListNode* head = createList({3,2,0,-4}, 1, &entry); // pos=1, 2处成环
    EXPECT_TRUE(sol.hasCycle(head));
    // 不能释放有环链表
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
[----------] 5 tests from HasCycleTest
[ RUN      ] HasCycleTest.EmptyList
[       OK ] HasCycleTest.EmptyList (0 ms)
[ RUN      ] HasCycleTest.SingleNodeNoCycle
[       OK ] HasCycleTest.SingleNodeNoCycle (0 ms)
[ RUN      ] HasCycleTest.SingleNodeWithCycle
[       OK ] HasCycleTest.SingleNodeWithCycle (0 ms)
[ RUN      ] HasCycleTest.NoCycle
[       OK ] HasCycleTest.NoCycle (0 ms)
[ RUN      ] HasCycleTest.WithCycle
[       OK ] HasCycleTest.WithCycle (0 ms)
[----------] 5 tests from HasCycleTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```