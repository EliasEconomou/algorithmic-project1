#include "../include/hash_table.hpp"

using namespace std;


HashNode::HashNode(std::vector<double> *p)
{
  point=p;
}


HashTable::HashTable(int bucketNumber)
{
    this->bucketsNumber = bucketNumber;
    lists = new std::list<HashNode>[bucketNumber]; //allocate 'bucketsNumber' space for lists
}
 

void HashTable::HTinsert(std::vector<double> *p)
{
    // int index = hashFunction(key);
    // table[index].push_back(key);
    // cout << "In insert. \n";
    lists[0].push_back(HashNode(p));
}


void HashTable::HTdisplay() 
{
  for (int k=0 ; k < bucketsNumber ; k++){
    cout << "In bucket #" << k << " of hashtable: \n" ;
    for (int i=0 ; i < lists[k].size() ; i++){
      std::list<HashNode>::iterator current;
      for (current = lists[k].begin() ; current != lists[k].end() ; ++current ){
        // std::cout << current->point->size() << endl;
        for (auto j = current->point->begin() ; j != current->point->end() ; ++j){
          std::cout << *j << " ";
        }
      }
    }
    cout << endl;
  }

  // for (int i = 0; i < bucketsNumber; i++) {
  //     cout << i;
  //     HashNode* node;
  //     // vector<double> temp = node;
  //     cout << endl;
  // }
}
