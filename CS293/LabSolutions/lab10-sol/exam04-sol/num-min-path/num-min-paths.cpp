#include "num-min-paths.h"

const int MOD = 1000000007;

std::vector<long long> find_num_min_paths(
        std::vector<std::vector<std::pair<int, int>>> &graph, int source) {
    // graph[i] --> list of adjacent vertices from vertex i 
    // along with edge weights (along long weights > 0)
    // i.e. i -- graph[i][j].first is an edge of weight graph[i][j].second
    // source --> source vertex from which number of minimum paths to 
    // along long other vertices are to be found
    //
    // NOTE : Vertices are 0 indexed from 0 to n-1
    // You are to return a vector v where v[i] = number of minimum weight paths 
    // from source vertex to vertex i ,number of min_paths to source itself = 1
    // Since the number of minimum weight paths can be very large, return the
    // number of minimum weight paths modulo 1000000007 (1e9 + 7)
    int n = graph.size();
    std::vector<long long> num_min_path(n, 0);
    // TODO: Write your code here
    std::vector<long long> min_dist(n, -1);
    std::multiset<std::array<long long, 3>> m;

    for (auto i : graph[source]) {
        std::array<long long, 3> temp;
        temp[0] = static_cast<long long>(i.second);
        temp[1] = static_cast<long long>(source);
        temp[2] = static_cast<long long>(i.first);
        m.insert(temp);
    }

    num_min_path[source] = static_cast<long long>(1);
    min_dist[source] = static_cast<long long>(0);

    while (m.size() > 0) {
        auto it = m.begin();
        if (min_dist[(*it)[2]] == -1 || min_dist[(*it)[2]] == (*it)[0]) {
            long long old_dist = min_dist[(*it)[2]];
            min_dist[(*it)[2]] = (*it)[0];
            num_min_path[(*it)[2]] += num_min_path[(*it)[1]];
            num_min_path[(*it)[2]] %= MOD;

            if (old_dist == -1) for (auto it2 : graph[(*it)[2]]) {
                std::array<long long, 3> temp;
                temp[0] = min_dist[(*it)[2]];
                temp[0] += static_cast<long long>(it2.second);
                temp[0] %= MOD;
                temp[1] = static_cast<long long>((*it)[2]);
                temp[2] = static_cast<long long>(it2.first);
                m.insert(temp);
            }
        }
        m.erase(m.begin());
    } 
    // End TODO
    return num_min_path;
}
