
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <getopt.h>
#include <vector>
#include "../../include/functions.hpp"
#include "../../include/hash_table.hpp"


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

    vector<vector<double>> data = parsing_lsh(inputFile);
    cout << endl;
    for (int i = 0; i < data.size(); i++) {  //print dataset
        for (int j = 0; j < (data)[i].size(); j++)
            cout << (data)[i][j] << " ";
        cout << endl;
    }
    
    HashTable *ht = new HashTable(10);
    vector<double> v1 = {1 ,2, 3};
    vector<double> v2 = {4 ,5, 6};
    vector<double> v3 = {7 ,8, 9};
    ht->HTinsert(&v1);
    ht->HTinsert(&v2);
    ht->HTinsert(&v3);
    ht->HTdisplay();



    return 0;

    
}