#pragma once
#include <stdexcept>
// equivalent to std::vector

template <typename Data>
class ArrayList
{
private:
	// currently pointer to an array of ints
	Data* array;
	int length; // the current length of all actual values
	int capacity; // the length of the actual array thats storing all these values. Doubles when we hit the limit

	bool resize(); // runs whenever we need to resize the array to have greater capacity;
	void setup(); // reuse for different constructors
public:
	ArrayList(); // default constructor
	ArrayList(unsigned int length);
	~ArrayList();

	// overloading the [] operator
	Data& operator[](unsigned int);

	int size();
	int max_size(); // returns capacity

	void push_back(Data new_data);
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
	array = new int[capacity] {0};
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

template <typename Data> ArrayList<Data>::~ArrayList()
{
	delete array;
}

template <typename Data> Data& ArrayList<Data>::operator[](unsigned int index)
{
	return array[index];
}

template <typename Data> int ArrayList<Data>::size()
{
	return length;
}

template <typename Data> int ArrayList<Data>::max_size()
{
	return capacity;
}

template <typename Data> void ArrayList<Data>::push_back(Data new_data)
{
	++length; // increase length since we're adding something at the end
	resize();
	array[length - 1] = new_data; // add thing on the end of the array
}

template <typename Data>  bool ArrayList<Data>::resize()
{
	// double capacity if the array has become too big
	if (length >= capacity)
	{
		capacity *= 2;
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
	return false; // we didn't resize the array, false
}