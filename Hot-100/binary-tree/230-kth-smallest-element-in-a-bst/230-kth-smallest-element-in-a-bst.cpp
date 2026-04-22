/*
 * @lc app=leetcode.cn id=230 lang=cpp
 *
 * [230] 二叉搜索树中第 K 小的元素
 */
#include <queue>
#include <vector>

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
    struct compare {
        bool operator()(int a, int b) {
            return a > b;
        }
    };

    int kthSmallest(TreeNode* root, int k) {
        priority_queue<int,vector<int>,compare> tree_priority_queue;
        queue<TreeNode*> tree_node_queue;
        tree_node_queue.push(root);
        while (!tree_node_queue.empty()) {
            if(tree_node_queue.front()->left) tree_node_queue.push(tree_node_queue.front()->left);
            if(tree_node_queue.front()->right) tree_node_queue.push(tree_node_queue.front()->right);
            tree_priority_queue.push(tree_node_queue.front()->val);
            tree_node_queue.pop();
        }
        while (--k) { tree_priority_queue.pop();}
        return tree_priority_queue.top();
    }
};
// @lc code=end

