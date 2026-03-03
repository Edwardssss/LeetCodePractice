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