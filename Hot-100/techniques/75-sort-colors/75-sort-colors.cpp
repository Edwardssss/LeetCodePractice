/*
 * @lc app=leetcode.cn id=75 lang=cpp
 *
 * [75] 颜色分类
 */
#include <utility>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    void sortColors(vector<int>& nums) {
        for(int i = 0;i < nums.size() - 1;++i){
            for(int j = 0;j < nums.size() - 1 - i;++j){
                if(nums[j + 1] < nums[j]) swap(nums[j],nums[j + 1]);
            }
        }
    }
};
// @lc code=end

