#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include "../../include/point_functions.hpp"


using namespace std;

class kplusplus_helper{
    public:
    vector<double> Additive_Square_Sums;
    vector<vector<double>> Dist_From_Centroids;
    vector<float> Minimum_Distances;
    vector<PPoint> Centroids;
    vector<bool> IsCentroid;
};

double random_double(double n1, double n2){
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(n1, n2);
    return dis(gen);
}

Cluster_of_points calculate_centroids(Cluster_of_points &cluster){
    PPoint new_centroid = new Point ;
    double sum_of_dimention=0;
    int centroid_count = cluster.centroids.size();
    
    //Set new centroids for cluster
    //..
   

    return cluster;
}

Cluster_of_points initialize_kplusplus(Vector_of_points &Data, Cluster_of_points &cluster, int number_of_clusters){
    // ---Creating Kplusplus iteam with data structures to help---
    kplusplus_helper Kplusplus;

    // ---Getting a random point to be a centroid and adding it to centroid vector---
    PPoint Rand_centroid = &Data.points[ random_number(1,Data.points.size()) ]; //Get random point to be the first centroid
    Kplusplus.Centroids.push_back(Rand_centroid.ppoint);

    int t=1;


    // ---LOOP TO FIND NEW CENTROIDS---
    while (Kplusplus.Centroids.size() < number_of_clusters){
        //---Calculating all distances to centroids---
        bool wascentroid;
        vector<double> distances;
        for (int i=0 ; i < Data.points.size() ; i++){
            PPoint CurrentPoint = &(Data.points[i]);
            wascentroid=false;
            for (int j=0 ; j < Kplusplus.Centroids.size() ; j++){
                if (Kplusplus.Centroids[j].ppoint->itemID == CurrentPoint.ppoint->itemID){ //if current is centroid dont
                    distances.push_back(0);
                    wascentroid=true;
                }
                else{
                    distances.push_back( distance( (Kplusplus.Centroids[j].ppoint)->vpoint , (CurrentPoint.ppoint)->vpoint , 2) );
                }
            }
            if(wascentroid){
                Kplusplus.IsCentroid.push_back(true);
            }
            else{
                Kplusplus.IsCentroid.push_back(false);
            }
            Kplusplus.Dist_From_Centroids.push_back(distances);
            distances.clear();
        }

        // ---Calculating minimum distances---
        for (int i=0 ; i < Data.points.size() ; i++){
            double min_dist = MAXFLOAT;
            for (int j=0 ; j < Kplusplus.Centroids.size() ; j++){
                if (Kplusplus.Dist_From_Centroids[i][j] < min_dist){
                    min_dist = Kplusplus.Dist_From_Centroids[i][j];
                }
            }
            // ---Saving minimum distances---
            Kplusplus.Minimum_Distances.push_back(min_dist);
        }

        // ---Calculating max D(i) to normalize---
        float max_di = 0;
        for (int i=0 ; i < Data.points.size() ; i++){
            if (Kplusplus.Minimum_Distances[i] > max_di){
                max_di = Kplusplus.Minimum_Distances[i];
            }
        }
        // ---Normalising and calculating cumulative sum of squares---
        for (int i=0 ; i < Data.points.size() ; i++){
            //Normalising
            float norm_distance = Kplusplus.Minimum_Distances[i] / max_di ;

            //Calculate sqare of normalised distance
            float norm_dist_squared = norm_distance * norm_distance;

            //Adding to vector of cumulative sums
            if (i==0){
                Kplusplus.Additive_Square_Sums.push_back(norm_dist_squared);
            }
            else{
                Kplusplus.Additive_Square_Sums.push_back(norm_dist_squared + Kplusplus.Additive_Square_Sums[i-1]);
            }
            // std::cout << Additive_Square_Sums[i] << endl;
        }

        // ---Calculating the probabilities to be centroids---
        double uniform_rand_possibility=0;
        
        uniform_rand_possibility = random_double(0.0 , Kplusplus.Additive_Square_Sums[Kplusplus.Additive_Square_Sums.size()-1]);

        
        // std::cout << "Random possibility number chosen:" << uniform_rand_possibility << endl; //PRINT RANDOM NUMBER CHOSEN

        // ---Searching for next centroid according to random number taken---
        int next_centroid_index;
        for (int i=0 ; i < Data.points.size() ; i++){
            if ( (Kplusplus.Additive_Square_Sums[i] >= uniform_rand_possibility) && (Kplusplus.IsCentroid[i]==false) ){
                next_centroid_index = i;
                break;
            }
        }

        // ---Making it a centroid---
        
        Kplusplus.IsCentroid[next_centroid_index]=true;
        Kplusplus.Centroids.push_back(&Data.points[next_centroid_index]);


        //Clearing for next loop
        Kplusplus.Minimum_Distances.clear();
        Kplusplus.Dist_From_Centroids.clear();
        Kplusplus.Additive_Square_Sums.clear();
        Kplusplus.IsCentroid.clear();
        t++;
    }   

    //Αssign centroids found to cluster and return
    for (int i=0 ; i < Kplusplus.Centroids.size() ; i++){
        cluster.centroids.push_back( Kplusplus.Centroids[i] );
    }
    return cluster;
}

Cluster_of_points lloyds(Vector_of_points &Data, Cluster_of_points &cluster, int iter_num_input){
    int iter_num = iter_num_input;

    // ---Manually preallocating the vectors to load iteams without problems---
    Vector_of_ppoints current_cluster;
    for (int i=0 ; i < cluster.centroids.size() ; i++){
        cluster.points.push_back(current_cluster);
    }


    while (iter_num > 0){
        // ---ASSIGN EACH POINT TO A CENTROID---
        int min_centroid_iterator;
        double min_centroid_distance;
        double dist;
        bool is_centroid;

        // ---ITERATING THROUGH POINTS---
        for (int i=0 ; i < Data.points.size() ; i++){

            //---Checking if point is centroid, if so ignoring it---
            is_centroid = false;
            for (int j=0 ; j < cluster.centroids.size() ; j++){
                if (cluster.centroids[j].ppoint->itemID == Data.points[i].itemID){
                    is_centroid = true;
                    break;
                }
            }
            if (is_centroid)continue;

            // ---Creating clusters of points by assigning them to closest centroid---
            for (int j=0 ; j < cluster.centroids.size() ; j++){
                //Calculating distance between current point and current centroid
                dist = distance( Data.points[i].vpoint, cluster.centroids[j].ppoint->vpoint , 2 );

                if (j==0){
                    min_centroid_iterator = 0;
                    min_centroid_distance = dist;
                }
                else{
                    if (dist < min_centroid_distance){
                        min_centroid_distance = dist;
                        min_centroid_iterator = j;
                    }
                }
            }
            cluster.points[min_centroid_iterator].ppoints.push_back(PPoint(&Data.points[i]));

        }
        // ---ASSIGNING NEW CENTROIDS-- 
        cluster = calculate_centroids(cluster);


        std::cout << "Iteration #" << iter_num_input - iter_num+1 << " of Lloyd's algorythm complete." << endl;
        for (int i=0 ; i<cluster.centroids.size() ; i++){
            std::cout << "Cluster #" << i+1 << ": Centroid ID - " << cluster.centroids[i].ppoint->itemID << ", Size - " << cluster.points[i].ppoints.size() << endl;
        }

        iter_num--;

        // ---IF NOT OVER , CLEANING UP FOR NEXT ITEARATION---
        if (iter_num > 0){
            for(int j=0 ; j < cluster.centroids.size() ; j++){
                cluster.points[j].ppoints.clear();
            }
        }
    }

    return cluster;
}

Cluster_of_points cluster_default(Vector_of_points &Data, Cluster_of_points &cluster, int number_of_clusters){
    std::cout << "CLUSTER CLASSIC - LLOYD'S ALGORYTHM.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;

    //INITIALISE WITH K++
    cluster = initialize_kplusplus(Data, cluster, number_of_clusters);

    // //PRINT CENTROIDS
    // for (int j = 0; j < cluster.centroids.size(); j++)
    // {
    //     std::cout << cluster.centroids[j].ppoint->itemID << endl;
    // }


    // ---LLOYDS ALGORYTHM---
    cluster = lloyds(Data, cluster, 2);

    // for (int i=0 ; i<cluster.centroids.size() ; i++){
    //     std::cout << "Cluster #" << i+1 << ": Centroid ID - " << cluster.centroids[i].ppoint->itemID << ", Size - " << cluster.points[i].ppoints.size() << endl;
    // }
    

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

Cluster_of_points cluster_data(Vector_of_points &data , string method , string config_file , bool complete){
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


    std::cout << "Operation Successfull. \n";
    
    //  ---DATABASE PRINT---
    // for (int i=0 ; i < Data.points.size() ; i++){
    //     cout << "POINT #" << Data.points[i].itemID << endl;
    //     for ( int j=0 ; j < Data.points[i].vpoint.size() ; j++ ) {
    //         cout << Data.points[i].vpoint[j] << " " ;
    //     }
    //     cout << endl;
    // }
    







}