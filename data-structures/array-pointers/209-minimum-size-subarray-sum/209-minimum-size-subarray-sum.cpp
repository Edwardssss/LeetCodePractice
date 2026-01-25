/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int min_len = 10e5;
        int left = 0, sum = 0;
        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                min_len = min(min_len, right - left + 1);
                sum -= nums[left++];
            }
        }
        return min_len == 10e5 ? 0 : min_len;
    }
};
// @lc code=end

