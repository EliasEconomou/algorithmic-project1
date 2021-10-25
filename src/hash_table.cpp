#include "../include/hash_table.hpp"

using namespace std;


HashNode::HashNode(std::vector<double> *p)
{
  point=p;
}


HashTable::HashTable(int bucketNumber)
{
    this->bucketsNumber = bucketNumber;
    lists = new std::list<HashNode>[bucketsNumber]; //allocate 'bucketsNumber' lists
}
 

void HashTable::HTinsert(std::vector<double> *p)
{
    // int index = hashFunction(key);
    // table[index].push_back(key);
    cout << "In insert. \n";
    HashNode* node = new HashNode(p);
    lists[0].push_back(node);
}


void HashTable::HTdisplay() 
{
  // std::cout << << endl;
  // for (int i = 0; i < bucketsNumber; i++) {
  //     cout << i;
  //     HashNode* node;
  //     // vector<double> temp = node;
  //     cout << endl;
  // }
}
