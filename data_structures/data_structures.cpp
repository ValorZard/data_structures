// data_structures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "linked_list.h"
#include "array_list.h"
#include "binary_tree.h"
#include "sorting.h"
#include <algorithm> // for random shuffle
#include <array>

int main()
{
    std::cout << "Hello World!\n";
    Node* n = new Node;
    Node* current_node = n;
    for (int i = 0; i < 100; ++i)
    {
        current_node->value = i;
        current_node->next = new Node;
        current_node = current_node->next;
    }
    std::cout << "print linked list\n";
    for (int i = 0; i < 100; ++i)
    {
        std::cout << n->value << "\n";
        n = n->next;
    }
    std::cout << "print ArrayList\n";
    ArrayList<int> vector(2);
    std::cout << vector.to_string() << "\n";

    // can i set and change shit?
    vector[1] = 2;
    std::cout << "Vector[1] = " << vector[1] << "\n";
    // IT DOES WORK WOOOO

    // test pushback
    std::cout << "Pushback test (second vec)" << "\n";
    ArrayList<int> second_vec;
    second_vec.push_back(12);
    std::cout << second_vec.to_string() << "\n";
    second_vec.push_back(123);
    second_vec.push_back(124);
    second_vec.push_back(125);
    second_vec.push_back(126);
    std::cout << "size of vec: " << second_vec.size() << " max size of vec: " << second_vec.max_size() << " vec: " << second_vec.to_string() << "\n";
   
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

    ArrayList<int> insertion_sort_vec(sorting_ints, + sizeof(sorting_ints) / sizeof(int));

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

    std::cout << "Test Erase: " << "\n";

    test_vec.erase(test_vec.iterator_at(10));

    std::cout << "Erased index 10 " << test_vec.to_string() << "\n";

    test_vec.erase(test_vec.iterator_at(7), test_vec.iterator_at(21));

    std::cout << "Erased between index 7 and 21 " << test_vec.to_string() << "\n";

    test_vec.remove_at(22);

    std::cout << "Deleted index 22 " << test_vec.to_string() << "\n";

    test_vec.remove_between(40, 60);
    
    std::cout << "Deleted from 40 and up to but not including 60 " << test_vec.to_string() << "\n";

    std::cout << "Check if test_vec has 69: " << std::to_string(test_vec.has(69)) << "\n";

    std::cout << "Check if test_vec has 81: " << std::to_string(test_vec.has(81)) << "\n";
    
    test_vec.erase(test_vec.find(81), test_vec.end());

    std::cout << "Since test_vec has 81, erase all values between 81 and the end of the vec " << test_vec.to_string() << "\n";

    std::random_shuffle(test_vec.begin(), test_vec.end());

    std::cout << "We've screwed up this vector enough, lets shuffle it" << test_vec.to_string() << "\n";

    //test_vec = insertion_sort(test_vec);

    //std::cout << "And now lets sort it! " << test_vec.to_string() << "\n";

    // randomly generate 10 numbers


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
