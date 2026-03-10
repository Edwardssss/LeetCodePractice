#include <gtest/gtest.h>
#include "226-invert-binary-tree.cpp"
#include <vector>

// 辅助函数：根据数组和下标递归构建完全二叉树（nullptr用-1表示）
TreeNode* createTree(const std::vector<int>& vals, int idx = 0) {
    if (idx >= vals.size() || vals[idx] == -1) return nullptr;
    TreeNode* root = new TreeNode(vals[idx]);
    root->left = createTree(vals, 2 * idx + 1);
    root->right = createTree(vals, 2 * idx + 2);
    return root;
}

// 辅助函数：层序遍历输出二叉树
std::vector<int> levelOrder(TreeNode* root) {
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

TEST(InvertTreeTest, Example1) {
    Solution sol;
    // 输入: [4,2,7,1,3,6,9]，翻转后: [4,7,2,9,6,3,1]
    TreeNode* root = createTree({4,2,7,1,3,6,9});
    TreeNode* inverted = sol.invertTree(root);
    std::vector<int> expected = {4,7,2,9,6,3,1};
    EXPECT_EQ(levelOrder(inverted), expected);
    freeTree(inverted);
}

TEST(InvertTreeTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    TreeNode* inverted = sol.invertTree(root);
    std::vector<int> expected = {1};
    EXPECT_EQ(levelOrder(inverted), expected);
    freeTree(inverted);
}

TEST(InvertTreeTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    TreeNode* inverted = sol.invertTree(root);
    EXPECT_EQ(inverted, nullptr);
}

TEST(InvertTreeTest, LeftSkewed) {
    Solution sol;
    // 手动构建左斜树 1->2->3->4，翻转后为右斜树
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    TreeNode* inverted = sol.invertTree(root);
    std::vector<int> expected = {1,-1,2,-1,3,-1,4};
    EXPECT_EQ(levelOrder(inverted), expected);
    freeTree(inverted);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}