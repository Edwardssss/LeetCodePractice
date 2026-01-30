/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> string_stack;
        if(s.size() <= 1) return false;
        for(auto i:s){
            if((i == '(') || (i == '[') || (i == '{')){
                string_stack.push(i);
            }
            else {
                if(string_stack.empty()) return false;
                switch (string_stack.top()) {
                    case '(':if(i == ')') break;else return false;
                    case '[':if(i == ']') break;else return false;
                    case '{':if(i == '}') break;else return false;
                    default: return false;
                }
                string_stack.pop();
            }
        }
        if(string_stack.empty()) return true;else return false;
    }
};
// @lc code=end

