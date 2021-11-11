#include <iostream>
#include <algorithm>
#include <string>
#include <getopt.h>
#include <vector>
#include "../../include/point_functions.hpp"
#include "../../include/cube_table.hpp"
#include "../../include/hash_functions.hpp"
#include "../../include/algorithms.hpp"

#define MAX_HAMMING_DIST 5 //maximum hamming distance to use when searching neighbor-vertices

using namespace std;


static struct option long_options[] = {
    {"probes", required_argument,  0,  'p' },
    {0,    0,            0,  0 }
};

int main(int argc, char** argv) {
    
    //Default values:
    int k = 14; //(=d') dimension to project points
    int M = 10; //maximum number of candidate-points to check
    int probes = 2; //maximum number of hypercube's vertices to check 
    int N = 1; //number of nearest neighbors
    double R = 10000; //search radius
    string inputFile = "0",queryFile = "0",outputFile = "0";

    //Check the "-" option of arguments.
    for (int i = 1; i < argc; i+=2)
    {
        if (argv[i][0]!='-')
        {
            cout << "Error in arguments. Exiting." << endl;
        }
    }

    //Get argument values.
    char option;
    while ((option = getopt_long_only(argc, argv, "i:q:k:M:p:o:N:R:", long_options, NULL)) != -1)
    {
        switch (option)
        {
            case 'i':
            {
                inputFile = optarg;
                cout << option << " " << inputFile << endl;
                break;
            }
            case 'q':
            {
                queryFile = optarg;
                cout << option << " " << queryFile << endl;
                break;
            }
            case 'k':
            {
                k = stoi(optarg);
                cout << option << " " << k << endl;
                break;
            }
            case 'M':
            {
                M = stoi(optarg);
                cout << option << " " << M << endl;
                break;
            }
            case 'p':
            {
                probes = stoi(optarg);
                cout << option << " " << probes << endl;
                break;
            }
            case 'o':
            {
                outputFile = optarg;
                cout << option << " " << outputFile << endl;
                break;
            }
            case 'N':
            {
                N = stoi(optarg);
                cout << option << " " << N << endl;
                break;
            }
            case 'R':
            {
                R = stoi(optarg);
                cout << option << " " << R << endl;
                break;
            }
            case '?':
            {
                cout << "Error in arguments" << endl;
                return -1;
            }
        }
    }

    if (inputFile == "0")
    {
        cout << "Give path to input file: ";
        cin >> inputFile;
    }
    

    Vector_of_points inputData;
    inputData = parsing(inputFile);
    
    int vectorsNumber = inputData.points.size();
    int dimension = inputData.points[0].vpoint.size();
    int bucketsNumber = pow(2,k);
    CUBE_hash_info hInfo(k, dimension, M, probes, MAX_HAMMING_DIST);

    CubeTable cubeTable(bucketsNumber);
    cubeTable.v = compute_v(k,dimension);
    cubeTable.t = compute_t(k);
    for (int i = 0; i < vectorsNumber; i++)
    {
        cubeTable.CTinsert(&inputData.points[i], &hInfo);
    }

    if (queryFile == "0")
    {
        cout << "Give path to query file: ";
        cin >> queryFile;
    }

    if (outputFile == "0")
    {
        cout << "Give path to output file: ";
        cin >> outputFile;
    }
    
    Vector_of_points queryData;
    queryData = parsing(queryFile);


    // pair<Point,double> cubeResult = cube_approximate_NN(queryData.points[0],cubeTable, &hInfo);
    // pair<Point,double> trueResult = true_NN(queryData.points[0], inputData);
    

    ofstream out (outputFile);


    for (int i = 0; i < queryData.points.size(); i++)
    {
        out << "Query: " << queryData.points[i].itemID << endl;
        double cubeTime, trueTime;
        set<pair<Point,double>, CompDist> cubeBestPointsDists;
        set<pair<Point,double>, CompDist> trueBestPointsDists;
        cubeBestPointsDists = cube_approximate_nNN(queryData.points[i], N, cubeTable, &hInfo, cubeTime);
        trueBestPointsDists = true_nNN(queryData.points[i], N, inputData, trueTime);
        int neighbor = 1;
        auto it1 = cubeBestPointsDists.begin();
        auto it2 = trueBestPointsDists.begin();
        for (it1,it2; it1 != cubeBestPointsDists.end(),it2 != trueBestPointsDists.end(); ++it1,++it2)
        {
            out << "Nearest neighbor-" << neighbor << ": " << it1->first.itemID << endl;
            out << "distanceHypercube: " << it1->second << endl;
            out << "distanceTrue: " << it2->second << endl;
            neighbor++;
        }
        out << "tHypercube: " << cubeTime << endl;
        out << "tTrue: " << trueTime << endl;
    }
    cout << endl;


    // unordered_map<int,double> PointsInR = cube_approximate_range_search(queryData.points[0], R, cubeTable, &hInfo);
    // cout << "Points inside radius: " << R << "." << endl;
    // for (auto it = PointsInR.begin(); it != PointsInR.end(); ++it)
    // {
    //     cout << it->first << " - " << it->second << endl;
    // }
    // cout << endl << endl;


    out.close();

    return 0;

}