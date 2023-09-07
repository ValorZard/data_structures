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
	for (int current_index_being_sorted = 0; current_index_being_sorted < array_list.size(); ++current_index_being_sorted)
	{
		int min_data = INT_MAX; // litterally every single value has to be less than this
		int min_index = -1; // if we swap with -1, something has gone horribly wrong and should throw an error

		// pretty sure selection sort is O(n^2) so this is the best we can do

		for (int index = current_index_being_sorted; index < array_list.size(); ++index)
		{
			if (array_list[index] < INT_MAX)
			{
				min_data = array_list[index];
				min_index = index;
			}
		}

		// swap the current data of the array we are indexing

		int old_data = array_list[current_index_being_sorted];
		array_list[current_index_being_sorted] = min_data;
		array_list[min_index] = old_data;
	}

	return array_list;
}

// Merge Sort

// Quick sort
