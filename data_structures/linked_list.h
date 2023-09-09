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

class LinkedList
{
private:
	size_t size;
	Node* head;
public:

	// I'm putting this first because I'll be using this in the copy-constructor
	void append(int value)
	{
		// increase size by one
		++size;
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

	// rule of three: Contrustor, Copy-Constructor, and Destructor
	LinkedList() {
		size = 0;
		head = nullptr;
	}

	LinkedList(const LinkedList& other)
	{
		// set same size
		size = other.size;
		// iterate through data in list
		Node* current_node = other.head;
		while (current_node != nullptr)
		{
			// append data in this list
			append(current_node->value);
			Node* next_node = current_node->next;
			current_node = next_node;
		}
	}

	~LinkedList()
	{
		// delete elements in linked list
		Node* current_node = head;
		while (current_node != nullptr)
		{
			Node* next_node = current_node->next;
			delete current_node;
			current_node = next_node;
		}
	}

	// we don't want to accidentally change head
	Node* get_head() const
	{
		return head;
	}

	Node* get_node(size_t index)
	{
		// throw exception if index is out of bounds
		if (index >= size)
		{
			throw std::length_error("index is out of bounds");
		}
		// iterate through nodes until we're at the index we want
		Node* current_node = head;
		for (size_t i = 0; i < index; ++i)
		{
			current_node = current_node->next;
		}
		return current_node;
	}
};