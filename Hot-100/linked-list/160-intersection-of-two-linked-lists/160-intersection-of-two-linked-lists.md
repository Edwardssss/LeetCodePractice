# 160. 相交链表

## 题目描述

160. 相交链表

给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 `null` 。

图示两个链表在节点 `c1` 开始相交：

![](./1.png)

题目数据 **保证** 整个链式结构中不存在环。

注意，函数返回结果后，链表必须 保持其原始结构 。

自定义评测：

评测系统 的输入如下（你设计的程序 **不适用** 此输入）：

- `intersectVal` - 相交的起始节点的值。如果不存在相交节点，这一值为 0
- `listA` - 第一个链表
- `listB` - 第二个链表
- `skipA` - 在 `listA` 中（从头节点开始）跳到交叉节点的节点数
- `skipB` - 在 `listB` 中（从头节点开始）跳到交叉节点的节点数

评测系统将根据这些输入创建链式数据结构，并将两个头节点 `headA` 和 `headB` 传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 **视作正确答案** 。

![](./2.png)

示例 1：

>  **输入**
>
> intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
>
>  **输出**
>
> Intersected at '8'
>
>  **解释**
>
> 相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
>
> 从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,6,1,8,4,5]。
>
> 在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
>
> 请注意相交节点的值不为 1，因为在链表 A 和链表 B 之中值为 1 的节点 (A 中第二个节点和 B 中第三个节点) 是不同的节点。换句话说，它们在内存中指向两个不同的位置，而链表 A 和链表 B 中值为 8 的节点 (A 中第三个节点，B 中第四个节点) 在内存中指向相同的位置。

![](./3.png)

示例 2：

>  **输入**
>
> intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
>
>  **输出**
>
> Intersected at '2'
>
>  **解释**
>
> 相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
>
> 从各自的表头开始算起，链表 A 为 [1,9,1,2,4]，链表 B 为 [3,2,4]。
>
> 在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。

![](./4.png)

示例 3：

>  **输入**
>
> intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
>
>  **输出**
>
> No intersection
>
>  **解释**
>
> 从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
>
> 由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
>
> 这两个链表不相交，因此返回 null。

提示：

- `listA` 中节点数目为 `m`
- `listB` 中节点数目为 `n`
- `1 <= m, n <= 3 * 104`
- `1 <= Node.val <= 105`
- `0 <= skipA <= m`
- `0 <= skipB <= n`
- 如果 `listA` 和 `listB` 没有交点，`intersectVal` 为 `0`
- 如果 `listA` 和 `listB` 有交点，`intersectVal == listA[skipA] == listB[skipB]`

进阶：你能否设计一个时间复杂度 $O(m + n)$ 、仅用 $O(1)$ 内存的解决方案？

## 思路分析

这道题我只想到了哈希表来进行一个节点映射，然后进行逐个对比。但是这个空间复杂度就是$O(m + n)$了。然后我又想到可以从链表尾部出发，也就是反转两个链表，但是题目要求不能改变原有的链表结构，所以这种方法也行不通。

LeetCode官方给出的方法是快慢指针法，两个指针在链表内部循环前进，最终会在相交处相遇。

只有当链表 `headA` 和 `headB` 都不为空时，两个链表才可能相交。因此首先判断链表 `headA` 和 `headB` 是否为空，如果其中至少有一个链表为空，则两个链表一定不相交，返回 `null`。

当链表 `headA` 和 `headB` 都不为空时，创建两个指针 `pA` 和 `pB`，初始时分别指向两个链表的头节点 `headA` 和 `headB`，然后将两个指针依次遍历两个链表的每个节点。具体做法如下：

- 每步操作需要同时更新指针 `pA` 和 `pB`。

- 如果指针 `pA` 不为空，则将指针 `pA` 移到下一个节点；如果指针 `pB` 不为空，则将指针 `pB` 移到下一个节点。

- 如果指针 `pA` 为空，则将指针 `pA` 移到链表 `headB` 的头节点；如果指针 `pB` 为空，则将指针 `pB` 移到链表 `headA` 的头节点。

- 当指针 `pA` 和 `pB` 指向同一个节点或者都为空时，返回它们指向的节点或者 `null`。

官方代码实现如下：

```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode *pA = headA, *pB = headB;
        while (pA != pB) {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> visited;
        ListNode *temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};
```

## 复杂度分析

- 哈希表

    - 时间复杂度：$O(m + n)$
    - 空间复杂度：$O(m)$

- 快慢指针

    - 时间复杂度：$O(m + n)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "160-intersection-of-two-linked-lists.cpp"
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

// 辅助函数：释放链表内存
void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

TEST(IntersectionTest, NoIntersection) {
    Solution sol;
    ListNode* headA = createList({1,2,3});
    ListNode* headB = createList({4,5,6});
    EXPECT_EQ(sol.getIntersectionNode(headA, headB), nullptr);
    freeList(headA);
    freeList(headB);
}

TEST(IntersectionTest, IntersectAtNode) {
    Solution sol;
    ListNode* common = createList({8,9});
    ListNode* headA = new ListNode(1);
    headA->next = new ListNode(2);
    headA->next->next = common;
    ListNode* headB = new ListNode(3);
    headB->next = common;
    EXPECT_EQ(sol.getIntersectionNode(headA, headB), common);
    // 只释放一次公共部分
    freeList(headA);
    delete headB; // headB->next已被freeList(headA)释放
}

TEST(IntersectionTest, SingleNodeIntersection) {
    Solution sol;
    ListNode* common = new ListNode(7);
    ListNode* headA = common;
    ListNode* headB = common;
    EXPECT_EQ(sol.getIntersectionNode(headA, headB), common);
    delete common;
}

TEST(IntersectionTest, EmptyLists) {
    Solution sol;
    EXPECT_EQ(sol.getIntersectionNode(nullptr, nullptr), nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：

```
[ RUN      ] IntersectionTest.NoIntersection
[       OK ] IntersectionTest.NoIntersection (0 ms)
[ RUN      ] IntersectionTest.IntersectAtNode
[       OK ] IntersectionTest.IntersectAtNode (0 ms)
[ RUN      ] IntersectionTest.SingleNodeIntersection
[       OK ] IntersectionTest.SingleNodeIntersection (0 ms)
[ RUN      ] IntersectionTest.EmptyLists
[       OK ] IntersectionTest.EmptyLists (0 ms)
[----------] 4 tests from IntersectionTest (2 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 4 tests.
```
