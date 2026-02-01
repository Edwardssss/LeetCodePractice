/*
 * @lc app=leetcode.cn id=496 lang=cpp
 *
 * [496] 下一个更大元素 I
 */

// @lc code=start
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        for(auto raw_num:nums1){
            auto find_index = find(nums2.begin(),nums2.end(),raw_num);
            int dis = distance(nums2.begin(),find_index);
            for(auto i = nums2.begin() + dis;i != nums2.end();++i){
                if(*i > raw_num){
                    result.push_back(*i);
                    goto next;
                }
            }
            result.push_back(-1);
            next:continue;
        }
        return result;
    }
};
// @lc code=end

