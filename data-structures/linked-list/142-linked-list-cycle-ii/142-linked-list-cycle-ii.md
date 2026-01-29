# 142. Linked List Cycle II

## 题目描述

142. 环形链表 II

给定一个链表的头节点`head` ，返回链表开始入环的第一个节点。 如果链表无环，则返回 `null`。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 `pos` 是 `-1`，则在该链表中没有环。注意：`pos` 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改**链表**。

![](./1.png)

示例 1：

>  **输入**
>
> head = [3,2,0,-4], pos = 1
>
>  **输出**
>
> 返回索引为 1 的链表节点
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
> 返回索引为 0 的链表节点
>
>  **解释**链表中有一个环，其尾部连接到第一个节点。

![](./3.png)

示例 3：

>  **输入**
>
> head = [1], pos = -1
>
>  **输出**
>
> 返回 null
>
>  **解释**
>
> 链表中没有环。

提示：

- 链表中节点的数目范围在范围 `[0, 104]` 内
- `-105 <= Node.val <= 105`
- `pos` 的值为 `-1` 或者链表中的一个有效索引

进阶：你是否可以使用 $O(1)$ 空间解决此题？

## 思路分析

这道题是141题的升级版，之前的141题只需要判断环是否存在，这道题就需要找到环的起点了。我用了和141题一模一样的代码，仍然是AC了，不过LeetCode官方的题解还是有必要学习一下的。

LeetCode官方题解如下：

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr) {
            slow = slow->next;
            if (fast->next == nullptr) {
                return nullptr;
            }
            fast = fast->next->next;
            if (fast == slow) {
                ListNode *ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};
```

使用两个指针，`fast` 与 `slow`。它们起始都位于链表的头部。随后，`slow` 指针每次向后移动一个位置，而 `fast` 指针向后移动两个位置。如果链表中存在环，则 `fast` 指针最终将再次与 `slow` 指针在环中相遇。

如下图所示，设链表中环外部分的长度为 $a$。`slow` 指针进入环后，又走了 $b$ 的距离与 `fast` 相遇。此时，`fast` 指针已经走完了环的$n$ 圈，因此它走过的总距离为 $a+n(b+c)+b=a+(n+1)b+nc$。

根据题意，任意时刻，`fast` 指针走过的距离都为 `slow` 指针的 $2$ 倍。因此，我们有

$$
a+(n+1)b+nc=2(a+b)⟹a=c+(n−1)(b+c)
$$

有了 $a=c+(n−1)(b+c)$ 的等量关系，我们会发现：从相遇点到入环点的距离加上 $n−1$ 圈的环长，恰好等于从链表头部到入环点的距离。

因此，当发现 `slow` 与 `fast` 相遇时，我们再额外使用一个指针 `ptr`。起始，它指向链表头部；随后，它和 `slow` 每次向后移动一个位置。最终，它们会在入环点相遇。

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
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;
        unordered_map<ListNode*, int> list_map;
        ListNode* cur = head;
        while(cur){
            if(!list_map.count(cur)){
                list_map[cur] = cur->val;
            }
            else {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }
};
```

## 复杂度分析

- 哈希表法：
    - 时间复杂度：$O(n)$，其中 $n$ 为链表长度。每个节点最多被访问一次。
    - 空间复杂度：$O(n)$，需要一个哈希表存储所有访问过的节点。

- 快慢指针：
    - 时间复杂度：$O(n)$，快慢指针最多遍历链表两遍。
    - 空间复杂度：$O(1)$，只使用了三个指针。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "142-linked-list-cycle-ii.cpp"
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

TEST(DetectCycleTest, EmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    EXPECT_EQ(sol.detectCycle(head), nullptr);
}

TEST(DetectCycleTest, SingleNodeNoCycle) {
    Solution sol;
    ListNode* head = createList({1}, -1);
    EXPECT_EQ(sol.detectCycle(head), nullptr);
    freeList(head);
}

TEST(DetectCycleTest, SingleNodeWithCycle) {
    Solution sol;
    ListNode* entry = nullptr;
    ListNode* head = createList({1}, 0, &entry);
    EXPECT_EQ(sol.detectCycle(head), entry);
    // 不能释放有环链表
}

TEST(DetectCycleTest, NoCycle) {
    Solution sol;
    ListNode* head = createList({3,2,0,-4}, -1);
    EXPECT_EQ(sol.detectCycle(head), nullptr);
    freeList(head);
}

TEST(DetectCycleTest, WithCycle) {
    Solution sol;
    ListNode* entry = nullptr;
    ListNode* head = createList({3,2,0,-4}, 1, &entry); // pos=1, 2处成环
    EXPECT_EQ(sol.detectCycle(head), entry);
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
[----------] 5 tests from DetectCycleTest
[ RUN      ] DetectCycleTest.EmptyList
[       OK ] DetectCycleTest.EmptyList (0 ms)
[ RUN      ] DetectCycleTest.SingleNodeNoCycle
[       OK ] DetectCycleTest.SingleNodeNoCycle (0 ms)
[ RUN      ] DetectCycleTest.SingleNodeWithCycle
[       OK ] DetectCycleTest.SingleNodeWithCycle (0 ms)
[ RUN      ] DetectCycleTest.NoCycle
[       OK ] DetectCycleTest.NoCycle (0 ms)
[ RUN      ] DetectCycleTest.WithCycle
[       OK ] DetectCycleTest.WithCycle (0 ms)
[----------] 5 tests from DetectCycleTest (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.
```
