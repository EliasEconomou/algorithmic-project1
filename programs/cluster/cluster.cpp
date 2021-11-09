#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include "../../include/point_functions.hpp"


using namespace std;

Cluster_of_points cluster_default(Vector_of_points Data, Cluster_of_points cluster, int number_of_clusters){
    //DO STUFF
    std::cout << "CLUSTER DEFAULT.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;
    return cluster;
}

Cluster_of_points cluster_LSH(Vector_of_points Data, Cluster_of_points cluster, int number_of_clusters, int L_of_LSH, int k_of_LSH){
    //DO STUFF
    std::cout << "CLUSTER LSH.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;
    std::cout << "L of LSH: " << L_of_LSH << endl;
    std::cout << "k of LSH: " << k_of_LSH << endl;
    return cluster;
}

Cluster_of_points cluster_Hypercube(Vector_of_points Data, Cluster_of_points cluster, int number_of_clusters, int M_of_Hypercube, int k_of_Hypercube){
    //DO STUFF
    std::cout << "CLUSTER HYPERCUBE.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;
    std::cout << "M of Hypercube: " << M_of_Hypercube << endl;
    std::cout << "k of Hypercube: " << k_of_Hypercube << endl;
    return cluster;
}

Cluster_of_points cluster_data(Vector_of_points data , string method , string config_file , bool complete){
    Cluster_of_points cluster;

    //---First check method---
    int method_int = 0;

    if ( strcmp(method.c_str(),"Classic")==0 ){
        method_int=1;
    }
    else if ( strcmp(method.c_str(),"LSH")==0 ){
        method_int=2;
    }
    else if( strcmp(method.c_str(),"Hypercube")==0 ){
        method_int=3;
    }
    else{
        std::cout << "Error in method chosen. \n";
        return cluster;
    }
    

    //---Then check config parameters---
    std::ifstream configfile(config_file);
    int kmedians = 0;
    int Lfactor = 4;
    int k_of_LSH = 4;
    int M_of_hypercube = 10;
    int k_of_hypercube = 3;
    int probes_of_hypercube = 2;

    if (configfile.is_open())
    {
        std::string line;
        while(getline(configfile, line))
       {
            auto delimiter_position = line.find(":");
            auto name = line.substr(0, delimiter_position);
            auto value = line.substr(delimiter_position+1);
            if ( strcmp(name.c_str(),"number_of_clusters")==0 ){
                kmedians = atoi(value.c_str());
            }
            else if( strcmp(name.c_str(),"number_of_vector_hash_tables")==0 ){
                Lfactor = atoi(value.c_str());
            }
            else if( strcmp(name.c_str(),"number_of_vector_hash_functions")==0 ){
                k_of_LSH = atoi(value.c_str());
            }
            else if( strcmp(name.c_str(),"max_number_M_hypercube")==0 ){
                M_of_hypercube = atoi(value.c_str());
            }
            else if( strcmp(name.c_str(),"number_of_hypercube_dimensions")==0 ){
                k_of_hypercube = atoi(value.c_str());
            }
            else if( strcmp(name.c_str(),"number_of_probes")==0 ){
                probes_of_hypercube = atoi(value.c_str());
            }
        }
    }
    else 
    {
        std::cerr << "Couldn't open config file for reading.\n";
    }
    if ( kmedians==0 ){
        std::cout << "No number_of_clusters given. \n";
        return cluster;
    }

    //Send data to correct cluster function
    switch(method_int){
        case 1:
            cluster = cluster_default(data, cluster, kmedians);
            break;
        case 2:
            cluster = cluster_LSH(data, cluster, kmedians , Lfactor, k_of_LSH);
            break;
        case 3:
            cluster = cluster_Hypercube(data, cluster, kmedians, M_of_hypercube, k_of_hypercube);
    }

    //Return said data
    return cluster;
}


int main(int argc, char** argv) {

    string input_file, config_file, output_file, method;
    string word;
    bool complete = false;

    //---Parse arguments---
    for (int i = 1; i < argc; i++){
        word  = argv[i];
        if(word == "-i"){
            if(i+1 < argc){
                input_file = argv[++i];
            }else{
                std::cout << "No argument for input file. \n";
                return -1;
            }
        }
        else if (word == "-c"){
            if(i+1 <= argc){
                config_file = argv[++i];
            }else{
                std::cout << "No argument for configuration file. \n";
                return -1;
            }
        }
        else if(word == "-o"){
            if(i+1 <= argc){
                output_file = argv[++i];
            }else{
                std::cout << "No argument for output file. \n";
                return -1;
            }
        }
        else if(word == "-m"){
            if(i+1 <= argc){
                method = argv[++i];
            }else{
                std::cout << "No argument for method to use. \n";
                return -1;
            }
        }
        else if(word == "-complete"){
            complete = true;
        }
        else{
            std::cout << "Unknown error in arguments. \n";
            return -1;
        }
    }

    Vector_of_points Data = parsing(input_file);

    // ---Check if arguments are ok---
    //..

    // ---Cluster the data---
    Cluster_of_points Cluster = cluster_data(Data, method , config_file , complete);

    // ---Print desired results to output file---
    //..


    std::cout << "I RAN! \n";
    
    //  ---DATABASE PRINT---
    // for (int i=0 ; i < Data.points.size() ; i++){
    //     cout << "POINT #" << Data.points[i].itemID << endl;
    //     for ( int j=0 ; j < Data.points[i].vpoint.size() ; j++ ) {
    //         cout << Data.points[i].vpoint[j] << " " ;
    //     }
    //     cout << endl;
    // }
    







}