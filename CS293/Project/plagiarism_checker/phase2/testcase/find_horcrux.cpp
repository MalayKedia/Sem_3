#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

#define MODULO 1000000007

int num_ways_reach(int x, int y, int z) {
    std::vector<std::vector<std::vector<int>>> DP(x + 1, 
            std::vector<std::vector<int>>(y + 1, std::vector<int>(z + 1, 0)));
    DP[0][0][0] = 1;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            for (int k = 0; k <= z; k++) {
                if (i > 0) DP[i][j][k] = (DP[i][j][k] + DP[i - 1][j][k]) % MODULO;
                if (j > 0) DP[i][j][k] = (DP[i][j][k] + DP[i][j - 1][k]) % MODULO;
                if (k > 0) DP[i][j][k] = (DP[i][j][k] + DP[i][j][k - 1]) % MODULO;
            }
        }
    }
    return DP[x][y][z];
}

int shortest_path_wt(std::vector<std::vector<std::pair<int, int>>> &graph) {
    int n = graph.size();
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>> pq;
    std::vector<int> dist(n, INT_MAX);
    pq.push(std::make_pair(0, 0));
    dist[0] = 0;
    while (!pq.empty()) {
        std::pair<int, int> top = pq.top();
        pq.pop();
        int u = top.second;
        for (auto &neighbour : graph[u]) {
            int v = neighbour.first;
            int w = neighbour.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
}

int main(void) {
    // I want a large number of nodes an edges. Like 10 vertices
    std::vector<std::vector<std::pair<int, int>>> graph = {
        {{1, 2}, {2, 3}},
        {{2, 4}},
        {{1, 1}, {3, 5}},
        {{0, 6}},
        {{2, 7}, {4, 8}},
        {{0, 9}, {3, 10}},
        {{1, 11}, {5, 12}},
        {{2, 13}, {6, 14}},
        {{3, 15}, {7, 16}},
        {{4, 17}, {8, 18}},
        {{5, 19}, {9, 20}}
    };
    int wt = shortest_path_wt(graph);
    std::cout << num_ways_reach(wt, wt*2, wt*3) << std::endl;
}
