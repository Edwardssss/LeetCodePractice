# 148. Sort List

## 题目描述

148. 排序链表

给你链表的头结点 `head` ，请将其按 **升序** 排列并返回 **排序后的链表** 。

示例 1：

>  **输入**
>
> head = [4,2,1,3]
>
>  **输出**
>
> [1,2,3,4]

示例 2：

>  **输入**
>
> head = [-1,5,3,4,0]
>
>  **输出**
>
> [-1,0,3,4,5]

示例 3：

>  **输入**
>
> head = []
>
>  **输出**
>
> []

提示：

- 链表中节点的数目在范围 `[0, 5 * 104]` 内
- `-105 <= Node.val <= 105`

进阶：你可以在 $O(n log n)$ 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

## 思路分析

这道题我想到了用排序算法，但是我不太会排序算法了，只记得冒泡排序，而这用处不大。所以我很自然的想到了使用一个最小堆去做，也就是`priority_queue`。

LeetCode官方使用了两种归并排序去做的：一种是自顶向下归并排序，一种是自底向上归并排序。

自顶向下归并排序的代码如下所示：

```c++
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return sortList(head, nullptr);
    }

    ListNode* sortList(ListNode* head, ListNode* tail) {
        if (head == nullptr) {
            return head;
        }
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }
        ListNode* slow = head, *fast = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }
        ListNode* mid = slow;
        return merge(sortList(head, mid), sortList(mid, tail));
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* temp = dummyHead, *temp1 = head1, *temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
};
```

自底向上归并排序的代码如下所示：

```c++
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        int length = 0;
        ListNode* node = head;
        while (node != nullptr) {
            length++;
            node = node->next;
        }
        ListNode* dummyHead = new ListNode(0, head);
        for (int subLength = 1; subLength < length; subLength <<= 1) {
            ListNode* prev = dummyHead, *curr = dummyHead->next;
            while (curr != nullptr) {
                ListNode* head1 = curr;
                for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                ListNode* head2 = curr->next;
                curr->next = nullptr;
                curr = head2;
                for (int i = 1; i < subLength && curr != nullptr && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                ListNode* next = nullptr;
                if (curr != nullptr) {
                    next = curr->next;
                    curr->next = nullptr;
                }
                ListNode* merged = merge(head1, head2);
                prev->next = merged;
                while (prev->next != nullptr) {
                    prev = prev->next;
                }
                curr = next;
            }
        }
        return dummyHead->next;
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* temp = dummyHead, *temp1 = head1, *temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <queue>

using namespace std;

class Solution {
public:
    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return (a->val) > (b->val);
        }
    };

    ListNode* sortList(ListNode* head) {
        if(!head) return nullptr;
        priority_queue<ListNode*, vector<ListNode*>, compare> list_queue;
        ListNode dummy_node;
        ListNode* cur = head;
        dummy_node.next = head;
        while (cur) {
            list_queue.push(cur);
            cur = cur->next;
        }
        cur = &dummy_node;
        while(!list_queue.empty()){
            cur->next = list_queue.top();
            list_queue.pop();
            cur = cur->next;
        }
        cur->next = nullptr;
        return dummy_node.next;
    }
};
```


## 复杂度分析

- 自顶向下归并排序
    - 时间复杂度：$O(n \log n)$，其中 $n$ 是链表的长度。
    - 空间复杂度：$O(\log n)$，主要取决于递归调用的栈空间。

- 自底向上归并排序
    - 时间复杂度：$O(n \log n)$，其中 $n$ 是链表的长度。
    - 空间复杂度：$O(1)$。

- 最小堆方法
    - 时间复杂度：$O(n \log n)$。遍历链表将所有节点入堆需要 $O(n \log n)$，每次弹出堆顶元素重建堆也需要 $O(n \log n)$，总共 $2n$ 次操作，故为 $O(n \log n)$。
    - 空间复杂度：$O(n)$。需要一个优先队列（最小堆）存储所有链表节点的指针，空间随节点数线性增长。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "148-sort-list.cpp"
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

TEST(SortListTest, Example1) {
    Solution sol;
    ListNode* head = createList({4,2,1,3});
    ListNode* res = sol.sortList(head);
    std::vector<int> expected = {1,2,3,4};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(SortListTest, Example2) {
    Solution sol;
    ListNode* head = createList({-1,5,3,4,0});
    ListNode* res = sol.sortList(head);
    std::vector<int> expected = {-1,0,3,4,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(SortListTest, EmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    ListNode* res = sol.sortList(head);
    EXPECT_EQ(res, nullptr);
}

TEST(SortListTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* res = sol.sortList(head);
    std::vector<int> expected = {1};
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
[----------] 4 tests from SortListTest
[ RUN      ] SortListTest.Example1
[       OK ] SortListTest.Example1 (0 ms)
[ RUN      ] SortListTest.Example2
[       OK ] SortListTest.Example2 (0 ms)
[ RUN      ] SortListTest.EmptyList
[       OK ] SortListTest.EmptyList (0 ms)
[ RUN      ] SortListTest.SingleNode
[       OK ] SortListTest.SingleNode (0 ms)
[----------] 4 tests from SortListTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```
