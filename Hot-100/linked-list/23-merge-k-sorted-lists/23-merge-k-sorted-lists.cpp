/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
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
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    struct compare{
        bool operator()(ListNode* a, ListNode* b) {
            return (a->val) > (b->val);
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return {};
        priority_queue<ListNode*, vector<ListNode*>, compare> list_queue;
        ListNode dummy(0,nullptr);
        ListNode* cur = &dummy;
        for(auto i:lists){
            if(i) list_queue.push(i);
        }
        while (!list_queue.empty()) {
            cur->next = list_queue.top();
            cur = cur->next;
            list_queue.pop();
            if (cur->next) {
                list_queue.push(cur->next);
            }
        }
        return dummy.next;
    }
};
// @lc code=end

