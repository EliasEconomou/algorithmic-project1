#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <utility>
#include <climits>
#include <float.h>
#include "point_functions.hpp"
#include "hash_table.hpp"
#include "cube_table.hpp"
#include "hash_functions.hpp"

// Compare function to use in set.
struct CompDist
{
    constexpr bool operator()(std::pair<Point, double> const& a, std::pair<Point, double> const& b)
    const noexcept
    {
        return a.second < b.second;
    }
};


//TRUE

Point true_NN(Point q, Vector_of_points inputData);

std::set<std::pair<Point,double>, CompDist> 
true_nNN(Point q, int N, Vector_of_points inputData);


//LSH

Point lsh_approximate_NN(Point q, std::vector<HashTable> hashTables, LSH_hash_info *hInfo);

std::set<std::pair<Point,double>, CompDist> lsh_approximate_nNN(Point q, int N, std::vector<HashTable> hashTables, LSH_hash_info *hInfo);

std::unordered_map<int,double> lsh_approximate_range_search(Point q, double R, std::vector<HashTable> hashTables, LSH_hash_info *hInfo);


//HYPERCUBE

std::pair<Point,double> cube_approximate_NN(Point q, CubeTable cubeTable, CUBE_hash_info *hInfo);



#endif