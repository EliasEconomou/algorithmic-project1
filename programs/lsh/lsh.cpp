
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <getopt.h>
#include <vector>
#include "../../include/functions.hpp"


using namespace std;

//Function that returns vector of vectors, having data from the file at filepath "inputFile"
vector<vector<double>> parsing_lsh(string inputfile){
    //Creating the vector to be returned
    vector<vector<double>> vector_of_vectors;


    //Opening input file
    ifstream file;
    file.open(inputfile);
    if (file.is_open()==false){
        std::cout << "Error with given input file name - no file '" << inputfile << "' was found or there was an error opening the file.\n";
        exit(-1);
    }
    string line;

    //sizelim : a size keeping variable to help with keeping consistent amount of dimentions
    int sizelim = 0;

    //getting line by line
    while(std::getline(file, line)){

        //getting data from each line and creating vectors to store them
        istringstream line_stringstream(line);
        string word;
        vector<double> entry_vec;

        while(line_stringstream >> word){
            entry_vec.push_back(stod(word));
        }

        //Check if same size vectors are created
        if (sizelim==0){
            sizelim=entry_vec.size();
        }
        if (entry_vec.size()!=sizelim){
            cout << "Error with input file - inconsistent record size. \n";
            exit(-1);
        }

        //Add newly created vector to vector_of_vectors
        vector_of_vectors.push_back(entry_vec);
    }

    return vector_of_vectors;
}


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
    cout << endl << endl;
    for (int i = 0; i < data.size(); i++) {  //print dataset
    // cout << "Entry #" << data[i][0] << ": " ;
        for (int j = 0; j < (data)[i].size(); j++)
            cout << (data)[i][j] << " ";
        cout << endl;
    }

    return 0;
    
    
    
}