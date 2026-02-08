/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
 */

// @lc code=start
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(s.length() < p.length()) return {};
        vector<int> result;
        unordered_map<char, int> p_char;
        unordered_map<char, int> win_char;
        int begin = 0,end = p.length() - 1;
        for (int i = 0;i < p.length();++i) {
            if(win_char.count(s[i])){
                ++win_char[s[i]];
            }
            else {
                win_char[s[i]] = 1;
            }
            if (p_char.count(p[i])) {
                ++p_char[p[i]];
            }
            else {
                p_char[p[i]] = 1;
            }
        }
        while (end < s.length()) {
            if (win_char == p_char) {
                result.push_back(begin);
            }
            ++end;
            if (end < s.length()) {
                win_char[s[end]]++;
                win_char[s[begin]]--;
                if (win_char[s[begin]] == 0) {
                    win_char.erase(s[begin]);
                }
                ++begin;
            }
        }
        return result;
    }
};
// @lc code=end

