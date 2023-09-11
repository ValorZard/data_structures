// data_structures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "linked_list.h"
#include "array_list.h"
#include "binary_tree.h"
#include "sorting.h"
#include <algorithm> // for random shuffle
#include <array>

std::string array_list_string(ArrayList<int> array_list)
{
    std::string list_string = "[";
    for (size_t i = 0; i < array_list.size(); ++i)
    {
        list_string += std::to_string(array_list[i]) + ",";
    }
    list_string += "]";
    
    return list_string;
}

int main()
{
    std::cout << "Hello World!\n";

    // test pushback
    std::cout << "Pushback test (second vec)" << "\n";
    ArrayList<int> second_vec;
    second_vec.push_back(12);
    std::cout << second_vec.to_string() << "\n";
    second_vec.push_back(123);
    second_vec.push_back(124);
    second_vec.push_back(125);
    second_vec.push_back(126);
    std::cout << "size of vec: " << second_vec.size() << " max size of vec: " << second_vec.get_capacity() << " vec: " << second_vec.to_string() << "\n";
   
    // do sorting stuff
    std::cout << "doing sorting" << "\n";
    ArrayList<int> unsorted_vec = second_vec;
    unsorted_vec.push_back(19);
    unsorted_vec.push_back(21);
    unsorted_vec.push_back(32);
    unsorted_vec.push_back(1);
    unsorted_vec.push_back(14);
    unsorted_vec.push_back(26);
    unsorted_vec.push_back(7);
    unsorted_vec.push_back(30);
    std::cout << "unsorted array: " << unsorted_vec.to_string() << "\n";
    // this caused horrible bugs before we added a copy constructor
    ArrayList<int> sorted_vec = selection_sort(unsorted_vec);
    std::cout << "unsorted array: " << unsorted_vec.to_string() << " sorted array: " << sorted_vec.to_string() << "\n";

    // popping data
    std::cout << "popping unsorted array" << "\n";
    while (!unsorted_vec.is_empty())
    {
        int popped_data = unsorted_vec.pop_back();
        std::cout << popped_data << "\n";
    }

    // resize
    sorted_vec.resize(4);
    std::cout << "resized: " << sorted_vec.to_string() << "\n";
    std::cout << "front: " << sorted_vec.front() << " back: " << sorted_vec.back() << "\n";

    // insertion sort
    int sorting_ints[] = {10, 9, 7, 14, 11};

    // insert list with size
    ArrayList<int> insertion_sort_vec(sorting_ints, sizeof(sorting_ints) / sizeof(int));

    std::cout << "Vector we're going to sort: " << insertion_sort_vec.to_string() << "\n";

    insertion_sort_vec = insertion_sort(insertion_sort_vec);

    std::cout << "It's sorted! -> " << insertion_sort_vec.to_string() << "\n";


    // check if for each loop works
    ArrayList<int> test_vec;
    for (int i = 0; i < 100; ++i)
    {
        test_vec.push_back(i);
    }

    std::cout << "Test ForEach: " << test_vec.to_string() << "ForEach Works!" << "\n";

    std::cout << "Test Erase! Size: " << test_vec.size() << "\n";

    test_vec.erase(test_vec.iterator_at(10));

    std::cout << "Erased index 10 " << test_vec.to_string() << "\n"; // - 1 element
    std::cout << "Test Erase! Size: " << test_vec.size()  << " Capacity: " << test_vec.get_capacity() << "\n";

    test_vec.erase(test_vec.iterator_at(7), test_vec.iterator_at(21));

    std::cout << "Erased between index 7 and 21 " << test_vec.to_string() << "\n"; // deleted (21 - 7) elements
    std::cout << "Test Erase! Size: " << test_vec.size() << "\n";

    test_vec.remove_at(22);

    std::cout << "Deleted index 22 " << test_vec.to_string() << "\n";
    std::cout << "Test Erase! Size: " << test_vec.size() << "\n";

    test_vec.remove_range(40, 60);
    
    std::cout << "Deleted from 40 and up to but not including 60 " << test_vec.to_string() << "\n"; // deleted (60 - 40) elements
    std::cout << "Test Erase! Size: " << test_vec.size() << "\n";

    std::cout << "Check if test_vec has 69: " << std::to_string(test_vec.has(69)) << "\n";

    std::cout << "Check if test_vec has 81: " << std::to_string(test_vec.has(81)) << "\n";
    
    test_vec.erase(test_vec.find(81), test_vec.end());

    std::cout << "Checking a random element to see if it's not junk data: " << *(test_vec.end() - 4) << "\n";

    std::cout << "Since test_vec has 81, erase all values between 81 and the end of the vec " << test_vec.to_string() << "\n";

    std::cout << "Let's try another way to print out the thing: " << array_list_string(test_vec) << "\n";

    std::random_shuffle(test_vec.begin(), test_vec.end());

    std::cout << "We've screwed up this vector enough, lets shuffle it" << test_vec.to_string() << "\n";

    test_vec = merge_sort(test_vec);

    std::cout << "And now lets sort it! " << test_vec.to_string() << "\n";

    // insertion test
    ArrayList<int> insertion_vec;
    for (int i = 0; i < 10; ++i)
    {
        insertion_vec.push_back(i);
    }
    std::cout << "We're inserting 69 into this: " << insertion_vec.to_string() << "\n";
    insertion_vec.insert(insertion_vec.begin(), 69);
    std::cout << "Check if it worked..: " << insertion_vec.to_string() << "\n";
    std::cout << "We're inserting 42 into this 4 times: " << insertion_vec.to_string() << "\n";
    insertion_vec.insert(insertion_vec.begin() + 4, 4, 42);
    std::cout << "Check if it worked..: " << insertion_vec.to_string() << "\n";
    //std::cout << "What length should be: " << 10 + 1 + 4 << " What it actually is: " << insertion_vec.size() << "\n";

    ArrayList<int> empty_vec;
    std::cout << "Here's an empty vec! " << empty_vec.to_string() << "\n";
    empty_vec.insert(empty_vec.begin(), insertion_vec.begin(), insertion_vec.end());
    std::cout << "Now not so empty! " << empty_vec.to_string() << "\n";

    // test test cases from unit test for debugging
    ArrayList<int> v;

    v.push_back(4);
    std::cout << "The following should be true: 4 should be equal to " << *v.begin() << " " << (4 == *v.begin()) << "\n";

    v.push_back(9);
    std::cout << "The following should be true: 4 should be equal to " << *v.begin() << " " << (4 == *v.begin()) << "\n";

    v[0] = -1;
    ArrayList<int>::Iterator itr = v.begin();
    std::cout << "The following should be true: -1 should be equal to " << *itr << " " << (-1 == *itr) << "\n";

    ++itr;
    std::cout << "The following should be true: 9 should be equal to " << *itr << " " << (9 == *itr) << "\n";

    v.push_back(5);

    std::cout << "The following should be true: 9 should be equal to " << *itr << " " << (9 == *itr) << "\n";
    ++itr;
    std::cout << "The following should be true: 5 should be equal to " << *itr << " " << (5 == *itr) << "\n";


    // Constant ArrayList
    const ArrayList<int> cv = v;

    ArrayList<int>::Iterator constItr = cv.begin();
    std::cout << "The following should be true: -1 should be equal to " << *constItr << " " << (-1 == *constItr) << "\n";

    // binary search tree
    BinarySearchTree bst;
    bst.insert(7);
    bst.insert(2);
    bst.insert(6);
    bst.insert(4);
    bst.insert(5);
    bst.insert(3);
    bst.insert(10);
    bst.insert(1);
    bst.insert(8);
    bst.insert(12);
    bst.print_tree();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
