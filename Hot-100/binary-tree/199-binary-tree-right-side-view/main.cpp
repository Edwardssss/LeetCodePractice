#include <gtest/gtest.h>
#include "199-binary-tree-right-side-view.cpp"
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

TEST(RightSideViewTest, Example1) {
    Solution sol;
    // 输入: [1,2,3,-1,5,-1,4]
    TreeNode* root = createTree({1,2,3,-1,5,-1,4});
    std::vector<int> expected = {1,3,4};
    EXPECT_EQ(sol.rightSideView(root), expected);
    freeTree(root);
}

TEST(RightSideViewTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    std::vector<int> expected = {1};
    EXPECT_EQ(sol.rightSideView(root), expected);
    freeTree(root);
}

TEST(RightSideViewTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    std::vector<int> expected = {};
    EXPECT_EQ(sol.rightSideView(root), expected);
}

TEST(RightSideViewTest, CompleteTree) {
    Solution sol;
    // 完全二叉树 [1,2,3,4,5,6,7]
    TreeNode* root = createTree({1,2,3,4,5,6,7});
    std::vector<int> expected = {1,3,7};
    EXPECT_EQ(sol.rightSideView(root), expected);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}