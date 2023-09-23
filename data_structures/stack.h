#pragma once
#include "array_list.h"

template <typename Data>
class Stack
{
private:
	ArrayList<Data> vector;
public:
	void push(Data value)
	{
		vector.push_back(value);
	}

	Data pop()
	{
		return vector.pop_back();
	}
};