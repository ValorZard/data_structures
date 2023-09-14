#pragma once
#include "linked_list.h"

template <typename Value> 
struct Bucket
{
	size_t hash; // the hash of the key of the value we're storing
	Value value; // the actual value we're storing
};

template <typename Key, typename Value> 
class HashMap
{

};