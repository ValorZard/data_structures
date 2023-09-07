#pragma once
#include <stdexcept>
#include <string>
#include <math.h>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t
#include <algorithm>

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

	void setup(const size_t size = 0); // reuse for different constructors
public:
	////////////////////////////////////////////////////////////
	//					CONSTRUCTORS						///
	//////////////////////////////////////////////////////////
	ArrayList(); // default constructor
	ArrayList(size_t length);
	//template <class InputIterator> ArrayList(InputIterator first, InputIterator last); // iterator constructor
	ArrayList(const Data data_array[], const size_t size);

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

	// using Iterator to insert elements
	template <class InputIterator> void insert(InputIterator position, Data value);
	template <class InputIterator> void insert(InputIterator position, size_t amount, Data value);
	// starts from the first but ends before the last
	template <class InputIterator> void insert(InputIterator position, InputIterator first, InputIterator last);

	////////////////////////////////////////////////////////////
	//				CAPACITY MANAGEMENT						///
	//////////////////////////////////////////////////////////

	// the following are const because these functions shouldn't change the data inside the vector itself
	size_t size() const;
	size_t get_capacity() const; // returns capacity

	// just so we don't have to constantly check array_list.size() != 0
	bool is_empty();
	const bool is_empty() const;

	/* runs whenever we need to resize the array to have greater capacity;
	 also just realized we can use this whenever we want to change size of the arraylist
	*/
	bool resize(size_t new_length, Data value = 0);

	// runs when we want to make sure we can fit at least n elements in the capacity
	void reserve(size_t new_capacity);

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

template <typename Data> 
inline void ArrayList<Data>::setup(const size_t size)
{
	this->length = size;
	// let's assume that we don't need to make the array bigger than it is already
	// If we do need to change the size, that will be handled by resize()
	this->capacity = this->length;
	// make sure the values of the array are all default
	array = new Data[capacity];

	for (size_t i = 0; i < capacity; ++i)
	{
		array[i] = 0;
	}
}

template <typename Data> 

inline ArrayList<Data>::ArrayList(const size_t size)
{
	setup(size);
}

template <typename Data> 
inline ArrayList<Data>::ArrayList()
{
	setup();
}

/* THIS IS BROKEN I NEED TO FIX IT!!
template<typename Data, class InputIterator>
inline ArrayList<Data>::ArrayList(InputIterator first, InputIterator last)
{
	setup(last-first);

	std::copy(first, last, array);

}
*/


template<typename Data>
inline ArrayList<Data>::ArrayList(const Data data_array[], const size_t size)
{
	setup();

	for (size_t i = 0; i < size; ++i)
	{
		push_back(data_array[i]);
	}
}

template <typename Data> ArrayList<Data>::ArrayList(const ArrayList& old)
{
	// do basic setup before we do anything too crazy
	setup(old.end() - old.begin());
	std::copy(old.begin(), old.end(), array);
}

template <typename Data> ArrayList<Data>& ArrayList<Data>::operator=(const ArrayList<Data>& old)
{
	if (this == &old)
	{
		return *this; // self assigment, so don't need to do anything
	}

	// reset the object
	clear();

	setup(old.end() - old.begin());
	std::copy(old.begin(), old.end(), array);

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

template <typename Data> size_t ArrayList<Data>::get_capacity() const
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

template <typename Data> 
inline void ArrayList<Data>::push_back(const Data& new_data)
{
	++length; // increase length since we're adding something at the end
	resize(length);
	array[length - 1] = new_data; // add thing on the end of the array
}

template <typename Data> 
inline Data ArrayList<Data>::pop_back()
{
	Data popped_data = array[length - 1]; // copy data, since this wont exist after deleting the array
	resize(length - 1); // technically unnecessary, as this will delete and create a new array, but for the sake of API consistency, this is fine
	return popped_data;
}

// this can be optimized better
template <typename Data> 
inline void ArrayList<Data>::erase(const Iterator iter)
{
	// the capacity is still the same
	Data* new_array = new Data[capacity];

	size_t index = 0;
	// https://stackoverflow.com/a/14374550
	for (auto it = begin(); it != end(); ++it)
	{
		// skip data we're erasing
		if (it == iter)
		{
			// make sure to decrease size by one now that we know we have erased the data
			length -= 1;
		}
		else
		{
			new_array[index] = *it;
			++index;
		}
	}

	delete[] array;
	array = new_array;
}

/* THIS CAN BE OPTIMIZED BETTER
* https://cplusplus.com/reference/vector/vector/erase/
* Removes from the vector either a single element (position) or a range of elements ([first,last)).

	This effectively reduces the container size by the number of elements removed, which are destroyed.

	Because vectors use an array as their underlying storage, 
	erasing elements in positions other than the vector end causes the container to relocate all the elements after the segment erased to their new positions. 
	This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
*/
template <typename Data> 
inline void ArrayList<Data>::erase(const Iterator begin_erase, const Iterator end_erase)
{
	Data* new_array = new Data[capacity];

	size_t index = 0;
	// https://stackoverflow.com/a/14374550
	for (auto it = begin(); it != end(); ++it)
	{
		// skip data we're erasing
		// erase starting from beginning but stop before last
		if (it >= begin_erase  && it < end_erase)
		{
			// make sure to decrease length by one now that we know we have erased the data
			length -= 1;
		}
		else
		{
			// idk why this generates an errror
			new_array[index] = *it;
			++index;
		}
	}

	delete[] array;
	array = new_array;
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

template<typename Data>
template <class InputIterator>
inline void ArrayList<Data>::insert(InputIterator position, Data value)
{
	size_t index_of_inserted_value = position - begin();
	if (index_of_inserted_value > length)
	{
		// we can't insert that doesn't exist
		// inserting at length is fine because thats just equivalent to push_back()
		throw std::length_error("we can't insert that at a position which doesn't exist");
	}

	// the length is now increased by one, so we should resize
	resize(length + 1);

	// this is like a reverse insertion sort

	// shuffle everything up by one
	Data old_value = array[index_of_inserted_value];
	
	// shuffle up by 1 and replace each old value with new value
	// ex. 10 9 8 7 -> 1 10 9 8 7
	for (size_t shuffle_index = index_of_inserted_value; shuffle_index < length; ++shuffle_index)
	{
		array[shuffle_index] = old_value; // set the current index to the old data before this one (shuffle_index - 1);
		old_value = array[shuffle_index + 1]; // now this shuffle index is old value
	}
	// now set our now emptied slot to our value
	array[index_of_inserted_value] = value;
}

template<typename Data>
template <class InputIterator>
inline void ArrayList<Data>::insert(InputIterator position, size_t amount, Data value)
{
	size_t index_of_inserted_value = position - begin();
	if (index_of_inserted_value > length)
	{
		// we can't insert that doesn't exist
		// inserting at length is fine because thats just equivalent to push_back()
		throw std::length_error("we can't insert that at a position which doesn't exist");
	}

	// the length is now increased by amount, so we should resize
	size_t old_length = length;
	length += amount;

	// we should resize the array if necessary
	Data* new_array;
	if (length > capacity)
	{
		capacity = 2 * length;
	}
	new_array = new Data[capacity];


	// fill in everything before like normal
	
	for (size_t index = 0; index < index_of_inserted_value; ++index)
	{
		new_array[index] = array[index];
	}
	
	// fill up the amount indexs with value
	for (size_t i = index_of_inserted_value; i < index_of_inserted_value + amount; ++i)
	{
		new_array[i] = value;
	}

	// keep iterating through the new array while remembering the offset
	for (size_t index = index_of_inserted_value + amount; index < length; ++index)
	{
		new_array[index] = array[index - amount];
	}

	// for everything else, make sure its zero
	for (size_t index = length; index < capacity; ++index)
	{
		new_array[index] = 0;
	}

	delete[] array;
	array = new_array;
}

template<typename Data>
template <class InputIterator>
inline void ArrayList<Data>::insert(InputIterator position, InputIterator first, InputIterator last)
{
	size_t index_of_inserted_value = position - begin();
	if (index_of_inserted_value > length)
	{
		// we can't insert that doesn't exist
		// inserting at length is fine because thats just equivalent to push_back()
		throw std::length_error("we can't insert that at a position which doesn't exist");
	}

	size_t amount = last - first; // the amount of elements we want to add

	// the length is now increased by amount, so we should resize
	size_t old_length = length;
	length += amount;

	// we should resize the array if necessary
	Data* new_array;
	if (length > capacity)
	{
		capacity = 2 * length;
	}
	new_array = new Data[capacity];


	// fill in everything before like normal

	size_t index = 0;

	for (auto iter = begin(); iter != position; ++iter)
	{
		new_array[index] = *iter;
		++index;
	}

	// fill up the amount indexs with value
	for (auto iter = first; iter != last; ++iter)
	{
		new_array[index] = *iter;
		++index;
	}

	// keep iterating through the new array while remembering the offset
	for (auto iter = position; iter != end(); ++iter)
	{
		new_array[index] = *iter;
	}

	
	delete[] array;
	array = new_array;
}


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
inline typename ArrayList<Data>::Iterator ArrayList<Data>::iterator_at(size_t index)
{
	return Iterator(&array[index]); // get pointer at this specific index
}

template <typename Data>
typename const ArrayList<Data>::Iterator 
inline ArrayList<Data>::iterator_at(size_t index) const
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

/*
this will delete objects after new_length if new_length is smaller than the current size
 we should optimize this better

 https://cplusplus.com/reference/vector/vector/resize/

 Resizes the container so that it contains n elements.

If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond(and destroying them).

If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n.If val is specified, the new elements are initialized as copies of val, otherwise, they are value - initialized.

If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.

Notice that this function changes the actual content of the container by inserting or erasing elements from it.
*/
template <typename Data>  
inline bool ArrayList<Data>::resize(size_t new_length, Data value)
{
	length = new_length;
	if (length > capacity)
	{
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
		return true; // return true if we did change the array's capacity
	}
	else
	{
		// fill up all the empty slots in the array with value
		for (size_t i = new_length; i < capacity; ++i)
		{
			array[i] = value;
		}
	}

}

template <typename Data>
inline void ArrayList<Data>::reserve(size_t new_capacity)
{
	if (new_capacity > capacity)
	{
		capacity = 2 * new_capacity; // double capacity just in case

		Data* new_array = new Data[capacity];
		// copy stuff from old array to new array
		for (size_t i = 0; i < length; ++i)
		{
			new_array[i] = array[i];
		}
		// delete old array and set it to new array
		delete array;
		array = new_array;
		return true; // return true if we did change the array's capacity
	}
}


template <typename Data> 
inline void ArrayList<Data>::clear()
{
	// reset everything
	delete[] array;
	setup();
}

template <typename Data>  
inline std::string ArrayList<Data>::to_string() const
{
	std::string list_string = "[";

	for (Data& data : *this) {
		list_string += std::to_string(data) + ",";
	}

	list_string += "]";
	return list_string;
}