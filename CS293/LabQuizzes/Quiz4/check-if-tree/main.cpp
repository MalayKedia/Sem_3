// DO NOT MODIFY THIS FILE

#include <iostream>
#include "check-tree.h"
using namespace std;


int main(){
    unsigned n;
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));

    for(unsigned i = 0; i < n; i++){
        for(unsigned j = 0; j < n; j++){
            cin >> dist[i][j];
        }
    }

    bool result;
    vector<tuple<int, int, int>> found_tree;

    result = check_tree(n, dist, found_tree);

    cout << result << endl;

    if(result){
        for(auto &[u, v, w] : found_tree){
            cout << u << " " << v << " " << w << endl;
        }
    }
    else{
        cout << "No Such Tree Exists" << endl;
    }

}
