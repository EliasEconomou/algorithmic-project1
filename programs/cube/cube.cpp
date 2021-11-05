#include <iostream>
#include <algorithm>
#include <string>
#include <getopt.h>
#include <vector>
#include "../../include/point_functions.hpp"
// #include "../../include/hash_table.hpp"
// #include "../../include/hash_functions.hpp"
// #include "../../include/algorithms.hpp"


using namespace std;


// static struct option long_options[] =
// {
//     {"title", required_argument, NULL, 'b'},
//     {"artist", required_argument, NULL, 'j'},
//     {NULL, 0, NULL, 0}
// };


static struct option long_options[] = {
    {"probes", required_argument,  0,  '1' },
    {"bb", required_argument,  0,  '2' },
    {0,    0,            0,  0 }
};

int main(int argc, char** argv) {
    
    //Default values:
    int k = 14; //(=d') dimension to project points
    int M = 10; //maximum number of candidate-points to check
    int probes = 2; //maximum number of hypercube's vertices to check 
    int N = 1; //number of nearest neighbors
    double R = 10000; //search radius
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
    while ((option = getopt(argc, argv, "i:q:k:M:p:o:N:R:")) != -1)
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
                cout << "Error in arguments" << endl;

        }
    }







}