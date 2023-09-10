#include "pch.h"
#include "../data_structures/array_list.h"
#include <algorithm> // for iterator stuff
#include <iterator>
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

// basic functionality
TEST(ArrayList, ChangeData)
{
	ArrayList<int> vector(2);
	// can i set and change shit?
	vector[1] = 2;
	EXPECT_EQ(vector[1], 2);
}

TEST(ArrayList, PushBack)
{
	ArrayList<int> vec;
	// capacity is 1
	vec.push_back(12);
	// capacity is now 2
	vec.push_back(123);
	// capacity double when we push back here because we reached the limit
	// 2 -> 3 (since we added an element) -> reserve() gets called and sets the capacity to double (6)
	vec.push_back(124);
	vec.push_back(125);
	vec.push_back(126);
	ASSERT_EQ(vec.size(), 5);
	ASSERT_EQ(vec.get_capacity(), 6);
	vec.push_back(25);
	// capacity double when we push back here because we reached the limit
	// 6 -> 7 (since we added an element) -> reserve() gets called and sets the capacity to double (14)
	vec.push_back(16);
	vec.push_back(55);
	vec.push_back(62);
	ASSERT_EQ(vec.size(), 9);
	ASSERT_EQ(vec.get_capacity(), 14);
}

TEST(ArrayList, EqualsOperator)
{
	ArrayList<int> vec;
	vec.push_back(10);
	vec.push_back(9);
	vec.push_back(8);
	ArrayList<int> second_vec = vec;
	ASSERT_EQ(vec, second_vec);
	second_vec.pop_back(); // delete the lsat element
	ASSERT_NE(vec, second_vec);
	second_vec.push_back(7); // add in an element so that they are now the same size
	ASSERT_NE(vec, second_vec);
	second_vec.pop_back();
	second_vec.push_back(8);
	ASSERT_EQ(vec, second_vec); // they should now be the same again
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

	// the following two can't work because the vector got resized, meaning the old iterator is no longer valid
	EXPECT_NE(9, *itr);
	++itr;
	EXPECT_NE(5, *itr);

	// if we make a new iterator, it should now work
	itr = v.begin();
	++itr;
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