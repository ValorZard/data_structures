#include "../data_structures/linked_list.h"
#include "pch.h"

/*
* this isnt working so fuck this
* 
class NodeTest : public ::testing::Test {
protected:
    Node* head;
    int amount_of_nodes;

    void SetUp() override{
        // fill up node with number from 0-99
        Node* current_node = head;
        amount_of_nodes = 100; // magic number i know
        for (int i = 0; i < amount_of_nodes; ++i)
        {
            current_node->value = i;
            current_node->next = new Node;
            current_node = current_node->next;
        }
    }

    void TearDown() override{
        // delete elements in node
        Node* current_node = head;
        while (current_node != nullptr)
        {
            Node* next_node = current_node->next;
            delete current_node;
            current_node = nullptr;
        }
    }

    // void TearDown() override {}
};
*/