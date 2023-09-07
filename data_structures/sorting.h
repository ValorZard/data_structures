#pragma once
#include "array_list.h"

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
		// current index we are at in the sorted subarray
		int sorted_index = 0;
		// get data at index in sorted subarray
		int current_data = array_list[sorted_index];
		for (sorted_index = 0; sorted_index < current_index_being_sorted - 1; ++sorted_index)
		{
			current_data = array_list[sorted_index];
			if (array_list[current_index_being_sorted] < current_data)
			{
				// we found a place to put the data, and swap it with the current subarray data which is in the wrong palce
				break;
			}
		}

		// swap the current data of the array we are indexing
		int old_data = array_list[current_index_being_sorted];
		array_list[current_index_being_sorted] = current_data;
		array_list[sorted_index] = old_data;

		++current_index_being_sorted;
	}

	return array_list;
}


// Merge Sort

// Quick sort
