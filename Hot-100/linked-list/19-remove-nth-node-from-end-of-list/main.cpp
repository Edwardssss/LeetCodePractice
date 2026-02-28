#include <gtest/gtest.h>
#include "19-remove-nth-node-from-end-of-list.cpp"
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

TEST(RemoveNthFromEndTest, Example1) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.removeNthFromEnd(head, 2);
    std::vector<int> expected = {1,2,3,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(RemoveNthFromEndTest, RemoveHead) {
    Solution sol;
    ListNode* head = createList({1,2});
    ListNode* res = sol.removeNthFromEnd(head, 2);
    std::vector<int> expected = {2};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(RemoveNthFromEndTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* res = sol.removeNthFromEnd(head, 1);
    EXPECT_EQ(res, nullptr);
}

TEST(RemoveNthFromEndTest, RemoveLast) {
    Solution sol;
    ListNode* head = createList({1,2,3});
    ListNode* res = sol.removeNthFromEnd(head, 1);
    std::vector<int> expected = {1,2};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}