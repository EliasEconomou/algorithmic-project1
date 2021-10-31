#include "../include/hash_table.hpp"

using namespace std;


HashNode::HashNode(Point *p, int ID)
{
  this->ID = ID;
  this->point = p;
}



HashTable::HashTable(int bucketNumber)
{
  this->bucketsNumber = bucketNumber;
  lists = new list<HashNode>[bucketNumber]; //allocate 'bucketsNumber' space for lists
}




void HashTable::HTinsert(Point *p, hash_info *hInfo)
{
  vector<int> hValues;
  int k = hInfo->get_k();
  vector<int> vp = p->vpoint;
  for (int i = 0; i < k; i++)
  {
    hValues.push_back(compute_hValue(i, vp, hInfo));
    
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
        for (auto j = current->point->vpoint.begin() ; j != current->point->vpoint.end() ; ++j){
          cout << *j << " ";
        }
        cout << endl;
      }
    cout << endl;
  }
}

