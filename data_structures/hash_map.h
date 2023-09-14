#pragma once
#include "linked_list.h"
#include <string>

// https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
template <typename Key, typename Value>
class HashNode
{
public:
	Key key; // the key of the value we're storing
	Value value; // the actual value we're storing
    // Constructor of hashnode
    HashNode(Key key, Value value)
    {
        this->value = value;
        this->key = key;
    }
};

template <typename Key, typename Value> 
class HashMap
{
private:
	HashNode<Key, Value>** array; // contains all of the nodes, each element in the array being a pointer to the actual node
	bool* deleted_array; // did you remove something at that index
	size_t size, capacity;
public:
    HashMap()
    {
        // Initial capacity of hash array
        capacity = 20;
        size = 0;
        array = new HashNode<Key, Value>* [capacity];


        // Initialise all elements of array as NULL
        for (size_t i = 0; i < capacity; i++)
            array[i] = nullptr;

        // fill deleted array
        deleted_array = new bool[capacity];
        for (size_t i = 0; i < capacity; i++)
            deleted_array[i] = false;
        
    }
    // This implements hash function to find index
    // for a key
    size_t hashCode(Key key)
    {
        return key % capacity;
    }

    // Function to add key value pair
    void insertNode(Key key, Value value)
    {
        HashNode<Key, Value>* temp = new HashNode<Key, Value>(key, value);

        // Apply hash function to find index for given key
        size_t hashIndex = hashCode(key);

        // find next free space
        // don't store value in a deleted space
        while ((array[hashIndex] != nullptr || array[hashIndex]->key != key) || deleted_array[hashIndex] == true)
        {
            hashIndex++;
            hashIndex %= capacity;
        }

        // if new node to be inserted
        // increase the current size
        if (array[hashIndex] == nullptr
            || deleted_array[hashIndex] == false)
            size++;
        array[hashIndex] = temp;
    }

    // Function to delete a key value pair
    Value deleteNode(size_t key)
    {
        // Apply hash function
        // to find index for given key
        size_t hashIndex = hashCode(key);

        // finding the node with given key
        while (deleted_array[hashIndex] == false) {
            // if node found
            if (array[hashIndex]->key == key) {
                //HashNode<Key, Value>* temp = array[hashIndex];

                // Insert dummy node here for further use
                //delete array[hashIndex];
                deleted_array[hashIndex] = true; // this position has been deleted

                // Reduce size
                size--;
                return array[hashIndex]->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }

        // If not found return null or empty
        return 0;
    }

    // Function to search the value for a given key
    Value get(size_t key)
    {
        // Apply hash function to find index for given key
        size_t hashIndex = hashCode(key);
        size_t counter = 0;

        // finding the node with given key
        while (array[hashIndex] != nullptr) { // int counter =0; // BUG!

            if (counter++ > capacity) // to avoid infinite loop
                return 0;

            // skip deleted values
            if (deleted_array[hashIndex] == false)
                continue;

            // if node found return its value
            if (array[hashIndex]->key == key)
                return array[hashIndex]->value;
            hashIndex++;
            hashIndex %= capacity;
        }

        // If not found return null
        return 0;
    }

    // Return current size
    size_t sizeofMap()
    {
        return size;
    }

    // Return true if size is 0
    bool isEmpty()
    {
        return size == 0;
    }

    // Function to display the stored key value pairs
    std::string toString()
    {
        std::string map_str = "";
        for (size_t i = 0; i < capacity; i++) {
            if (array[i] != nullptr && deleted_array[i] == false)
            {
                map_str += "key = ";
                map_str += std::to_string(array[i]->key);
                map_str += "  value = ";
                map_str += std::to_string(array[i]->value);
            }
        }
    }
};
