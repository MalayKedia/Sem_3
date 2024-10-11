#include "solution.cpp"
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    int x, y;
    for(int i = 0; i < m; i++){
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    cout << solve(adj) << endl;

}

