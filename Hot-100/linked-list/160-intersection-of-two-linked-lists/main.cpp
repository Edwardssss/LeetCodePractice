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