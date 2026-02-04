/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 轮转数组
 */

// @lc code=start
#include <vector>

using namespace std;

class Solution {
  public:
    // 暴力解法
    /*
    void rotate(vector<int>& nums, int k) {
        vector<int> temp;
        int step = k % nums.size();
        for(int i = 0;i < nums.size();++i){
            temp.push_back(nums[(nums.size() + i - step) % nums.size()]);
        }
        nums.swap(temp);
    }
    */
    // 暂存法
    void rotate(vector<int> &nums, int k) {
        vector<int> temp;
        int step = k % nums.size();
        for (int i = nums.size() - step; i < nums.size(); ++i) {
            temp.push_back(nums[i]);
        }
        for (int j = nums.size() - 1; j > step - 1; --j) {
            nums[j] = nums[j - step];
        }
        for (int p = 0; p < step; ++p) {
            nums[p] = temp[p];
        }
    }
    // 单步轮转法
    /*
    void rotate(vector<int>& nums, int k){
        int temp = nums[nums.size() - 1];
        int step = k % nums.size();
        while (step > 0) {
            for(int i = nums.size() - 1;i > 0;--i){
                nums[i] = nums[i - 1];
            }
            nums[0] = temp;
            temp = nums[nums.size() - 1];
            --step;
        }
    }
    */
};
// @lc code=end
