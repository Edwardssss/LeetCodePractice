/*
 * @lc app=leetcode.cn id=240 lang=cpp
 *
 * [240] 搜索二维矩阵 II
 */

// @lc code=start
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for(int i = 0;i < matrix.size();++i){
            for(int j = 0;j < matrix[0].size();++j){
                if (matrix[i][j] == target) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end

