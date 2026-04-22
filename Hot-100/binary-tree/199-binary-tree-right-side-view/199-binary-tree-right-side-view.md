# 199. 二叉树的右视图

## 题目描述

199. 二叉树的右视图

给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例 1：

>  **输入**
>
> root = [1,2,3,null,5,null,4]
>
>  **输出**
>
> [1,3,4]
>
>  **解释**
>
> ![](./1.png)

示例 2：

>  **输入**
>
> root = [1,2,3,4,null,null,null,5]
>
>  **输出**
>
> [1,3,4,5]
>
>  **解释**
>
> ![](./2.png)

示例 3：

>  **输入**
>
> root = [1,null,3]
>
>  **输出**
>
> [1,3]

示例 4：

>  **输入**
>
> root = []
>
>  **输出**
>
> []

提示:

- 二叉树的节点个数的范围是 `[0,100]`
- `-100 <= Node.val <= 100`

## 思路分析

这道题我的思路是进行层序遍历，然后输出当前层中最右侧的节点值即可。

LeetCode官方使用了DFS和BFS两种方法来写，感觉会略微繁琐一些。

DFS的代码示例如下：

```c++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        unordered_map<int, int> rightmostValueAtDepth;
        int max_depth = -1;

        stack<TreeNode*> nodeStack;
        stack<int> depthStack;
        nodeStack.push(root);
        depthStack.push(0);

        while (!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();nodeStack.pop();
            int depth = depthStack.top();depthStack.pop();

            if (node != NULL) {
            	// 维护二叉树的最大深度
                max_depth = max(max_depth, depth);

                // 如果不存在对应深度的节点我们才插入
                if (rightmostValueAtDepth.find(depth) == rightmostValueAtDepth.end()) {
                    rightmostValueAtDepth[depth] =  node -> val;
                }

                nodeStack.push(node -> left);
                nodeStack.push(node -> right);
                depthStack.push(depth + 1);
                depthStack.push(depth + 1);
            }
        }

        vector<int> rightView;
        for (int depth = 0; depth <= max_depth; ++depth) {
            rightView.push_back(rightmostValueAtDepth[depth]);
        }

        return rightView;
    }
};
```

BFS的代码示例如下：

```c++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        unordered_map<int, int> rightmostValueAtDepth;
        int max_depth = -1;

        queue<TreeNode*> nodeQueue;
        queue<int> depthQueue;
        nodeQueue.push(root);
        depthQueue.push(0);

        while (!nodeQueue.empty()) {
            TreeNode* node = nodeQueue.front();nodeQueue.pop();
            int depth = depthQueue.front();depthQueue.pop();

            if (node != NULL) {
            	// 维护二叉树的最大深度
                max_depth = max(max_depth, depth);

                // 由于每一层最后一个访问到的节点才是我们要的答案，因此不断更新对应深度的信息即可
                rightmostValueAtDepth[depth] =  node -> val;

                nodeQueue.push(node -> left);
                nodeQueue.push(node -> right);
                depthQueue.push(depth + 1);
                depthQueue.push(depth + 1);
            }
        }

        vector<int> rightView;
        for (int depth = 0; depth <= max_depth; ++depth) {
            rightView.push_back(rightmostValueAtDepth[depth]);
        }

        return rightView;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return {};
        vector<int> result;
        queue<TreeNode*> node_queue;
        node_queue.push(root);
        int cnt = 0;
        int pre_cnt = 1;
        bool first_flag = true;
        while (!node_queue.empty()) {
            TreeNode* node = node_queue.front();
            node_queue.pop();
            if (first_flag) {
                result.push_back(node->val);
                first_flag = false;
            }
            if(node->right){
                node_queue.push(node->right);
                ++cnt;
            }
            if(node->left){
                node_queue.push(node->left);
                ++cnt;
            }
            --pre_cnt;
            if(!pre_cnt){
                pre_cnt = cnt;
                cnt = 0;
                first_flag = true;
            }
        }
        return result;
    }
};
```


## 复杂度分析

- 层序遍历
    - 时间复杂度：$O(n)$，其中 $n$ 为二叉树的节点数。每个节点只会被访问一次。
    - 空间复杂度：$O(n)$，最坏情况下队列中会存储一层的所有节点，空间消耗与树的最大宽度成正比。

- BFS
    - 时间复杂度：$O(n)$，其中 $n$ 为二叉树的节点数。每个节点只会被访问一次。
    - 空间复杂度：$O(n)$，最坏情况下队列中会存储一层的所有节点，空间消耗与树的最大宽度成正比

- DFS
    - 时间复杂度：$O(n)$，每个节点只会被访问一次。
    - 空间复杂度：$O(n)$，递归或栈的深度为树的高度，最坏情况下为 $O(n)$（树退化为链表）。


## 测试用例

测试用例如下：

```c++
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
```

## 测试结果

测试结果如下所示：

```
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from RightSideViewTest
[ RUN      ] RightSideViewTest.Example1
[       OK ] RightSideViewTest.Example1 (0 ms)
[ RUN      ] RightSideViewTest.SingleNode
[       OK ] RightSideViewTest.SingleNode (0 ms)
[ RUN      ] RightSideViewTest.EmptyTree
[       OK ] RightSideViewTest.EmptyTree (0 ms)
[ RUN      ] RightSideViewTest.CompleteTree
[       OK ] RightSideViewTest.CompleteTree (0 ms)
[----------] 4 tests from RightSideViewTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```