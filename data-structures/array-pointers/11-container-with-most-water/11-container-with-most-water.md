# 11. Container With Most Water

## 题目描述

11. 盛最多水的容器

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

**说明**：你不能倾斜容器。

![](./1.jpg)

示例 1：

>  **输入**
>
> [1,8,6,2,5,4,8,3,7]
>
>  **输出**
>
> 49
>
>  **解释**
>
> 图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

示例 2：

>  **输入**
>
> height = [1,1]
>
>  **输出**
>
> 1

提示：

- `n == height.length`
- `2 <= n <= 105`
- `0 <= height[i] <= 104`

## 思路分析

我第一反应就是for循环嵌套，然后我想了很久也没想到其他的解法。LeetCode官方用的是双指针法，只移动二者中短板对应的指针（可以证明），我目前是第一次见，后面还需要多多复习来熟练一下这种方法。

LeetCode官方题解如下：

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int ans = 0;
        while (l < r) {
            int area = min(height[l], height[r]) * (r - l);
            ans = max(ans, area);
            if (height[l] <= height[r]) {
                ++l;
            }
            else {
                --r;
            }
        }
        return ans;
    }
};
```

## 代码实现

我的代码实现如下：
```c++
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
```

## 复杂度分析

- for循环嵌套算法
    - 时间复杂度：$O(n^2)$
    - 空间复杂度：$O(1)$

- LeetCode官方解法（双指针）
    - 时间复杂度：$O(n)$
    - 空间复杂度：$O(1)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "11-container-with-most-water.cpp"

static Solution solution;

TEST(MaxAreaTest, Example1) {
    std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    EXPECT_EQ(solution.maxArea(height), 49);
}

TEST(MaxAreaTest, Example2) {
    std::vector<int> height{1, 1};
    EXPECT_EQ(solution.maxArea(height), 1);
}

TEST(MaxAreaTest, Increasing) {
    std::vector<int> height{1, 2, 3, 4, 5};
    EXPECT_EQ(solution.maxArea(height), 6);
}

TEST(MaxAreaTest, Decreasing) {
    std::vector<int> height{5, 4, 3, 2, 1};
    EXPECT_EQ(solution.maxArea(height), 6);
}

TEST(MaxAreaTest, WithZeros) {
    std::vector<int> height{0, 2, 0, 4, 0, 3};
    EXPECT_EQ(solution.maxArea(height), 8);
}

TEST(MaxAreaTest, TwoBars) {
    std::vector<int> height{2, 3};
    EXPECT_EQ(solution.maxArea(height), 2);
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
[----------] 6 tests from MaxAreaTest
[ RUN      ] MaxAreaTest.Example1
[       OK ] MaxAreaTest.Example1 (0 ms)       
[ RUN      ] MaxAreaTest.Example2
[       OK ] MaxAreaTest.Example2 (0 ms)       
[ RUN      ] MaxAreaTest.Increasing
[       OK ] MaxAreaTest.Increasing (0 ms)     
[ RUN      ] MaxAreaTest.Decreasing
[       OK ] MaxAreaTest.Decreasing (0 ms)     
[ RUN      ] MaxAreaTest.WithZeros
[       OK ] MaxAreaTest.WithZeros (0 ms)      
[ RUN      ] MaxAreaTest.TwoBars
[       OK ] MaxAreaTest.TwoBars (0 ms)        
[----------] 6 tests from MaxAreaTest (2 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 6 tests.
```