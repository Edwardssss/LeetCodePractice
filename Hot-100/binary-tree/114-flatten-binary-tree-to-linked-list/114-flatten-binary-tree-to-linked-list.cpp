/*
 * @lc app=leetcode.cn id=114 lang=cpp
 *
 * [114] 二叉树展开为链表
 */
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    queue<TreeNode*> node_queue;

    void pre_order(TreeNode* node){
        if(!node) return;
        this->node_queue.push(node);
        pre_order(node->left);
        pre_order(node->right);
    }

    void flatten(TreeNode* root) {
        if(!root) return;
        pre_order(root);
        TreeNode* cur_node = this->node_queue.front();
        node_queue.pop();
        while (!node_queue.empty()) {
            cur_node->left = nullptr;
            cur_node->right = node_queue.front();
            cur_node = node_queue.front();
            node_queue.pop();
        }
        cur_node->left = nullptr;
        cur_node->right = nullptr;
    }
};
// @lc code=end

