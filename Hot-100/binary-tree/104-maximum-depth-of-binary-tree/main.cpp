#include <gtest/gtest.h>
#include "104-maximum-depth-of-binary-tree.cpp"
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

TEST(MaxDepthTest, Example1) {
    Solution sol;
    // [3,9,20,null,null,15,7] 层序为 [3,9,20,-1,-1,15,7]
    TreeNode* root = createTree({3,9,20,-1,-1,15,7});
    EXPECT_EQ(sol.maxDepth(root), 3);
    freeTree(root);
}

TEST(MaxDepthTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    EXPECT_EQ(sol.maxDepth(root), 1);
    freeTree(root);
}

TEST(MaxDepthTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    EXPECT_EQ(sol.maxDepth(root), 0);
}

TEST(MaxDepthTest, CompleteTree) {
    Solution sol;
    // 完全二叉树 [1,2,3,4,5,6,7]
    TreeNode* root = createTree({1,2,3,4,5,6,7});
    EXPECT_EQ(sol.maxDepth(root), 3);
    freeTree(root);
}

TEST(MaxDepthTest, LeftSkewed) {
    Solution sol;
    // 手动构建左斜树 1->2->3->4
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    EXPECT_EQ(sol.maxDepth(root), 4);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}