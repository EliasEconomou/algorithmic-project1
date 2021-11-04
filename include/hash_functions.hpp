#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include <climits>
#include <algorithm>
#include <functional>
#include "point_functions.hpp"

class hash_info
{
private:
    int w,k,d,L; //k = number of h functions, d = dimension
    long long int M;
    std::vector<double> t;
    std::vector<std::vector<double> > v; //k vectors to use to compute every h
    std::vector<int> r;
public:
    hash_info(int k, int d, int L);
    ~hash_info();
    
    // Clear vectors v and add new random values to them.
    void update_v(std::vector<std::vector<double> >);
    // Clear vector t and add new random values to it.
    void update_t(std::vector<double>);
    // Clear vector r and add new random values to it.
    void update_r(std::vector<int>);
    
    // Get vectors and values. 
    std::vector<std::vector<double> > get_v();
    std::vector<double> get_t();
    std::vector<int> get_r();
    int get_w();
    int get_k();
    int get_d();
    int get_L();
    long int get_M();
};


// Returns a vector with k ints computed from k-h functions
int compute_hValue(int i, std::vector<int> p, hash_info *hInfo);


// Returns the ID value for quicker searching
long int compute_IDvalue(std::vector<int> hValues, hash_info *hInfo);


// Returns the g hash function - value
int compute_gValue(long int ID, int bucketNumber);


// Returns the t vector with values in [0,w).
std::vector<double> compute_t(int k);


// Returns the v vector with values distributed according to the Gaussian distribution.
std::vector<std::vector<double> > compute_v(int k, int d);


// Returns the r vector to use in g function
std::vector<int> compute_r(int k);


#endif