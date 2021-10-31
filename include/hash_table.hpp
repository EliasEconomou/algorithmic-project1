#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <list>
#include <vector>
#include "hash_functions.hpp"
#include "functions.hpp"

class Point;

class HashNode
{
public:
    long int ID;
    Point *point;
    HashNode(Point *p, int ID);
};

class HashTable
{
    int bucketsNumber;
    std::list<HashNode> *lists; //a list for every bucket
public:
    HashTable(int bucketsNumber);
    
    // Insert item in hash table
    void HTinsert(Point *p, hash_info *hInfo);

    // Display hash table (debug)
    void HTdisplay();
};


#endif