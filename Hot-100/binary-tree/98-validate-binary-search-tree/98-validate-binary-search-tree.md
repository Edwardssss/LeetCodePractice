# 98. 验证二叉搜索树

## 题目描述

98. 验证二叉搜索树

给你一个二叉树的根节点 `root` ，判断其是否是一个有效的二叉搜索树。

**有效** 二叉搜索树定义如下：

- 节点的左子树只包含 **严格小于** 当前节点的数。
- 节点的右子树只包含 **严格大于** 当前节点的数。
- 所有左子树和右子树自身必须也是二叉搜索树。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [2,1,3]
>
>  **输出**
>
> true

![](./2.jpg)

示例 2：

>  **输入**
>
> root = [5,1,4,null,null,3,6]
>
>  **输出**
>
> false
>
>  **解释**
>
> 根节点的值是 5 ，但是右子节点的值是 4 。

提示：

- 树中节点数目范围在`[1, 104]` 内
- `-231 <= Node.val <= 231 - 1`

## 思路分析

这道题一开始是使用简单的左右子树递归判断写的，但是WA之后发现要左右子树的所有节点都严格符合条件。所以需要加入两个参数，以记录最大节点和最小节点。

LeetCode官方用了递归和中序遍历两种方法来写，中序遍历的结果一定是严格递增的，所以可以用于判断平衡树。中序遍历的代码如下所示：

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stack;
        long long inorder = (long long)INT_MIN - 1;

        while (!stack.empty() || root != nullptr) {
            while (root != nullptr) {
                stack.push(root);
                root = root -> left;
            }
            root = stack.top();
            stack.pop();
            // 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
            if (root -> val <= inorder) {
                return false;
            }
            inorder = root -> val;
            root = root -> right;
        }
        return true;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, nullptr, nullptr);
    }
    bool helper(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
        if (!node) return true;
        if (minNode && node->val <= minNode->val) return false;
        if (maxNode && node->val >= maxNode->val) return false;
        return helper(node->left, minNode, node) && helper(node->right, node, maxNode);
    }
};
```

## 复杂度分析

- 递归法

    - 时间复杂度：$O(n)$，其中 $n$ 为二叉树的节点个数。在递归调用的时候二叉树的每个节点最多被访问一次，因此时间复杂度为 $O(n)$。

    - 空间复杂度：$O(n)$，其中 $n$ 为二叉树的节点个数。递归函数在递归过程中需要为每一层递归函数分配栈空间，所以这里需要额外的空间且该空间取决于递归的深度，即二叉树的高度。最坏情况下二叉树为一条链，树的高度为 $n$ ，递归最深达到 $n$ 层，故最坏情况下空间复杂度为 $O(n)$ 。

- 中序遍历法

    - 时间复杂度：$O(n)$，其中 $n$ 为二叉树的节点个数。二叉树的每个节点最多被访问一次，因此时间复杂度为 $O(n)$。

    - 空间复杂度：$O(n)$，其中 $n$ 为二叉树的节点个数。栈最多存储 $n$ 个节点，因此需要额外的 $O(n)$ 的空间。

## 测试用例

测试用例如下：

```c++
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
```

## 测试结果

测试结果如下所示：

```
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from IsValidBSTTest
[ RUN      ] IsValidBSTTest.Example1
[       OK ] IsValidBSTTest.Example1 (0 ms)
[ RUN      ] IsValidBSTTest.NotBST
[       OK ] IsValidBSTTest.NotBST (0 ms)
[ RUN      ] IsValidBSTTest.SingleNode
[       OK ] IsValidBSTTest.SingleNode (0 ms)
[ RUN      ] IsValidBSTTest.DuplicateValue
[       OK ] IsValidBSTTest.DuplicateValue (0 ms)
[----------] 4 tests from IsValidBSTTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```