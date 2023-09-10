#include "pch.h"
#include "../data_structures/array_list.h"

// taken from https://github.com/Miguel-Deniz/Vector-Implementation/blob/master/unittest_Vector/test.cpp



// Constructors
TEST(ArrayList, ctor)
{
	ArrayList<int> v;

	// Check size = 0, capacity = 0, no elements
	EXPECT_EQ(0, v.size());
	EXPECT_EQ(0, v.get_capacity());
}

TEST(ArrayList, ArrayListCopyCtor)
{
	ArrayList<char> v;
	v.push_back('a');
	v.push_back('z');
	v.push_back('x');
	v.push_back('r');
	v.push_back('e');

	ArrayList<char> copy = v;

	EXPECT_EQ(v.at(0), copy.at(0));
	EXPECT_EQ(v.at(1), copy.at(1));
	EXPECT_EQ(v.at(2), copy.at(2));
	EXPECT_EQ(v.at(3), copy.at(3));
	EXPECT_EQ(v.at(4), copy.at(4));
}




// Iterators
TEST(ArrayList, iteratorBegin)
{
	ArrayList<int> v;

	v.push_back(4);
	EXPECT_EQ(4, *v.begin());

	v.push_back(9);
	EXPECT_EQ(4, *v.begin());

	v[0] = -1;
	ArrayList<int>::Iterator itr = v.begin();
	EXPECT_EQ(-1, *itr);

	++itr;
	EXPECT_EQ(9, *itr);

	v.push_back(5);

	EXPECT_EQ(9, *itr);
	++itr;
	EXPECT_EQ(5, *itr);


	// Constant ArrayList
	const ArrayList<int> cv = v;

	ArrayList<int>::Iterator constItr = cv.begin();
	EXPECT_EQ(-1, *constItr);
}

TEST(ArrayList, iteratorEnd)
{

}

TEST(ArrayList, iteratorSequence)
{

}




// Capacity
TEST(ArrayList, size)
{
	ArrayList<double> v;

	// Size should be 0 upon creation
	EXPECT_EQ(0, v.size());

	v.push_back(3.14);
	EXPECT_EQ(1, v.size());

	v.push_back(0);
	EXPECT_EQ(2, v.size());
}

TEST(ArrayList, capacity)
{

}




// Modifiers
TEST(ArrayList, push_back_ints)
{
	ArrayList<int> v;

	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(i, v[i]);

	v.push_back(1000);
	EXPECT_EQ(1000, v[v.size() - 1]);
}




// Accessors
TEST(ArrayList, accessAt)
{
	// Non-const ArrayList
	ArrayList<int> v;

	EXPECT_THROW(v.at(0), std::out_of_range);
	EXPECT_THROW(v.at(-97), std::out_of_range);
	EXPECT_THROW(v.at(1), std::out_of_range);

	v.push_back(4);
	v.push_back(8);
	v.push_back(10);
	v.push_back(-19);
	v.push_back(0);

	EXPECT_EQ(4, v.at(0));
	EXPECT_EQ(8, v.at(1));
	EXPECT_EQ(10, v.at(2));
	EXPECT_EQ(-19, v.at(3));
	EXPECT_EQ(0, v.at(4));

	//EXPECT_THROW(v.at(-1), std::out_of_range);
	EXPECT_THROW(v.at(5), std::out_of_range);


	// Const ArrayList
	const ArrayList<int> cv = v;

	EXPECT_EQ(4, cv.at(0));
	EXPECT_EQ(8, cv.at(1));
	EXPECT_EQ(10, cv.at(2));
	EXPECT_EQ(-19, cv.at(3));
	EXPECT_EQ(0, cv.at(4));

	//EXPECT_THROW(cv.at(-1), std::out_of_range);
	EXPECT_THROW(cv.at(5), std::out_of_range);
	//EXPECT_THROW(cv.at(-2), std::out_of_range);
	EXPECT_THROW(cv.at(8), std::out_of_range);
}

TEST(ArrayList, accessBrackets)
{
	const int NUM_ELEMENTS = 50;

	ArrayList<double> v;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
		v.push_back(i);

	for (int i = 0; i < NUM_ELEMENTS; ++i)
		EXPECT_EQ(i, v[i]);

	const ArrayList<double> cv = v;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
		EXPECT_EQ(i, cv[i]);
}

TEST(ArrayList, accessFront)
{
	ArrayList<int> v;

	v.push_back(9);
	EXPECT_EQ(9, v.front());

	v.push_back(4);
	EXPECT_EQ(9, v.front());
}

TEST(ArrayList, accessBack)
{
	ArrayList<int> v;

	v.push_back(9);
	EXPECT_EQ(9, v.back());

	v.push_back(4);
	EXPECT_EQ(4, v.back());

	v.push_back(1);
	EXPECT_EQ(1, v.back());
}

TEST(ArrayList, accessData)
{
	ArrayList<char> v;

	v.push_back('t');
	v.push_back('r');
	v.push_back('o');
	v.push_back('l');
	v.push_back('l');

	char* ptrCh = v.get_array();

	EXPECT_EQ(*ptrCh, v.front());
	EXPECT_EQ(*(ptrCh + 1), v.at(1));
	EXPECT_EQ(*(ptrCh + 2), v.at(2));
	EXPECT_EQ(*(ptrCh + 3), v.at(3));
	EXPECT_EQ(*(ptrCh + 4), v.at(4));
}