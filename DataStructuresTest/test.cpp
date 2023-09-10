#include "pch.h"
#include "../data_structures/array_list.h"
#include "../data_structures/sorting.h"
#include "../data_structures/binary_tree.h"
#include "../data_structures/binary_tree.cpp"

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
int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
