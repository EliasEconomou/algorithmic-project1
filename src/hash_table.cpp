#include "../include/hash_table.hpp"

using namespace std;

template <class T>
HashNode<T>::HashNode(std::vector<T> *p)
{
  point=p;
}

template <class T>
HashTable<T>::HashTable(int bucketNumber)
{
    this->bucketsNumber = bucketNumber;
    lists = new std::list<HashNode<T> >[bucketNumber]; //allocate 'bucketsNumber' space for lists
}

template class HashTable<int>;
template class HashTable<float>;
template class HashTable<double>;

template <class T>
void HashTable<T>::HTinsert(std::vector<T> *p)
{
    // int index = hashFunction(key);
    // table[index].push_back(key);
    // cout << "In insert. \n";
    lists[0].push_back(HashNode<T>(p));
}

template <class T>
void HashTable<T>::HTdisplay() 
{
  for (int k=0 ; k < bucketsNumber ; k++){
    cout << "In bucket #" << k << " of hashtable: \n" ;
    typename std::list<HashNode<T> >::iterator current;
      for (current = lists[k].begin() ; current != lists[k].end() ; ++current ){
        // std::cout << current->point->size() << endl;
        for (auto j = current->point->begin() ; j != current->point->end() ; ++j){
          std::cout << *j << " ";
        }
        cout << endl;
      }
    cout << endl;
  }
}
