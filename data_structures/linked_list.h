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
	int size;
	Node* head;
	Node* tail;
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
			tail = new_node;
		}
		else
		{
			// append at end of linked list
			tail->next = new_node;
			tail = tail->next;
		}
	}

	// rule of three: Contrustor, Copy-Constructor, and Destructor
	LinkedList() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	LinkedList(const LinkedList& other)
	{
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

	// we don't want to accidentally change head
	Node* get_tail() const
	{
		return tail;
	}

	Node* get_node(int index)
	{
		// throw exception if index is out of bounds
		if (index >= size)
		{
			throw std::length_error("index is out of bounds");
		}
		// iterate through nodes until we're at the index we want
		Node* current_node = head;
		for (int i = 0; i < index; ++i)
		{
			current_node = current_node->next;
		}
		return current_node;
	}

	int get_size() const
	{
		return size;
	}

	void remove(int value)
	{
		// delete elements in linked list
		Node* current_node = head;
		Node* previous_node = head;

		// check find 
		bool has_found = false;
		while (current_node != nullptr)
		{
			if (current_node->value == value)
			{
				has_found = true;
				break;
			}
			previous_node = current_node;
			current_node = current_node->next;
		}

		if (has_found)
		{
			// remove node out of list by connecting the parent and child note
			previous_node->next = current_node->next;
			delete current_node;
			// decrease size by 1
			--size;
		}
	}

	// returns -1 if not found
	int find(int value)
	{
		// delete elements in linked list
		Node* current_node = head;

		int index = 0;

		// check find 
		bool has_found = false;
		while (current_node != nullptr)
		{
			if (current_node->value == value)
			{
				has_found = true;
				break;
			}
			current_node = current_node->next;
			++index;
		}

		if (!has_found)
		{
			return -1;
		}
		else
		{
			return index;
		}
	}
};