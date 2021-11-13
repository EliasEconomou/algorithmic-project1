
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


    pair<Point,double> lshResult = lsh_approximate_NN(queryData.points[0],hashTables, &hInfo);
    pair<Point,double> trueResult = true_NN(queryData.points[0], inputData);


    ofstream out (outputFile);

    std::cout << "Writing to output file..." << endl;
    for (int i = 0; i < queryData.points.size(); i++)
    {
        out << "Query: " << queryData.points[i].itemID << endl;
        double lshTime, trueTime;
        set<pair<Point,double>, CompDist> lshBestPointsDists;
        set<pair<Point,double>, CompDist> trueBestPointsDists;
        lshBestPointsDists = lsh_approximate_nNN(queryData.points[i], N, hashTables, &hInfo, lshTime);
        trueBestPointsDists = true_nNN(queryData.points[i], N, inputData, trueTime);
        int neighbor = 1;
        auto it1 = lshBestPointsDists.begin();
        auto it2 = trueBestPointsDists.begin();
        for (it1,it2; it1 != lshBestPointsDists.end(),it2 != trueBestPointsDists.end(); ++it1,++it2)
        {
            out << "Nearest neighbor-" << neighbor << ": " << it1->first.itemID << endl;
            out << "distanceLSH: " << it1->second << endl;
            out << "distanceTrue: " << it2->second << endl;
            neighbor++;
        }
        out << "tLSH: " << lshTime << endl;
        out << "tTrue: " << trueTime << endl;
        unordered_map<int,double> PointsInR = lsh_approximate_range_search(queryData.points[i], R, hashTables, &hInfo);
        out << "R-near neighbors:" << endl;
        for (auto it = PointsInR.begin(); it != PointsInR.end(); ++it)
        {
            out << it->first << endl;
        }
    }
    out << endl;
    out.close();

    std::cout << "Operation completed successfully." << endl << "Exiting." << endl;

    return 0;

    
}