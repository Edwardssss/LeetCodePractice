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
