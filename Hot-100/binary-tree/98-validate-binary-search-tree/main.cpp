#include <gtest/gtest.h>
#include "98-validate-binary-search-tree.cpp"
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

TEST(IsValidBSTTest, Example1) {
    Solution sol;
    // 输入: [2,1,3]
    TreeNode* root = createTree({2,1,3});
    EXPECT_TRUE(sol.isValidBST(root));
    freeTree(root);
}

TEST(IsValidBSTTest, NotBST) {
    Solution sol;
    // 输入: [5,1,4,-1,-1,3,6]
    TreeNode* root = createTree({5,1,4,-1,-1,3,6});
    EXPECT_FALSE(sol.isValidBST(root));
    freeTree(root);
}

TEST(IsValidBSTTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    EXPECT_TRUE(sol.isValidBST(root));
    freeTree(root);
}

TEST(IsValidBSTTest, DuplicateValue) {
    Solution sol;
    // 输入: [1,1]
    TreeNode* root = createTree({1,1});
    EXPECT_FALSE(sol.isValidBST(root));
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}