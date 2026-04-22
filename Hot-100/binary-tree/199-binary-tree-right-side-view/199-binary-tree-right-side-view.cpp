/*
 * @lc app=leetcode.cn id=199 lang=cpp
 *
 * [199] 二叉树的右视图
 */
#include <vector>
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
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return {};
        vector<int> result;
        queue<TreeNode*> node_queue;
        node_queue.push(root);
        int cnt = 0;
        int pre_cnt = 1;
        bool first_flag = true;
        while (!node_queue.empty()) {
            TreeNode* node = node_queue.front();
            node_queue.pop();
            if (first_flag) {
                result.push_back(node->val);
                first_flag = false;
            }
            if(node->right){
                node_queue.push(node->right);
                ++cnt;
            }
            if(node->left){
                node_queue.push(node->left);
                ++cnt;
            }
            --pre_cnt;
            if(!pre_cnt){
                pre_cnt = cnt;
                cnt = 0;
                first_flag = true;
            }
        }
        return result;
    }
};
// @lc code=end
