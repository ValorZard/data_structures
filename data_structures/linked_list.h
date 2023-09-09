#pragma once
struct Node
{
	int value;
	Node* next = nullptr;
};


void append_node(Node* head, int value)
{
	// make a new node to insert
	Node* new_node = new Node;
	new_node->value = value;

	// if the head itself is null, that will be the new node
	if (head == nullptr)
	{
		head = new_node;
	}
	else
	{
		// iterate through linked list tilll we find a good spot
		Node* current_node = head;
		while (current_node->next != nullptr)
		{
			current_node = current_node->next;
		}
		// now append node at the end of the linked llist
		current_node->next = new_node;
	}
}

struct NodeIterator
{

};