#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include "functions.hpp"

// Returns a vector with k ints computed from k-h functions
std::vector<int> compute_hValues(int k, std::vector<std::vector<int> > data);
std::vector<int> compute_hValues(int k, std::vector<std::vector<float> > data);
std::vector<int> compute_hValues(int k, std::vector<std::vector<double> > data);






#endif