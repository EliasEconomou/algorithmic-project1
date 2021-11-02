#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <float.h>
#include "functions.hpp"
#include "hash_table.hpp"
#include "hash_functions.hpp"

// Compare function to use in priority queue
struct CompDist
{
    constexpr bool operator()(std::pair<Point, double> const& a, std::pair<Point, double> const& b)
    const noexcept
    {
        return a.second < b.second;
    }
};

Point lsh_approximate_NN(Point q, std::vector<HashTable> hashTables, hash_info *hInfo);

Point true_approximate_NN(Point q, Vector_of_points inputData);

std::priority_queue<std::pair<Point,double>,std::vector<std::pair<Point,double>>,CompDist> 
lsh_approximate_nNN(Point q, int N, std::vector<HashTable> hashTables, hash_info *hInfo);

std::priority_queue<std::pair<Point,double>,std::vector<std::pair<Point,double>>,CompDist> 
true_approximate_nNN(Point q, int N, Vector_of_points inputData);




#endif