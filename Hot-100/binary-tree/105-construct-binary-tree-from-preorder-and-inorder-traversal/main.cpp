#include <gtest/gtest.h>
#include "105-construct-binary-tree-from-preorder-and-inorder-traversal.cpp"
#include <vector>
#include <queue>

// 辅助函数：层序遍历展开树为数组，空节点用-1表示
std::vector<int> flattenToVector(TreeNode* root) {
    std::vector<int> res;
    std::queue<TreeNode*> q;
    if (!root) return res;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (node) {
            res.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        } else {
            res.push_back(-1);
        }
    }
    // 去除末尾多余的-1
    while (!res.empty() && res.back() == -1) res.pop_back();
    return res;
}

// 辅助函数：释放二叉树内存
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

TEST(BuildTreeTest, Example1) {
    Solution sol;
    std::vector<int> preorder = {3,9,20,15,7};
    std::vector<int> inorder = {9,3,15,20,7};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {3,9,20,-1,-1,15,7};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(BuildTreeTest, EmptyTree) {
    Solution sol;
    std::vector<int> preorder = {};
    std::vector<int> inorder = {};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(BuildTreeTest, SingleNode) {
    Solution sol;
    std::vector<int> preorder = {1};
    std::vector<int> inorder = {1};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {1};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(BuildTreeTest, CompleteTree) {
    Solution sol;
    std::vector<int> preorder = {1,2,4,5,3,6,7};
    std::vector<int> inorder = {4,2,5,1,6,3,7};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {1,2,3,4,5,6,7};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}