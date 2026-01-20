# 211. Design Add and Search Words Data Structure

## 题目描述

211. **添加与搜索单词 - 数据结构设计 Medium**

请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配。

实现词典类 `WordDictionary`：

- `WordDictionary()` 初始化词典对象
- `void addWord(word)` 将 `word` 添加到数据结构中，之后可以对它进行匹配
- `bool search(word)` 如果数据结构中存在字符串与 `word` 匹配，则返回 `true` ；否则，返回 `false`。`word` 中可能包含一些 `'.'` ，每个 `.` 都可以表示任何一个字母。


示例：

> **输入**
>
> ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
>
> [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
>
> **输出**
>
> [null,null,null,null,false,true,true,true]
>
> **解释**
>
> WordDictionary wordDictionary = new WordDictionary();
> wordDictionary.addWord("bad");
> wordDictionary.addWord("dad");
> wordDictionary.addWord("mad");
> wordDictionary.search("pad"); // 返回 False
> wordDictionary.search("bad"); // 返回 True
> wordDictionary.search(".ad"); // 返回 True
> wordDictionary.search("b.."); // 返回 True

提示：

- `1 <= word.length <= 25`
- `addWord` 中的 `word` 由小写英文字母组成
- `search` 中的 `word` 由 `'.'` 或小写英文字母组成
- 最多调用 $10^4$ 次 `addWord` 和 `search`

## 思路分析

这道题是基于208题的基础上拓展的，可以直接复用数据结构和添加节点部分的代码。但是需要对`'.'`进行额外的处理，这里使用DFS进行处理。

## 代码实现

代码实现如下：
```c++
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
```

## 复杂度分析

- 插入（addWord）

    - 时间复杂度：O(L)，其中 L 为插入单词的长度。需要沿着字典树走完每个字符。
    - 空间复杂度：O(L)，最坏情况下每个字符都需要新建一个节点。

- 查找（search）

    - 时间复杂度：
        - 若不含 `.`，为 O(L)
        - 若包含 `.`，最坏 O(b^k · L)，b 为平均分支数（≤26），k 为 . 个数；极端情况下可达 O(节点数)

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "211-design-add-and-search-words-data-structure.cpp"

static WordDictionary dict;

TEST(WordDictionaryTest, AddBad) {
    dict.addWord("bad");
    SUCCEED();
}

TEST(WordDictionaryTest, AddDad) {
    dict.addWord("dad");
    SUCCEED();
}

TEST(WordDictionaryTest, AddMad) {
    dict.addWord("mad");
    SUCCEED();
}

TEST(WordDictionaryTest, SearchPad) {
    EXPECT_FALSE(dict.search("pad"));
}

TEST(WordDictionaryTest, SearchBad) {
    EXPECT_TRUE(dict.search("bad"));
}

TEST(WordDictionaryTest, SearchDotAd) {
    EXPECT_TRUE(dict.search(".ad"));
}

TEST(WordDictionaryTest, SearchBDotDot) {
    EXPECT_TRUE(dict.search("b.."));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 7 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 7 tests from WordDictionaryTest
[ RUN      ] WordDictionaryTest.AddBad
[       OK ] WordDictionaryTest.AddBad (0 ms)
[ RUN      ] WordDictionaryTest.AddDad
[       OK ] WordDictionaryTest.AddDad (0 ms)
[ RUN      ] WordDictionaryTest.AddMad
[       OK ] WordDictionaryTest.AddMad (0 ms)
[ RUN      ] WordDictionaryTest.SearchPad
[       OK ] WordDictionaryTest.SearchPad (0 ms)
[ RUN      ] WordDictionaryTest.SearchBad
[       OK ] WordDictionaryTest.SearchBad (0 ms)
[ RUN      ] WordDictionaryTest.SearchDotAd
[       OK ] WordDictionaryTest.SearchDotAd (0 ms)
[ RUN      ] WordDictionaryTest.SearchBDotDot
[       OK ] WordDictionaryTest.SearchBDotDot (0 ms)
[----------] 7 tests from WordDictionaryTest (4 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (5 ms total)
[  PASSED  ] 7 tests.
```