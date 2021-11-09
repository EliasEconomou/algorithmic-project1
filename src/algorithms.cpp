#include "../include/algorithms.hpp"

using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRUE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Point true_NN(Point q, Vector_of_points inputData)
{
    Point b; //best true point/candidate
    double bestDist = DBL_MAX; // best true distance of best candidate
    
    for (int i = 0; i < inputData.points.size(); i++)
    {
        double dist = distance(q.vpoint,inputData.points[i].vpoint, 2);
        if (dist < bestDist)
        {
            bestDist = dist;
            b = inputData.points[i];
        }
        
    }
    cout << "Query index " << q.itemID << " - BEST TRUE DISTANCE : " << bestDist << endl;
    return b;
}


set<pair<Point,double>, CompDist> true_nNN(Point q, int N, Vector_of_points inputData)
{
    // Initialise a set two hold pairs of true best point/best distance.
    set<pair<Point,double>, CompDist> bestPointsDists;
    Point a;
    bestPointsDists.insert(make_pair(a,DBL_MAX));
    
    for (int i = 0; i < inputData.points.size(); i++)
    {
        double dist = distance(q.vpoint,inputData.points[i].vpoint, 2);
        if (bestPointsDists.size()==N) //if set is full
        {
            //if the biggest distance in set is equal/greater than current distance
            if (prev(bestPointsDists.end())->second >= dist)
            {
                bestPointsDists.erase(prev(bestPointsDists.end())); //pop biggest distance pair
                bestPointsDists.insert(make_pair(inputData.points[i],dist)); //insert new point/distance
            }
        }
        else if (bestPointsDists.size()<N) //if there is space in set insert pair
        {
            bestPointsDists.insert(make_pair(inputData.points[i],dist));
        }
    }
    return bestPointsDists;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LSH //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Point lsh_approximate_NN(Point q, vector<HashTable> hashTables, LSH_hash_info *hInfo)
{
    Point b; // best point-candidate
    double bestDist = INT_MAX; // best distance of best candidate
    int L = hInfo->get_L();
    for (int i = 0; i < L; i++) {
        // Update hinfo with the right vectors for every hash table, to compute query's g-value
        hInfo->update_v(hashTables[i].v);
        hInfo->update_t(hashTables[i].t);
        hInfo->update_r(hashTables[i].r);
        // Find g value for query point.
        vector<int> hValues;
        int k = hInfo->get_k();
        vector<int> vp = q.vpoint;
        for (int j = 0; j < k; j++)
        {
            hValues.push_back(compute_hValue(j, vp, hInfo));
            
        }
        long int ID = compute_IDvalue(hValues, hInfo);
        // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << b.itemID << " ID = " << ID << endl;
        int g = compute_gValue(ID, hashTables[i].get_bucketsNumber());
        list<HashNode> listToSearch = hashTables[i].get_bucketList(g);
        typename list<HashNode>::iterator current;
        for (current = listToSearch.begin() ; current != listToSearch.end() ; ++current ) {
            // cout << current->point->itemID << ":" << current->ID << endl << endl;
            double dist = distance(q.vpoint,current->point->vpoint, 2);
            if (dist < bestDist)
            {
                bestDist = dist;
                b = *(current->point);
            }

            
            // for (auto j = current->point->vpoint.begin() ; j != current->point->vpoint.end() ; ++j){
            //     cout << *j << " ";
            // }
            // cout << endl;
        }
    }
    cout << "Query index " << q.itemID << " - BEST LSH DISTANCE : " << bestDist << endl;
    return b;
    
}


set<pair<Point,double>, CompDist> lsh_approximate_nNN(Point q, int N, vector<HashTable> hashTables, LSH_hash_info *hInfo)
{
    // Initialise a set two hold pairs of best point/best distance.
    set<pair<Point,double>, CompDist> bestPointsDists;
    Point a;
    bestPointsDists.insert(make_pair(a,DBL_MAX));
    int L = hInfo->get_L();
    for (int i = 0; i < L; i++) {
        // cout << "HASH TABLE : " << i << endl;
        // Update hinfo with the right vectors for every hash table, to compute query's g-value
        hInfo->update_v(hashTables[i].v);
        hInfo->update_t(hashTables[i].t);
        hInfo->update_r(hashTables[i].r);
        // Find g value for query point.
        vector<int> hValues;
        int k = hInfo->get_k();
        vector<int> vp = q.vpoint;
        for (int j = 0; j < k; j++)
        {
            hValues.push_back(compute_hValue(j, vp, hInfo));
            
        }
        long int ID = compute_IDvalue(hValues, hInfo);
        // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << b.itemID << " ID = " << ID << endl;
        int g = compute_gValue(ID, hashTables[i].get_bucketsNumber());
        list<HashNode> listToSearch = hashTables[i].get_bucketList(g);
        typename list<HashNode>::iterator current;
        for (current = listToSearch.begin() ; current != listToSearch.end() ; ++current ) {
            // cout << current->point->itemID << ":" << current->ID << endl << endl;
            double dist = distance(q.vpoint,current->point->vpoint, 2);
            // cout << "--------------distance = " << dist << " best distance = " << bestDist << endl;
            if (bestPointsDists.size()==N) //if set is full
            {
                //if the biggest distance in set is equal/greater than current distance
                if (prev(bestPointsDists.end())->second >= dist)
                {
                    bestPointsDists.erase(prev(bestPointsDists.end())); //pop biggest distance pair
                    bestPointsDists.insert(make_pair(*(current->point),dist)); //insert new point/distance
                }
            }
            else if (bestPointsDists.size()<N) //if there is space in set insert pair
            {
                bestPointsDists.insert(make_pair(*(current->point),dist));
            }
        }
    }
    return bestPointsDists;
}


unordered_map<int,double> lsh_approximate_range_search(Point q, double R, vector<HashTable> hashTables, LSH_hash_info *hInfo)
{
    // Initialise an unordered map two hold points-distances inside radius r.
    unordered_map<int,double> rPoints;
    int L = hInfo->get_L();
    for (int i = 0; i < L; i++) {
        // cout << "HASH TABLE : " << i << endl;
        // Update hinfo with the right vectors for every hash table, to compute query's g-value
        hInfo->update_v(hashTables[i].v);
        hInfo->update_t(hashTables[i].t);
        hInfo->update_r(hashTables[i].r);
        // Find g value for query point.
        vector<int> hValues;
        int k = hInfo->get_k();
        vector<int> vp = q.vpoint;
        for (int j = 0; j < k; j++)
        {
            hValues.push_back(compute_hValue(j, vp, hInfo));
            
        }
        long int ID = compute_IDvalue(hValues, hInfo);
        // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << b.itemID << " ID = " << ID << endl;
        int g = compute_gValue(ID, hashTables[i].get_bucketsNumber());
        list<HashNode> listToSearch = hashTables[i].get_bucketList(g);
        typename list<HashNode>::iterator current;
        for (current = listToSearch.begin() ; current != listToSearch.end() ; ++current ) {
            // cout << current->point->itemID << ":" << current->ID << endl << endl;
            double dist = distance(q.vpoint,current->point->vpoint, 2);
            // cout << "--------------distance = " << dist << " best distance = " << bestDist << endl;
            if (dist < R)
            {

                rPoints.insert(make_pair(current->point->itemID,dist));
            }
        }
    }
    return rPoints;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CUBE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int hammingDistance(int n1, int n2)
{
    int x = n1 ^ n2;
    int setBits = 0;
 
    while (x > 0) {
        setBits += x & 1;
        x >>= 1;
    }
 
    return setBits;
}


Point cube_approximate_NN(Point q, CubeTable cubeTable, CUBE_hash_info *hInfo)
{
    Point b; // best point-candidate
    double bestDist = INT_MAX; // best distance of best candidate
    
    // Update hinfo with the right vectors for hash table, to compute query's g-value
    hInfo->update_v(cubeTable.v);
    hInfo->update_t(cubeTable.t);
    // Find g value for query point.
    vector<int> hValues;
    int k = hInfo->get_k();
    vector<int> vp = q.vpoint;
    for (int i = 0; i < k; i++)
    {
        hValues.push_back(compute_hValue(i, vp, hInfo));
    }
    vector<int> fValues;
    for (int i = 0; i < k; i++)
    {
        fValues.push_back(compute_fValue(i, hValues[i], hInfo));
    }
    int g = compute_gValue(fValues, hInfo);

    int M = hInfo->get_M(); //maximum number of points to search
    int tempM = 0; //keep track how many points we have searched

    list<Vertice> listToSearch = cubeTable.get_bucketList(g);

    typename list<Vertice>::iterator current;
    for (current = listToSearch.begin() ; current != listToSearch.end() ; ++current ) {
        cout << " i = " << tempM << "  " << current->point->itemID << ":" << endl << endl;
        double dist = distance(q.vpoint,current->point->vpoint, 2);
        tempM++;
        if (dist < bestDist)
        {
            bestDist = dist;
            b = *(current->point);
        }
        if (tempM == M)
        {
            return b;
        }   
    }

    // We finished checking vertice g but we have more points to check (because tempM < M).
    // We can't check more than 'probes' vertices minus the g and we will search until hamming distance = maxHD.
    int probes = hInfo->get_probes()-1;
    int maxHD = hInfo->maxHD;

    vector<int> probesToCheck;
    int numVertices = cubeTable.get_bucketsNumber();
    for (int i = 0; i < numVertices; i++)
    {
        if(hammingDistance(g,i) == 1)
        {
            cout << g << " - " << i << endl;
        }
        
    }
    



    

    // we need to find and keep the neighbor/vertices (indexes) of g according to hamming distance.


    cout << "Query index " << q.itemID << " - BEST LSH DISTANCE : " << bestDist << endl;
    return b; //todo del
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////