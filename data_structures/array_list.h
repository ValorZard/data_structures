#pragma once

// equivalent to std::vector

class ArrayList
{
private:
	// currently pointer to an array of ints
	int* array;
	int length; // the current length of all actual values
	int capacity; // the length of the actual array thats storing all these values. Doubles when we hit the limit

	bool resize(); // runs whenever we need to resize the array to have greater capacity;
	void setup(); // reuse for different constructors
public:
	ArrayList(); // default constructor
	ArrayList(int length);
	~ArrayList();

	// overloading the [] operator
	int& operator[](int);

	int size();
	int max_size(); // returns capacity

	void push_back(int thing);
};
