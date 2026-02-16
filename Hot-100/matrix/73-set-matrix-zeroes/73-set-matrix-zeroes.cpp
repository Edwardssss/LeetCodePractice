/*
 * @lc app=leetcode.cn id=73 lang=cpp
 *
 * [73] 矩阵置零
 */

// @lc code=start
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        // unordered_set<int> row_set,col_set;
        // for (int i = 0; i < matrix.size(); ++i) {
        //     for (int j = 0; j < matrix[0].size(); ++j) {
        //         if(!matrix[i][j]){
        //             row_set.insert(i);
        //             col_set.insert(j);
        //         }
        //     }
        // }
        // for (auto m : row_set) {
        //     for (int i = 0;i < matrix[0].size();++i) {
        //         matrix[m][i] = 0;
        //     }
        // }
        // for (auto n : col_set){
        //     for (int j = 0;j < matrix.size();++j) {
        //         matrix[j][n] = 0;
        //     }
        // }

        unordered_set<int> zero_col;
        for(auto &m : matrix){
            auto result_index = find(m.begin(),m.end(), 0);
            bool insert_flag = false;
            while (result_index != m.end()) {
                zero_col.insert(result_index - m.begin());
                result_index = find(result_index + 1,m.end(),0);
                insert_flag = true;
            }
            if(insert_flag){
                fill(m.begin(),m.end(),0);
            }
        }
        for (auto n : zero_col){
            for (int j = 0;j < matrix.size();++j) {
                matrix[j][n] = 0;
            }
        }
    }
};
// @lc code=end

