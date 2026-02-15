/*
 * @lc app=leetcode.cn id=41 lang=cpp
 *
 * [41] 缺失的第一个正数
 */

// @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int minimum_num = 1;
        sort(nums.begin(),nums.end());
        for(int i = 0;i < nums.size();++i){
            if (nums[i] == minimum_num) {
                ++minimum_num;
            }
            else if(nums[i] > minimum_num){
                return minimum_num;
            }
            else if (nums[i] < minimum_num) {
                continue;
            }
        }
        return minimum_num;
    }
};
// @lc code=end

