/*
 * @lc app=leetcode.cn id=503 lang=cpp
 *
 * [503] 下一个更大元素 II
 */

// @lc code=start
#include <cmath>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result;
        float length = nums.size();
        for(int i = 0;i < nums.size();++i){
            int index = i + 1;
            int temp_index = index - nums.size() * floor(index / nums.size());
            while (temp_index % nums.size() != i) {
                if(nums[temp_index] > nums[i]){
                    result.push_back(nums[temp_index]);
                    goto next_loop;
                }
                ++index;
                temp_index = index - nums.size() * floor(index / nums.size());
            }
            result.push_back(-1);
            next_loop:continue;
        }
        return result;
    }
};
// @lc code=end

