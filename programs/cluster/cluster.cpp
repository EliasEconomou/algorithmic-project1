#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "../../include/point_functions.hpp"


using namespace std;

Cluster_of_points cluster_data(Vector_of_points data , string method , string config_file , bool complete){
    Cluster_of_points cluster;

    //First check method
    //..

    //Then check config parameters
    //..

    //Then check if complete
    //..

    //Send data to correct cluster function
    //..

    //Return said data
    return cluster;
}


int main(int argc, char** argv) {

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
            cout << "Unknown error in arguments. \n";
            return -1;
        }
    }

    Vector_of_points Data = parsing(input_file);

    // if all on input is well then.. TODO CHECK

    Cluster_of_points Cluster  = cluster_data(Data, method , config_file , complete);
    cout << "I RAN! \n";
    
    //  ---DATABASE PRINT---
    // for (int i=0 ; i < Data.points.size() ; i++){
    //     cout << "POINT #" << Data.points[i].itemID << endl;
    //     for ( int j=0 ; j < Data.points[i].vpoint.size() ; j++ ) {
    //         cout << Data.points[i].vpoint[j] << " " ;
    //     }
    //     cout << endl;
    // }
    







}