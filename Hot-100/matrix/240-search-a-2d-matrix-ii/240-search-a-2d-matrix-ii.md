# 240. 搜索二维矩阵 II

## 题目描述

240. 搜索二维矩阵 II

编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。

![](./1.jpg)

示例 1：

>  **输入**
>
> matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
>
>  **输出**
>
> true

![](./2.jpg)

示例 2：

>  **输入**
>
> matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
>
>  **输出**
>
> false

提示：

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= n, m <= 300`
- `-109 <= matrix[i][j] <= 109`
- 每行的所有元素从左到右升序排列
- 每列的所有元素从上到下升序排列
- `-109 <= target <= 109`

## 思路分析

这道题只想到了暴力算法实现，LeetCode官方给出了其他两种更高效的解法：二分查找和Z字形查找。

**二分查找**

由于矩阵 $matrix$ 中每一行的元素都是升序排列的，因此我们可以对每一行都使用一次二分查找，判断 $target$ 是否在该行中，从而判断 $target$ 是否出现。

官方代码实现如下：

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (const auto& row: matrix) {
            auto it = lower_bound(row.begin(), row.end(), target);
            if (it != row.end() && *it == target) {
                return true;
            }
        }
        return false;
    }
};
```

**Z字形查找**

我们可以从矩阵 $matrix$ 的右上角 $(0,n−1)$ 进行搜索。在每一步的搜索过程中，如果我们位于位置 $(x,y)$，那么我们希望在以 $matrix$ 的左下角为左下角、以 $(x,y)$ 为右上角的矩阵中进行搜索，即行的范围为 $[x,m−1]$，列的范围为 $[0,y]$：

- 如果 $matrix[x,y]=target$，说明搜索完成；

- 如果 $matrix[x,y]>target$，由于每一列的元素都是升序排列的，那么在当前的搜索矩阵中，所有位于第 $y$ 列的元素都是严格大于 $target$ 的，因此我们可以将它们全部忽略，即将 $y$ 减少 1；

- 如果 $matrix[x,y]<target$，由于每一行的元素都是升序排列的，那么在当前的搜索矩阵中，所有位于第 $x$ 行的元素都是严格小于 $target$ 的，因此我们可以将它们全部忽略，即将 $x$ 增加 1。

在搜索的过程中，如果我们超出了矩阵的边界，那么说明矩阵中不存在 $target$。

官方代码实现如下：

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0) {
            if (matrix[x][y] == target) {
                return true;
            }
            if (matrix[x][y] > target) {
                --y;
            }
            else {
                ++x;
            }
        }
        return false;
    }
};
```

## 代码实现

代码实现如下：

```c++
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
```

## 复杂度分析

- 暴力搜索

    - 时间复杂度：$O(mn)$
    - 空间复杂度：$O(1)$

- 二分查找

    - 时间复杂度：$O(m\log n)$
    - 空间复杂度：$O(1)$

- Z字形查找

    - 时间复杂度：$O(m+n)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "240-search-a-2d-matrix-ii.cpp"
#include <vector>

static Solution solution;

TEST(SearchMatrixIITest, Example1) {
    std::vector<std::vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    EXPECT_TRUE(solution.searchMatrix(matrix, 5));
    EXPECT_FALSE(solution.searchMatrix(matrix, 20));
}

TEST(SearchMatrixIITest, SingleRow) {
    std::vector<std::vector<int>> matrix = {{1, 2, 3, 4, 5}};
    EXPECT_TRUE(solution.searchMatrix(matrix, 3));
    EXPECT_FALSE(solution.searchMatrix(matrix, 6));
}

TEST(SearchMatrixIITest, SingleCol) {
    std::vector<std::vector<int>> matrix = {{1}, {2}, {3}, {4}, {5}};
    EXPECT_TRUE(solution.searchMatrix(matrix, 4));
    EXPECT_FALSE(solution.searchMatrix(matrix, 0));
}

TEST(SearchMatrixIITest, Empty) {
    std::vector<std::vector<int>> matrix = {};
    EXPECT_FALSE(solution.searchMatrix(matrix, 1));
}

TEST(SearchMatrixIITest, OneElement) {
    std::vector<std::vector<int>> matrix = {{7}};
    EXPECT_TRUE(solution.searchMatrix(matrix, 7));
    EXPECT_FALSE(solution.searchMatrix(matrix, 8));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：

```
[==========] Running 5 tests from 1 test suite.  
[----------] Global test environment set-up.     
[----------] 5 tests from SearchMatrixIITest     
[ RUN      ] SearchMatrixIITest.Example1
[       OK ] SearchMatrixIITest.Example1 (0 ms)  
[ RUN      ] SearchMatrixIITest.SingleRow        
[       OK ] SearchMatrixIITest.SingleRow (0 ms) 
[ RUN      ] SearchMatrixIITest.SingleCol        
[       OK ] SearchMatrixIITest.SingleCol (0 ms) 
[ RUN      ] SearchMatrixIITest.Empty
[       OK ] SearchMatrixIITest.Empty (0 ms)     
[ RUN      ] SearchMatrixIITest.OneElement       
[       OK ] SearchMatrixIITest.OneElement (0 ms)
[----------] 5 tests from SearchMatrixIITest (2 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (5 ms total)
[  PASSED  ] 5 tests.
```