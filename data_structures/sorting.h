#pragma once
#include "array_list.h"
#include <iostream>
/*
* Find the smallest card. Swap it with the first card.
Find the second-smallest card. Swap it with the second card.
Find the third-smallest card. Swap it with the third card.
Repeat finding the next-smallest card, and swapping it into the correct position until the array is sorted.
*/

// Selection Sort
ArrayList<int> selection_sort(ArrayList<int> array_list) // let's not change the original array
{
	int current_index_being_sorted = 0;
	while(current_index_being_sorted < array_list.size())
	{
		int min_data = INT_MAX; // litterally every single value has to be less than this
		int min_index = -1; // if we swap with -1, something has gone horribly wrong and should throw an error

		// pretty sure selection sort is O(n^2) so this is the best we can do

		for (int index = current_index_being_sorted; index < array_list.size(); ++index)
		{
			if (array_list[index] < min_data)
			{
				min_data = array_list[index];
				min_index = index;
			}
		}

		// swap the current data of the array we are indexing
		// don't swap if it's already sorted
		if (current_index_being_sorted != min_index)
		{
			int old_data = array_list[current_index_being_sorted];
			array_list[current_index_being_sorted] = min_data;
			array_list[min_index] = old_data;
		}

		++current_index_being_sorted;
	}

	return array_list;
}

// Insertion Sort
/*	Call insert to insert the element that starts at index 1 into the sorted subarray in index 0.
	Call insert to insert the element that starts at index 2 into the sorted subarray in indices 0 through 1.
	Call insert to insert the element that starts at index 3 into the sorted subarray in indices 0 through 2.
*  Eventually, Call insert to insert the element that starts at index n - 1 into the sorted subarray in index 0 tbrough n - 2.
*/
ArrayList<int> insertion_sort(ArrayList<int> array_list) // let's not change the original array
{
	// we start at one for insertion sort (since we're using a subarray)
	int current_index_being_sorted = 1;
	while (current_index_being_sorted < array_list.size())
	{
		int data_being_sorted = array_list[current_index_being_sorted];
		
		// current index we are at in the sorted subarray
		// (Right now, its the index right before the element we're sorting
		// ex. 10, 9, 7, 14, 11, with [10, 9, 7, 14] being the sub array, and [11] being the element we're sorting
		// sorted index here would be 3 since array[3] = 14
		int sorted_index = current_index_being_sorted - 1;

		// going down the subarray, sort all the data not in order
		// since we're starting with a subarray of one, it HAS to be sorted properly
		// and then each time we have something not in order, we can just shuffle it down until it is sorted
		// ex. [10], 9, 7, 14, 11 -> [10, [9]] , 8, 14, 11 -> [10, 10] , 8, 14, 11 -> [[9], 10] , 8, 14, 11 
		// -> [[9, 10] ,[8]] , 14, 11 -> [[9, [8] , 10] , 14, 11 -> [[8], 9 , 10 , 14, 11
		// and so on
		while (sorted_index >= 0 && array_list[sorted_index] > data_being_sorted)
		{
			array_list[sorted_index + 1] = array_list[sorted_index];
			--sorted_index;
		}
		
		// During the first round, sorted_index will actually be -1, so sorted_index + 1 = 0
		// this mean that sorted_index + 1 is where the final insertion should be
		// sorted_index + 1 is also the last element in the sorted subarray
		array_list[sorted_index + 1] = data_being_sorted;

		++current_index_being_sorted;
	}

	return array_list;
}

void merge(ArrayList<int>::Iterator left, ArrayList<int>::Iterator middle, ArrayList<int>::Iterator right, ArrayList<int>& work_list)
{
	auto left_iter = left;
	auto right_iter = middle;

	// While there are elements in the left or right runs...
	for (auto iter = left; iter != right; ++iter) {
		// If left run head exists and is <= existing right run head.
		if (left_iter < middle && (right_iter >= right || *left_iter <= *right_iter)) {
			work_list.push_back(*left_iter);
			++left_iter;
		}
		else {
			work_list.push_back(*right_iter);
			++right_iter;
		}
	}
}

void merge_sort_helper(ArrayList<int>::Iterator left, ArrayList<int>::Iterator right, ArrayList<int>& work_list)
{
	auto size = std::distance(left, right);
	if (size <= 1) // only two hop between begin and end, which means run_size == 1
	{
		return;
	}
	auto middle = std::next(left, (size / 2));
	merge_sort_helper(left, middle, work_list);
	merge_sort_helper(middle, right, work_list);
	merge(left, middle, right, work_list);
}

// Merge Sort
ArrayList<int> merge_sort(ArrayList<int>& unsorted_list)
{
	ArrayList<int> sorted_list = unsorted_list;

	ArrayList<int> work_list = unsorted_list;

	merge_sort_helper(sorted_list.begin(), sorted_list.end(), work_list);
	return sorted_list;
}


// Quick sort
