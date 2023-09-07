#pragma once
#include <stdexcept>
#include <string>
#include <math.h>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

// ArrayList is equivalent to std::vector
// Influenced by https://github.com/Miguel-Deniz/Vector-Implementation/
// Most of this code is mine, but if I ever got stuck on something, I looked at how he did it

template <typename Data>
class ArrayList
{
private:
	// currently pointer to an array of ints
	Data* array;
	size_t length; // the current length of all actual values
	size_t capacity; // the length of the actual array thats storing all these values. Doubles when we hit the limit
	void setup(); // reuse for different constructors
public:
	////////////////////////////////////////////////////////////
	//					CONSTRUCTORS						///
	//////////////////////////////////////////////////////////
	ArrayList(); // default constructor
	ArrayList(size_t length);

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
	Data& operator[](size_t);

	// for const correctness, we should also have a const version of this function when ArrayList is const
	// https://isocpp.org/wiki/faq/const-correctness
	const Data& operator[](size_t) const;

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

	// useful function that idk why normal vector doesn't have
	Iterator iterator_at(size_t index);
	const Iterator iterator_at(size_t index) const;

	// these two versions of begin and end work when we want the iterator to not change any of the data inside of the array_List
	const Iterator cbegin() const;
	const Iterator cend() const;

	// this is just a wrapped for std::find
	// we don't want to change the data being searched or the array
	Iterator find(const Data& data) const;
	// check if the array_list has what we're looking for
	bool has(const Data& data) const;

	////////////////////////////////////////////////////////////
	//				CHANGING DATA							///
	//////////////////////////////////////////////////////////

	void push_back(const Data& new_data); // const and a reference because we don't want to change the data being inserted
	Data pop_back(); // returns the last element as we remove it from the array

	// if we want to delete everything and reset it
	void clear();

	// delete element at specific position
	void erase(Iterator iter);
	// delete elements starting from begin_erase, but ending before end_erase
	void erase(Iterator begin_erase, Iterator end_erase);
	// does same thing as erase
	void remove_at(size_t index);
	// does the same thing as erase
	void remove_between(size_t start, size_t end);

	// pop element at specific position
	Data pop_at(size_t index);

	////////////////////////////////////////////////////////////
	//				CAPACITY MANAGEMENT						///
	//////////////////////////////////////////////////////////

	// the following are const because these functions shouldn't change the data inside the vector itself
	size_t size() const;
	size_t max_size() const; // returns capacity

	// just so we don't have to constantly check array_list.size() != 0
	bool is_empty();
	const bool is_empty() const;

	/* runs whenever we need to resize the array to have greater capacity;
	 also just realized we can use this whenever we want to change size of the arraylist
	*/
	bool resize(size_t new_length);

	////////////////////////////////////////////////////////////
	//				NICE TO HAVES							///
	//////////////////////////////////////////////////////////

	// this should be const even though we're creating a string, we are not touching any data
	std::string to_string() const;
};

// https://stackoverflow.com/questions/12092448/code-for-a-basic-random-access-iterator-based-on-pointers
template <typename Data> 
class ArrayList<Data>::Iterator
{
public:
	// members of a struct are auto-public
	using iterator_category = std::random_access_iterator_tag; // we're making this a random_access_iterator so we can do a random shuffle
	using difference_type = std::ptrdiff_t;
	using value_type = Data;
	using pointer = Data*;  // or also value_type*
	using reference = Data&;  // or also value_type&

	Iterator(Data* _ptr) : ptr(_ptr) {};

	Iterator(const Iterator& other) : ptr(other.ptr) {};

	inline Iterator& operator+=(difference_type difference) 
	{ 
		ptr += difference; 
		return *this; 
	}
	inline Iterator& operator-=(difference_type difference) 
	{
		ptr -= difference; 
		return *this; 
	}

	// return data when dereferenced
	inline Data& operator*() const {
		return *ptr;
	}

	// make this const so we can use this in const
	// will not be able to edit the data inside the ptr
	inline Data* operator->() const
	{
		return ptr;
	}

	inline Data& operator[](difference_type difference) const { return ptr[difference]; }

	inline Iterator& operator++()
	{
		++ptr;
		return *this;
	}

	inline Iterator operator++(int) {
		Iterator temp = *this; ++(*this); return temp;
	}

	inline Iterator& operator--()
	{
		--ptr;
		return *this;
	}

	inline Iterator operator--(int) {
		Iterator temp = *this; ++(*this); return temp;
	}

	inline difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }
	inline Iterator operator+(difference_type difference) const { return Iterator(ptr + difference); }
	inline Iterator operator-(difference_type difference) const { return Iterator(ptr - difference); }
	friend inline Iterator operator+(difference_type left, const Iterator& right) { return Iterator(left + right.ptr); }
	friend inline Iterator operator-(difference_type left, const Iterator& right) { return Iterator(left - right.ptr); }

	
	// also using https://www.learncpp.com/cpp-tutorial/overloading-the-comparison-operators/
	inline bool operator== (const Iterator& other)
	{ 
		return ptr == other.ptr; 
	};

	inline bool operator!= (const Iterator& other)
	{
		return ptr != other.ptr;
	};

	inline bool operator< (const Iterator& other)
	{
		return ptr < other.ptr;
	};

	inline bool operator> (const Iterator& other)
	{
		return ptr > other.ptr;
	};

	inline bool operator<= (const Iterator& other)
	{
		return ptr <= other.ptr;
	};

	inline bool operator>= (const Iterator& other)
	{
		return ptr >= other.ptr;
	};

private:
	Data* ptr; // points to an element of ArrayList
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

template <typename Data> ArrayList<Data>::ArrayList(const size_t size)
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

template <typename Data> Data& ArrayList<Data>::operator[](size_t index)
{
	return array[index];
}

template <typename Data> const Data& ArrayList<Data>::operator[](size_t index) const
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

template <typename Data> size_t ArrayList<Data>::size() const
{
	return length;
}

template <typename Data> size_t ArrayList<Data>::max_size() const
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

template <typename Data> Data ArrayList<Data>::pop_back()
{
	Data popped_data = array[length - 1]; // copy data, since this wont exist after deleting the array
	resize(length - 1); // technically unnecessary, as this will delete and create a new array, but for the sake of API consistency, this is fine
	return popped_data;
}

template <typename Data> void ArrayList<Data>::erase(const Iterator iter)
{
	Data* new_array = new Data[length];

	size_t index = 0;
	// https://stackoverflow.com/a/14374550
	for (auto it = begin(); it != end(); ++it)
	{
		// skip data we're erasing
		if (it == iter)
		{
			continue;
		}
		new_array[index] = *it;
		++index;
	}

	delete[] array;
	array = new_array;

	// index is now the length of the new array
	// this means we can now resize to the length of the new array
	// this will create another array, which will probably waste memory, but oh well
	resize(index);
}

template <typename Data> 
void ArrayList<Data>::erase(const Iterator begin_erase, const Iterator end_erase)
{
	Data* new_array = new Data[length];

	size_t index = 0;
	// https://stackoverflow.com/a/14374550
	for (auto it = begin(); it != end(); ++it)
	{
		// skip data we're erasing
		// erase starting from beginning but stop before last
		if (it >= begin_erase  && it < end_erase)
		{
			continue;
		}
		// idk why this generates an errror
		new_array[index] = *it;
		++index;
	}

	delete[] array;
	array = new_array;

	// index is now the length of the new array
	// this means we can now resize to the length of the new array
	// this will create another array, which will probably waste memory, but oh well
	resize(index);
}

template <typename Data> void ArrayList<Data>::remove_at(size_t index)
{
	erase(iterator_at(index));
}

template <typename Data> void ArrayList<Data>::remove_between(size_t start, size_t end)
{
	erase(iterator_at(start), iterator_at(end));
}

template <typename Data> Data ArrayList<Data>::pop_at(size_t index)
{
	Data data_popped = array[index];
	erase(iterator_at(index));
	return Data;
}

/*TODO: implement this
template <typename Data> Data& ArrayList<Data>::pop_at(size_t position)
{
}
*/

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
const typename ArrayList<Data>::Iterator ArrayList<Data>::cbegin() const
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
const typename ArrayList<Data>::Iterator ArrayList<Data>::cend() const
{
	return Iterator(&array[length]); // get pointer to end of the array
}

template <typename Data>
typename ArrayList<Data>::Iterator ArrayList<Data>::iterator_at(size_t index)
{
	return Iterator(&array[index]); // get pointer at this specific index
}

template <typename Data>
typename const ArrayList<Data>::Iterator ArrayList<Data>::iterator_at(size_t index) const
{
	return Iterator(&array[index]); // get pointer at this specific index
}

template <typename Data>
typename ArrayList<Data>::Iterator ArrayList<Data>::find(const Data& data) const
{
	return std::find(begin(), end(), data);
}

template <typename Data>
typename bool ArrayList<Data>::has(const Data& data) const
{
	return find(data) != end();
}

// this will delete objects after new_length if new_length is smaller than the current size
template <typename Data>  bool ArrayList<Data>::resize(size_t new_length)
{
	length = new_length;
	capacity = 2 * length;

	Data* new_array = new Data[capacity];
	// copy stuff from old array to new array
	for (size_t i = 0; i < length; ++i)
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