#include "pch.h"
#include "../data_structures/binary_tree.h"
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