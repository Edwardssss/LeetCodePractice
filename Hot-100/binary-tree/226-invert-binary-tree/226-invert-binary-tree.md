# 226. 翻转二叉树

## 题目描述

226. 翻转二叉树

给你一棵二叉树的根节点 `root` ，翻转这棵二叉树，并返回其根节点。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [4,2,7,1,3,6,9]
>
>  **输出**
>
> [4,7,2,9,6,3,1]

![](./2.jpg)

示例 2：

>  **输入**
>
> root = [2,1,3]
>
>  **输出**
>
> [2,3,1]

示例 3：

>  **输入**
>
> root = []
>
>  **输出**
>
> []

提示：

- 树中节点数目范围在 `[0, 100]` 内
- `-100 <= Node.val <= 100`

## 思路分析

这道题就是递归地去翻转所有的节点的子节点就可以了，但是我没有想出来递归的写法，所以写的是迭代法。

LeetCode官方代码示例如下：

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <queue>

using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;
        queue<TreeNode*> node_queue;
        node_queue.push(root);
        TreeNode* temp;
        while (!node_queue.empty()) {
            temp = node_queue.front()->left;
            node_queue.front()->left = node_queue.front()->right;
            node_queue.front()->right = temp;
            if(node_queue.front()->left) node_queue.push(node_queue.front()->left);
            if(node_queue.front()->right) node_queue.push(node_queue.front()->right);
            node_queue.pop();
        }
        return root;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(N)$，其中 $N$ 为二叉树节点的数目。我们会遍历二叉树中的每一个节点，对每个节点而言，我们在常数时间内交换其两棵子树。
- 空间复杂度：$O(N)$。使用的空间由递归栈的深度决定，它等于当前节点在二叉树中的高度。在平均情况下，二叉树的高度与节点个数为对数关系，即 $O(logN)$。而在最坏情况下，树形成链状，空间复杂度为 $O(N)$。

## 测试用例

测试用例如下：

```c++
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
```

## 测试结果

测试结果如下所示：

```
[==========] Running 4 tests from 1 test suite.      
[----------] Global test environment set-up.
[----------] 4 tests from InvertTreeTest
[ RUN      ] InvertTreeTest.Example1
[       OK ] InvertTreeTest.Example1 (0 ms)
[ RUN      ] InvertTreeTest.SingleNode
[       OK ] InvertTreeTest.SingleNode (0 ms)
[ RUN      ] InvertTreeTest.EmptyTree
[       OK ] InvertTreeTest.EmptyTree (0 ms)
[ RUN      ] InvertTreeTest.LeftSkewed
[       OK ] InvertTreeTest.LeftSkewed (0 ms)
[----------] 4 tests from InvertTreeTest (1 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 4 tests.
```
