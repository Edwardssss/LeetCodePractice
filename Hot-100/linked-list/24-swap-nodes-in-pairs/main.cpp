#include <gtest/gtest.h>
#include "24-swap-nodes-in-pairs.cpp"
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

TEST(SwapPairsTest, Example1) {
    Solution sol;
    ListNode* head = createList({1,2,3,4});
    ListNode* res = sol.swapPairs(head);
    std::vector<int> expected = {2,1,4,3};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(SwapPairsTest, OddNodes) {
    Solution sol;
    ListNode* head = createList({1,2,3});
    ListNode* res = sol.swapPairs(head);
    std::vector<int> expected = {2,1,3};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(SwapPairsTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* res = sol.swapPairs(head);
    std::vector<int> expected = {1};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(SwapPairsTest, EmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    ListNode* res = sol.swapPairs(head);
    EXPECT_EQ(res, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}