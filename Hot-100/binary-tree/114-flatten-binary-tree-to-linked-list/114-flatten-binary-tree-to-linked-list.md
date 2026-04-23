# 114. 二叉树展开为链表

## 题目描述

114. 二叉树展开为链表

给你二叉树的根结点 `root` ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 `TreeNode` ，其中 `right` 子指针指向链表中下一个结点，而左子指针始终为 `null` 。
展开后的单链表应该与二叉树 **先序遍历** 顺序相同。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [1,2,5,3,4,null,6]
>
>  **输出**
>
> [1,null,2,null,3,null,4,null,5,null,6]

示例 2：

>  **输入**
>
> root = []
>
>  **输出**
>
> []

示例 3：

>  **输入**
>
> root = [0]
>
>  **输出**
>
> [0]

提示：

- 树中结点数在范围 `[0, 2000]` 内
- `-100 <= Node.val <= 100`

进阶：你可以使用原地算法（$O(1)$ 额外空间）展开这棵树吗？

## 思路分析

这道题我就是想到通过递归的前序遍历先确定顺序，再按照顺序依次连接所有的节点即可。

LeetCode官方还给出了基于迭代的前序遍历，代码示例如下：

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        auto v = vector<TreeNode*>();
        auto stk = stack<TreeNode*>();
        TreeNode *node = root;
        while (node != nullptr || !stk.empty()) {
            while (node != nullptr) {
                v.push_back(node);
                stk.push(node);
                node = node->left;
            }
            node = stk.top(); stk.pop();
            node = node->right;
        }
        int size = v.size();
        for (int i = 1; i < size; i++) {
            auto prev = v.at(i - 1), curr = v.at(i);
            prev->left = nullptr;
            prev->right = curr;
        }
    }
};
```

但是前序遍历的方法会在破坏二叉树的结构之后丢失子节点的信息，是因为在对左子树进行遍历时，没有存储右子节点的信息，在遍历完左子树之后才获得右子节点的信息。只要对前序遍历进行修改，在遍历左子树之前就获得左右子节点的信息，并存入栈内，子节点的信息就不会丢失，就可以将前序遍历和展开为单链表同时进行。

该做法不适用于递归实现的前序遍历，只适用于迭代实现的前序遍历。修改后的前序遍历的具体做法是，每次从栈内弹出一个节点作为当前访问的节点，获得该节点的子节点，如果子节点不为空，则依次将右子节点和左子节点压入栈内（注意入栈顺序）。

展开为单链表的做法是，维护上一个访问的节点 `prev`，每次访问一个节点时，令当前访问的节点为 `curr`，将 `prev` 的左子节点设为 `null` 以及将 `prev` 的右子节点设为 `curr`，然后将 `curr` 赋值给 `prev`，进入下一个节点的访问，直到遍历结束。需要注意的是，初始时 `prev` 为 `null`，只有在 `prev` 不为 `null` 时才能对 `prev` 的左右子节点进行更新。

代码示例如下：

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        auto stk = stack<TreeNode*>();
        stk.push(root);
        TreeNode *prev = nullptr;
        while (!stk.empty()) {
            TreeNode *curr = stk.top(); stk.pop();
            if (prev != nullptr) {
                prev->left = nullptr;
                prev->right = curr;
            }
            TreeNode *left = curr->left, *right = curr->right;
            if (right != nullptr) {
                stk.push(right);
            }
            if (left != nullptr) {
                stk.push(left);
            }
            prev = curr;
        }
    }
};

注意到前序遍历访问各节点的顺序是根节点、左子树、右子树。如果一个节点的左子节点为空，则该节点不需要进行展开操作。如果一个节点的左子节点不为空，则该节点的左子树中的最后一个节点被访问之后，该节点的右子节点被访问。该节点的左子树中最后一个被访问的节点是左子树中的最右边的节点，也是该节点的前驱节点。因此，问题转化成寻找当前节点的前驱节点。

具体做法是，对于当前节点，如果其左子节点不为空，则在其左子树中找到最右边的节点，作为前驱节点，将当前节点的右子节点赋给前驱节点的右子节点，然后将当前节点的左子节点赋给当前节点的右子节点，并将当前节点的左子节点设为空。对当前节点处理结束后，继续处理链表中的下一个节点，直到所有节点都处理结束。

代码示例如下：

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode *curr = root;
        while (curr != nullptr) {
            if (curr->left != nullptr) {
                auto next = curr->left;
                auto predecessor = next;
                while (predecessor->right != nullptr) {
                    predecessor = predecessor->right;
                }
                predecessor->right = curr->right;
                curr->left = nullptr;
                curr->right = next;
            }
            curr = curr->right;
        }
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    queue<TreeNode*> node_queue;

    void pre_order(TreeNode* node){
        if(!node) return;
        this->node_queue.push(node);
        pre_order(node->left);
        pre_order(node->right);
    }

    void flatten(TreeNode* root) {
        if(!root) return;
        pre_order(root);
        TreeNode* cur_node = this->node_queue.front();
        node_queue.pop();
        while (!node_queue.empty()) {
            cur_node->left = nullptr;
            cur_node->right = node_queue.front();
            cur_node = node_queue.front();
            node_queue.pop();
        }
        cur_node->left = nullptr;
        cur_node->right = nullptr;
    }
};
```


## 复杂度分析

- 前序遍历+队列
    - 时间复杂度：$O(n)$，其中 $n$ 为二叉树的节点数。每个节点只会被访问一次。
    - 空间复杂度：$O(n)$，递归栈和队列都需要存储所有节点。

- 递归+原地展开
    - 时间复杂度：$O(n)$，每个节点只会被访问一次。
    - 空间复杂度：$O(n)$，递归栈的深度为树的高度，最坏情况下为 $O(n)$（树退化为链表）。

- Morris遍历
    - 时间复杂度：$O(n)$，每个节点只会被访问一次。
    - 空间复杂度：$O(1)$，只使用常数级别的额外空间。

## 测试用例

测试用例如下：

```c++
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
```

## 测试结果

测试结果如下所示：

```
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from FlattenTest
[ RUN      ] FlattenTest.Example1
[       OK ] FlattenTest.Example1 (0 ms)
[ RUN      ] FlattenTest.SingleNode
[       OK ] FlattenTest.SingleNode (0 ms)
[ RUN      ] FlattenTest.EmptyTree
[       OK ] FlattenTest.EmptyTree (0 ms)
[ RUN      ] FlattenTest.LeftSkewed
[       OK ] FlattenTest.LeftSkewed (0 ms)
[----------] 4 tests from FlattenTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```