#include "../include/hash_table.hpp"

using namespace std;


HashNode::HashNode(std::vector<int> *p, int ID)
{
  this->ID = ID;
  this->point = p;
}



HashTable::HashTable(int bucketNumber)
{
  this->bucketsNumber = bucketNumber;
  lists = new list<HashNode>[bucketNumber]; //allocate 'bucketsNumber' space for lists
}




void HashTable::HTinsert(vector<int> *p, hash_info *hInfo)
{
  vector<int> hValues;
  int k = hInfo->get_k();
  for (int i = 0; i < k; i++)
  {
    hValues.push_back(compute_hValue(i, *p, hInfo));
    
  }

  long int ID = compute_IDvalue(hValues, hInfo);
  int g = compute_gValue(ID, this->bucketsNumber);
  
  //vector<int> hValues = compute_hValues(p, k,data);
  lists[g].push_back(HashNode(p, ID));
}



void HashTable::HTdisplay() 
{
  for (int k=0 ; k < bucketsNumber ; k++){
    cout << "In bucket #" << k << " of hashtable: \n" ;
    typename list<HashNode>::iterator current;
      for (current = lists[k].begin() ; current != lists[k].end() ; ++current ){
        // std::cout << current->point->size() << endl;
        for (auto j = current->point->begin() ; j != current->point->end() ; ++j){
          cout << *j << " ";
        }
        cout << endl;
      }
    cout << endl;
  }
}

