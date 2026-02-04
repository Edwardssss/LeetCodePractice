/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int p = 0,q = numbers.size() - 1;
        while(p != q){
            if(numbers[p] + numbers[q] < target){
                ++p;
            }
            else if(numbers[p] + numbers[q] > target){
                --q;
            }
            else {
                return {p + 1,q + 1};
            }
        }
        return {};
    }
};
// @lc code=end

