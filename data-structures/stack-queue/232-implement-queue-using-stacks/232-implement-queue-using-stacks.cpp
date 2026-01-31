/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */

// @lc code=start
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

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end

