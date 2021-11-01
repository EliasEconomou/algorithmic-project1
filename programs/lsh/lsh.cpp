
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <getopt.h>
#include <vector>
#include "../../include/functions.hpp"
#include "../../include/hash_table.hpp"
#include "../../include/hash_functions.hpp"
#include "../../include/algorithms.hpp"


using namespace std;


int main(int argc, char** argv) {
    
    //Default values:
    int k = 4; //number of 'h functions'
    int L = 5; //number of hash tables
    int N = 1; //number of nearest neighbors
    float R = 10000; //search radius
    string inputFile,queryFile,outputFile;

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
                R = stoi(optarg);
                //cout << option << " " << R << endl;
                break;
            case '?':
                cout << "Error in arguments" << endl;

        }
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
    int bucketsNumber = vectorsNumber/4;
    hash_info hInfo(k, dimension, L);

    vector<HashTable> hashTables;
    for (int i = 0; i < L; i++)
    {
        HashTable ht(bucketsNumber);
        hashTables.push_back(ht);
    }
    
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < vectorsNumber; j++)
        {
            hashTables[i].HTinsert(&inputData.points[j], &hInfo);
        }
        hInfo.update_v();
        hInfo.update_t();
        hInfo.update_r();
    }
    
    //hashTables[0].HTdisplay();


    Vector_of_points queryData;
    queryData = parsing(queryFile);

    // for (int i = 0; i < queryData.points.size(); i++) //print data
    // {
    //     cout << queryData.points[i].itemID << endl;
    //     for (int j = 0; j < queryData.points[0].vpoint.size(); j++)
    //     {
    //         cout << queryData.points[i].vpoint[j] << " ";
    //     }
    //     cout << endl;
    // }

    Point result = approximate_NN(queryData.points[0],hashTables, &hInfo);

    
    return 0;

    
}