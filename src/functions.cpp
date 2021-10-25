using namespace std;

#include "../include/functions.hpp"

void hello() {
    cout << "Hello cpp" << endl; 
}

void goodbye(int n) {
    for( int i = 0; i < n; ++i )
    cout << "Goodbye" << endl;
}


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