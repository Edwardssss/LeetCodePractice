# 234. 回文链表

## 题目描述

234. 回文链表

给你一个单链表的头节点 `head` ，请你判断该链表是否为回文链表。如果是，返回 `true` ；否则，返回 `false` 。

![](./1.jpg)

示例 1：

>  **输入**
>
> head = [1,2,2,1]
>
>  **输出**
>
> true

![](./2.jpg)

示例 2：

>  **输入**
>
> head = [1,2]
>
>  **输出**
>
> false

提示：

- 链表中节点数目在范围`[1, 105]`内
- `0 <= Node.val <= 9`

进阶：你能否用 $O(n)$ 时间复杂度和 $O(1)$ 空间复杂度解决此题？

## 思路分析

回文的意思就是从左往右和从右往左读的结果是一样的，那么我第一时间想到的就是反转链表。当链表反转之后，反转的结果和原链表读起来应该是一样的。但是又有一个新问题：链表反转之后，原链表的顺序也不存在了，那么就需要一个折中的办法：从链表的中间开始反转后半段，然后读取的结果应该是一样的。

LeetCode官方给出了基于数组+双指针的方法，虽然方法很朴素且无法满足进阶要求，但是不得不承认这个解法的速度比我那种方法要快。

官方示例代码如下所示：

```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vals;
        while (head != nullptr) {
            vals.emplace_back(head->val);
            head = head->next;
        }
        for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j) {
            if (vals[i] != vals[j]) {
                return false;
            }
        }
        return true;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* secondHalf = reverseList(slow->next);
        ListNode* p1 = head;
        ListNode* p2 = secondHalf;

        bool result = true;
        while (result && p2) {
            if (p1->val != p2->val) {
                result = false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return result;
    }

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

## 复杂度分析

- 数组+双指针

    - 时间复杂度：$O(n)$
    - 空间复杂度：$O(n)$

- 反转链表

    - 时间复杂度：$O(n)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "234-palindrome-linked-list.cpp"
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

TEST(PalindromeListTest, EmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    EXPECT_TRUE(sol.isPalindrome(head));
}

TEST(PalindromeListTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    EXPECT_TRUE(sol.isPalindrome(head));
    freeList(head);
}

TEST(PalindromeListTest, EvenPalindrome) {
    Solution sol;
    ListNode* head = createList({1,2,2,1});
    EXPECT_TRUE(sol.isPalindrome(head));
    freeList(head);
}

TEST(PalindromeListTest, OddPalindrome) {
    Solution sol;
    ListNode* head = createList({1,2,3,2,1});
    EXPECT_TRUE(sol.isPalindrome(head));
    freeList(head);
}

TEST(PalindromeListTest, NotPalindrome) {
    Solution sol;
    ListNode* head = createList({1,2,3,4});
    EXPECT_FALSE(sol.isPalindrome(head));
    freeList(head);
}

TEST(PalindromeListTest, TwoNodesNotPalindrome) {
    Solution sol;
    ListNode* head = createList({1,2});
    EXPECT_FALSE(sol.isPalindrome(head));
    freeList(head);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from PalindromeListTest
[ RUN      ] PalindromeListTest.EmptyList
[       OK ] PalindromeListTest.EmptyList (0 ms)
[ RUN      ] PalindromeListTest.SingleNode
[       OK ] PalindromeListTest.SingleNode (0 ms)
[ RUN      ] PalindromeListTest.EvenPalindrome
[       OK ] PalindromeListTest.EvenPalindrome (0 ms)       
[ RUN      ] PalindromeListTest.OddPalindrome
[       OK ] PalindromeListTest.OddPalindrome (0 ms)        
[ RUN      ] PalindromeListTest.NotPalindrome
[       OK ] PalindromeListTest.NotPalindrome (0 ms)        
[ RUN      ] PalindromeListTest.TwoNodesNotPalindrome       
[       OK ] PalindromeListTest.TwoNodesNotPalindrome (0 ms)
[----------] 6 tests from PalindromeListTest (4 ms total)   

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (7 ms total)    
[  PASSED  ] 6 tests.
```
