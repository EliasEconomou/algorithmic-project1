#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <numeric>
#include <cmath>
#include <climits>
#include <algorithm>
#include <functional>
#include "point_functions.hpp"

class LSH_hash_info
{
private:
    int w,k,d,L; //k = number of h functions, d = dimension
    long long int M;
    std::vector<double> t;
    std::vector<std::vector<double> > v; //k vectors to use to compute every h
    std::vector<int> r;
public:
    LSH_hash_info(int k, int d, int L);
    
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


class CUBE_hash_info
{
private:
    int w,k,d,M,probes; //d = dimension, k = new dimension to project points
    std::vector<double> t;
    std::vector<std::vector<double> > v; //k vectors to use to compute every h
    std::unordered_map<int,int> MapHtoF;
public:
    CUBE_hash_info(int k, int d, int M, int probes);

    // Clear vectors v and add new random values to them.
    void update_v(std::vector<std::vector<double> >);
    // Clear vector t and add new random values to it.
    void update_t(std::vector<double>);

    // Check if h-key is in map and has an f-value. If not assign f-value and add it to map. Return the f-value.
    int update_map(int hValue);
    
    // Get vectors and values. 
    std::vector<std::vector<double> > get_v();
    std::vector<double> get_t();
    int get_w();
    int get_k();
    int get_d();
    int get_M();
    int get_probes();
};


// Returns a vector with k ints computed from k-h functions.
int compute_hValue(int i, std::vector<int> p, LSH_hash_info *hInfo);
int compute_hValue(int i, std::vector<int> p, CUBE_hash_info *hInfo);


// Returns the f value that corresponds to the h value given.
int compute_fValue(int hValue, CUBE_hash_info *hInfo);


// Returns the ID value for quicker searching.
long int compute_IDvalue(std::vector<int> hValues, LSH_hash_info *hInfo);


// Returns the g hash function - value.
int compute_gValue(long int ID, int bucketNumber);
int compute_gValue(std::vector<int> fValues, CUBE_hash_info *hInfo);


// Returns the t vector with values in [0,w).
std::vector<double> compute_t(int k);


// Returns the v vector with values distributed according to the Gaussian distribution.
std::vector<std::vector<double> > compute_v(int k, int d);


// Returns the r vector to use in g function.
std::vector<int> compute_r(int k);


#endif