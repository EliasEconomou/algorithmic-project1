
#include <iostream>
#include <algorithm>
#include <string>
#include <getopt.h>
#include <vector>
#include "../../include/point_functions.hpp"
#include "../../include/hash_table.hpp"
#include "../../include/hash_functions.hpp"
#include "../../include/algorithms.hpp"


using namespace std;


int main(int argc, char** argv) {
    
    //Default values:
    int k = 4; //number of 'h functions'
    int L = 5; //number of hash tables
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
    while ((option = getopt(argc, argv, "i:q:k:L:o:N:R:")) != -1)
    {
        switch (option)
        {
            case 'i':
            {
                inputFile = optarg;
                //cout << option << " " << inputFile << endl;
                break;
            }
            case 'q':
            {
                queryFile = optarg;
                //cout << option << " " << queryFile << endl;
                break;
            }
            case 'k':
            {
                k = stoi(optarg);
                //cout << option << " " << k << endl;
                break;
            }
            case 'L':
            {
                L = stoi(optarg);
                //cout << option << " " << L << endl;
                break;
            }
            case 'o':
            {
                outputFile = optarg;
                //cout << option << " " << outputFile << endl;
                break;
            }
            case 'N':
            {
                N = stoi(optarg);
                //cout << option << " " << N << endl;
                break;
            }
            case 'R':
            {
                R = stoi(optarg);
                //cout << option << " " << R << endl;
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

    // for (int i = 0; i < inputData.points.size(); i++) //print data
    // {
    //     cout << inputData.points[i].itemID << endl;
    //     for (int j = 0; j < inputData.points[0].vpoint.size(); j++)
    //     {
    //         cout << inputData.points[i].vpoint[j] << " ";
    //     }
    //     cout << endl;
    // }

    int vectorsNumber = inputData.points.size();
    int dimension = inputData.points[0].vpoint.size();
    int bucketsNumber = vectorsNumber/8;
    LSH_hash_info hInfo(k, dimension, L);

    vector<HashTable> hashTables;
    for (int i = 0; i < L; i++)
    {
        HashTable ht(bucketsNumber);
        hashTables.push_back(ht);
    }
    
    for (int i = 0; i < L; i++)
    {
        hashTables[i].v = compute_v(k,dimension);
        hashTables[i].t = compute_t(k);
        hashTables[i].r = compute_r(k);
        for (int j = 0; j < vectorsNumber; j++)
        {
            hashTables[i].HTinsert(&inputData.points[j], &hInfo);
        }
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


    Point lshResult = lsh_approximate_NN(queryData.points[0],hashTables, &hInfo);


    Point trueResult = true_NN(queryData.points[0], inputData);

    
    set<pair<Point,double>, CompDist> lshBestPointsDists;
    lshBestPointsDists = lsh_approximate_nNN(queryData.points[0], N, hashTables, &hInfo);
    cout << "LSH distances: " << endl;
    for (auto it = lshBestPointsDists.begin(); it != lshBestPointsDists.end(); ++it)
    {
        cout << it->first.itemID << " - " << it->second << endl;
    }
    

    set<pair<Point,double>, CompDist> trueBestPointsDists;
    trueBestPointsDists = true_nNN(queryData.points[0], N, inputData);
    cout << "TRUE distances: " << endl;
    for (auto it = trueBestPointsDists.begin(); it != trueBestPointsDists.end(); ++it)
    {
        cout << it->first.itemID << " - " << it->second << endl;
    }


    unordered_map<int,double> PointsInR = lsh_approximate_range_search(queryData.points[0], R, hashTables, &hInfo);
    //cout << "Points inside radius: " << R << "." << endl;
    // for (auto it = PointsInR.begin(); it != PointsInR.end(); ++it)
    // {
    //     cout << it->first << " ";
    // }
    // cout << endl;

    return 0;

    
}