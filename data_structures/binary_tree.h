#pragma once

struct Leaf {
	Leaf* right;
	Leaf* left;
	int value;
};

class BinarySearchTree {

public:
// variables
	Leaf* head;
// functions
	void insert(int value);
	int find(int value); // return level the value is at
	// use for destruction
	void destroy_tree(Leaf* current_leaf);
	void destroy_tree();
	void print_tree();

// constructors

	BinarySearchTree()
	{
		head = nullptr;
	}

	~BinarySearchTree()
	{
		destroy_tree();
	}
};