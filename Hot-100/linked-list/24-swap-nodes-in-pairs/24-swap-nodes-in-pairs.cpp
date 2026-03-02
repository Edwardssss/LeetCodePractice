/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head) return head;
        ListNode dummy_node(0,head);
        ListNode* pre_cur = &dummy_node;
        ListNode* cur_1 = head;
        while (cur_1 && cur_1->next) {
            ListNode* cur_2 = cur_1->next;
            pre_cur->next = cur_2;
            cur_1->next = cur_2->next;
            cur_2->next = cur_1;
            pre_cur = cur_1;
            cur_1 = cur_1->next;
        }
        return dummy_node.next;
    }
};
// @lc code=end

