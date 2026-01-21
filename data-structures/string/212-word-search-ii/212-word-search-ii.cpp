/*
 * @lc app=leetcode.cn id=212 lang=cpp
 *
 * [212] 单词搜索 II
 */

// @lc code=start
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
// @lc code=end
