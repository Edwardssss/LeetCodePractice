/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 */

// @lc code=start
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

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end
