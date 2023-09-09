#include "binary_tree.h"
#include <iostream>


Leaf* insert_helper(Leaf* current_leaf, int value)
{
	if (current_leaf == nullptr)
	{
		current_leaf = new Leaf;
		current_leaf->value = value;
		current_leaf->right = nullptr;
		current_leaf->left = nullptr;
	}
	else if (current_leaf->value > value)
	{
		// switch current leaf to the left leaf and keep going down
		std::cout << "insert left\n";
		current_leaf->left = insert_helper(current_leaf->left, value);
	}
	else if (current_leaf->value <= value)
	{
		// switch current leaf to the right leaf and keep going down
		std::cout << "insert right\n";
		current_leaf->right = insert_helper(current_leaf->right, value);
	}
	return current_leaf;
}


void BinarySearchTree::insert(int value)
{
	std::cout << "value being added: " << value << "\n";
	// handle edge case of head being null
	if (head == nullptr)
	{
		head = new Leaf;
		head->value = value;
		head->right = nullptr;
		head->left = nullptr;
	}
	else
	{
		Leaf* leaf_added = insert_helper(head, value); // this will just give back the head
	}
	//std::cout << "head value: " << head->value << "\n";
	//std::cout << "leaf value: " << leaf_added->value << "\n";
}


void delete_leaf_and_children(Leaf* current_leaf)
{
	if (current_leaf == nullptr)
	{
		return;
	}
	delete_leaf_and_children(current_leaf->left);
	delete_leaf_and_children(current_leaf->right);
	delete current_leaf;
}


void BinarySearchTree::clear()
{
	// handle edge case of head being null
	if (head != nullptr)
	{
		delete_leaf_and_children(head);
	}
}

void print_helper(Leaf* current_leaf, int level = 1)
{
	if (current_leaf != nullptr)
	{
		print_helper(current_leaf->left, level + 1);
		std::cout << "value: " << current_leaf->value << " Level: " << level << "\n";
		print_helper(current_leaf->right, level + 1);
	}
}

void BinarySearchTree::print_tree()
{
	std::cout << "Printing tree!\n";
	print_helper(head);
}
