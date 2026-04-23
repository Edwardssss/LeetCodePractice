/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1) return;
        if(nums.size() == 2) {
            swap(nums[0],nums[1]);
            return;
        }
        for(int i = nums.size();i > 1;--i) {
            if(nums[i] > nums[i - 1]) {
                swap(nums[i],nums[i - 1]);
                return;
            }
        }
        sort(nums.begin(),nums.end());
    }
};
// @lc code=end
