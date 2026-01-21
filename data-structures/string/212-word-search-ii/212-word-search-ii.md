# 212. Word Search II

## 题目描述

212. 单词搜索 II

给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。

示例 1：

![](./1.jpg)

>  **输入**
>
> board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
>
>  **输出**
>
> ["eat","oath"]

示例 2：

![](./2.jpg)

>  **输入**
>
> board = [["a","b"],["c","d"]], words = ["abcb"]
>
>  **输出**
>
> []

提示：

- `m == board.length`
- `n == board[i].length`
- `1 <= m`, `n <= 12`
- `board[i][j]` 是一个小写英文字母
- `1 <= words.length <= 3 * 10^4`
- `1 <= words[i].length <= 10`
- `words[i]` 由小写英文字母组成
- `words` 中的所有字符串互不相同

## 思路分析

本题是基于208题的一个拓展。不同于之前的题目，本题使用了一个二维结构来存储字母表。和之前的题目一样的地方是，都是输入一个单词然后去递归查找该单词是否存在，所以仍然使用DFS递归查找，每个小方格最多有4个邻接的小方格，所以最多需要向4个方向进行DFS搜索。当搜索过程中发现当前路径无法满足单词前缀要求的时候，就可以立刻进行截断，并尝试其他路径（即DFS回溯）。若能够完全匹配上，就可以直接返回结果了，避免多次搜索。

## 代码实现

代码实现如下：
```c++
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<string> findWords(vector<vector<char>> &board,
                            vector<string> &words) {
        vector<string> result;
        if (board.empty() || board[0].empty() || words.empty()) {
            return result;
        }

        TrieNode root;
        for (const auto &w : words) {
            insertWord(root, w);
        }

        const int rows = static_cast<int>(board.size());
        const int cols = static_cast<int>(board[0].size());
        string path;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dfs(board, i, j, root, path, result);
            }
        }

        return result;
    }

  private:
    struct TrieNode {
        TrieNode *next[26];
        bool end;
        TrieNode() : end(false) {
            for (auto &p : next) {
                p = nullptr;
            }
        }
    };

    void insertWord(TrieNode &root, const string &word) {
        TrieNode *node = &root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->next[idx]) {
                node->next[idx] = new TrieNode();
            }
            node = node->next[idx];
        }
        node->end = true;
    }

    void dfs(vector<vector<char>> &board, int r, int c, TrieNode &node,
            string &path, vector<string> &result) {
        if (r < 0 || c < 0 || r >= static_cast<int>(board.size()) ||
            c >= static_cast<int>(board[0].size())) {
            return;
        }
        char ch = board[r][c];
        if (ch == '#') {
            return;
        }
        TrieNode *nextNode = node.next[ch - 'a'];
        if (!nextNode) {
            return;
        }

        board[r][c] = '#';
        path.push_back(ch);
        if (nextNode->end) {
            result.push_back(path);
            nextNode->end = false;
        }

        dfs(board, r + 1, c, *nextNode, path, result);
        dfs(board, r - 1, c, *nextNode, path, result);
        dfs(board, r, c + 1, *nextNode, path, result);
        dfs(board, r, c - 1, *nextNode, path, result);

        path.pop_back();
        board[r][c] = ch;
    }
};
```

## 复杂度分析

- 时间复杂度

    - 构建 Trie 树：
假设单词总数为$W$，所有单词的总长度为$L$，则插入所有单词到 Trie 的时间复杂度为$O(L)$。

    - DFS 搜索：
假设网格大小为$m\times n$，每个格子最多被访问一次。在最坏情况下，每个格子都可能作为起点进行 DFS，DFS 的深度不会超过单词最大长度 $k$（因为 Trie 没有更长的路径）。每次递归最多有 4 个方向，理论上单次 DFS 的复杂度为$O(4k)$，但由于 Trie 会进行剪枝，实际远小于这个值。总体上，DFS 的总复杂度近似为$O(mnk)$，其中$k$是单词最大长度。

- 空间复杂度
    - Trie 树空间：
最多$O(L)$，即所有单词的总长度（每个字符一个节点，最坏情况无公共前缀）。
    - 递归栈空间：
最深递归为单词最大长度$k$，即O(k)。

    - 其他辅助空间：
结果集空间$O(W)$，$W$为找到的单词数。路径字符串$O(k)$。

## 测试用例

测试用例如下：
```c++
#include <algorithm>
#include <gtest/gtest.h>
#include "212-word-search-ii.cpp"

static Solution solution;

TEST(WordSearchIITest, Example1) {
    std::vector<std::vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    std::vector<std::string> words = {"oath","pea","eat","rain"};
    std::vector<std::string> expected = {"oath","eat"};
    auto result = solution.findWords(board, words);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(result, expected);
}

TEST(WordSearchIITest, Example2) {
    std::vector<std::vector<char>> board = {
        {'a','b'},
        {'c','d'}
    };
    std::vector<std::string> words = {"abcb"};
    std::vector<std::string> expected = {};
    auto result = solution.findWords(board, words);
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from WordSearchIITest
[ RUN      ] WordSearchIITest.Example1
[       OK ] WordSearchIITest.Example1 (0 ms)
[ RUN      ] WordSearchIITest.Example2
[       OK ] WordSearchIITest.Example2 (0 ms)
[----------] 2 tests from WordSearchIITest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 2 tests.
```