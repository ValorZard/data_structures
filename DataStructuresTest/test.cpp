#include "pch.h"
#include <gtest/gtest.h>
#include "../data_structures/array_list.h"
#include "../data_structures/linked_list.h"
#include "../data_structures/array_list.h"
#include "../data_structures/binary_tree.h"
#include "../data_structures/sorting.h"

#include "test_linked_list.h"

//test linked_list working
TEST(LinkedListTestSuite, TestNodes) {
	// check we have all of the nodes we created
	// make a string containing all the data inside the nodes

	Node* head = new Node;
	head->value = 0;
	std::string test_string = "0";
	// fill up node with number from 0-99
	int amount_of_nodes = 100; // magic number i know
	for (int i = 1; i < amount_of_nodes; ++i)
	{
		append_node(head, i);

		// add data to test_string
		test_string += std::to_string(i);
	}

	// make a string out of all the values in Node
	std::string node_test_string = "";
	Node* current_node = head;
	while (current_node != nullptr)
	{
		node_test_string += std::to_string(current_node->value);
		current_node = current_node->next;
	}

	ASSERT_EQ(test_string, node_test_string);

	// delete elements in node
	current_node = head;
	while (current_node != nullptr)
	{
		Node* next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	}
}

TEST(LinkedListTestSuite, TestLinkedListBasic) {
	LinkedList list{};
	list.append(1);
	list.append(2);
	list.append(3);

	// check if appends works
	ASSERT_EQ(list.get_node(0)->value, 1);
	ASSERT_EQ(list.get_node(1)->value, 2);
	ASSERT_EQ(list.get_node(2)->value, 3);
	
	// check if find works
	ASSERT_EQ(list.find(1), 0);
	ASSERT_EQ(list.find(2), 1);
	ASSERT_EQ(list.find(3), 2);
	//ASSERT_EQ(list.find(69), -1);
}

TEST(LinkedListTestSuite, TestLinkedListRemove) {
	LinkedList list{};
	list.append(1);
	list.append(2);
	list.append(3);
	
	//list.remove(1);
	// this should shuffle things around
	ASSERT_EQ(list.find(1), -1); // should no longer exist
	ASSERT_EQ(list.get_size(), 2);
	ASSERT_EQ(list.get_node(1)->value, 3); // the node at index 2 is now at index 1
}