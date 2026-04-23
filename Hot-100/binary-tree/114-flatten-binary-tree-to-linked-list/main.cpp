#include <gtest/gtest.h>
#include "114-flatten-binary-tree-to-linked-list.cpp"
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
    freeTree(root->right); // 展开后只需递归右子树
    delete root;
}

// 辅助函数：展开后链表转vector
std::vector<int> flattenToVector(TreeNode* root) {
    std::vector<int> res;
    while (root) {
        res.push_back(root->val);
        if (root->left) break; // 展开后不应有左子树
        root = root->right;
    }
    return res;
}

TEST(FlattenTest, Example1) {
    Solution sol;
    // 输入: [1,2,5,3,4,-1,6]
    TreeNode* root = createTree({1,2,5,3,4,-1,6});
    sol.flatten(root);
    std::vector<int> expected = {1,2,3,4,5,6};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(FlattenTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    sol.flatten(root);
    std::vector<int> expected = {1};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(FlattenTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    sol.flatten(root);
    std::vector<int> expected = {};
    EXPECT_EQ(flattenToVector(root), expected);
}

TEST(FlattenTest, LeftSkewed) {
    Solution sol;
    // 输入: [1,2,-1,3]
    TreeNode* root = createTree({1,2,-1,3});
    sol.flatten(root);
    std::vector<int> expected = {1,2,3};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}