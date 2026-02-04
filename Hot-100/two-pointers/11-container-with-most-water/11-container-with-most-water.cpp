/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_result = 0;
        for(size_t i = 0;i < height.size();++i){
            for (size_t j = i + 1;j < height.size();++j) {
                if(min({height[i],height[j]}) * (j - i) > max_result){
                    max_result = min({height[i],height[j]}) * (j - i);
                }
            }
        }
        return max_result;
    }
};
// @lc code=end

