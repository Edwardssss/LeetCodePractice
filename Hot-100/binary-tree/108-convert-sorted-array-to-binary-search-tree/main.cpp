#include <gtest/gtest.h>
#include "108-convert-sorted-array-to-binary-search-tree.cpp"
#include <vector>

// 辅助函数：释放二叉树内存
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// 辅助函数：中序遍历二叉树，返回节点值
void inorder(TreeNode* root, std::vector<int>& res) {
    if (!root) return;
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

TEST(SortedArrayToBSTTest, Example1) {
    Solution sol;
    std::vector<int> nums = {-10,-3,0,5,9};
    TreeNode* root = sol.sortedArrayToBST(nums);
    std::vector<int> inorderRes;
    inorder(root, inorderRes);
    EXPECT_EQ(inorderRes, nums);
    freeTree(root);
}

TEST(SortedArrayToBSTTest, SingleNode) {
    Solution sol;
    std::vector<int> nums = {1};
    TreeNode* root = sol.sortedArrayToBST(nums);
    std::vector<int> inorderRes;
    inorder(root, inorderRes);
    EXPECT_EQ(inorderRes, nums);
    freeTree(root);
}

TEST(SortedArrayToBSTTest, EmptyArray) {
    Solution sol;
    std::vector<int> nums = {};
    TreeNode* root = sol.sortedArrayToBST(nums);
    EXPECT_EQ(root, nullptr);
}

TEST(SortedArrayToBSTTest, TwoNodes) {
    Solution sol;
    std::vector<int> nums = {1,2};
    TreeNode* root = sol.sortedArrayToBST(nums);
    std::vector<int> inorderRes;
    inorder(root, inorderRes);
    EXPECT_EQ(inorderRes, nums);
    freeTree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}