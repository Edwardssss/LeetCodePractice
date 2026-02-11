/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int maxSum = nums[0];
        int minSum = 0;
        int currentSum = 0;
        for (int num : nums) {
            currentSum += num;
            maxSum = max(maxSum, currentSum - minSum);
            minSum = min(minSum, currentSum);
        }
        return maxSum;
    }
};
// @lc code=end
