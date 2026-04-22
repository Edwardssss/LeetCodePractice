# 230. 二叉搜索树中第 K 小的元素

## 问题描述

230. 二叉搜索树中第 K 小的元素

给定一个二叉搜索树的根节点 `root` ，和一个整数 `k` ，请你设计一个算法查找其中第 `k` 小的元素（`k` 从 1 开始计数）。

![](./1.jpg)

示例 1：

>  **输入**
>
> root = [3,1,4,null,2], k = 1
>
>  **输出**
>
> 1

![](./2.jpg)

示例 2：

>  **输入**
>
> root = [5,3,6,2,4,null,null,1], k = 3
>
>  **输出**
>
> 3

提示：

- 树中的节点数为 `n` 。
- `1 <= k <= n <= 10^4`
- `0 <= Node.val <= 10^4`

进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 `k` 小的值，你将如何优化算法？

## 思路分析

这道题我用最小堆做的，虽然差点没过，但是至少写出来了。

LeetCode官方使用了中序遍历，记录子节点数，构造AVL树三种方法来做。

由于题目说了是二叉搜索树，所以中序遍历可以获得第$k$个最小元素，代码示例如下：

```c++
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode *> stack;
        while (root != nullptr || stack.size() > 0) {
            while (root != nullptr) {
                stack.push(root);
                root = root->left;
            }
            root = stack.top();
            stack.pop();
            --k;
            if (k == 0) {
                break;
            }
            root = root->right;
        }
        return root->val;
    }
};
```

记录子节点则是记录下以每个结点为根结点的子树的结点数，并在查找第 $k$ 小的值时，使用如下方法搜索：

令 `node` 等于根结点，开始搜索。

对当前结点 `node` 进行如下操作：

如果 `node` 的左子树的结点数 `left` 小于 `k−1`，则第 `k` 小的元素一定在 `node` 的右子树中，令 `node` 等于其的右子结点，`k` 等于 `k−left−1`，并继续搜索；
如果 `node` 的左子树的结点数 `left` 等于 `k−1`，则第 `k` 小的元素即为 `node` ，结束搜索并返回 `node` 即可；
如果 `node` 的左子树的结点数 `left` 大于 `k−1`，则第 `k` 小的元素一定在 `node` 的左子树中，令 `node` 等于其左子结点，并继续搜索。
在实现中，我们既可以将以每个结点为根结点的子树的结点数存储在结点中，也可以将其记录在哈希表中。

代码示例如下：

```c++
class MyBst {
public:
    MyBst(TreeNode *root) {
        this->root = root;
        countNodeNum(root);
    }

    // 返回二叉搜索树中第k小的元素
    int kthSmallest(int k) {
        TreeNode *node = root;
        while (node != nullptr) {
            int left = getNodeNum(node->left);
            if (left < k - 1) {
                node = node->right;
                k -= left + 1;
            } else if (left == k - 1) {
                break;
            } else {
                node = node->left;
            }
        }
        return node->val;
    }

private:
    TreeNode *root;
    unordered_map<TreeNode *, int> nodeNum;

    // 统计以node为根结点的子树的结点数
    int countNodeNum(TreeNode * node) {
        if (node == nullptr) {
            return 0;
        }
        nodeNum[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
        return nodeNum[node];
    }

    // 获取以node为根结点的子树的结点数
    int getNodeNum(TreeNode * node) {
        if (node != nullptr && nodeNum.count(node)) {
            return nodeNum[node];
        }else{
            return 0;
        }
    }
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        MyBst bst(root);
        return bst.kthSmallest(k);
    }
};
```

最后一种方法则是在记录子树的结点数的基础上，将二叉搜索树转换为平衡二叉搜索树，并在插入和删除操作中维护它的平衡状态。

代码示例如下所示：

```c++
// 平衡二叉搜索树结点
struct Node {
    int val;
    Node * parent;
    Node * left;
    Node * right;
    int size;
    int height;

    Node(int val) {
        this->val = val;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0; // 结点高度：以node为根节点的子树的高度（高度定义：叶结点的高度是0）
        this->size = 1; // 结点元素数：以node为根节点的子树的节点总数
    }

    Node(int val, Node * parent) {
        this->val = val;
        this->parent = parent;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0; // 结点高度：以node为根节点的子树的高度（高度定义：叶结点的高度是0）
        this->size = 1; // 结点元素数：以node为根节点的子树的节点总数
    }

    Node(int val, Node * parent, Node * left, Node * right) {
        this->val = val;
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->height = 0; // 结点高度：以node为根节点的子树的高度（高度定义：叶结点的高度是0）
        this->size = 1; // 结点元素数：以node为根节点的子树的节点总数
    }
};


// 平衡二叉搜索树（AVL树）：允许重复值
class AVL {
public:
    AVL(vector<int> & vals) {
        if (!vals.empty()) {
            root = build(vals, 0, vals.size() - 1, nullptr);
        }
    }

    // 根据vals[l:r]构造平衡二叉搜索树 -> 返回根结点
    Node * build(vector<int> & vals, int l, int r, Node * parent) {
        int m = (l + r) >> 1;
        Node * node = new Node(vals[m], parent);
        if (l <= m - 1) {
            node->left = build(vals, l, m - 1, node);
        }
        if (m + 1 <= r) {
            node->right = build(vals, m + 1, r, node);
        }
        recompute(node);
        return node;
    }

    // 返回二叉搜索树中第k小的元素
    int kthSmallest(int k) {
        Node * node = root;
        while (node != nullptr) {
            int left = getSize(node->left);
            if (left < k - 1) {
                node = node->right;
                k -= left + 1;
            } else if (left == k - 1) {
                break;
            } else {
                node = node->left;
            }
        }
        return node->val;
    }

    void insert(int v) {
        if (root == nullptr) {
            root = new Node(v);
        } else {
            // 计算新结点的添加位置
            Node * node = subtreeSearch(root, v);
            bool isAddLeft = v <= node->val; // 是否将新结点添加到node的左子结点
            if (node->val == v) { // 如果值为v的结点已存在
                if (node->left != nullptr) { // 值为v的结点存在左子结点，则添加到其左子树的最右侧
                    node = subtreeLast(node->left);
                    isAddLeft = false;
                } else { // 值为v的结点不存在左子结点，则添加到其左子结点
                    isAddLeft = true;
                }
            }

            // 添加新结点
            Node * leaf = new Node(v, node);
            if (isAddLeft) {
                node->left = leaf;
            } else {
                node->right = leaf;
            }

            rebalance(leaf);
        }
    }

    // 删除值为v的结点 -> 返回是否成功删除结点
    bool Delete(int v) {
        if (root == nullptr) {
            return false;
        }

        Node * node = subtreeSearch(root, v);
        if (node->val != v) { // 没有找到需要删除的结点
            return false;
        }

        // 处理当前结点既有左子树也有右子树的情况
        // 若左子树比右子树高度低，则将当前结点替换为右子树最左侧的结点，并移除右子树最左侧的结点
        // 若右子树比左子树高度低，则将当前结点替换为左子树最右侧的结点，并移除左子树最右侧的结点
        if (node->left != nullptr && node->right != nullptr) {
            Node * replacement = nullptr;
            if (node->left->height <= node->right->height) {
                replacement = subtreeFirst(node->right);
            } else {
                replacement = subtreeLast(node->left);
            }
            node->val = replacement->val;
            node = replacement;
        }

        Node * parent = node->parent;
        Delete(node);
        rebalance(parent);
        return true;
    }

private:
    Node * root;

    // 删除结点p并用它的子结点代替它，结点p至多只能有1个子结点
    void Delete(Node * node) {
        if (node->left != nullptr && node->right != nullptr) {
            return;
            // throw new Exception("Node has two children");
        }
        Node * child = node->left != nullptr ? node->left : node->right;
        if (child != nullptr) {
            child->parent = node->parent;
        }
        if (node == root) {
            root = child;
        } else {
            Node * parent = node->parent;
            if (node == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
        node->parent = node;
    }

    // 在以node为根结点的子树中搜索值为v的结点，如果没有值为v的结点，则返回值为v的结点应该在的位置的父结点
    Node * subtreeSearch(Node * node, int v) {
        if (node->val < v && node->right != nullptr) {
            return subtreeSearch(node->right, v);
        } else if (node->val > v && node->left != nullptr) {
            return subtreeSearch(node->left, v);
        } else {
            return node;
        }
    }

    // 重新计算node结点的高度和元素数
    void recompute(Node * node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }

    // 从node结点开始（含node结点）逐个向上重新平衡二叉树，并更新结点高度和元素数
    void rebalance(Node * node) {
        while (node != nullptr) {
            int oldHeight = node->height, oldSize = node->size;
            if (!isBalanced(node)) {
                node = restructure(tallGrandchild(node));
                recompute(node->left);
                recompute(node->right);
            }
            recompute(node);
            if (node->height == oldHeight && node->size == oldSize) {
                node = nullptr; // 如果结点高度和元素数都没有变化则不需要再继续向上调整
            } else {
                node = node->parent;
            }
        }
    }

    // 判断node结点是否平衡
    bool isBalanced(Node * node) {
        return abs(getHeight(node->left) - getHeight(node->right)) <= 1;
    }

    // 获取node结点更高的子树
    Node * tallChild(Node * node) {
        if (getHeight(node->left) > getHeight(node->right)) {
            return node->left;
        } else {
            return node->right;
        }
    }

    // 获取node结点更高的子树中的更高的子树
    Node * tallGrandchild(Node * node) {
        Node * child = tallChild(node);
        return tallChild(child);
    }

    // 重新连接父结点和子结点（子结点允许为空）
    static void relink(Node * parent, Node * child, bool isLeft) {
        if (isLeft) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        if (child != nullptr) {
            child->parent = parent;
        }
    }

    // 旋转操作
    void rotate(Node * node) {
        Node * parent = node->parent;
        Node * grandparent = parent->parent;
        if (grandparent == nullptr) {
            root = node;
            node->parent = nullptr;
        } else {
            relink(grandparent, node, parent == grandparent->left);
        }

        if (node == parent->left) {
            relink(parent, node->right, true);
            relink(node, parent, false);
        } else {
            relink(parent, node->left, false);
            relink(node, parent, true);
        }
    }

    // trinode操作
    Node * restructure(Node * node) {
        Node * parent = node->parent;
        Node * grandparent = parent->parent;

        if ((node == parent->right) == (parent == grandparent->right)) { // 处理需要一次旋转的情况
            rotate(parent);
            return parent;
        } else { // 处理需要两次旋转的情况：第1次旋转后即成为需要一次旋转的情况
            rotate(node);
            rotate(node);
            return node;
        }
    }

    // 返回以node为根结点的子树的第1个元素
    static Node * subtreeFirst(Node * node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 返回以node为根结点的子树的最后1个元素
    static Node * subtreeLast(Node * node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // 获取以node为根结点的子树的高度
    static int getHeight(Node * node) {
        return node != nullptr ? node->height : 0;
    }

    // 获取以node为根结点的子树的结点数
    static int getSize(Node * node) {
        return node != nullptr ? node->size : 0;
    }
};

class Solution {
public:
    int kthSmallest(TreeNode * root, int k) {
        // 中序遍历生成数值列表
        vector<int> inorderList;
        inorder(root, inorderList);
        // 构造平衡二叉搜索树
        AVL avl(inorderList);

        // 模拟1000次插入和删除操作
        vector<int> randomNums(1000);
        std::random_device rd;
        for (int i = 0; i < 1000; ++i) {
            randomNums[i] = rd()%(10001);
            avl.insert(randomNums[i]);
        }
        shuffle(randomNums); // 列表乱序
        for (int i = 0; i < 1000; ++i) {
            avl.Delete(randomNums[i]);
        }

        return avl.kthSmallest(k);
    }

private:
    void inorder(TreeNode * node, vector<int> & inorderList) {
        if (node->left != nullptr) {
            inorder(node->left, inorderList);
        }
        inorderList.push_back(node->val);
        if (node->right != nullptr) {
            inorder(node->right, inorderList);
        }
    }

    void shuffle(vector<int> & arr) {
        std::random_device rd;
        int length = arr.size();
        for (int i = 0; i < length; i++) {
            int randIndex = rd()%length;
            swap(arr[i],arr[randIndex]);
        }
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    struct compare {
        bool operator()(int a, int b) {
            return a > b;
        }
    };

    int kthSmallest(TreeNode* root, int k) {
        priority_queue<int,vector<int>,compare> tree_priority_queue;
        queue<TreeNode*> tree_node_queue;
        tree_node_queue.push(root);
        while (!tree_node_queue.empty()) {
            if(tree_node_queue.front()->left) tree_node_queue.push(tree_node_queue.front()->left);
            if(tree_node_queue.front()->right) tree_node_queue.push(tree_node_queue.front()->right);
            tree_priority_queue.push(tree_node_queue.front()->val);
            tree_node_queue.pop();
        }
        while (--k) { tree_priority_queue.pop();}
        return tree_priority_queue.top();
    }
};
```

## 复杂度分析

- 最小堆
    - 时间复杂度：$O(n \log n)$，其中 $n$ 为节点数。需要遍历所有节点并将其插入最小堆，每次插入/弹出操作为 $O(\log n)$，总共 $n$ 次。
    - 空间复杂度：$O(n)$，最小堆和队列都需要存储所有节点。

- 中序遍历
    - 时间复杂度：$O(H + k)$，其中 $H$ 为树的高度。最坏情况下 $O(n)$，但通常只需遍历到第 $k$ 个节点即可。
    - 空间复杂度：$O(H)$，递归或栈的深度为树的高度。

- 记录子树节点数
    - 预处理时间复杂度：$O(n)$，统计每个节点的子树节点数。
    - 查询时间复杂度：$O(H)$，每次查找第 $k$ 小元素只需沿树高递归。
    - 空间复杂度：$O(n)$，需要哈希表或节点字段存储每个节点的子树节点数。

- 平衡二叉搜索树
    - 单次插入/删除/查找第 $k$ 小元素的时间复杂度：$O(\log n)$。
    - 构建树的时间复杂度：$O(n)$（平衡化建树），后续每次操作 $O(\log n)$。
    - 空间复杂度：$O(n)$，需要存储所有节点及其平衡信息。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "230-kth-smallest-element-in-a-bst.cpp"
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

TEST(KthSmallestTest, Example1) {
    Solution sol;
    // 输入: [3,1,4,-1,2], k=1
    TreeNode* root = createTree({3,1,4,-1,2});
    int k = 1;
    int expected = 1;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

TEST(KthSmallestTest, Example2) {
    Solution sol;
    // 输入: [5,3,6,2,4,-1,-1,1], k=3
    TreeNode* root = createTree({5,3,6,2,4,-1,-1,1});
    int k = 3;
    int expected = 3;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

TEST(KthSmallestTest, SingleNode) {
    Solution sol;
    TreeNode* root = createTree({1});
    int k = 1;
    int expected = 1;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
    freeTree(root);
}

TEST(KthSmallestTest, LeftSkewed) {
    Solution sol;
    // 输入: [3,2,-1,1], k=2
    TreeNode* root = createTree({3,2,-1,1});
    int k = 2;
    int expected = 2;
    EXPECT_EQ(sol.kthSmallest(root, k), expected);
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
[----------] 4 tests from KthSmallestTest
[ RUN      ] KthSmallestTest.Example1
[       OK ] KthSmallestTest.Example1 (0 ms)
[ RUN      ] KthSmallestTest.Example2
[       OK ] KthSmallestTest.Example2 (0 ms)
[ RUN      ] KthSmallestTest.SingleNode
[       OK ] KthSmallestTest.SingleNode (0 ms)
[ RUN      ] KthSmallestTest.LeftSkewed
[       OK ] KthSmallestTest.LeftSkewed (0 ms)
[----------] 4 tests from KthSmallestTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.
```