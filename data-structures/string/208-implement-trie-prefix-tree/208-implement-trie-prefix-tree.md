# 208. Implement Trie (Prefix Tree)

## 题目描述

208. **实现 Trie (前缀树) Medium**

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类：

- `Trie()` 初始化前缀树对象。
- `void insert(String word)` 向前缀树中插入字符串 word。
- `boolean search(String word)` 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
- `boolean startsWith(String prefix)` 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

示例：

>   **输入**
>
>  ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
>
>  [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
>
>   **输出**
>
>   [null, null, true, false, true, null, true]
>
>   **解释**
>
>   Trie trie = new Trie();
>   trie.insert("apple");
>   trie.search("apple");   // 返回 True
>   trie.search("app");     // 返回 False
>   trie.startsWith("app"); // 返回 True
>   trie.insert("app");
>   trie.search("app");     // 返回 True

提示：

- `1 <= word.length, prefix.length <= 2000`
- `word`和 `prefix` 仅由小写英文字母组成
- `insert`、`search` 和 `startsWith` 调用次数 总计 不超过$3\times 10^4$次

## 思路分析

这道题是前缀树的实现。前缀树需要注意的是：**根节点为空**。前缀树的每个节点表示一个字符，但并不是所有由前缀树表示的字符串都是有意义的（也就是不一定能够组成单词）。如果我们只想在前缀树中存储单词，那么我们就需要在每个节点中声明一个布尔值（Boolean）作为标志，来表明该节点所表示的字符串是否可以作为一个单词。（这也是后面`search`判断是否存储该单词的关键，否则的话识别到前缀也可能会归类为单词）

前缀树可以用数组或者HashMap实现。如果我们只存储含有字母 `a` 到 `z` 的字符串，我们可以在每个节点中声明一个大小为26的数组来存储其子节点。对于特定字符 `c`，我们可以使用 `c - 'a'` 作为索引来查找数组中相应的子节点。而对于HashMap，我们可以在每个节点中都声明一个Hashmap，其中Map的键是字符，值是相对应的子节点。

## 代码实现

代码实现如下：
```c++
#include <cstddef>
#include <map>
#include <string>
#include <vector>


using namespace std;

class Trie {
  public:
    struct Node {
        map<char, int> next;
        bool end = false;
    };
    vector<Node> trie;

    Trie() {
        trie.clear();
        trie.push_back(Node());
    }

    void insert(string word) {
        size_t cur = 0;
        for (auto i : word) {
            if (trie[cur].next.find(i) == trie[cur].next.end()) {
                trie[cur].next[i] = trie.size();
                trie.push_back(Node());
            }
            cur = trie[cur].next[i]; // 需要更新cur
        }
        trie[cur].end = true; // 标记单词结尾
    }

    bool search(string word) {
        size_t cur = 0;
        for (auto i : word) {
            if (trie[cur].next.find(i) == trie[cur].next.end()) {
                return false;
            }
            cur = trie[cur].next[i]; // 需要更新cur
        }
        return trie[cur].end; // 只有到达结尾且end为true才返回true
    }

    bool startsWith(string prefix) {
        size_t cur = 0;
        for (auto i : prefix) {
            if (trie[cur].next.find(i) == trie[cur].next.end()) {
                return false;
            }
            cur = trie[cur].next[i];
        }
        return true;
    }
};
```

## 复杂度分析

- 插入（insert）

    - 时间复杂度：O(L)，其中 L 为插入单词的长度。每次插入需要遍历单词的每个字符。
    - 空间复杂度：O(L)，最坏情况下每个字符都需要新建一个节点。

- 查找（search）

    - 时间复杂度：O(L)，L 为查找单词的长度。需要遍历单词的每个字符。
    - 空间复杂度：O(1)，只使用了常数级别的额外空间。

- 前缀查找（startsWith）

    - 时间复杂度：O(L)，L 为前缀的长度。需要遍历前缀的每个字符。
    - 空间复杂度：O(1)，只使用了常数级别的额外空间。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "208.实现-trie-前缀树.cpp"

static Trie trie;

TEST(TrieTest, InsertApple) {
    trie.insert("apple");
    SUCCEED();
}

TEST(TrieTest, SearchApple) {
    EXPECT_TRUE(trie.search("apple"));
}

TEST(TrieTest, SearchApp) {
    EXPECT_FALSE(trie.search("app"));
}

TEST(TrieTest, StartsWithApp) {
    EXPECT_TRUE(trie.startsWith("app"));
}

TEST(TrieTest, InsertApp) {
    trie.insert("app");
    SUCCEED();
}

TEST(TrieTest, SearchAppAfterInsert) {
    EXPECT_TRUE(trie.search("app"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from TrieTest
[ RUN      ] TrieTest.InsertApple
[       OK ] TrieTest.InsertApple (0 ms)
[ RUN      ] TrieTest.SearchApple
[       OK ] TrieTest.SearchApple (0 ms)
[ RUN      ] TrieTest.SearchApp
[       OK ] TrieTest.SearchApp (0 ms)
[ RUN      ] TrieTest.StartsWithApp
[       OK ] TrieTest.StartsWithApp (0 ms)
[ RUN      ] TrieTest.InsertApp
[       OK ] TrieTest.InsertApp (0 ms)
[ RUN      ] TrieTest.SearchAppAfterInsert
[       OK ] TrieTest.SearchAppAfterInsert (0 ms)
[----------] 6 tests from TrieTest (3 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 6 tests.
```