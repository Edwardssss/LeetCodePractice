/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] 最长连续序列
 */

// @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return 1;
        sort(nums.begin(), nums.end());
        int max_length = 1;
        int cur_length = 1;
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1]) {
                continue;
            } else if (nums[i] == nums[i - 1] + 1) {
                ++cur_length;
            } else {
                cur_length = 1;
            }
            if (cur_length > max_length) {
                max_length = cur_length;
            }
        }
        return max_length;
    }
};
// @lc code=end

