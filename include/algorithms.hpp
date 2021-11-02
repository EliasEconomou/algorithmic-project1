#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <float.h>
#include "functions.hpp"
#include "hash_table.hpp"
#include "hash_functions.hpp"

Point lsh_approximate_NN(Point q, std::vector<HashTable> hashTables, hash_info *hInfo);

Point true_approximate_NN(Point q, Vector_of_points inputData);

Point lsh_approximate_nNN(Point q, int N, vector<HashTable> hashTables, hash_info *hInfo);

#endif