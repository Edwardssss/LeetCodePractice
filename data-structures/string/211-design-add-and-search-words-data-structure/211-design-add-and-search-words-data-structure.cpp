/*
 * @lc app=leetcode.cn id=211 lang=cpp
 *
 * [211] 添加与搜索单词 - 数据结构设计
 */

// @lc code=start
#include <cstddef>
#include <string>
#include <vector>
#include <map>

using namespace std;

class WordDictionary {
public:
    struct Node{
        map<char, size_t> node_map;
        bool is_end = false;
    };
    vector<Node> node_list;
    WordDictionary() {
        this->node_list.push_back(Node());
    }

    void addWord(string word) {
        size_t cur = 0;
        for(auto i:word){
            if(node_list.at(cur).node_map.find(i) == node_list.at(cur).node_map.end()){
                node_list.at(cur).node_map[i] = node_list.size();
                node_list.push_back(Node());
            }
            cur = node_list.at(cur).node_map[i];
        }
        node_list.at(cur).is_end = true;
    }

    bool search(string word) {
        auto dfs = [&](auto&& self, size_t node, size_t idx) -> bool {
            if (idx == word.size()) {
                return node_list[node].is_end;
            }
            char ch = word[idx];
            if (ch == '.') {
                for (const auto& kv : node_list[node].node_map) {
                    if (self(self, kv.second, idx + 1)) {
                        return true;
                    }
                }
                return false;
            }
            auto it = node_list[node].node_map.find(ch);
            if (it == node_list[node].node_map.end()) {
                return false;
            }
            return self(self, it->second, idx + 1);
        };

        return dfs(dfs, 0, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
// @lc code=end

