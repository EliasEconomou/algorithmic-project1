using namespace std;

#include "../include/functions.hpp"

void hello() {
    cout << "Hello cpp" << endl; 
}

void goodbye(int n) {
    for( int i = 0; i < n; ++i )
    cout << "Goodbye" << endl;
}


vector<vector<double>> parsing_lsh(void) {
    // Allocate the vector of dataset's vectors.
    vector<vector<double>> vec;

    string inputFile = "../../dataset.txt";
    
    ifstream file; 
    file.open(inputFile); 
    string line, token;
    while(getline(file, line, '\n'))
    {
        vector<double> row;
        stringstream ss1(line);
        //cout << line << endl;
        getline(ss1, token,' '); //avoid index
        while (getline(ss1, token,' ')) { //todo tab?????????????????????????????
            stringstream ss2(token);
            double num;
            ss2 >> num;
            row.push_back(num);
        } 
        vec.push_back(row);
    }
    
    return vec;
}