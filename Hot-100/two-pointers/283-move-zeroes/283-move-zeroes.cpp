/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if (nums.size() == 1) return;
        for (int i = 0,cnt = 0; cnt < nums.size(); ++i,++cnt) {
            while (nums[i] == 0){
                nums.erase(nums.begin() + i);
                nums.push_back(0);
                if(++cnt >= nums.size()) break;
            }
        }
        return;
    }
};
// @lc code=end
