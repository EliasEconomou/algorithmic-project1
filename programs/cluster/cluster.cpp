#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include <ctime>
#include "unistd.h"
#include "../../include/cluster_methods.hpp"



using namespace std;

Cluster_of_points cluster_data(Vector_of_points &data , string method , string config_file){
    Cluster_of_points cluster;

    //---CHECK METHOD---
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
    

    //---CHECK CONFIG PARAMETERS---
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

    //SEND DATA TO CORRECT CLUSTER FUNCTION
    switch(method_int){
        case 1:
            cluster = cluster_Classic(data, cluster, kmedians);
            break;
        case 2:
            cluster = cluster_LSH(data, cluster, kmedians , Lfactor, k_of_LSH);
            break;
        case 3:
            cluster = cluster_Hypercube(data, cluster, kmedians, M_of_hypercube, k_of_hypercube);
            break;
    }

    //RETURN DATA
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


    // ---CLUSTER DATA---
    clock_t begin = clock();
    Cluster_of_points Cluster = cluster_data(Data, method , config_file);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


    std::cout << "Operation Successfull. \n";

    // ---PRINT RESULTS TO OUTPUT FILE---
    string method_name;
    if (method=="Classic")method_name="Lloyds";
    else if(method=="LSH")method_name="Range search LSH";
    else if(method=="Hypercube")method_name="Range search Hypercube";
    
    ofstream out_file;
    out_file.open (output_file);
    out_file << "Algorithm: " << method_name << endl;
    for (int i = 0; i < Cluster.centroids.size(); i++)
    {
        out_file << "CLUSTER-" << i+1 << " {size: " << Cluster.points[i].points.size() << ", centroid: [";
        for (int j = 0; j < Cluster.centroids[i].vpoint.size(); j++)
        {
            if (j==0)out_file << Cluster.centroids[i].vpoint[j];
            else out_file << ", " << Cluster.centroids[i].vpoint[j];
        }
        out_file << "] }" << endl;
    }
    out_file << "clustering_time: " << elapsed_secs << " seconds." << endl;
    out_file << "Silhuette: [";
    double sum_of_sps;
    for (int i = 0; i < Cluster.centroids.size(); i++)
    {
        double cur_sil = silhuette(Cluster, i);
        if (i==0)out_file << cur_sil;
        else out_file << ", " << cur_sil;
        sum_of_sps += cur_sil;
    }
    out_file << ", " << sum_of_sps / Cluster.centroids.size() << "]";
    out_file << endl;
    


    if(complete){
        // out_file << "Complete option additional data:" << endl;
        for (int i = 0; i < Cluster.centroids.size(); i++)
        {
            out_file << "CLUSTER-" << i+1 << " {";
            out_file << Cluster.centroids[i].itemID;
            for (int j = 0; j < Cluster.points[i].points.size() ; j++)
            {
                out_file <<  ", " << Cluster.points[i].points[j].itemID;
            }
            out_file << "}" << endl;
        }
    }

    out_file.close();
    return 0;
}