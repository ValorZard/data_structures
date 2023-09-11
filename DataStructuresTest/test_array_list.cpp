#include "pch.h"
#include "../data_structures/array_list.h"
#include <algorithm> // for iterator stuff
#include <iterator>
#include <array>
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

TEST(ArrayList, ArrayListCopyAssignment)
{
	ArrayList<char> v;
	v.push_back('a');
	v.push_back('z');
	v.push_back('x');
	v.push_back('r');
	v.push_back('e');

	ArrayList<char> second_vec = v;
	second_vec.push_back('l');
	second_vec.push_back('e');
	second_vec.push_back('g');
	second_vec.push_back('o');
	second_vec.push_back('s');

	second_vec = v;

	EXPECT_EQ(v.at(0), second_vec.at(0));
	EXPECT_EQ(v.at(1), second_vec.at(1));
	EXPECT_EQ(v.at(2), second_vec.at(2));
	EXPECT_EQ(v.at(3), second_vec.at(3));
	EXPECT_EQ(v.at(4), second_vec.at(4));
}

TEST(ArrayList, GenerateFromArray)
{
	int array_of_ints[] = { 10, 9, 7, 14, 11 };
	size_t array_size = sizeof(array_of_ints) / sizeof(int);
	ArrayList<int> vec{ array_of_ints, array_size };

	// test if the vec and the array_of_ints generate the same
	for (size_t i = 0; i < array_size; ++i)
	{
		ASSERT_EQ(array_of_ints[i], vec[i]);
	}
}

TEST(ArrayList, GenerateFromIter)
{
	// create array of size 9
	std::array<int, 9> array = {4, 7, 9, 12, 43, 32, 17, -1, 0};
	ArrayList<int> array_list( array.begin(), array.end() );
	// test if the array and the array_list generated from its iterator are the same
	int i = 0;
	for (int numb : array_list)
	{
		ASSERT_EQ(numb, array[i]);
		++i;
	}
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

TEST(ArrayList, FindAndHas)
{
	ArrayList<int> vec;
	vec.push_back(22);
	vec.push_back(64);
	vec.push_back(96);

	// this should be in there
	ASSERT_EQ(vec.has(64), true); // check if it has the data
	ASSERT_NE(vec.find(64), vec.end()); // get the iterator for the data

	// this should NOT be in there
	ASSERT_EQ(vec.has(39), false); // check if it has the data
	ASSERT_EQ(vec.find(39), vec.end()); // get the iterator for the data
}

TEST(ArrayList, Clear)
{
	ArrayList<int> vec;
	for (int i = 0; i < 100; ++i)
	{
		vec.push_back(i);
	}
	ASSERT_EQ(vec.is_empty(), false);
	vec.clear();
	ASSERT_EQ(vec.is_empty(), true);
	ASSERT_EQ(vec, ArrayList<int>()); // check if vec is the same as a newly initalized ArrayList
}

TEST(ArrayList, EraseData)
{
	ArrayList<int> vec;
	vec.push_back(22);
	vec.push_back(64);
	vec.push_back(96);

	// check to see if 64 is in there, which it should be
	auto my_iter = vec.find(64);
	ASSERT_NE(my_iter, vec.end());

	// check if 42 is in there, which it isnt
	my_iter = vec.find(42);
	ASSERT_EQ(my_iter, vec.end());

	// Erase 64
	vec.erase(vec.find(64));
	// check to see if 64 doesn't exist anymore and if the array is the same size with all of its elements
	ASSERT_EQ(vec.find(64), vec.end());
	ASSERT_EQ(vec.size(), 2);
	ASSERT_EQ(vec[0], 22);
	ASSERT_EQ(vec[1], 96);
}

TEST(ArrayList, EraseRange)
{
	ArrayList<int> vec;
	for (int i = 0; i < 100; ++i)
	{
		vec.push_back(i);
	}
	ASSERT_EQ(vec.size(), 100);
	// remove all numbers between 39 and up to but not including 42
	vec.erase(vec.begin() + 39, vec.begin() + 42);
	// check to see if it worked
	ASSERT_EQ(vec.size(), 97); // we removed 3 elements (39, 40, 41) so size should be 97
	// check if the elements we removed actually got removed
	for (int i = 0; i < 100; ++i)
	{
		if (i < 42 && i >= 39)
		{
			ASSERT_EQ(vec.find(i), vec.end()); // we shouldn't be able to find these numbers in the array
		}
	}
}

TEST(ArrayList, RemoveAt)
{
	ArrayList<int> vec;
	vec.push_back(22);
	vec.push_back(64);
	vec.push_back(96);

	// check to see if 64 is in there, which it should be
	size_t index = vec.find(64) - vec.begin();
	ASSERT_EQ(index, 1);

	// Erase 64
	vec.remove_at(index);
	// check to see if 64 doesn't exist anymore and if the array is the same size with all of its elements
	ASSERT_EQ(vec.find(64), vec.end());
	ASSERT_EQ(vec.size(), 2);
	ASSERT_EQ(vec[0], 22);
	ASSERT_EQ(vec[1], 96);
}

TEST(ArrayList, RemoveRange)
{
	ArrayList<int> vec;
	for (int i = 0; i < 100; ++i)
	{
		vec.push_back(i);
	}
	ASSERT_EQ(vec.size(), 100);
	// remove all numbers between 39 and up to but not including 42
	// since this is remove_range, we're removing the items at vec[39], vec[40], and vec[41]
	vec.remove_range(39, 42);
	// check to see if it worked
	ASSERT_EQ(vec.size(), 97); // we removed 3 elements (39, 40, 41) so size should be 97
	// check if the elements we removed actually got removed
	for (int i = 0; i < 100; ++i)
	{
		if (i < 42 && i >= 39)
		{
			ASSERT_EQ(vec.find(i), vec.end()); // we shouldn't be able to find these numbers in the array
		}
	}
}

TEST(ArrayList, PopAt)
{
	ArrayList<int> vec;
	vec.push_back(22);
	vec.push_back(64);
	vec.push_back(96);

	// check to see if 64 is in there, which it should be
	size_t index = vec.find(64) - vec.begin();
	ASSERT_EQ(index, 1);

	// Pop the element at index 1 
	int data = vec.pop_at(index);
	// check if the data we popped is equal to 64
	ASSERT_EQ(data, 64);
	// check to see if 64 doesn't exist anymore in the array_list and if the array is the same size with all of its elements
	ASSERT_EQ(vec.find(64), vec.end());
	ASSERT_EQ(vec.size(), 2);
	ASSERT_EQ(vec[0], 22);
	ASSERT_EQ(vec[1], 96);
}

TEST(ArrayList, PopBack)
{
	ArrayList<int> vec;
	vec.push_back(22);
	vec.push_back(64);
	vec.push_back(96);

	// Pop back the last element
	int data = vec.pop_back();
	// check if the data we popped is equal to 96
	ASSERT_EQ(data, 96);
	// check to see if 64 doesn't exist anymore in the array_list and if the array is the same size with all of its elements
	ASSERT_EQ(vec.find(96), vec.end());
	ASSERT_EQ(vec.size(), 2);
	ASSERT_EQ(vec[0], 22);
	ASSERT_EQ(vec[1], 64);
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

TEST(ArrayList, ForEach)
{
	ArrayList<int> vec;
	vec.push_back(10);
	vec.push_back(9);
	vec.push_back(8);
	vec.push_back(42);
	vec.push_back(64);

	size_t index = 0;
	// check if each item is in the same place in the for each as the index its supposed to be at
	for (auto& item : vec)
	{
		ASSERT_EQ(vec[index], item);
		++index;
	}
}

TEST(ArrayList, insert)
{
	ArrayList<int> insertion_vec;
	for (int i = 0; i < 10; ++i)
	{
		insertion_vec.push_back(i);
	}
	EXPECT_EQ(insertion_vec.size(), 10);
	// insert 69, and check if we actually inserted it
	insertion_vec.insert(insertion_vec.begin() + 1, 69);
	// we inserted it at index 1
	int index = insertion_vec.find(69) - insertion_vec.begin();
	ASSERT_EQ(index, 1);
	// size increase by 1
	EXPECT_EQ(insertion_vec.size(), 11);
	// We're inserting 42 into this 4 times
	int amount_added = 4;
	insertion_vec.insert(insertion_vec.begin() + 4, amount_added, 42);
	// Check if it worked...
	EXPECT_EQ(insertion_vec.size(), 15);
	int amount_counted = 0; // checks the amount of 42 we've found
	for (int numb : insertion_vec)
	{
		if (numb == 42)
		{
			++amount_counted;
		}
	}
	ASSERT_EQ(amount_added, amount_counted);
}

TEST(ArrayList, insertIter)
{
	//std::array<int, 5> full_array = { 1, 2, 3, 4, 5 };
	ArrayList<int> full_array;
	full_array.push_back(1);
	full_array.push_back(2);
	full_array.push_back(3);
	full_array.push_back(4);
	full_array.push_back(5);
	// we're going to combine these two array's using insertion
	//std::array<int, 3> array1 = { 1, 4, 5 };
	ArrayList<int> array1;
	array1.push_back(1);
	array1.push_back(4);
	array1.push_back(5);
	//std::array<int, 2> array2 = { 2, 3};
	ArrayList<int> array2;
	array2.push_back(2);
	array2.push_back(3);

	// convert array 1 into an ArrayList
	ArrayList<int> insertion_vec(array1.begin(), array1.end());
	// insert array2 into the vec
	insertion_vec.insert(insertion_vec.begin() + 1, array2.begin(), array2.end());
	// the size of the insertion vec should be the same as the full array
	ASSERT_EQ(full_array.size(), insertion_vec.size());
	// make sure each element full_array and insertion_vec is equal
	ASSERT_EQ(full_array[0], insertion_vec[0]);
	ASSERT_EQ(full_array[1], insertion_vec[1]);
	ASSERT_EQ(full_array[2], insertion_vec[2]);
	ASSERT_EQ(full_array[3], insertion_vec[3]);
	ASSERT_EQ(full_array[4], insertion_vec[4]);
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

TEST(ArrayList, resize)
{
	ArrayList<int> vec;
	vec.push_back(10);
	vec.push_back(9);
	vec.push_back(8);
	vec.push_back(42);
	vec.push_back(64);

	ASSERT_EQ(vec.size(), 5);

	vec.resize(3);
	
	// Check size has changed
	ASSERT_EQ(vec.size(), 3);
	// Check all the elements are in the right places
	ASSERT_EQ(vec[0], 10); 
	ASSERT_EQ(vec[1], 9);
	ASSERT_EQ(vec[2], 8);
	// Resize again and check size
	vec.resize(69);
	ASSERT_EQ(vec.size(), 69);
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