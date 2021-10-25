#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <list>
#include <vector>


template <class T>
class HashNode
{
public:
    std::vector<T> *point;
    HashNode(std::vector<T> *p);
};

template <class T>
class HashTable
{
    int bucketsNumber;
    std::list<HashNode<T> > *lists; //a list for every bucket
public:
    HashTable(int bucketsNumber);
    
    // inserts point into hash table
    void HTinsert(std::vector<T> *item);
 
//     // hash function to map values to key
    int hashFunction(int x) {
        return (x % bucketsNumber);
    }
 
    void HTdisplay();
};


#endif