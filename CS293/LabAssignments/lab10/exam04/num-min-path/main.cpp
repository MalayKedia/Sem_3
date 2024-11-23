#include<iostream>
#include "num-min-paths.h"
// You should NOT modify ANYTHING in this file

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph[a].push_back(std::make_pair(b, c));
        graph[b].push_back(std::make_pair(a, c));
    }
    
    std::vector<long long> num_min_paths;
    num_min_paths = find_num_min_paths(graph,s);
    
    for(int i = 0; i < n; i++){
        std::cout << num_min_paths[i] << " ";
    }
    std::cout << std::endl;
    return 0;

}
