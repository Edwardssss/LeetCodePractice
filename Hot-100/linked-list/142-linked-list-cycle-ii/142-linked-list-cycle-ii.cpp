/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;
        unordered_map<ListNode*, int> list_map;
        ListNode* cur = head;
        while(cur){
            if(!list_map.count(cur)){
                list_map[cur] = cur->val;
            }
            else {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }
};
// @lc code=end

