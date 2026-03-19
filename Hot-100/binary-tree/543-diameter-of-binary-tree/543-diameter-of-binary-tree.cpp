/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
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
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDiameter = 0;
    int distance_from_root(TreeNode * node){
        if (!node) return 0;
        int left = distance_from_root(node->left);
        int right = distance_from_root(node->right);
        if (left + right > maxDiameter) maxDiameter = left + right;
        return std::max(left, right) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        distance_from_root(root);
        return maxDiameter;
    }
};
// @lc code=end

