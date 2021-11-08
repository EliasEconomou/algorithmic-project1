#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "../../include/point_functions.hpp"


using namespace std;

void cluster_data(Vector_of_points data,string method, bool complete){
    return;
}


int main(int argc, char** argv) {


// kalytera na kaneis parse ta arguments ths main me allon tropo ap oti exw kanei sta lsh/cube, giati edw exei kai to 'complete' pou 
// einai optional argument

    string input_file, config_file, output_file, method;
    string word;
    bool complete = false;


    for (int i = 1; i < argc; i++){
        word  = argv[i];
        if(word == "-i"){
            if(i+1 < argc){
                input_file = argv[++i];
            }else{
                cout << "No argument for input file. \n";
                return -1;
            }
        }
        else if (word == "-c"){
            if(i+1 <= argc){
                config_file = argv[++i];
            }else{
                cout << "No argument for configuration file. \n";
                return -1;
            }
        }
        else if(word == "-o"){
            if(i+1 <= argc){
                output_file = argv[++i];
            }else{
                cout << "No argument for output file. \n";
                return -1;
            }
        }
        else if(word == "-m"){
            if(i+1 <= argc){
                method = argv[++i];
            }else{
                cout << "No argument for method to use. \n";
                return -1;
            }
        }
        else if(word == "-complete"){
            complete = true;
        }
        else{
            cout << "Unknown error occured. \n";
            return -1;
        }
    }

    Vector_of_points Data = parsing(input_file);

    // if all on input is well then..
    cluster_data(Data, method , complete);
    cout << "I RAN! \n";
    
    // for (int i=0 ; i < Data.points.size() ; i++){
    //     cout << "POINT #" << Data.points[i].itemID << endl;
    //     for ( int j=0 ; j < Data.points[i].vpoint.size() ; j++ ) {
    //         cout << Data.points[i].vpoint[j] << " " ;
    //     }
    //     cout << endl;
    // }
    







}