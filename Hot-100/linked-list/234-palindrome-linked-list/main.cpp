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