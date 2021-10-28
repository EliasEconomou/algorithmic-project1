#include "../include/hash_functions.hpp"

using namespace std;


// Returns w (int 3 to 6) // todo w
int compute_w(void)
{
    return 4;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Returns the t vector with values in [0,w).
vector<double> compute_t(int k)
{
    vector<double> t;
    random_device rd;
    mt19937 generator(rd());
    for (int i = 0; i < k; i++)
    {
        uniform_real_distribution<double> d(0.0, float(compute_w()));
        double coordinate = d(generator);
        t.push_back(coordinate);
    }
    return t;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Returns the v vector with values distributed according to the Gaussian distribution.
vector<vector<double> > compute_v(int k, int d)
{
    vector<vector<double> > v;
    random_device rd;
    mt19937 generator(rd());
    for (int i = 0; i < k; i++)
    {
        vector<double> vi;
        for (int j = 0; j < d; j++)
        {
            normal_distribution<double> d{0,1};
            double coordinate = d(generator);
            vi.push_back(coordinate);
        }
        v.push_back(vi);
        
    }
    // for (int i = 0; i < k; i++)
    // {
    //     for (int j = 0; j < d; j++)
    //     {
    //         cout << v[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return v;

 
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Returns the r vector to use in g function
vector<int> compute_r(int k)
{
    vector<int> r;
    for (int i = 0; i < k; i++)
    {
        int rValue = random_number(1,100);
        r.push_back(rValue);
    }
    return r;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


hash_info::hash_info(int k, int d)
{
    this->k = k;
    this->d = d;
    this->w = compute_w();
    this->v = compute_v(k, d);
    this->t = compute_t(k);
    this->r = compute_r(k);
    
}

hash_info::~hash_info()
{
}

vector<vector<double> > hash_info::get_v()
{
    return this->v;
}

vector<double> hash_info::get_t()
{
    return this->t;
}

vector<int> hash_info::get_r()
{
    return this->r;
}

int hash_info::get_w()
{
    return this->w;
}

int hash_info::get_k()
{
    return this->k;
}

int hash_info::get_d()
{
    return this->d;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Returns an h-value.
int compute_hValue(int i, vector<int> p, hash_info *hInfo)
{
    
    
    int hValue;
    vector<vector<double> > v = hInfo->get_v();
    vector<double> vi = v[i];
    // Creating all k-h functions
    // Extract vector-point (cordinates), leave out the index
    auto first = p.begin() + 1;
    auto last = p.begin() + hInfo->get_d() + 1;
    vector<int> pRow(first, last);
    // for (size_t j = 0; j < hInfo->get_d(); j++)
    // {
    //     cout << "j : " << j << " - " << "p = " << pRow[j] << " and " << vi[j] << endl;
    // }
    // cout << endl;
    double pv = inner_prod(pRow,vi); //compute inner product p*v

    vector<double> t = hInfo->get_t();
    double ti = t[i];

    int w = hInfo->get_w();
    
    // cout << "pv = " << pv << " " << "ti = " << ti << " and w = " << w << endl<<endl; 
    hValue = (pv - ti)/w;
    return hValue;
}
int compute_hValue(int i, vector<double> p, hash_info *hInfo)
{
    int hValue;
    vector<vector<double> > v = hInfo->get_v();
    vector<double> vi = v[i];
    for (int j = 0; j < vi[j]; j++)
    {
        cout << vi[j] << " " << endl;
    }
    
    // Creating all k-h functions
    // Extract vector-point (cordinates), leave out the index
    auto first = p.begin() + 1;
    auto last = p.begin() + hInfo->get_d() + 1;
    vector<double> pRow(first, last);
    double pv = inner_prod(pRow,vi); //compute inner product p*v
    
    vector<double> t = hInfo->get_t();
    double ti = t[i];

    int w = hInfo->get_w();
    
    hValue = (pv - ti)/w;
    return hValue;
}


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// // Returns the ID - value
// int compute_IDvalue(std::vector<int> hValues)
// {
//     int hSize = hValues.size();
//     vector<int> r;
//     for (int i = 0; i < hSize; i++)
//     {
//         int rValue = random_number(1,100);
//         r.push_back(rValue);
//     }
    
    
    
// }