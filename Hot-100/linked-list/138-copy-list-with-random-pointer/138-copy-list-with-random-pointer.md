# 138. 随机链表的复制

## 题目描述

138. 随机链表的复制

给你一个长度为 `n` 的链表，每个节点包含一个额外增加的随机指针 `random` ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 **深拷贝**。 深拷贝应该正好由 `n` 个 **全新** 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 `next` 指针和 `random` 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 `X` 和 `Y` 两个节点，其中 `X.random --> Y` 。那么在复制链表中对应的两个节点 `x` 和 `y` ，同样有 `x.random --> y` 。

返回复制链表的头节点。

用一个由 `n` 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 `[val, random_index]` 表示：

- `val`：一个表示 `Node.val` 的整数。
- `random_index`：随机指针指向的节点索引（范围从 `0` 到 `n-1`）；如果不指向任何节点，则为`null` 。
你的代码 **只** 接受原链表的头节点 `head` 作为传入参数。

![](./1.png)

示例 1：

>  **输入**
>
> head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
>
>  **输出**
>
> [[7,null],[13,0],[11,4],[10,2],[1,0]]

![](./2.png)

示例 2：

>  **输入**
>
> head = [[1,1],[2,1]]
>
>  **输出**
>
> [[1,1],[2,1]]

![](./3.png)

示例 3：

>  **输入**
>
> head = [[3,null],[3,0],[3,null]]
>
>  **输出**
>
> [[3,null],[3,0],[3,null]]

提示：

- `0 <= n <= 1000`
- `-104 <= Node.val <= 104`
- `Node.random` 为 `null` 或指向链表中的节点。

## 思路分析

这道题没想出来，LeetCode官方用了两种不同的方法来解决：

**回溯 + 哈希表**

本题要求我们对一个特殊的链表进行深拷贝。如果是普通链表，我们可以直接按照遍历的顺序创建链表节点。而本题中因为随机指针的存在，当我们拷贝节点时，「当前节点的随机指针指向的节点」可能还没创建，因此我们需要变换思路。一个可行方案是，我们利用回溯的方式，让每个节点的拷贝操作相互独立。对于当前节点，我们首先要进行拷贝，然后我们进行「当前节点的后继节点」和「当前节点的随机指针指向的节点」拷贝，拷贝完成后将创建的新节点的指针返回，即可完成当前节点的两指针的赋值。

具体地，我们用哈希表记录每一个节点对应新节点的创建情况。遍历该链表的过程中，我们检查「当前节点的后继节点」和「当前节点的随机指针指向的节点」的创建情况。如果这两个节点中的任何一个节点的新节点没有被创建，我们都立刻递归地进行创建。当我们拷贝完成，回溯到当前层时，我们即可完成当前节点的指针赋值。注意一个节点可能被多个其他节点指向，因此我们可能递归地多次尝试拷贝某个节点，为了防止重复拷贝，我们需要首先检查当前节点是否被拷贝过，如果已经拷贝过，我们可以直接从哈希表中取出拷贝后的节点的指针并返回即可。

在实际代码中，我们需要特别判断给定节点为空节点的情况。

官方代码实现示例如下：

```c++
class Solution {
public:
    unordered_map<Node*, Node*> cachedNode;

    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        if (!cachedNode.count(head)) {
            Node* headNew = new Node(head->val);
            cachedNode[head] = headNew;
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        return cachedNode[head];
    }
};
```

**迭代 + 节点拆分**

注意到方法一需要使用哈希表记录每一个节点对应新节点的创建情况，而我们可以使用一个小技巧来省去哈希表的空间。

我们首先将该链表中每一个节点拆分为两个相连的节点，例如对于链表 $A→B→C$，我们可以将其拆分为 $A→A′→B→B′→C→C′$。对于任意一个原节点 $S$，其拷贝节点 $S′$即为其后继节点。

这样，我们可以直接找到每一个拷贝节点 $S′$的随机指针应当指向的节点，即为其原节点 $S$ 的随机指针指向的节点 $T$ 的后继节点 $T′$ 。需要注意原节点的随机指针可能为空，我们需要特别判断这种情况。

当我们完成了拷贝节点的随机指针的赋值，我们只需要将这个链表按照原节点与拷贝节点的种类进行拆分即可，只需要遍历一次。同样需要注意最后一个拷贝节点的后继节点为空，我们需要特别判断这种情况。

## 代码实现

代码实现如下：

```c++
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = node->next;
            nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
        }
        Node* headNew = head->next;
        for (Node* node = head; node != nullptr; node = node->next) {
            Node* nodeNew = node->next;
            node->next = node->next->next;
            nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;
        }
        return headNew;
    }
};
```

## 复杂度分析

- 回溯 + 哈希表

    - 时间复杂度：$O(n)$，其中 $n$ 是链表的长度。对于每个节点，我们至多访问其「后继节点」和「随机指针指向的节点」各一次，均摊每个点至多被访问两次。
    - 空间复杂度：$O(n)$，其中 $n$ 是链表的长度。为哈希表的空间开销。

- 迭代 + 节点拆分

    - 时间复杂度：$O(n)$。其中 $n$ 是链表的节点数。每个节点被遍历常数次，无论是插入新节点、设置 random 指针还是拆分链表，整体都是线性复杂度。
    - 空间复杂度：$O(1)$。只使用了常数级别的额外空间（不计输出链表），没有使用额外的数据结构存储节点映射。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "138-copy-list-with-random-pointer.cpp"
#include <vector>
#include <tuple>
#include <unordered_set>
#include <unordered_map>

// 辅助函数：根据节点值和random索引创建链表
Node* createRandomList(const std::vector<std::tuple<int, int>>& nodes) {
    if (nodes.empty()) return nullptr;
    std::vector<Node*> nodePtrs;
    for (const auto& [val, _] : nodes) {
        nodePtrs.push_back(new Node(val));
    }
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i + 1 < nodePtrs.size()) nodePtrs[i]->next = nodePtrs[i+1];
        int randomIdx = std::get<1>(nodes[i]);
        if (randomIdx >= 0) nodePtrs[i]->random = nodePtrs[randomIdx];
    }
    return nodePtrs[0];
}

// 辅助函数：链表转vector，返回每个节点的(val, random_index)
std::vector<std::tuple<int, int>> listToVector(Node* head) {
    std::vector<Node*> nodes;
    for (Node* p = head; p; p = p->next) nodes.push_back(p);
    std::vector<std::tuple<int, int>> res;
    for (size_t i = 0; i < nodes.size(); ++i) {
        int val = nodes[i]->val;
        int randomIdx = -1;
        if (nodes[i]->random) {
            for (size_t j = 0; j < nodes.size(); ++j) {
                if (nodes[i]->random == nodes[j]) {
                    randomIdx = j;
                    break;
                }
            }
        }
        res.emplace_back(val, randomIdx);
    }
    return res;
}

// 记录链表节点地址，便于判断浅拷贝
std::unordered_set<Node*> collectNodes(Node* head) {
    std::unordered_set<Node*> nodes;
    while (head) {
        if (nodes.count(head)) break;
        nodes.insert(head);
        head = head->next;
    }
    return nodes;
}

// 释放链表内存，避免释放共享节点
void freeRandomList(Node* head, const std::unordered_set<Node*>& skip) {
    std::unordered_map<Node*, bool> visited;
    while (head) {
        if (visited[head]) break;
        visited[head] = true;
        Node* tmp = head;
        head = head->next;
        if (!skip.count(tmp)) delete tmp;
    }
}

TEST(CopyRandomListTest, Example1) {
    // 输入: [[7,null],[13,0],[11,4],[10,2],[1,0]]
    std::vector<std::tuple<int, int>> nodes = {
        {7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}
    };
    Node* head = createRandomList(nodes);
    Solution sol;
    Node* copied = sol.copyRandomList(head);
    auto expected = nodes;
    auto result = listToVector(copied);
    EXPECT_EQ(result, expected);
    auto originalNodes = collectNodes(head);
    freeRandomList(head, {});
    freeRandomList(copied, originalNodes);
}

TEST(CopyRandomListTest, SingleNodeSelfRandom) {
    std::vector<std::tuple<int, int>> nodes = {{1, 0}};
    Node* head = createRandomList(nodes);
    Solution sol;
    Node* copied = sol.copyRandomList(head);
    auto expected = nodes;
    auto result = listToVector(copied);
    EXPECT_EQ(result, expected);
    auto originalNodes = collectNodes(head);
    freeRandomList(head, {});
    freeRandomList(copied, originalNodes);
}

TEST(CopyRandomListTest, EmptyList) {
    Node* head = nullptr;
    Solution sol;
    Node* copied = sol.copyRandomList(head);
    EXPECT_EQ(copied, nullptr);
    // 无需释放
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：

```
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from CopyRandomListTest
[ RUN      ] CopyRandomListTest.Example1
[       OK ] CopyRandomListTest.Example1 (0 ms)
[ RUN      ] CopyRandomListTest.SingleNodeSelfRandom
[       OK ] CopyRandomListTest.SingleNodeSelfRandom (0 ms)
[ RUN      ] CopyRandomListTest.EmptyList
[       OK ] CopyRandomListTest.EmptyList (0 ms)
[----------] 3 tests from CopyRandomListTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
```
