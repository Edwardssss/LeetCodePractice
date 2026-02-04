/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */

// @lc code=start
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.size() < t.size()) return "";
        map<char, int> need;
        for (char c : t) need[c]++;
        int required = need.size();
        int formed = 0;
        map<char, int> window;
        int left = 0, right = 0;
        int min_len = s.size() + 1, min_left = 0;
        while (right < s.size()) {
            char c = s[right];
            window[c]++;
            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }
            while (left <= right && formed == required) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    min_left = left;
                }
                char d = s[left];
                window[d]--;
                if (need.count(d) && window[d] < need[d]) {
                    formed--;
                }
                left++;
            }
            right++;
        }
        return min_len > s.size() ? "" : s.substr(min_left, min_len);
    }
};
// @lc code=end

