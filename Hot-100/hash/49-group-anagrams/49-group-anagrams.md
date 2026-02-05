# 49. Group Anagrams

## 题目描述

49. 字母异位词分组

给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

示例 1:

>  **输入**
>
> strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
>
>  **输出**
>
> [["bat"],["nat","tan"],["ate","eat","tea"]]
>
>  **解释**
>
> 在 strs 中没有字符串可以通过重新排列来形成 "bat"。
>
> 字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
>
> 字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。

示例 2:

>  **输入**
>
> strs = [""]
>
>  **输出**
>
> [[""]]

示例 3:

>  **输入**
>
> strs = ["a"]
>
>  **输出**
>
> [["a"]]

提示：

- `1 <= strs.length <= 104`
- `0 <= strs[i].length <= 100`
- `strs[i]` 仅包含小写字母

## 思路分析

这道题并不难，但是我没写出来。之前想的是对字符串进行哈希编码，但是想想感觉容易哈希碰撞，而且哈希编码肯定会和字符位置相关的，所以不适用于这道题。

LeetCode官方有两种解法：排序法和计数法，其中排序法写在代码实现部分中。

排序法考虑到互为字母异位词的两个字符串包含的字母相同，因此对两个字符串分别进行排序之后得到的字符串一定是相同的，故可以将排序之后的字符串作为哈希表的键。

计数法考虑到互为字母异位词的两个字符串包含的字母相同，因此两个字符串中的相同字母出现的次数一定是相同的，故可以将每个字母出现的次数使用字符串表示，作为哈希表的键。由于字符串只包含小写字母，因此对于每个字符串，可以使用长度为 26 的数组记录每个字母出现的次数。需要注意的是，在使用数组作为哈希表的键时，不同语言的支持程度不同，因此不同语言的实现方式也不同。

官方代码示例如下所示：

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [fn = hash<int>{}] (const array<int, 26>& arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string& str: strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};
```

## 代码实现

代码实现如下：
```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};
```

## 复杂度分析

- 排序法

    - 时间复杂度：$O(nklogk)$，其中 $n$ 是 $strs$ 中的字符串的数量，$k$ 是 $strs$ 中的字符串的的最大长度。
    - 空间复杂度：$O(nk)$，其中 $n$ 是 $strs$ 中的字符串的数量，$k$ 是 $strs$ 中的字符串的的最大长度。

- 计数法

    - 时间复杂度：$O(n(k+∣Σ∣))$，其中 $n$ 是 $strs$ 中的字符串的数量，$k$ 是 $strs$ 中的字符串的的最大长度，$Σ$ 是字符集，在本题中字符集为所有小写字母，$∣Σ∣=26$。
    - 空间复杂度：$O(n(k+∣Σ∣))$，其中 $n$ 是 $strs$ 中的字符串的数量，$k$ 是 $strs$ 中的字符串的最大长度，$Σ$ 是字符集，在本题中字符集为所有小写字母，$∣Σ∣=26$。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "49-group-anagrams.cpp"

static Solution solution;

void sortInner(std::vector<std::vector<std::string>>& v) {
    for (auto& group : v) {
        std::sort(group.begin(), group.end());
    }
    std::sort(v.begin(), v.end());
}

TEST(GroupAnagramsTest, Example1) {
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<std::vector<std::string>> expected = {
        {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}
    };
    auto result = solution.groupAnagrams(strs);
    sortInner(result);
    sortInner(expected);
    EXPECT_EQ(result, expected);
}

TEST(GroupAnagramsTest, Example2) {
    std::vector<std::string> strs = {""};
    std::vector<std::vector<std::string>> expected = {{""}};
    auto result = solution.groupAnagrams(strs);
    sortInner(result);
    sortInner(expected);
    EXPECT_EQ(result, expected);
}

TEST(GroupAnagramsTest, Example3) {
    std::vector<std::string> strs = {"a"};
    std::vector<std::vector<std::string>> expected = {{"a"}};
    auto result = solution.groupAnagrams(strs);
    sortInner(result);
    sortInner(expected);
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
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from GroupAnagramsTest
[ RUN      ] GroupAnagramsTest.Example1
[       OK ] GroupAnagramsTest.Example1 (0 ms)
[ RUN      ] GroupAnagramsTest.Example2
[       OK ] GroupAnagramsTest.Example2 (0 ms)
[ RUN      ] GroupAnagramsTest.Example3
[       OK ] GroupAnagramsTest.Example3 (0 ms)
[----------] 3 tests from GroupAnagramsTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
```
