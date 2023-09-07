#pragma once
#include <stdexcept>
#include <string>
#include <math.h> 
// equivalent to std::vector

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


	// the following are const because these functions shouldn't change the data inside the vector itself
	int size() const;
	int max_size() const; // returns capacity

	void push_back(const Data& new_data); // const and a reference because we don't want to change the data being inserted

	// runs whenever we need to resize the array to have greater capacity;
	// also just realized we can use this whenever we want to change size of the arraylist
	bool resize(int new_length);

	// if we want to delete everything and reset it
	void clear();

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
	for (int i = 0; i < old.length; ++i) {
		// get each of the data from the old ArrayList and put it into this one
		push_back(old.array[i]);
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

	for (int i = 0; i < old.size(); ++i) {
		push_back(old.array[i]);
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

template <typename Data> int ArrayList<Data>::size() const
{
	return length;
}

template <typename Data> int ArrayList<Data>::max_size() const
{
	return capacity;
}

template <typename Data> void ArrayList<Data>::push_back(const Data& new_data)
{
	++length; // increase length since we're adding something at the end
	resize(length);
	array[length - 1] = new_data; // add thing on the end of the array
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

	for (int i = 0; i < size(); ++i) {
		list_string += std::to_string(array[i]) + ",";
	}

	list_string += "]";
	return list_string;
}