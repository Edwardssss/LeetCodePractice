/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
 */

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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!(l1->val || l2->val) && !((l1->next) || (l2->next))) return new ListNode(0,nullptr);
        if(!(l1->val) && !(l1->next)) return l2;
        if(!(l2->val) && !(l2->next)) return l1;
        bool add_flag = false;
        ListNode* result_head = new ListNode();
        ListNode* result = result_head;
        ListNode* l1_cur = l1;
        ListNode* l2_cur = l2;
        int l1_value;
        int l2_value;
        while(l1_cur || l2_cur || add_flag){
            if(!l1_cur){
                l1_value = 0;
            }
            else{
                l1_value = l1_cur->val;
                l1_cur = l1_cur->next;
            }
            if(!l2_cur){
                l2_value = 0;
            }
            else{
                l2_value = l2_cur->val;
                l2_cur = l2_cur->next;
            }
            if(l1_value + l2_value + add_flag > 9){
                result->val = l1_value + l2_value + add_flag - 10;
                add_flag = true;
            }
            else{
                result->val = l1_value + l2_value + add_flag;
                add_flag = false;
            }
            if(l1_cur || l2_cur || add_flag){
                result->next = new ListNode();
                result = result->next;
            }
        }
        return result_head;
    }
};
// @lc code=end

