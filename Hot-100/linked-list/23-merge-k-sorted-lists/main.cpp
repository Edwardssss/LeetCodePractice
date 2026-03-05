#include <gtest/gtest.h>
#include "23-merge-k-sorted-lists.cpp"
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

TEST(MergeKListsTest, Example1) {
    Solution sol;
    std::vector<std::vector<int>> input = {{1,4,5},{1,3,4},{2,6}};
    std::vector<ListNode*> lists;
    for (const auto& arr : input) lists.push_back(createList(arr));
    ListNode* res = sol.mergeKLists(lists);
    std::vector<int> expected = {1,1,2,3,4,4,5,6};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
    // for (auto l : lists) freeList(l); // 移除这行
}

TEST(MergeKListsTest, AllEmpty) {
    Solution sol;
    std::vector<ListNode*> lists(3, nullptr);
    ListNode* res = sol.mergeKLists(lists);
    EXPECT_EQ(res, nullptr);
}

TEST(MergeKListsTest, SingleList) {
    Solution sol;
    std::vector<ListNode*> lists = {createList({1,2,3})};
    ListNode* res = sol.mergeKLists(lists);
    std::vector<int> expected = {1,2,3};
    EXPECT_EQ(listToVector(res), expected);
    freeList(res);
    // for (auto l : lists) freeList(l); // 移除这行
}

TEST(MergeKListsTest, EmptyInput) {
    Solution sol;
    std::vector<ListNode*> lists;
    ListNode* res = sol.mergeKLists(lists);
    EXPECT_EQ(res, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}