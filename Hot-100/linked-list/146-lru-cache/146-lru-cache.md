# 146. LRU Cache

## 题目描述

146. LRU 缓存

请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。

实现 `LRUCache` 类：

`LRUCache(int capacity)` 以 正整数 作为容量 `capacity` 初始化 LRU 缓存

`int get(int key)` 如果关键字 `key` 存在于缓存中，则返回关键字的值，否则返回 `-1` 。

`void put(int key, int value)` 如果关键字 `key` 已经存在，则变更其数据值 `value` ；如果不存在，则向缓存中插入该组 `key-value` 。如果插入操作导致关键字数量超过 `capacity` ，则应该 逐出 最久未使用的关键字。

函数 `get` 和 `put` 必须以 $O(1)$ 的平均时间复杂度运行。

示例：

>  **输入**
>
> ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
>
> [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
>
>  **输出**
>
> [null, null, null, 1, null, -1, null, -1, 3, 4]
>
>  **解释**
>
> LRUCache lRUCache = new LRUCache(2);
>
> lRUCache.put(1, 1); // 缓存是 {1=1}
>
> lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
>
> lRUCache.get(1);    // 返回 1
>
> lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
>
> lRUCache.get(2);    // 返回 -1 (未找到)
>
> lRUCache.put(4, 4); // 该操作会使得关键字 1作废，缓存是 {4=4, 3=3}
>
> lRUCache.get(1);    // 返回 -1 (未找到)
>
> lRUCache.get(3);    // 返回 3
>
> lRUCache.get(4);    // 返回 4


提示：

- `1 <= capacity <= 3000`
- `0 <= key <= 10000`
- `0 <= value <= 105`
最多调用 `2 * 105` 次 `get` 和 `put`

## 思路分析

这道题没写出来，可能是因为之前没遇见过这种题。

LRU 缓存机制可以通过哈希表辅以双向链表实现，我们用一个哈希表和一个双向链表维护所有在缓存中的键值对。

- 双向链表按照被使用的顺序存储了这些键值对，靠近头部的键值对是最近使用的，而靠近尾部的键值对是最久未使用的。

- 哈希表即为普通的哈希映射（HashMap），通过缓存数据的键映射到其在双向链表中的位置。

这样以来，我们首先使用哈希表进行定位，找出缓存项在双向链表中的位置，随后将其移动到双向链表的头部，即可在 $O(1)$ 的时间内完成 `get` 或者 `put` 操作。

## 代码实现

代码实现如下：
```c++
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};
```

## 复杂度分析

- 时间复杂度：$O(1)$
- 空间复杂度：$O(capacity)$

## 测试用例

测试用例如下：
```c++
#include <gtest/gtest.h>
#include "146-lru-cache.cpp"

TEST(LRUCacheTest, BasicPutGet) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    EXPECT_EQ(cache.get(1), 1);
    cache.put(3, 3);
    EXPECT_EQ(cache.get(2), -1);
    cache.put(4, 4);
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(3), 3);
    EXPECT_EQ(cache.get(4), 4);
}

TEST(LRUCacheTest, OverwriteValue) {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), 10);
}

TEST(LRUCacheTest, CapacityOne) {
    LRUCache cache(1);
    cache.put(1, 1);
    EXPECT_EQ(cache.get(1), 1);
    cache.put(2, 2);
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 2);
}

TEST(LRUCacheTest, GetNonExist) {
    LRUCache cache(2);
    EXPECT_EQ(cache.get(100), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 测试结果

测试结果如下所示：
```
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from LRUCacheTest
[ RUN      ] LRUCacheTest.BasicPutGet
[       OK ] LRUCacheTest.BasicPutGet (0 ms)
[ RUN      ] LRUCacheTest.OverwriteValue
[       OK ] LRUCacheTest.OverwriteValue (0 ms)
[ RUN      ] LRUCacheTest.CapacityOne
[       OK ] LRUCacheTest.CapacityOne (0 ms)
[ RUN      ] LRUCacheTest.GetNonExist
[       OK ] LRUCacheTest.GetNonExist (0 ms)
[----------] 4 tests from LRUCacheTest (1 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 4 tests.
```