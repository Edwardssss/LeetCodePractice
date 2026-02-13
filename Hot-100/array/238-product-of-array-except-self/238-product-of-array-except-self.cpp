/*
 * @lc app=leetcode.cn id=238 lang=cpp
 *
 * [238] 除了自身以外数组的乘积
 */

// @lc code=start
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> preffix,suffix,result;
        int length = nums.size();
        preffix.push_back(1);
        suffix.push_back(1);
        for(int i = 0;i < length;++i){
            preffix.push_back(preffix[i] * nums[i]);
            suffix.push_back(suffix[i] * nums[length - i - 1]);
        }
        for(int j = 0;j < length;++j){
            result.push_back(preffix[j] * suffix[length - j - 1]);
        }
        return result;
    }
};
// @lc code=end

