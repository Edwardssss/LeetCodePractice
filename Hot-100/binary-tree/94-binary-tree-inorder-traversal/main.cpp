#include <gtest/gtest.h>
#include "94-binary-tree-inorder-traversal.cpp"
#include <vector>

// 辅助函数：根据数组和下标递归构建完全二叉树（nullptr用-1表示）
TreeNode* createTree(const std::vector<int>& vals, int idx = 0) {
    if (idx >= vals.size() || vals[idx] == -1) return nullptr;
    TreeNode* root = new TreeNode(vals[idx]);
    root->left = createTree(vals, 2 * idx + 1);
    root->right = createTree(vals, 2 * idx + 2);
    return root;
}

// 辅助函数：释放二叉树内存
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

TEST(InorderTraversalTest, Example1) {
    Solution sol;
    // 输入: [1,null,2,3]，层序为[1,-1,2,-1,-1,3]
    TreeNode* root = createTree({1,-1,2,-1,-1,3});
    std::vector<int> expected = {1,3,2};
    EXPECT_EQ(sol.inorderTraversal(root), expected);
    freeTree(root);
}

TEST(InorderTraversalTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    std::vector<int> expected = {1};
    EXPECT_EQ(sol.inorderTraversal(root), expected);
    freeTree(root);
}

TEST(InorderTraversalTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    std::vector<int> expected = {};
    EXPECT_EQ(sol.inorderTraversal(root), expected);
}

TEST(InorderTraversalTest, CompleteTree) {
    Solution sol;
    // 完全二叉树 [1,2,3,4,5,6,7]
    TreeNode* root = createTree({1,2,3,4,5,6,7});
    std::vector<int> expected = {4,2,5,1,6,3,7};
    EXPECT_EQ(sol.inorderTraversal(root), expected);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}