/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */

// @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty()) {
            return {};
        }
        vector<int> result;
        for (int i = 0; i <= (int)nums.size() - k; ++i) {
            result.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
        }
        return result;
    }
};
// @lc code=end

