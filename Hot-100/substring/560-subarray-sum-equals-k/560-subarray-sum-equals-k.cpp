/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int result_cnt = 0;
        for (int start = 0; start < n; ++start) {
            int sum = 0;
            for (int end = start; end < n; ++end) {
                sum += nums[end];
                if (sum == k) {
                    ++result_cnt;
                }
            }
        }
        return result_cnt;
    }
};
// @lc code=end

