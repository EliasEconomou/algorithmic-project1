#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <list>
#include <vector>
#include "hash_functions.hpp"


class HashNode
{
public:
    std::vector<int> *point;
    HashNode(std::vector<int> *p);
};

class HashTable
{
    int bucketsNumber;
    std::list<HashNode> *lists; //a list for every bucket
public:
    HashTable(int bucketsNumber);
    
    // Insert item in hash table
    void HTinsert(std::vector<int> *p, hash_info *hInfo);

    // Display hash table (debug)
    void HTdisplay();
};


#endif