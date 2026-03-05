# 23. 合并 K 个升序链表

## 题目描述

23. 合并 K 个升序链表

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：

>  **输入**
>
> lists = [[1,4,5],[1,3,4],[2,6]]
>
>  **输出**
>
> [1,1,2,3,4,4,5,6]
>
>  **解释**
>
> 链表数组如下：
>
> [
>
>   1->4->5,
>
>   1->3->4,
>
>   2->6
>
> ]
>
> 将它们合并到一个有序链表中得到。
>
> 1->1->2->3->4->4->5->6

示例 2：

>  **输入**
>
> lists = []
>
>  **输出**
>
> []

示例 3：

>  **输入**
>
> lists = [[]]
>
>  **输出**
>
> []

提示：

- `k == lists.length`
- `0 <= k <= 10^4`
- `0 <= lists[i].length <= 500`
- `-10^4 <= lists[i][j] <= 10^4`
- `lists[i]` 按 升序 排列
- `lists[i].length` 的总和不超过 `10^4`

## 思路分析

这道题我还以为要用什么排序去做，然后想了一下，只想到了最小堆，然后看了下思路和官方的一模一样。

这里就额外提一下官方的分治法吧：

- 将 $k$ 个链表配对并将同一对中的链表合并
- 第一轮合并以后，k 个链表被合并成了$\frac k2$个链表，，然后是$\frac k4$个链表，$\frac k8$个链表等等；
- 重复这一过程，直到我们得到了最终的有序链表。

官方代码示例如下：

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* merge(vector <ListNode*> &lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    struct compare{
        bool operator()(ListNode* a, ListNode* b) {
            return (a->val) > (b->val);
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return {};
        priority_queue<ListNode*, vector<ListNode*>, compare> list_queue;
        ListNode dummy(0,nullptr);
        ListNode* cur = &dummy;
        for(auto i:lists){
            if(i) list_queue.push(i);
        }
        while (!list_queue.empty()) {
            cur->next = list_queue.top();
            cur = cur->next;
            list_queue.pop();
            if (cur->next) {
                list_queue.push(cur->next);
            }
        }
        return dummy.next;
    }
};
```

## 复杂度分析

- 最小堆

    - 时间复杂度：$O(kn\log k)$
    - 空间复杂度：$O(1)$

- 分治法

    - 时间复杂度：$O(kn\log k)$
    - 空间复杂度：$O(\log k)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "23-merge-k-sorted-lists.cpp"
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

TEST(MergeKListsTest, Example1) {
    Solution sol;
    std::vector<std::vector<int>> input = {{1,4,5},{1,3,4},{2,6}};
    std::vector<ListNode*> lists;
    for (const auto& arr : input) lists.push_back(createList(arr));
    ListNode* res = sol.mergeKLists(lists);
    std::vector<int> expected = {1,1,2,3,4,4,5,6};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
    // for (auto l : lists) freeList(l); // 移除这行
}

TEST(MergeKListsTest, AllEmpty) {
    Solution sol;
    std::vector<ListNode*> lists(3, nullptr);
    ListNode* res = sol.mergeKLists(lists);
    EXPECT_EQ(res, nullptr);
}

TEST(MergeKListsTest, SingleList) {
    Solution sol;
    std::vector<ListNode*> lists = {createList({1,2,3})};
    ListNode* res = sol.mergeKLists(lists);
    std::vector<int> expected = {1,2,3};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
    // for (auto l : lists) freeList(l); // 移除这行
}

TEST(MergeKListsTest, EmptyInput) {
    Solution sol;
    std::vector<ListNode*> lists;
    ListNode* res = sol.mergeKLists(lists);
    EXPECT_EQ(res, nullptr);
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
[----------] 4 tests from MergeKListsTest
[ RUN      ] MergeKListsTest.Example1
[       OK ] MergeKListsTest.Example1 (0 ms)
[ RUN      ] MergeKListsTest.AllEmpty
[       OK ] MergeKListsTest.AllEmpty (0 ms)
[ RUN      ] MergeKListsTest.SingleList
[       OK ] MergeKListsTest.SingleList (0 ms)
[ RUN      ] MergeKListsTest.EmptyInput
[       OK ] MergeKListsTest.EmptyInput (0 ms)
[----------] 4 tests from MergeKListsTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```
