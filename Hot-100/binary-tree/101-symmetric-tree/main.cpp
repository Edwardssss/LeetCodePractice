#include <gtest/gtest.h>
#include "101-symmetric-tree.cpp"
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

TEST(SymmetricTreeTest, Example1) {
    Solution sol;
    // 输入: [1,2,2,3,4,4,3] 是对称的
    TreeNode* root = createTree({1,2,2,3,4,4,3});
    EXPECT_TRUE(sol.isSymmetric(root));
    freeTree(root);
}

TEST(SymmetricTreeTest, NotSymmetric) {
    Solution sol;
    // 输入: [1,2,2,-1,3,-1,3] 不是对称的
    TreeNode* root = createTree({1,2,2,-1,3,-1,3});
    EXPECT_FALSE(sol.isSymmetric(root));
    freeTree(root);
}

TEST(SymmetricTreeTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    EXPECT_TRUE(sol.isSymmetric(root));
    freeTree(root);
}

TEST(SymmetricTreeTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    EXPECT_TRUE(sol.isSymmetric(root));
}

TEST(SymmetricTreeTest, LeftSkewed) {
    Solution sol;
    // 手动构建左斜树 1->2->3
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    EXPECT_FALSE(sol.isSymmetric(root));
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}