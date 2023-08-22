#pragma once

struct Leaf {
	Leaf* right;
	Leaf* left;
	int value;
};

class BinarySearchTree {
public:
	Leaf* head;

	BinarySearchTree()
	{
		head = nullptr;
	}
	~BinarySearchTree()
	{
		delete head;
	}

	void insert(int value);
	void print_tree();
};