# 105. 从前序与中序遍历序列构造二叉树

## 题目描述

105. 从前序与中序遍历序列构造二叉树

给定两个整数数组 `preorder` 和 `inorder` ，其中 `preorder` 是二叉树的先序遍历， `inorder` 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

![](./1.jpg)

示例 1:

>  **输入**
>
> preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
>
>  **输出**
>
> [3,9,20,null,null,15,7]

示例 2:

>  **输入**
>
> preorder = [-1], inorder = [-1]
>
>  **输出**
>
> [-1]

提示:

- `1 <= preorder.length <= 3000`
- `inorder.length == preorder.length`
- `-3000 <= preorder[i], inorder[i] <= 3000`
- `preorder` 和 `inorder` 均 **无重复** 元素
- `inorder` 均出现在 `preorder`
- `preorder` **保证** 为二叉树的前序遍历序列
- `inorder` **保证** 为二叉树的中序遍历序列

## 思路分析

这道题完全不会写。

LeetCode官方给出了基于递归和迭代的两种方法。

**递归法**

对于任意一颗树而言，前序遍历的形式总是

```
[ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]
```

即根节点总是前序遍历中的第一个节点。而中序遍历的形式总是

```
[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]
```

只要我们在中序遍历中定位到根节点，那么我们就可以分别知道左子树和右子树中的节点数目。由于同一颗子树的前序遍历和中序遍历的长度显然是相同的，因此我们就可以对应到前序遍历的结果中，对上述形式中的所有左右括号进行定位。

这样以来，我们就知道了左子树的前序遍历和中序遍历结果，以及右子树的前序遍历和中序遍历结果，我们就可以递归地对构造出左子树和右子树，再将这两颗子树接到根节点的左右位置。

代码实现示例如下所示：

```c++
class Solution {
private:
    unordered_map<int, int> index;

public:
    TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
        if (preorder_left > preorder_right) {
            return nullptr;
        }
        
        // 前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;
        // 在中序遍历中定位根节点
        int inorder_root = index[preorder[preorder_root]];
        
        // 先把根节点建立出来
        TreeNode* root = new TreeNode(preorder[preorder_root]);
        // 得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left;
        // 递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};
```

**迭代法**

对于前序遍历中的任意两个连续节点 `u` 和 `v`，根据前序遍历的流程，我们可以知道 `u` 和 `v` 只有两种可能的关系：

`v` 是 `u` 的左儿子。这是因为在遍历到 `u` 之后，下一个遍历的节点就是 `u` 的左儿子，即 `v`；

`u` 没有左儿子，并且 `v` 是 `u` 的某个祖先节点（或者 `u` 本身）的右儿子。如果 `u` 没有左儿子，那么下一个遍历的节点就是 `u` 的右儿子。如果 `u` 没有右儿子，我们就会向上回溯，直到遇到第一个有右儿子（且 `u` 不在它的右儿子的子树中）的节点 $u_a$，那么 `v` 就是 $u_a$ 的右儿子。

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};
```

## 复杂度分析

- 递归法

    - 时间复杂度：$O(n)$，其中 $n$ 是树中的节点个数。

    - 空间复杂度：$O(n)$，除去返回的答案需要的 $O(n)$ 空间之外，我们还需要使用 $O(n)$ 的空间存储哈希映射，以及 $O(h)$（其中 $h$ 是树的高度）的空间表示递归时栈空间。这里 $h<n$，所以总空间复杂度为 $O(n)$。

- 迭代法

    - 时间复杂度：$O(n)$，其中 $n$ 是树中的节点个数。

    - 空间复杂度：$O(n)$，除去返回的答案需要的 $O(n)$ 空间之外，我们还需要使用 $O(h)$（其中 $h$ 是树的高度）的空间存储栈。这里 $h<n$，所以（在最坏情况下）总空间复杂度为 $O(n)$。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "105-construct-binary-tree-from-preorder-and-inorder-traversal.cpp"
#include <vector>
#include <queue>

// 辅助函数：层序遍历展开树为数组，空节点用-1表示
std::vector<int> flattenToVector(TreeNode* root) {
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

TEST(BuildTreeTest, Example1) {
    Solution sol;
    std::vector<int> preorder = {3,9,20,15,7};
    std::vector<int> inorder = {9,3,15,20,7};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {3,9,20,-1,-1,15,7};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(BuildTreeTest, EmptyTree) {
    Solution sol;
    std::vector<int> preorder = {};
    std::vector<int> inorder = {};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(BuildTreeTest, SingleNode) {
    Solution sol;
    std::vector<int> preorder = {1};
    std::vector<int> inorder = {1};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {1};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
}

TEST(BuildTreeTest, CompleteTree) {
    Solution sol;
    std::vector<int> preorder = {1,2,4,5,3,6,7};
    std::vector<int> inorder = {4,2,5,1,6,3,7};
    TreeNode* root = sol.buildTree(preorder, inorder);
    std::vector<int> expected = {1,2,3,4,5,6,7};
    EXPECT_EQ(flattenToVector(root), expected);
    freeTree(root);
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
[----------] 4 tests from BuildTreeTest
[ RUN      ] BuildTreeTest.Example1
[       OK ] BuildTreeTest.Example1 (0 ms)
[ RUN      ] BuildTreeTest.EmptyTree
[       OK ] BuildTreeTest.EmptyTree (0 ms)
[ RUN      ] BuildTreeTest.SingleNode
[       OK ] BuildTreeTest.SingleNode (0 ms)
[ RUN      ] BuildTreeTest.CompleteTree
[       OK ] BuildTreeTest.CompleteTree (0 ms)
[----------] 4 tests from BuildTreeTest (0 ms total)

[----------] GloO(n)bal test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```