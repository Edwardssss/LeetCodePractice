# 104. 二叉树的最大深度

## 题目描述

104. 二叉树的最大深度

给定一个二叉树 `root` ，返回其最大深度。

二叉树的 **最大深度** 是指从根节点到最远叶子节点的最长路径上的节点数。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [3,9,20,null,null,15,7]
>
>  **输出**
>
> 3

示例 2：

>  **输入**
>
> root = [1,null,2]
>
>  **输出**
>
> 2

提示：

- 树中节点的数量在 `[0, 104]` 区间内。
- `-100 <= Node.val <= 100`

## 思路分析

这道题我用的队列层序遍历+计数，计算每层的节点个数，最后就能知道有几层了，也就是BFS的迭代版。LeetCode官方给出了基于递归的BFS和DFS实现。

DFS代码示例如下

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

BFS代码示例如下

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> Q;
        Q.push(root);
        int ans = 0;
        while (!Q.empty()) {
            int sz = Q.size();
            while (sz > 0) {
                TreeNode* node = Q.front();Q.pop();
                if (node->left) Q.push(node->left);
                if (node->right) Q.push(node->right);
                sz -= 1;
            }
            ans += 1;
        }
        return ans;
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
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        int last_in_queue = 1;
        int now_in_queue = 0;
        int layer = 1;
        queue<TreeNode*> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            if(node_queue.front()->left){
                node_queue.push(node_queue.front()->left);
                ++now_in_queue;
            }
            if(node_queue.front()->right){
                node_queue.push(node_queue.front()->right);
                ++now_in_queue;
            }
            node_queue.pop();
            --last_in_queue;
            if(!last_in_queue){
                if(!now_in_queue) return layer;
                last_in_queue = now_in_queue;
                now_in_queue = 0;
                ++layer;
            }
        }
        return layer;
    }
};
```

## 复杂度分析

- DFS

    - 时间复杂度：$O(n)$
    - 空间复杂度：$O(height)$，其中 $height$ 表示二叉树的高度。递归函数需要栈空间，而栈空间取决于递归的深度，因此空间复杂度等价于二叉树的高度

- BFS

    - 时间复杂度：$O(n)$
    - 空间复杂度：此方法空间的消耗取决于队列存储的元素数量，其在最坏情况下会达到 $O(n)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "104-maximum-depth-of-binary-tree.cpp"
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

TEST(MaxDepthTest, Example1) {
    Solution sol;
    // [3,9,20,null,null,15,7] 层序为 [3,9,20,-1,-1,15,7]
    TreeNode* root = createTree({3,9,20,-1,-1,15,7});
    EXPECT_EQ(sol.maxDepth(root), 3);
    freeTree(root);
}

TEST(MaxDepthTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    EXPECT_EQ(sol.maxDepth(root), 1);
    freeTree(root);
}

TEST(MaxDepthTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    EXPECT_EQ(sol.maxDepth(root), 0);
}

TEST(MaxDepthTest, CompleteTree) {
    Solution sol;
    // 完全二叉树 [1,2,3,4,5,6,7]
    TreeNode* root = createTree({1,2,3,4,5,6,7});
    EXPECT_EQ(sol.maxDepth(root), 3);
    freeTree(root);
}

TEST(MaxDepthTest, LeftSkewed) {
    Solution sol;
    // 手动构建左斜树 1->2->3->4
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    EXPECT_EQ(sol.maxDepth(root), 4);
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
[==========] Running 5 tests from 1 test suite.    
[----------] Global test environment set-up.       
[----------] 5 tests from MaxDepthTest
[ RUN      ] MaxDepthTest.Example1
[       OK ] MaxDepthTest.Example1 (0 ms)
[ RUN      ] MaxDepthTest.SingleNode
[       OK ] MaxDepthTest.SingleNode (0 ms)
[ RUN      ] MaxDepthTest.EmptyTree
[       OK ] MaxDepthTest.EmptyTree (0 ms)
[ RUN      ] MaxDepthTest.CompleteTree
[       OK ] MaxDepthTest.CompleteTree (0 ms)
[ RUN      ] MaxDepthTest.LeftSkewed
[       OK ] MaxDepthTest.LeftSkewed (0 ms)
[----------] 5 tests from MaxDepthTest (2 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (5 ms total)
[  PASSED  ] 5 tests.
```
