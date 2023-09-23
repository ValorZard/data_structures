#include "pch.h"
#include "../data_structures/sorting.h"
#include "../data_structures/binary_tree.h"
#include "../data_structures/hash_map.h"
#include "../data_structures/stack.h"

TEST(HashMapTestSuite, BasicTest)
{
	HashMap<int, int>* h = new HashMap<int, int>;
	h->insertNode(1, 1);
	h->insertNode(2, 2);
	h->insertNode(2, 3);
	ASSERT_EQ(h->sizeofMap(), 2);
	ASSERT_EQ(h->deleteNode(2), 3);
	ASSERT_EQ(h->sizeofMap(), 1);
	ASSERT_EQ(h->isEmpty(), false);
	ASSERT_EQ(h->get(2), 2); // this should cause an error
}

TEST(BinarySearchTreeTestSuite, TestInsertTree) {

	BinarySearchTree bst{};

	bst.insert(7);
	bst.insert(2);
	bst.insert(6);
	bst.insert(4);
	bst.insert(5);
	bst.insert(3);
	bst.insert(10);
	bst.insert(1);
	bst.insert(8);
	bst.insert(12);

	ASSERT_EQ(bst.find(13), -1); // 13 doesn't exist

}

TEST(StackTestSuite, TestStack)
{
	Stack<int> stack;
	for (int i = 0; i < 10; ++i)
	{
		stack.push(i);
	}

	// this should pop in the reverse direction
	for (int i = 9; i >= 0; --i)
	{
		ASSERT_EQ(stack.pop(), i);
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
