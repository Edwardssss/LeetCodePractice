#include <gtest/gtest.h>
#include "25-reverse-nodes-in-k-group.cpp"
#include <vector>

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

std::vector<int> listToVector(ListNode* head) {
    std::vector<int> res;
    while (head) {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

TEST(ReverseKGroupTest, SingleNode) {
    Solution sol;
    ListNode* head = createList({1});
    ListNode* res = sol.reverseKGroup(head, 2);
    std::vector<int> expected = {1};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KEquals1) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.reverseKGroup(head, 1);
    std::vector<int> expected = {1,2,3,4,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KEquals2) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.reverseKGroup(head, 2);
    std::vector<int> expected = {2,1,4,3,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KEquals3) {
    Solution sol;
    ListNode* head = createList({1,2,3,4,5});
    ListNode* res = sol.reverseKGroup(head, 3);
    std::vector<int> expected = {3,2,1,4,5};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(ReverseKGroupTest, KGreaterThanLength) {
    Solution sol;
    ListNode* head = createList({1,2});
    ListNode* res = sol.reverseKGroup(head, 3);
    std::vector<int> expected = {1,2};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
