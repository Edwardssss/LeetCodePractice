/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
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
#include <queue>

using namespace std;

class Solution {
public:
    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return (a->val) > (b->val);
        }
    };

    ListNode* sortList(ListNode* head) {
        if(!head) return nullptr;
        priority_queue<ListNode*, vector<ListNode*>, compare> list_queue;
        ListNode dummy_node;
        ListNode* cur = head;
        dummy_node.next = head;
        while (cur) {
            list_queue.push(cur);
            cur = cur->next;
        }
        cur = &dummy_node;
        while(!list_queue.empty()){
            cur->next = list_queue.top();
            list_queue.pop();
            cur = cur->next;
        }
        cur->next = nullptr;
        return dummy_node.next;
    }
};
// @lc code=end

