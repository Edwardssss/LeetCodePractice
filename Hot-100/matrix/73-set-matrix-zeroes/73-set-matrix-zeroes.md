# 73. 矩阵置零

## 题目描述

73. 矩阵置零

给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

![](./1.jpg)

示例 1：

>  **输入**
>
> matrix = [[1,1,1],[1,0,1],[1,1,1]]
>
>  **输出**
>
> [[1,0,1],[0,0,0],[1,0,1]]

![](./2.jpg)

示例 2：

>  **输入**
>
> matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
>
> **输出**
>
> [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

提示：

- `m == matrix.length`
- `n == matrix[0].length`
- `1 <= m, n <= 200`
- `-231 <= matrix[i][j] <= 231 - 1`

进阶：

- 一个直观的解决方案是使用 $O(mn)$ 的额外空间，但这并不是一个好的解决方案。
- 一个简单的改进方案是使用 $O(m + n)$ 的额外空间，但这仍然不是最好的解决方案。
- 你能想出一个仅使用常量空间的解决方案吗？

## 思路分析

这次我想到了一种解法：先遍历一遍矩阵，然后记录下所有的0的行、列，然后再去依次填充0。但是我发现这个算法的耗时和空间都很烂，代码如下所示:

```c++
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_set<int> row_set,col_set;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if(!matrix[i][j]){
                    row_set.insert(i);
                    col_set.insert(j);
                }
            }
        }
        for (auto m : row_set) {
            for (int i = 0;i < matrix[0].size();++i) {
                matrix[m][i] = 0;
            }
        }
        for (auto n : col_set){
            for (int j = 0;j < matrix.size();++j) {
                matrix[j][n] = 0;
            }
        }
    }
}
```

然后我想到了可以逐行先置零，存储列数据即可，然后就再次进行优化了，具体的代码见代码实现部分。这次的官方代码感觉很抽象，所以这次不管官方了，反正我这次的算法运行时间也能打败100%的cpp选手了。

## 代码实现

代码实现如下：

```c++
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
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
```

## 复杂度分析

- 时间复杂度：$O(mn)$。需要遍历矩阵一次收集需要置零的列，并对记录到的列逐列置零；置零列的操作总量不超过 $mn$。
- 空间复杂度：$O(n)$。额外使用一个集合记录所有需要置零的列，最坏为 $n$。

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "73-set-matrix-zeroes.cpp"
#include <vector>

static Solution solution;

void expectMatrixEq(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(SetMatrixZeroesTest, Example1) {
    std::vector<std::vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
    std::vector<std::vector<int>> expected = {{1,0,1},{0,0,0},{1,0,1}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, Example2) {
    std::vector<std::vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    std::vector<std::vector<int>> expected = {{0,0,0,0},{0,4,5,0},{0,3,1,0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, NoZero) {
    std::vector<std::vector<int>> matrix = {{1,2},{3,4}};
    std::vector<std::vector<int>> expected = {{1,2},{3,4}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, AllZero) {
    std::vector<std::vector<int>> matrix = {{0,0},{0,0}};
    std::vector<std::vector<int>> expected = {{0,0},{0,0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, SingleRow) {
    std::vector<std::vector<int>> matrix = {{1,0,3}};
    std::vector<std::vector<int>> expected = {{0,0,0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

TEST(SetMatrixZeroesTest, SingleCol) {
    std::vector<std::vector<int>> matrix = {{1},{0},{3}};
    std::vector<std::vector<int>> expected = {{0},{0},{0}};
    solution.setZeroes(matrix);
    expectMatrixEq(matrix, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from SetMatrixZeroesTest
[ RUN      ] SetMatrixZeroesTest.Example1
[       OK ] SetMatrixZeroesTest.Example1 (0 ms)
[ RUN      ] SetMatrixZeroesTest.Example2
[       OK ] SetMatrixZeroesTest.Example2 (0 ms)
[ RUN      ] SetMatrixZeroesTest.NoZero
[       OK ] SetMatrixZeroesTest.NoZero (0 ms)
[ RUN      ] SetMatrixZeroesTest.AllZero
[       OK ] SetMatrixZeroesTest.AllZero (0 ms)
[ RUN      ] SetMatrixZeroesTest.SingleRow
[       OK ] SetMatrixZeroesTest.SingleRow (0 ms)
[ RUN      ] SetMatrixZeroesTest.SingleCol
[       OK ] SetMatrixZeroesTest.SingleCol (0 ms)
[----------] 6 tests from SetMatrixZeroesTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 6 tests.
```
