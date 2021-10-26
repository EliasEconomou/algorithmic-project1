#include "../include/hash_functions.hpp"

using namespace std;

// Returns w (int 3 to 6) todo
int compute_w(void)
{
    return 4;
}

// Returns random t-shift with values in [0,w).
double compute_t(void)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> dis(0.0, float(compute_w()));
    return dis(generator);
}

// Returns the v vector of coordinates distributed according to the Gaussian distribution.
vector<double> compute_v(int dimension)
{
    vector<double> v;
    random_device rd;
    mt19937 generator(rd());
    for (int i = 0; i < dimension; i++)
    {
        normal_distribution<double> d{0,1};
        double coordinate = d(generator);
        v.push_back(coordinate);
    }
    return v;
 
}

// Returns a vector with k ints computed from k-h functions.
vector<int> compute_hValues(int k, vector<vector<int> > data)
{
    int dimension = data[0].size();
    int w = compute_w();
    vector<int> hValues;
    vector<double> v;
    // Creating all k-h functions
    for (int i = 0; i < k; i++)
    {
        double t = compute_t();
        v = compute_v(dimension);
        int randomIndex = random_number(0,data.size()-1); //choose random vector from data (vector of vectors)
        double pv = inner_prod(data[randomIndex],v); //compute inner product p*v
        int h = (pv - t)/w;
        hValues.push_back(h);
    }    
    return hValues;
}
// vector<int> compute_hValues(int k, vector<vector<float> > data) todo polymorphism
// {

// }
// vector<int> compute_hValues(int k, vector<vector<double> > data)
// {
                
// }