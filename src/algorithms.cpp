#include "../include/algorithms.hpp"

using namespace std;


Point approximate_NN(Point q, vector<HashTable> hashTables, hash_info *hInfo)
{
    Point b; // best point-candidate
    double bestDist = INT_MAX; // best distance of best candidate
    int L = hInfo->get_L();
    cout << "L = " << L << endl; 
    for (int i = 0; i < L; i++) {
        cout << "HASH TABLE : " << i << endl;
        // Find g value for query point.
        vector<int> hValues;
        int k = hInfo->get_k();
        vector<int> vp = q.vpoint;
        for (int j = 0; j < k; j++)
        {
            hValues.push_back(compute_hValue(j, vp, hInfo));
            
        }
        long int ID = compute_IDvalue(hValues, hInfo);
        int g = compute_gValue(ID, hashTables[i].get_bucketsNumber());
        list<HashNode> listToSearch = hashTables[i].get_bucketList(g);
        typename list<HashNode>::iterator current;
        for (current = listToSearch.begin() ; current != listToSearch.end() ; ++current ) {
            cout << current->ID << endl << endl;
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
            cout << endl;
        }
    }
    cout << "BEST: " << bestDist << endl;
    return b;
    
}