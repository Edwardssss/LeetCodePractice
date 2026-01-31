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
