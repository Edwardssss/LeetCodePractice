/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0){
            return 0;
        }
        else if(s.length() == 1){
            return 1;
        }
        int window_length = 1;
        int begin = 0,end = 1;
        bool enlarge_window_flag;
        bool exit_flag = false;
        while(end != s.length()){
            enlarge_window_flag = true;
            for (int i = begin; i < end; ++i) {
                if(s[end] == s[i]){
                    ++begin;
                    exit_flag = false; // 重置
                    while (!exit_flag) {
                        exit_flag = true;
                        for (int j = begin; j < end; ++j) {
                            if(s[end] == s[j]){
                                begin++;
                                exit_flag = false;
                                break;
                            }
                        }
                    }
                    ++end;
                    window_length = max(window_length, end - begin); // 补更新
                    enlarge_window_flag = false;
                    break;
                }
            }
            if(enlarge_window_flag){
                ++end;
                window_length = max(window_length,end - begin);
            }
        }
        return window_length;
    }
};
// @lc code=end

