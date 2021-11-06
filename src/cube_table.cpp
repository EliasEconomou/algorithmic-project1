#include "../include/cube_table.hpp"

using namespace std;


Vertice::Vertice(Point *p)
{
  this->point = p;
}



CubeTable::CubeTable(int bucketsNumber)
{
  this->bucketsNumber = bucketsNumber;
  this->lists.resize(this->bucketsNumber);
}



// void HashTable::HTinsert(Point *p, hash_info *hInfo)
// {
//   vector<int> hValues;
//   hInfo->update_v(this->v);
//   hInfo->update_t(this->t);
//   hInfo->update_r(this->r);
//   int k = hInfo->get_k();
//   vector<int> vp = p->vpoint;
//   for (int i = 0; i < k; i++)
//   {
//     hValues.push_back(compute_hValue(i, vp, hInfo));
//   }

//   long int ID = compute_IDvalue(hValues, hInfo);
//   int g = compute_gValue(ID, this->bucketsNumber);
//   lists[g].push_back(HashNode(p, ID));
// }



// void HashTable::HTdisplay() 
// {
//   for (int k=0 ; k < bucketsNumber ; k++){
//     cout << "In bucket #" << k << " of hashtable: \n" ;
//     typename list<HashNode>::iterator current;
//       for (current = lists[k].begin() ; current != lists[k].end() ; ++current ){
//         // std::cout << current->point->size() << endl;
//         for (auto j = current->point->vpoint.begin() ; j != current->point->vpoint.end() ; ++j){
//           cout << *j << " ";
//         }
//         cout << endl;
//       }
//     cout << endl;
//   }
// }



// int HashTable::get_bucketsNumber()
// {
//   return this->bucketsNumber;
// }



// list<HashNode> HashTable::get_bucketList(int g)
// {
//   return this->lists[g];
// }