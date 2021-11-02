#include "../include/algorithms.hpp"

using namespace std;


Point lsh_approximate_NN(Point q, vector<HashTable> hashTables, hash_info *hInfo)
{
    Point b; // best point-candidate
    double bestDist = INT_MAX; // best distance of best candidate
    int L = hInfo->get_L();
    for (int i = 0; i < L; i++) {
        cout << "HASH TABLE : " << i << endl;
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
            cout << "--------------distance = " << dist << " best distance = " << bestDist << endl;
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Point true_approximate_NN(Point q, Vector_of_points inputData)
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


priority_queue<pair<Point,double>,vector<pair<Point,double>>,CompDist> lsh_approximate_nNN(Point q, int N, vector<HashTable> hashTables, hash_info *hInfo)
{
    // Initialise a max priority queue two hold pairs of best point/best distance.
    priority_queue<pair<Point,double>,vector<pair<Point,double>>,CompDist> bestPointsDists;
    Point a;
    bestPointsDists.push(make_pair(a,DBL_MAX));
    cout << " ---- size " << bestPointsDists.size() << endl;
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
            if (bestPointsDists.size()==N) //if priority queue is full
            {
                //if the biggest distance in priority queue is equal/greater than current distance
                if (bestPointsDists.top().second >= dist)
                {
                    bestPointsDists.pop(); //pop biggest distance pair
                    bestPointsDists.push(make_pair(*(current->point),dist)); //push new point/distance
                }
            }
            else if (bestPointsDists.size()<N) //if there is space in priority queue push pair
            {
                cout << "here" << endl;
                bestPointsDists.push(make_pair(*(current->point),dist));
            }
        }
    }
    return bestPointsDists;
}