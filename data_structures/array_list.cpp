#include "array_list.h"
#include <stdexcept>

void ArrayList::setup()
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

ArrayList::ArrayList(const int size = 0)
{
	// i'm just going to throw an error if the size is set to be less than to zero to make shit less weird to deal with
	if (size < 0)
	{
		throw std::runtime_error("size is less than 0, this is currently not supported!");
	}
	this->length = size;
	setup();
}

ArrayList::ArrayList()
{
	this->length = 0;
	setup();
}

ArrayList::~ArrayList()
{
	delete array;
}

int& ArrayList::operator[](int index)
{
	return array[index];
}

int ArrayList::size()
{
	return length;
}

int ArrayList::max_size()
{
	return capacity;
}

void ArrayList::push_back(int thing)
{
	++length; // increase length since we're adding something at the end
	resize();
	array[length - 1] = thing; // add thing on the end of the array
}

bool ArrayList::resize()
{
	// double capacity if the array has become too big
	if (length >= capacity)
	{
		capacity *= 2;
		int* new_array = new int[capacity];
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