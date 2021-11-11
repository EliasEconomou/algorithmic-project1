#include "../include/cluster_methods.hpp"

using namespace std;

void calculate_centroids(Cluster_of_points &cluster){
    Point new_centroid;
    vector<Point> new_centroids;
    vector<double> sum_of_dimention;
    int centroid_count = cluster.centroids.size();
    
    //Set new centroids for cluster

    //FOR EVERY CLUSTER OF POINTS
    for (int i = 0 ; i < cluster.centroids.size() ; i++ ){
        //FOR EVERY POINT IN CLUSTER
        if ( cluster.points[i].points.size() > 0 ){
            for (int j = 0 ; j < cluster.points[i].points.size() ; j++){
                //FOR EVERY DIMENTION IN VECTOR
                for (int k = 0 ; k < cluster.points[i].points[j].vpoint.size() ; k++){
                    if ( j == 0 ){
                        new_centroid.vpoint.push_back(cluster.points[i].points[j].vpoint[k]);
                    }
                    else{
                        new_centroid.vpoint[k]+=cluster.points[i].points[j].vpoint[k];
                    }
                }
            }
            for (int k = 0 ; k < new_centroid.vpoint.size() ; k++){
                new_centroid.vpoint[k] = new_centroid.vpoint[k] / cluster.points[i].points.size(); 
                // std::cout << new_centroid.vpoint[k] << " ";
            }
            new_centroid.itemID=0;
            new_centroids.push_back(new_centroid);
            new_centroid.vpoint.clear();
        }
        else{
            for (int k = 0 ; k < cluster.centroids[i].vpoint.size() ; k++){
                new_centroid.vpoint.push_back(cluster.centroids[i].vpoint[k]);
            }
            new_centroid.itemID=cluster.centroids[i].itemID;
            new_centroids.push_back(new_centroid);
            new_centroid.vpoint.clear();
        }
        sum_of_dimention.clear();
    }
    cluster.centroids.swap(new_centroids);

   
}

Cluster_of_points initialize_kplusplus(Vector_of_points &Data, Cluster_of_points &cluster, int number_of_clusters){
    // ---Creating Kplusplus iteam with data structures to help---
    kplusplus_helper Kplusplus;

    // ---Getting a random point to be a centroid and adding it to centroid vector---
    Point Rand_centroid = Data.points[ random_number(1,Data.points.size()) ]; //Get random point to be the first centroid
    Kplusplus.Centroids.push_back(Rand_centroid);

    int t=1;


    // ---LOOP TO FIND NEW CENTROIDS---
    while (Kplusplus.Centroids.size() < number_of_clusters){
        //---Calculating all distances to centroids---
        bool wascentroid;
        vector<double> distances;
        for (int i=0 ; i < Data.points.size() ; i++){
            Point* CurrentPoint = &(Data.points[i]);
            wascentroid=false;
            for (int j=0 ; j < Kplusplus.Centroids.size() ; j++){
                if (Kplusplus.Centroids[j].itemID == CurrentPoint->itemID){ //if current is centroid dont
                    distances.push_back(0);
                    wascentroid=true;
                }
                else{
                    distances.push_back( distance( Kplusplus.Centroids[j].vpoint , CurrentPoint->vpoint , 2) );
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
        Kplusplus.Centroids.push_back(Data.points[next_centroid_index]);


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
    Vector_of_points current_cluster;
    for (int i=0 ; i < cluster.centroids.size() ; i++){
        cluster.points.push_back(current_cluster);
    }


    // ---FOR ITER_NUM ITERATION OF THE ALGORYTHM---
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
                if (cluster.centroids[j].itemID == Data.points[i].itemID){
                    is_centroid = true;
                    break;
                }

            }
            if (is_centroid)continue;

            // ---Creating clusters of points by assigning them to closest centroid---
            for (int j=0 ; j < cluster.centroids.size() ; j++){
                //Calculating distance between current point and current centroid
                dist = distance( Data.points[i].vpoint, cluster.centroids[j].vpoint , 2 );

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
            cluster.points[min_centroid_iterator].points.push_back(Data.points[i]);

        }


        std::cout << "Iteration #" << iter_num_input - iter_num+1 << " of Lloyd's algorythm." << endl;
        for (int i=0 ; i<cluster.centroids.size() ; i++){
            std::cout << "Cluster #" << i+1 << ": Centroid ID - " << cluster.centroids[i].itemID << ", Size - " << cluster.points[i].points.size() << endl;
        }

        iter_num--;

        // ---IF NOT OVER , CLEANING UP FOR NEXT ITEARATION---
        if (iter_num > 0){
            // ---ASSIGNING NEW CENTROIDS-- 
            calculate_centroids(cluster);

            //CLEANUP POINTS TO BE ABLE TO BE REASSIGNED
            for(int j=0 ; j < cluster.centroids.size() ; j++){
                cluster.points[j].points.clear();
            }
        }
    }

    return cluster;
}


Cluster_of_points cluster_Classic(Vector_of_points &Data, Cluster_of_points &cluster, int number_of_clusters){
    std::cout << "CLUSTER CLASSIC - LLOYD'S ALGORYTHM.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;

    //INITIALISE WITH K++
    cluster = initialize_kplusplus(Data, cluster, number_of_clusters);


    //CALCULATE LLOYDS ITERATIONS
    int iter_lloyd=0;
    int datasize = Data.points.size();
    while (datasize/2 > 1){
        datasize = datasize/2;
        iter_lloyd++;
    }

    // ---LLOYDS ALGORYTHM---
    cluster = lloyds(Data, cluster, iter_lloyd);

    // ---PRINT FINAL PRODUCT---
    std::cout << "---FINAL PRODUCT OF LLOYDS CLUSTERING---" << endl;
    for (int i=0 ; i<cluster.centroids.size() ; i++){
        std::cout << "Cluster #" << i+1 << ": Centroid ID - " << cluster.centroids[i].itemID << ", Size - " << cluster.points[i].points.size() << endl;
    }
    return cluster;
}

Cluster_of_points cluster_LSH(Vector_of_points Data, Cluster_of_points cluster, int number_of_clusters, int L_of_LSH, int k_of_LSH){
    std::cout << "CLUSTER LSH.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;
    std::cout << "L of LSH: " << L_of_LSH << endl;
    std::cout << "k of LSH: " << k_of_LSH << endl;

    cluster = initialize_kplusplus(Data, cluster, number_of_clusters);

    //DO STUFF
    //..
    

    return cluster;
}

Cluster_of_points cluster_Hypercube(Vector_of_points Data, Cluster_of_points cluster, int number_of_clusters, int M_of_Hypercube, int k_of_Hypercube){
    std::cout << "CLUSTER HYPERCUBE.\n";
    std::cout << "Number of clusters: " << number_of_clusters << endl;
    std::cout << "M of Hypercube: " << M_of_Hypercube << endl;
    std::cout << "k of Hypercube: " << k_of_Hypercube << endl;

    cluster = initialize_kplusplus(Data, cluster, number_of_clusters);

    //DO STUFF
    //..

    return cluster;
}
