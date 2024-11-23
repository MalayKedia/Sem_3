#include "num-min-paths.h"

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
 
    // End TODO
    return num_min_path;
}
