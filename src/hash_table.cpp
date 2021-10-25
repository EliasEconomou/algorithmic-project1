#include "../include/hash_table.hpp"

using namespace std;


HashNode::HashNode(std::vector<int> * p)
{
  point=p;
}

HashTable::HashTable(int bucketNumber)
{
    this->bucketsNumber = bucketNumber;
    lists = new std::list<HashNode>[bucketsNumber]; //allocate 'bucketsNumber' lists
}
 
void HashTable::HTinsert(std::vector<int> *p)
{
    // int index = hashFunction(key);
    // table[index].push_back(key);
    HashNode node = HashNode(p);
    lists[0].push_back(node);
}

void HashTable::HTdisplay() 
{
  for (int i = 0; i < bucketsNumber; i++) {
      cout << i;
      HashNode* node;
      vector<int> temp = ;
      cout << endl;
  }
}
