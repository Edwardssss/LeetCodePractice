#include <gtest/gtest.h>
#include "21-merge-two-sorted-lists.cpp"
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

TEST(MergeTwoListsTest, Example1) {
    Solution sol;
    ListNode* l1 = createList({1,2,4});
    ListNode* l2 = createList({1,3,4});
    ListNode* res = sol.mergeTwoLists(l1, l2);
    std::vector<int> expected = {1,1,2,3,4,4};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(MergeTwoListsTest, OneEmpty) {
    Solution sol;
    ListNode* l1 = nullptr;
    ListNode* l2 = createList({0});
    ListNode* res = sol.mergeTwoLists(l1, l2);
    std::vector<int> expected = {0};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

TEST(MergeTwoListsTest, BothEmpty) {
    Solution sol;
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;
    ListNode* res = sol.mergeTwoLists(l1, l2);
    EXPECT_EQ(res, nullptr);
}

TEST(MergeTwoListsTest, DifferentLength) {
    Solution sol;
    ListNode* l1 = createList({2,5,7});
    ListNode* l2 = createList({1,3,4,6,8});
    ListNode* res = sol.mergeTwoLists(l1, l2);
    std::vector<int> expected = {1,2,3,4,5,6,7,8};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}