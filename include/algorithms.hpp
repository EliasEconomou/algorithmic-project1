#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include "functions.hpp"
#include "hash_table.hpp"
#include "hash_functions.hpp"

Point approximate_NN(Point q, std::vector<HashTable> hashTables, hash_info *hInfo);



#endif