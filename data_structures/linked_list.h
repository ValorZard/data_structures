#pragma once
template <typename Data>
struct Node
{
	Data value;
	Node* next = nullptr;
};


template <typename Data>
void append_node(Node<Data>* head, Data value)
{
	// make a new node to insert
	Node<Data>* new_node = new Node<Data>;
	new_node->value = value;

	// if the head itself is null, that will be the new node
	if (head == nullptr)
	{
		head = new_node;
	}
	else
	{
		// iterate through linked list tilll we find a good spot
		Node<Data>* current_node = head;
		while (current_node->next != nullptr)
		{
			current_node = current_node->next;
		}
		// now append node at the end of the linked llist
		current_node->next = new_node;
	}
}

template <typename Data>
class LinkedList
{
private:
	int size;
	Node<Data>* head;
	Node<Data>* tail;
public:

	// I'm putting this first because I'll be using this in the copy-constructor
	void append(Data value)
	{
		// increase size by one
		++size;

		// make a new node to insert
		Node<Data>* new_node = new Node<Data>;
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
		Node<Data>* current_node = other.head;
		while (current_node != nullptr)
		{
			// append data in this list
			append(current_node->value);
			Node<Data>* next_node = current_node->next;
			current_node = next_node;
		}
	}

	~LinkedList()
	{
		// delete elements in linked list
		Node<Data>* current_node = head;
		while (current_node != nullptr)
		{
			Node<Data>* next_node = current_node->next;
			delete current_node;
			current_node = next_node;
		}
	}

	// we don't want to accidentally change head
	const Node<Data>* get_head() const
	{
		return head;
	}

	// we don't want to accidentally change head
	const Node<Data>* get_tail() const
	{
		return tail;
	}

	// make data inside the node uneditable
	const Node<Data>* get_node(int index) const
	{
		// throw exception if index is out of bounds
		if (index >= size)
		{
			throw std::length_error("index is out of bounds");
		}

		// for optimization, handle these special cases
		if (index == 0)
		{
			return get_head();
		}

		if (index == size - 1)
		{
			return get_tail();
		}

		// iterate through nodes until we're at the index we want
		Node<Data>* current_node = head;
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

	bool remove_at(int index_to_remove)
	{
		// return false if the index doesn't even exist
		if (index_to_remove >= size || index_to_remove < 0)
		{
			return false;
		}

		// head is null, which mean nothing exists in the list
		if (head == nullptr)
		{
			return false;
		}

		// delete elements in linked list
		Node<Data>* current_node = head;
		Node<Data>* previous_node = nullptr;

		// if index_to_remove is zero, we're just removing the head, which is easy
		if (index_to_remove == 0)
		{
			head = head->next;
			delete current_node;
			return true;
		}

		int index = 0;
		// checking to see if we've found it yet
		while (index < index_to_remove)
		{
			previous_node = current_node;
			current_node = current_node->next;
			++index;
		}

		previous_node->next = current_node->next;
		delete current_node;
		// decrease size by one
		--size;
		// we did it!
		return true;
	}

	// returns -1 if not found
	int find(Data value)
	{
		// delete elements in linked list
		Node<Data>* current_node = head;

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

	// Iterator stuff
	// https://www.geeksforgeeks.org/implementing-iterator-pattern-of-a-single-linked-list/
	// https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Node<Data>;
		using pointer = Node<Data>*;
		using reference = Node<Data>&;

		pointer node_ptr;

		Iterator(pointer ptr) : node_ptr(ptr) {}

		// Copy assigment
		Iterator& operator=(Node<Data>* pNode)
		{
			this->node_ptr = pNode;
			return *this;
		}

		Data& operator*() const 
		{ 
			return node_ptr->value; 
		}

		pointer operator->() 
		{ 
			return node_ptr; 
		}

		Iterator& operator++() 
		{ 
			if (node_ptr != nullptr)
			{
				node_ptr = node_ptr->next;
			}
			return *this; 
		}

		Iterator operator++(int) 
		{ 
			Iterator tmp = *this; 
			++(*this); 
			return tmp; 
		}

		friend bool operator== (const Iterator& a, const Iterator& b) 
		{ 
			return a.node_ptr == b.node_ptr; 
		};

		friend bool operator!= (const Iterator& a, const Iterator& b) 
		{ 
			return a.node_ptr != b.node_ptr; 
		};
	};

	// Having begin() and end() will make for each loops "just work" since they are looking under the hood for begin() and end()

	Iterator begin()
	{
		return Iterator(head);
	}

	const Iterator begin() const
	{
		return Iterator(head);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}
	const Iterator end() const
	{
		return Iterator(nullptr);
	}

	// these two versions of begin and end work when we want the iterator to not change any of the data inside of the array_List
	const Iterator cbegin() const
	{
		return Iterator(head);
	}

	const Iterator cend() const
	{
		return Iterator(nullptr);
	}
};