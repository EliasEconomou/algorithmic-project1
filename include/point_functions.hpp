#ifndef POINT_FUNCTIONS_H
#define POINT_FUNCTIONS_H

#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>


class Point
{
public:
    int itemID; //index id of point
    std::vector<int> vpoint; //point-vector of coordinates
    
};


class Vector_of_points
{
public:
    std::vector<Point> points; //vector of points
};

//----Same classes as above but with pointers----

class PPoint
{
    public:
    Point* ppoint;
};

class Vector_of_ppoints
{
    public:
    std::vector<PPoint> ppoints; //vector of pointers to points
};

class Cluster_of_points // class to implement clusters easier
{
    public:
    vector<PPoint> centroids; //vector of pointers to centroid Points
    vector<Vector_of_ppoints> points; //vector of pointers to Points in each cluster
};

//-------------------------------------------------



// Parse dataset and return a vector of dataset's vectors.
Vector_of_points parsing(std::string);

// Compute distance between vectors. L=1 for manhattan, L=2 for euclidian.
double distance(std::vector<int> v1, std::vector<int> v2, int L);

// Compute the inner product between two vectors.
double inner_prod(std::vector<int> v1, std::vector<double> v2);
int inner_prod(std::vector<int> v1, std::vector<int> v2);
double inner_prod(std::vector<double> v1, std::vector<double> v2);
double inner_prod(std::vector<double> v1, std::vector<int> v2);

// Returns a random integer in the specified range.
int random_number(int begin, int end);

// Returns modulo of two numbers.
long int modulo(long int a, long long int b);


#endif