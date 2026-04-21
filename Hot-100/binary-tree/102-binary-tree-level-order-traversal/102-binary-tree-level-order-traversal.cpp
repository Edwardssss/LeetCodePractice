/*
 * @lc app=leetcode.cn id=102 lang=cpp
 *
 * [102] 二叉树的层序遍历
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

    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> result = {};
        queue<TreeNode*> pipe = {};
        pipe.push(root);
        int pre_cnt = 1;
        int cnt = 0;
        vector<int> layer_storage = {};
        while (!pipe.empty()) {
            TreeNode* node = pipe.front();
            pipe.pop();
            layer_storage.push_back(node->val);
            if (node->left) {
                pipe.push(node->left);
                ++cnt;
            }
            if (node->right) {
                pipe.push(node->right);
                ++cnt;
            }
            --pre_cnt;
            if (pre_cnt == 0) {
                result.push_back(layer_storage);
                layer_storage.clear();
                pre_cnt = cnt;
                cnt = 0;
            }
        }
        return result;
    }
};
// @lc code=end

