#pragma once
#include "pch.h"
#include "../data_structures/linked_list.h"

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

	ASSERT_EQ(list.remove_at(69), false);
	ASSERT_EQ(list.remove_at(1), true);
	// this should shuffle things around
	ASSERT_EQ(list.find(2), -1); // should no longer exist
	ASSERT_EQ(list.get_size(), 2);
	ASSERT_EQ(list.get_node(1)->value, 3); // the node at index 2 is now at index 1

	list.append(9);
	list.append(7);
	list.append(69);

	ASSERT_EQ(list.remove_at(list.find(7)), true); // this finds the node we want, and then removes that node
	ASSERT_EQ(list.remove_at(list.find(13)), false); // this will try to remove a node that doesn't exist
	ASSERT_EQ(list.get_size(), 4); // the linked list should now have a lenght of 4

}