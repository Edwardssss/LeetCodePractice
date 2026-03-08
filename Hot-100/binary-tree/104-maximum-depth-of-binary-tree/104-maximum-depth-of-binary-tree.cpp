/*
 * @lc app=leetcode.cn id=104 lang=cpp
 *
 * [104] 二叉树的最大深度
 */
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
#include <queue>

using namespace std;

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        int last_in_queue = 1;
        int now_in_queue = 0;
        int layer = 1;
        queue<TreeNode*> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            if(node_queue.front()->left){
                node_queue.push(node_queue.front()->left);
                ++now_in_queue;
            }
            if(node_queue.front()->right){
                node_queue.push(node_queue.front()->right);
                ++now_in_queue;
            }
            node_queue.pop();
            --last_in_queue;
            if(!last_in_queue){
                if(!now_in_queue) return layer;
                last_in_queue = now_in_queue;
                now_in_queue = 0;
                ++layer;
            }
        }
        return layer;
    }
};
// @lc code=end

