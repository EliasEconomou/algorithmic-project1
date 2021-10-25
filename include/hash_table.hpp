#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <list>
#include <vector>



class HashNode
{
public:
    std::vector<double>* point;
    HashNode(std::vector<double> *p);
};


class HashTable
{
    int bucketsNumber;
    std::list<HashNode> *lists; //a list for every bucket
public:
    HashTable(int bucketsNumber);
    
    // inserts point into hash table
    void HTinsert(std::vector<double> *item);
 
    // hash function to map values to key
    int hashFunction(int x) {
        return (x % bucketsNumber);
    }
 
    void HTdisplay();
};


#endif