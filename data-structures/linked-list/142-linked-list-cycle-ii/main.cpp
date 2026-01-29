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
