# 232. Implement Queue using Stacks

## 题目描述

232. 用栈实现队列

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 `MyQueue` 类：

- `void push(int x)` 将元素 `x` 推到队列的末尾
- `int pop()` 从队列的开头移除并返回元素
- `int peek()` 返回队列开头的元素
- `boolean empty()` 如果队列为空，返回 `true` ；否则，返回 `false`

说明：

你 **只能** 使用标准的栈操作 —— 也就是只有 `push to top`, `peek/pop from top`, `size`, 和 `is empty` 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 `list` 或者 `deque`（双端队列）来模拟一个栈，只要是标准的栈操作即可。

示例 1：

>  **输入**
>
> ["MyQueue", "push", "push", "peek", "pop", "empty"]
>
> [[], [1], [2], [], [], []]
>
>  **输出**
>
> [null, null, null, 1, 1, false]
>
>  **解释**
>
> MyQueue myQueue = new MyQueue();
>
> myQueue.push(1); // queue is: [1]
>
> myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
>
> myQueue.peek(); // return 1
>
> myQueue.pop(); // return 1, queue is [2]
>
> myQueue.empty(); // return false

提示：

- `1 <= x <= 9`
- 最多调用 `100` 次 `push`、`pop`、`peek` 和 `empty`
- 假设所有操作都是有效的 （例如，一个空的队列不会调用 `pop` 或者 `peek` 操作）

进阶：

你能否实现每个操作均摊时间复杂度为 $O(1)$ 的队列？换句话说，执行 `n` 个操作的总时间复杂度为 $O(n)$ ，即使其中一个操作可能花费较长时间。

## 思路分析

很简单的一道题：队列的结构是FIFO，而栈的结构是LIFO，所以将一个栈中的元素依次弹出并压入另一个栈即可实现FIFO特性。

## 代码实现

代码实现如下：

```c++
#include <stack>

using namespace std;

class MyQueue {
public:
    stack<int> store;
    MyQueue() {
        while (!this->store.empty()) {
            this->store.pop();
        }
    }

    void push(int x) {
        this->store.push(x);
    }

    int pop() {
        stack<int> temp_store;
        int value;
        while (!this->store.empty()) {
            temp_store.push(this->store.top());
            this->store.pop();
        }
        value = temp_store.top();
        temp_store.pop();
        while (!temp_store.empty()) {
            this->store.push(temp_store.top());
            temp_store.pop();
        }
        return value;
    }

    int peek() {
        stack<int> temp_store;
        int value;
        while (!this->store.empty()) {
            temp_store.push(this->store.top());
            this->store.pop();
        }
        value = temp_store.top();
        while (!temp_store.empty()) {
            this->store.push(temp_store.top());
            temp_store.pop();
        }
        return value;
    }

    bool empty() {
        return this->store.empty();
    }
};
```

## 复杂度分析

- 时间复杂度：`push` 和 `empty` 为 $O(1)$，`pop` 和 `peek` 为均摊 $O(1)$。对于每个元素，至多入栈和出栈各两次，故均摊复杂度为 $O(1)$。

- 空间复杂度：$O(n)$。其中 `n` 是操作总数。对于有 `n` 次 `push` 操作的情况，队列中会有 `n` 个元素，故空间复杂度为 $O(n)$。

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "232-implement-queue-using-stacks.cpp"

TEST(MyQueueTest, BasicOps) {
	MyQueue q;
	EXPECT_TRUE(q.empty());
	q.push(1);
	EXPECT_FALSE(q.empty());
	q.push(2);
	EXPECT_EQ(q.peek(), 1);
	EXPECT_EQ(q.pop(), 1);
	EXPECT_EQ(q.peek(), 2);
	EXPECT_EQ(q.pop(), 2);
	EXPECT_TRUE(q.empty());
}

TEST(MyQueueTest, MultiplePushPop) {
	MyQueue q;
	for (int i = 0; i < 5; ++i) q.push(i);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(q.peek(), i);
		EXPECT_EQ(q.pop(), i);
	}
	EXPECT_TRUE(q.empty());
}

TEST(MyQueueTest, InterleavedOps) {
	MyQueue q;
	q.push(10);
	EXPECT_EQ(q.peek(), 10);
	q.push(20);
	EXPECT_EQ(q.pop(), 10);
	q.push(30);
	EXPECT_EQ(q.peek(), 20);
	EXPECT_EQ(q.pop(), 20);
	EXPECT_EQ(q.pop(), 30);
	EXPECT_TRUE(q.empty());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from MyQueueTest
[ RUN      ] MyQueueTest.BasicOps
[       OK ] MyQueueTest.BasicOps (0 ms)
[ RUN      ] MyQueueTest.MultiplePushPop
[       OK ] MyQueueTest.MultiplePushPop (0 ms)
[ RUN      ] MyQueueTest.InterleavedOps
[       OK ] MyQueueTest.InterleavedOps (0 ms)
[----------] 3 tests from MyQueueTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
```
