// DO NOT MODIFY THIS FILE !!!

/** README !!!
 * There are n cities and some roads which connect any 2 cities.
 * You are given the layout of the map as an undirected weighted graph where
 * nodes represent the cities and edges represent the roads.
 *
 * The weight on any edge represents the time taken to cover that road 
 * (represented by that edge). All weights will be positive.
 * Each node is represented by an integer from 0 to n-1.
 * 
 * Alice is at City A and Bob is at City B (A and B are different).
 * Alice has to reach City B in the minimum time possible. 
 * Bob also wants to reach City A in the minimum time possible.
 * They both start at the same time (consider this time t = 0).
 *
 * Your task is to efficiently find and print the number of ways 
 * Alice and Bob can move such that they never "clash" at a city.
 * Since this number could be huge, just print its modulo 1e9+7 (1000000007).
 *
 * In other words, there shouldn't be a time t where both 
 * Alice and Bob are simultaneously present at a city (node).
 * They may meet on a road (i.e. an edge) but we don't care about that.
 * 
 * Contrainsts: 2 <= n <= 10^5, 0 <= A, B < n, A != B, 
 *              1 <= weight of edge <= 10^9
 * 
 * Complete the function getNumNonClashWays in file `clash-of-paths.cpp`.
 * It is a part of the class Testcase (see below).
 * DO NOT MODIFY this .h file nor main.cpp.
 * NO new "#include"s allowed.
 * You can add any helper functions in the clash-of-paths.cpp file.
 * 
 * There are 2 short and 1 long testcases. 
 * Ideally even the long testcase should run in few seconds.
 * Explanation for both the short testcases:
 *
 * Short testcase 1:
 * The 7 ways Alice and Bob can work around are:-
 * 1. Alice goes from 0->1->2->4->5 and Bob goes from 5 to 0 direct.
 * 2. Alice goes from 0->1->3->4->5 and Bob goes from 5 to 0 direct.
 * 3. Bob goes from 5->4->2->1->0 and Alice goes from 0 to 5 direct.
 * 4. Bob goes from 5->4->3->1->0 and Alice goes from 0 to 5 direct.
 * 5. Alice goes from 0->1->2->4->5 and Bob goes from 5->4->3->1->0.
 * 6. Bob goes from 5->4->2->1->0 and Alice goes from 0->1->3->4->5.
 * 7. Alice and Bob both go on the edge with weight 4. 
 * (They will meet on road but not at a city).
 * 
 * Short testcase 2:
 * Any path will have to go through city 3 and Alice and Bob will meet there 
 * at time t = 2. So, there is no way for Alice and Bob to move.
 */

#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

class Testcase {
private:
    // AdjacencyList is a vector of vectors of pairs. 
    // Each pair represents an edge between two nodes.
    // The first element of the pair is the other node of the edge 
    // and the second element is the weight of that edge.
    std::vector<std::vector<std::pair<int, int>>> AdjacencyList;
    int A, B; 
    // A is the city no. where Alice initially is and 
    // B is the city no. where Bob initially is.

    void addEdge(int u, int v, int edge_weight) {
        AdjacencyList[u].push_back(std::make_pair(v, edge_weight));
        if(u != v) {
            AdjacencyList[v].push_back(std::make_pair(u, edge_weight));
        }
    }
    
public:
    Testcase();
    void getNumNonClashWays();
};
