# 54. 螺旋矩阵

## 题目描述

54. 螺旋矩阵

给你一个 `m` 行 `n` 列的矩阵 `matrix` ，请按照 **顺时针螺旋顺序** ，返回矩阵中的所有元素。

![](./1.jpg)

示例 1：

>  **输入**
>
> matrix = [[1,2,3],[4,5,6],[7,8,9]]
>
>  **输出**
>
> [1,2,3,6,9,8,7,4,5]

![](./2.jpg)

示例 2：

>  **输入**
>
> matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
>
>  **输出**
>
> [1,2,3,4,8,12,11,10,9,5,6,7]

提示：

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 10`
- `-100 <= matrix[i][j] <= 100`

## 思路分析

这道题只想到了标记法：即创建一个和矩阵相同大小的表，用于标记对应位置的值是否已经输出过了，然后依次遍历。

官方在这种解法的基础上进行了改进：可以将矩阵看成若干层，首先输出最外层的元素，其次输出次外层的元素，直到输出最内层的元素。

定义矩阵的第 $k$ 层是到最近边界距离为 $k$ 的所有顶点。例如，下图矩阵最外层元素都是第 $1$ 层，次外层元素都是第 $2$ 层，剩下的元素都是第 $3$ 层。

```
[[1, 1, 1, 1, 1, 1, 1],
 [1, 2, 2, 2, 2, 2, 1],
 [1, 2, 3, 3, 3, 2, 1],
 [1, 2, 2, 2, 2, 2, 1],
 [1, 1, 1, 1, 1, 1, 1]]
```

对于每层，从左上方开始以顺时针的顺序遍历所有元素。假设当前层的左上角位于 $(top,left)$，右下角位于 $(bottom,right)$，按照如下顺序遍历当前层的元素。

1. 从左到右遍历上侧元素，依次为 $(top,left)$ 到 $(top,right)$。

2. 从上到下遍历右侧元素，依次为 $(top+1,right)$ 到 $(bottom,right)$。

3. 如果 $left<right$ 且 $top<bottom$，则从右到左遍历下侧元素，依次为 $(bottom,right−1)$ 到 $(bottom,left+1)$，以及从下到上遍历左侧元素，依次为 $(bottom,left)$ 到 $(top+1,left)$。

遍历完当前层的元素之后，将 $left$ 和 $top$ 分别增加 $1$，将 $right$ 和 $bottom$ 分别减少 $1$，进入下一层继续遍历，直到遍历完所有元素为止。

![](./3.png)

官方代码实现如下所示：

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }

        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                order.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; row++) {
                order.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    order.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    order.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};
```

## 代码实现

代码实现如下：

```c++
class Solution {
private:
    static constexpr int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(columns));
        int total = rows * columns;
        vector<int> order(total);
        int row = 0, column = 0;
        int directionIndex = 0;
        for (int i = 0; i < total; i++) {
            order[i] = matrix[row][column];
            visited[row][column] = true;
            int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
            if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
                directionIndex = (directionIndex + 1) % 4;
            }
            row += directions[directionIndex][0];
            column += directions[directionIndex][1];
        }
        return order;
    }
};
```

## 复杂度分析

- 标记法

    - 时间复杂度：$O(mn)$
    - 空间复杂度：$O(mn)$

- 分层法

    - 时间复杂度：$O(mn)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：

```c++
#include <gtest/gtest.h>
#include "54-spiral-matrix.cpp"
#include <vector>

static Solution solution;

TEST(SpiralMatrixTest, Example1) {
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    std::vector<int> expected = {1,2,3,6,9,8,7,4,5};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, Example2) {
    std::vector<std::vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    std::vector<int> expected = {1,2,3,4,8,12,11,10,9,5,6,7};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, SingleRow) {
    std::vector<std::vector<int>> matrix = {{1,2,3,4}};
    std::vector<int> expected = {1,2,3,4};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, SingleCol) {
    std::vector<std::vector<int>> matrix = {{1},{2},{3},{4}};
    std::vector<int> expected = {1,2,3,4};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
}

TEST(SpiralMatrixTest, Empty) {
    std::vector<std::vector<int>> matrix = {};
    std::vector<int> expected = {};
    EXPECT_EQ(solution.spiralOrder(matrix), expected);
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
[----------] 5 tests from SpiralMatrixTest
[ RUN      ] SpiralMatrixTest.Example1
[       OK ] SpiralMatrixTest.Example1 (0 ms)
[ RUN      ] SpiralMatrixTest.Example2
[       OK ] SpiralMatrixTest.Example2 (0 ms)
[ RUN      ] SpiralMatrixTest.SingleRow
[       OK ] SpiralMatrixTest.SingleRow (0 ms)
[ RUN      ] SpiralMatrixTest.SingleCol
[       OK ] SpiralMatrixTest.SingleCol (0 ms)
[ RUN      ] SpiralMatrixTest.Empty
[       OK ] SpiralMatrixTest.Empty (0 ms)
[----------] 5 tests from SpiralMatrixTest (1 ms total) 

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (4 ms total)
[  PASSED  ] 5 tests.
```