#include <gtest/gtest.h>
#include "230-kth-smallest-element-in-a-bst.cpp"
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

TEST(KthSmallestTest, Example1) {
    Solution sol;
    // 输入: [3,1,4,-1,2], k=1
    TreeNode* root = createTree({3,1,4,-1,2});
    int k = 1;
    int expected = 1;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

TEST(KthSmallestTest, Example2) {
    Solution sol;
    // 输入: [5,3,6,2,4,-1,-1,1], k=3
    TreeNode* root = createTree({5,3,6,2,4,-1,-1,1});
    int k = 3;
    int expected = 3;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

TEST(KthSmallestTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    int k = 1;
    int expected = 1;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

TEST(KthSmallestTest, LeftSkewed) {
    Solution sol;
    // 输入: [3,2,-1,1], k=2
    TreeNode* root = createTree({3,2,-1,1});
    int k = 2;
    int expected = 2;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}