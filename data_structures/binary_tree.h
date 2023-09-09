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

	// use for destruction
	void clear();

	~BinarySearchTree()
	{
		clear();
	}

	void insert(int value);
	int find(int value); // return level the value is at
	void print_tree();
};