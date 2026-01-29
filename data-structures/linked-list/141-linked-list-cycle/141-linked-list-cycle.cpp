/*
 * @lc app=leetcode.cn id=141 lang=cpp
 *
 * [141] 环形链表
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
    bool hasCycle(ListNode *head) {
        unordered_map<ListNode*, int> list_map;
        ListNode* cur = head;
        while (cur) {
            if(!list_map.count(cur)){
                list_map[cur] = cur->val;
            }
            else {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};
// @lc code=end
