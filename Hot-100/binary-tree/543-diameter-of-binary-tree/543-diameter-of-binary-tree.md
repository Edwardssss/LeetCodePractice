# 543. 二叉树的直径

## 题目描述

543. 二叉树的直径

给你一棵二叉树的根节点，返回该树的 **直径** 。

二叉树的 **直径** 是指树中任意两个节点之间最长路径的 **长度** 。这条路径可能经过也可能不经过根节点 `root` 。

两节点之间路径的 **长度** 由它们之间边数表示。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [1,2,3,4,5]
>
>  **输出**
>
> 3
>
>  **解释**
>
> 3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。

示例 2：

>  **输入**
>
> root = [1,2]
>
>  **输出**
>
> 1

提示：

- 树中节点数目在范围 `[1, 104]` 内
- `-100 <= Node.val <= 100`

## 思路分析

这道题求二叉树的直径，本质上就是求`root`节点的左子树和右子树的最大深度之和，所以可以使用递归的方法写。我看到有人也写了基于迭代的做法，我也贴一下：

```c++
class Solution {
public:
    int getMaxDepth(TreeNode* root){
        if(!root) return 0;
        return max(getMaxDepth(root->left), getMaxDepth(root->right))+1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            while(sz){
                TreeNode* node = q.front();q.pop();
                sz --;
                if(!node) continue;
                int L = getMaxDepth(node->left);
                int R = getMaxDepth(node->right);
                ans = max(ans, L+R+1);
                q.push(node->left);
                q.push(node->right);
            }
        }
        return ans-1;
    }
};
```

## 代码实现

代码实现如下：

```c++
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDiameter = 0;
    int distance_from_root(TreeNode * node){
        if (!node) return 0;
        int left = distance_from_root(node->left);
        int right = distance_from_root(node->right);
        if (left + right > maxDiameter) maxDiameter = left + right;
        return std::max(left, right) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        distance_from_root(root);
        return maxDiameter;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(N)$，其中 $N$ 为二叉树的节点数，即遍历一棵二叉树的时间复杂度，每个结点只被访问一次
- 空间复杂度：$O(Height)$，其中 $Height$ 为二叉树的高度。由于递归函数在递归过程中需要为每一层递归函数分配栈空间，所以这里需要额外的空间且该空间取决于递归的深度，而递归的深度显然为二叉树的高度，并且每次递归调用的函数里又只用了常数个变量，所以所需空间复杂度为 $O(Height)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "543-diameter-of-binary-tree.cpp"
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

TEST(DiameterOfBinaryTreeTest, Example1) {
    Solution sol;
    // 输入: [1,2,3,4,5]
    TreeNode* root = createTree({1,2,3,4,5});
    int expected = 3;
    EXPECT_EQ(sol.diameterOfBinaryTree(root), expected);
    freeTree(root);
}

TEST(DiameterOfBinaryTreeTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    int expected = 0;
    EXPECT_EQ(sol.diameterOfBinaryTree(root), expected);
    freeTree(root);
}

TEST(DiameterOfBinaryTreeTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    int expected = 0;
    EXPECT_EQ(sol.diameterOfBinaryTree(root), expected);
}

TEST(DiameterOfBinaryTreeTest, CompleteTree) {
    Solution sol;
    // 完全二叉树 [1,2,3,4,5,6,7]
    TreeNode* root = createTree({1,2,3,4,5,6,7});
    int expected = 4;
    EXPECT_EQ(sol.diameterOfBinaryTree(root), expected);
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
[----------] 4 tests from DiameterOfBinaryTreeTest
[ RUN      ] DiameterOfBinaryTreeTest.Example1
[       OK ] DiameterOfBinaryTreeTest.Example1 (0 ms)
[ RUN      ] DiameterOfBinaryTreeTest.SingleNode
[       OK ] DiameterOfBinaryTreeTest.SingleNode (0 ms)
[ RUN      ] DiameterOfBinaryTreeTest.EmptyTree
[       OK ] DiameterOfBinaryTreeTest.EmptyTree (0 ms)
[ RUN      ] DiameterOfBinaryTreeTest.CompleteTree
[       OK ] DiameterOfBinaryTreeTest.CompleteTree (0 ms)
[----------] 4 tests from DiameterOfBinaryTreeTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```