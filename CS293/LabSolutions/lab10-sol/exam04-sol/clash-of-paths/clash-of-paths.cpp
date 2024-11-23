#include "clash-of-paths.h"

/**
 * You can define any helper functions here. NO new "#include"s allowed.
 * 
 * You can access the adjacency list using the variable AdjacencyList.
 * Values of cities A and B are also member variables of the Testcase class.
 * 
 * Print the number of ways (mod 1e9+7) Alice and Bob can move such that 
 * they never "clash" at a city. Don't return anything.
 */

const int MOD = 1000000007;

void modifiedDijkstra(int start, 
        std::vector<std::vector<std::pair<int, int>>>& AdjacencyList,
        std::vector<long long>& dist, std::vector<long long>& numWays) {
    int n = AdjacencyList.size();
    dist.resize(n, INT_MAX);
    numWays.resize(n, 0);

    std::priority_queue<std::pair<long long, int>, 
        std::vector<std::pair<long long, int>>, 
        std::greater<std::pair<long long, int>>> pq;
    pq.push(std::make_pair(0, start));
    dist[start] = 0;
    numWays[start] = 1;

    while(!pq.empty()) {
        std::pair<long long, int> top = pq.top();
        pq.pop();
        long long d = top.first; int u = top.second;
        if(d > dist[u]) {
            continue;
        }
        for(int i = 0; i < AdjacencyList[u].size(); i++) {
            std::pair<int, int> v = AdjacencyList[u][i];

            if(dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                numWays[v.first] = numWays[u];
                pq.push(std::make_pair(dist[v.first], v.first));
            } 
            else if(dist[u] + v.second == dist[v.first]) {
                numWays[v.first] = (numWays[v.first] + numWays[u]) % MOD;
            }
        }
    }
}

void Testcase::getNumNonClashWays() {
    std::vector<long long> distA, numWaysA, distB, numWaysB;
    modifiedDijkstra(A, AdjacencyList, distA, numWaysA);
    modifiedDijkstra(B, AdjacencyList, distB, numWaysB);

    int n = AdjacencyList.size();
    int minTime = distA[B];
    long long totalWays = (numWaysA[B] * numWaysB[A]) % MOD;

    for(int i = 0; i < n; i++) {
        if(distA[i] + distB[i] == minTime && distA[i] == distB[i]) {
            // means they meet at city i
            long long numPathsThroughI = (numWaysA[i] * numWaysB[i]) % MOD;
            totalWays = (totalWays - 
                    ((numPathsThroughI * numPathsThroughI) % MOD) 
                + MOD) % MOD;
        }
    }
    std::cout << totalWays << std::endl;
}
