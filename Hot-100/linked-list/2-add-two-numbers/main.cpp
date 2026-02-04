#include <gtest/gtest.h>
#include "2-add-two-numbers.cpp"
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

TEST(AddTwoNumbersTest, Example1) {
    Solution sol;
    ListNode* l1 = createList({2,4,3});
    ListNode* l2 = createList({5,6,4});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {7,0,8};
    EXPECT_EQ(listToVector(res), expected);
}

TEST(AddTwoNumbersTest, CarryOver) {
    Solution sol;
    ListNode* l1 = createList({9,9,9,9,9,9,9});
    ListNode* l2 = createList({9,9,9,9});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {8,9,9,9,0,0,0,1};
    EXPECT_EQ(listToVector(res), expected);
}

TEST(AddTwoNumbersTest, SingleNode) {
    Solution sol;
    ListNode* l1 = createList({0});
    ListNode* l2 = createList({0});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {0};
    EXPECT_EQ(listToVector(res), expected);
}

TEST(AddTwoNumbersTest, DifferentLength) {
    Solution sol;
    ListNode* l1 = createList({1,8});
    ListNode* l2 = createList({0});
    ListNode* res = sol.addTwoNumbers(l1, l2);
    std::vector<int> expected = {1,8};
    EXPECT_EQ(listToVector(res), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
