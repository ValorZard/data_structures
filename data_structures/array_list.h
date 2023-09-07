#pragma once
#include <stdexcept>
#include <string>
#include <math.h>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

// ArrayList is equivalent to std::vector

template <typename Data>
class ArrayList
{
private:
	// currently pointer to an array of ints
	Data* array;
	int length; // the current length of all actual values
	int capacity; // the length of the actual array thats storing all these values. Doubles when we hit the limit
	void setup(); // reuse for different constructors
public:
	////////////////////////////////////////////////////////////
	//					CONSTRUCTORS						///
	//////////////////////////////////////////////////////////
	ArrayList(); // default constructor
	ArrayList(unsigned int length);

	// we need a destructor, a copy constructor, and an assigment operator due to the rule of three
	// https://en.cppreference.com/w/cpp/language/rule_of_three

	// copy constructor
	// used when we want to initalize a new ArrayList with the data of an old arraylist
	// https://www.geeksforgeeks.org/copy-constructor-in-cpp/
	ArrayList(const ArrayList& old);

	// copy assignment (just to make sure there's nothing weird going on)
	ArrayList<Data>& operator=(const ArrayList<Data>& old);

	~ArrayList();

	// overloading the [] operator
	Data& operator[](unsigned int);

	// for const correctness, we should also have a const version of this function when ArrayList is const
	// https://isocpp.org/wiki/faq/const-correctness
	const Data& operator[](unsigned int) const;

	////////////////////////////////////////////////////////////
	//				ARRAY MANAGEMENT						///
	//////////////////////////////////////////////////////////

	// if we want to get the array inside of the array_list
	Data* get_array();

	// have a const version too just in case
	const Data* get_array() const;

	// Get the data at the front of the array
	Data& front();
	const Data& front() const;

	// Get the data at the back of the array
	Data& back();
	const Data& back() const;

	////////////////////////////////////////////////////////////
	//				CHANGING DATA							///
	//////////////////////////////////////////////////////////

	void push_back(const Data& new_data); // const and a reference because we don't want to change the data being inserted
	Data& pop_back(); // returns the last element as we remove it from the array

	// if we want to delete everything and reset it
	void clear();

	////////////////////////////////////////////////////////////
	//				CAPACITY MANAGEMENT						///
	//////////////////////////////////////////////////////////

	// the following are const because these functions shouldn't change the data inside the vector itself
	int size() const;
	int max_size() const; // returns capacity

	// just so we don't have to constantly check array_list.size() != 0
	bool is_empty();
	const bool is_empty() const;

	/* runs whenever we need to resize the array to have greater capacity;
	 also just realized we can use this whenever we want to change size of the arraylist
	*/
	bool resize(int new_length);

	////////////////////////////////////////////////////////////
	//						ITERATORS						///
	//////////////////////////////////////////////////////////

	/* we should also make an iterator for this class
		https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
		This is meant to handle all the nasty pointer arthmetic and other bullshit for us
		(We define it later in this file)
	*/
	class Iterator;

	// Having begin() and end() will make for each loops "just work" since they are looking under the hood for begin() and end()

	Iterator begin();
	const Iterator begin() const;

	Iterator end();
	const Iterator end() const;

	// these two versions of begin and end work when we want the iterator to not change any of the data inside of the array_List
	const Iterator const_begin() const;
	const Iterator const_end() const;

	////////////////////////////////////////////////////////////
	//				NICE TO HAVES							///
	//////////////////////////////////////////////////////////

	// this should be const even though we're creating a string, we are not touching any data
	std::string to_string() const;
};


template <typename Data> void ArrayList<Data>::setup()
{
	// capacity : the actual size of the array to make it bigger
	if (length == 0)
	{
		capacity = 1; // make the array at least have the space for one element
	}
	else
	{
		capacity = length * 2; // else double the size of the array so we can optimize memory assignment
	}
	// make sure the values of the array are all default
	array = new Data[capacity];
}

template <typename Data> ArrayList<Data>::ArrayList(const unsigned int size)
{
	// i'm just going to throw an error if the size is set to be less than to zero to make shit less weird to deal with
	if (size < 0)
	{
		throw std::runtime_error("size is less than 0, this is currently not supported!");
	}
	this->length = size;
	setup();
}

template <typename Data> ArrayList<Data>::ArrayList()
{
	this->length = 0;
	setup();
}

template <typename Data> ArrayList<Data>::ArrayList(const ArrayList& old)
{
	// do basic setup before we do anything too crazy
	this->length = 0;
	setup();
	// this should work fine i think, unless we horribly fuck things up
	// since this will result in something the same size as the other array list with all the data in the right place
	for (Data& data : old) {
		// get each of the data from the old ArrayList and put it into this one
		push_back(data);
	}
}

template <typename Data> ArrayList<Data>& ArrayList<Data>::operator=(const ArrayList<Data>& old)
{
	if (this == &old)
	{
		return *this; // self assigment, so don't need to do anything
	}

	// reset the object
	clear();

	for (Data& data : old) {
		push_back(data);
	}

	return *this;
}

template <typename Data> ArrayList<Data>::~ArrayList()
{
	delete[] array;
}

template <typename Data> Data& ArrayList<Data>::operator[](unsigned int index)
{
	return array[index];
}

template <typename Data> const Data& ArrayList<Data>::operator[](unsigned int index) const
{
	return array[index];
}

template <typename Data> Data* ArrayList<Data>::get_array()
{
	return array;
}

template <typename Data> const Data* ArrayList<Data>::get_array() const
{
	return array;
}

template <typename Data> Data& ArrayList<Data>::front()
{
	return array[0];
}

template <typename Data> const Data& ArrayList<Data>::front() const
{
	return array[0];
}

template <typename Data> Data& ArrayList<Data>::back()
{
	return array[length - 1];
}

template <typename Data> const Data& ArrayList<Data>::back() const
{
	return array[length - 1];
}

template <typename Data> int ArrayList<Data>::size() const
{
	return length;
}

template <typename Data> int ArrayList<Data>::max_size() const
{
	return capacity;
}

template <typename Data> bool ArrayList<Data>::is_empty()
{
	return length == 0;
}

template <typename Data> const bool ArrayList<Data>::is_empty() const
{
	return length == 0;
}

template <typename Data> void ArrayList<Data>::push_back(const Data& new_data)
{
	++length; // increase length since we're adding something at the end
	resize(length);
	array[length - 1] = new_data; // add thing on the end of the array
}

template <typename Data> Data& ArrayList<Data>::pop_back()
{
	Data popped_data = array[length - 1]; // copy data, since this wont exist after deleting the array
	resize(length - 1); // technically unnecessary, as this will delete and create a new array, but for the sake of API consistency, this is fine
	return popped_data;
}

template <typename Data> class ArrayList<Data>::Iterator
{
public:
	// members of a struct are auto-public
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = Data;
	using pointer = Data*;  // or also value_type*
	using reference = Data&;  // or also value_type&

	Iterator(pointer ptr) : current_ptr(ptr) {};

	reference operator*() const {
		return *current_ptr;
	}

	// make this const so we can use this in const
	// will not be able to edit the data inside the pointer

	pointer operator->()
	{
		return current_ptr;
	}

	// make this const so we can use this in const
	const pointer operator->() const
	{
		return current_ptr;
	}

	Iterator& operator++()
	{
		current_ptr++;
		return *this;
	}

	Iterator operator++(int) {
		Iterator temp = *this; ++(*this); return temp;
	}
	// setting these as "friend" is a handy way to define the operators as non-member functions, yet being able to access private parts of the Iterator class 
	// https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421729#4421729
	bool operator== (const Iterator& other) const
	{
		return current_ptr == other.current_ptr;
	};
	bool operator!= (const Iterator& other) const
	{
		return current_ptr != other.current_ptr;
	};

private:
	pointer current_ptr; // points to an element of ArrayList
};

// have to put typename before ArrayList<Data>::Iterator to tell the compiler that Iterator is a type
// see https://stackoverflow.com/a/1600968
template <typename Data> 
typename ArrayList<Data>::Iterator ArrayList<Data>::begin()
{
	return Iterator(&array[0]); // get pointer to beginning of the array
}

template <typename Data> 
const typename ArrayList<Data>::Iterator ArrayList<Data>::begin() const
{
	return Iterator(&array[0]); // get pointer to beginning of the array
}

template <typename Data> 
const typename ArrayList<Data>::Iterator ArrayList<Data>::const_begin() const
{
	return Iterator(&array[0]); // get pointer to beginning of the array
}

template <typename Data> 
typename ArrayList<Data>::Iterator ArrayList<Data>::end()
{
	return Iterator(&array[length]); // get pointer to end of the array (There should be nothing here and that's the point)
}

template <typename Data>
const typename ArrayList<Data>::Iterator ArrayList<Data>::end() const
{
	return Iterator(&array[length]); // get pointer to end of the array (There should be nothing here and that's the point)
}

template <typename Data> 
const typename ArrayList<Data>::Iterator ArrayList<Data>::const_end() const
{
	return Iterator(&array[length]); // get pointer to end of the array
}


// this will delete objects after new_length if new_length is smaller than the current size
template <typename Data>  bool ArrayList<Data>::resize(int new_length)
{
	length = new_length;
	capacity = 2 * length;

	Data* new_array = new Data[capacity];
	// copy stuff from old array to new array
	for (int i = 0; i < length; ++i)
	{
		new_array[i] = array[i];
	}
	// delete old array and set it to new array
	delete array;
	array = new_array;
	return true; // return true if we did resize the array
}

template <typename Data> void ArrayList<Data>::clear()
{
	// reset everything
	this->length = 0;
	delete[] array;
	setup();
}

template <typename Data>  std::string ArrayList<Data>::to_string() const
{
	std::string list_string = "[";

	for (Data& data : *this) {
		list_string += std::to_string(data) + ",";
	}

	list_string += "]";
	return list_string;
}