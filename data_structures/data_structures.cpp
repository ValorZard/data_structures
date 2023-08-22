// data_structures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "linked_list.h"
#include "array_list.h"

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
    ArrayList vector(2);
    for (int i = 0; i < vector.size(); ++i)
    {
        std::cout << vector[i] << "\n";
    }

    // can i set and change shit?
    vector[1] = 2;
    std::cout << vector[1] << "\n";
    // IT DOES WORK WOOOO

    // test pushback
    std::cout << "Pushback test" << "\n";
    ArrayList second_vec;
    second_vec.push_back(12);
    for (int i = 0; i < second_vec.size(); ++i)
    {
        std::cout << second_vec[i] << "\n";
    }
    second_vec.push_back(123);
    second_vec.push_back(124);
    second_vec.push_back(125);
    second_vec.push_back(126);
    std::cout << "size of vec: " << second_vec.size() << " max size of vec: " << second_vec.max_size() << "\n";
    for (int i = 0; i < second_vec.size(); ++i)
    {
        std::cout << second_vec[i] << "\n";
    }
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
