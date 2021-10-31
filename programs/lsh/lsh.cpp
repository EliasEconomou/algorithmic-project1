
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

    Vector_of_points data;

    data = parsing(inputFile);
    cout << data.points.size() << endl;

    // for (int i = 0; i < data.points.size(); i++) //print data
    // {
    //     cout << data.points[i].itemID << "  ";
    //     for (int j = 0; j < data.points[0].vpoint.size(); j++)
    //     {
    //         cout << data.points[i].vpoint[j] << " ";
    //     }
    //     cout << endl;
    // }

    int vectorsNumber = data.points.size();
    int dimension = data.points[0].vpoint.size();
    hash_info hInfo(k, dimension);

    vector<HashTable> hashTables;
    for (int i = 0; i < L; i++)
    {
        HashTable ht((vectorsNumber/4)+1);
        hashTables.push_back(ht);
    }
    
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < vectorsNumber; j++)
        {
            hashTables[i].HTinsert(&data.points[j], &hInfo);
        }
        hInfo.update_v();
        hInfo.update_t();
    }
    
    hashTables[0].HTdisplay();



    
    return 0;

    
}