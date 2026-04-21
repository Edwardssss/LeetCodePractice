# 102. 二叉树的层序遍历

## 题目描述

102. 二叉树的层序遍历

给你二叉树的根节点 `root` ，返回其节点值的 **层序遍历** 。 （即逐层地，从左到右访问所有节点）。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [3,9,20,null,null,15,7]
>  **输出**
>
> [[3],[9,20],[15,7]]

示例 2：

>  **输入**
>
> root = [1]
>
>  **输出**
>
> [[1]]

示例 3：

>  **输入**
>
> root = []
>
>  **输出**
>
> []

提示：

- 树中节点数目在范围 `[0, 2000]` 内
- `-1000 <= Node.val <= 1000`

## 思路分析

这道题想到的是使用FIFO队列+计数法，这样就可以逐层读取，然后实现一个计数器从而分割不同的层。

LeetCode官方想的是用一个二元组 (node, level) 来表示状态，它表示某个节点和它所在的层数，每个新进队列的节点的 level 值都是父亲节点的 level 值加一。最后根据每个点的 level 对点进行分类，分类的时候我们可以利用哈希表，维护一个以 level 为键，对应节点值组成的数组为值，广度优先搜索结束以后按键 level 从小到大取出所有值，组成答案返回即可。

官方用一种巧妙的方法修改广度优先搜索：

- 首先根元素入队
- 当队列不为空的时候
    - 求当前队列的长度 $s_i$
    - 依次从队列中取 $s_i$个元素进行拓展，然后进入下一次迭代

它和普通广度优先搜索的区别在于，普通广度优先搜索每次只取一个元素拓展，而这里每次取 $s_i$个元素。在上述过程中的第 $i$ 次迭代就得到了二叉树的第 $i$ 层的 $s_i$个元素。

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector <int>> ret;
        if (!root) {
            return ret;
        }

        queue <TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int currentLevelSize = q.size();
            ret.push_back(vector <int> ());
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front(); q.pop();
                ret.back().push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return ret;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:

    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> result = {};
        queue<TreeNode*> pipe = {};
        pipe.push(root);
        int pre_cnt = 1;
        int cnt = 0;
        vector<int> layer_storage = {};
        while (!pipe.empty()) {
            TreeNode* node = pipe.front();
            pipe.pop();
            layer_storage.push_back(node->val);
            if (node->left) {
                pipe.push(node->left);
                ++cnt;
            }
            if (node->right) {
                pipe.push(node->right);
                ++cnt;
            }
            --pre_cnt;
            if (pre_cnt == 0) {
                result.push_back(layer_storage);
                layer_storage.clear();
                pre_cnt = cnt;
                cnt = 0;
            }
        }
        return result;
    }
};
```


## 复杂度分析

- 时间复杂度：$O(n)$，其中 $n$ 是二叉树的节点数。每个节点只会被入队和出队各一次，遍历和访问操作均为常数时间，总体为线性复杂度。
- 空间复杂度：$O(n)$，最坏情况下队列中会存储一层的所有节点，空间消耗与树的最大宽度成正比，最坏为 $O(n)$。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "102-binary-tree-level-order-traversal.cpp"
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

TEST(LevelOrderTest, Example1) {
    Solution sol;
    // 输入: [3,9,20,-1,-1,15,7]
    TreeNode* root = createTree({3,9,20,-1,-1,15,7});
    std::vector<std::vector<int>> expected = {{3},{9,20},{15,7}};
    EXPECT_EQ(sol.levelOrder(root), expected);
    freeTree(root);
}

TEST(LevelOrderTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    std::vector<std::vector<int>> expected = {{1}};
    EXPECT_EQ(sol.levelOrder(root), expected);
    freeTree(root);
}

TEST(LevelOrderTest, EmptyTree) {
    Solution sol;
    TreeNode* root = nullptr;
    std::vector<std::vector<int>> expected = {};
    EXPECT_EQ(sol.levelOrder(root), expected);
}

TEST(LevelOrderTest, CompleteTree) {
    Solution sol;
    // 完全二叉树 [1,2,3,4,5,6,7]
    TreeNode* root = createTree({1,2,3,4,5,6,7});
    std::vector<std::vector<int>> expected = {{1},{2,3},{4,5,6,7}};
    EXPECT_EQ(sol.levelOrder(root), expected);
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
[----------] 4 tests from LevelOrderTest
[ RUN      ] LevelOrderTest.Example1
[       OK ] LevelOrderTest.Example1 (0 ms)
[ RUN      ] LevelOrderTest.SingleNode
[       OK ] LevelOrderTest.SingleNode (0 ms)
[ RUN      ] LevelOrderTest.EmptyTree
[       OK ] LevelOrderTest.EmptyTree (0 ms)
[ RUN      ] LevelOrderTest.CompleteTree
[       OK ] LevelOrderTest.CompleteTree (0 ms)
[----------] 4 tests from LevelOrderTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```