// DO NOT MODIFY THIS FILE !!!

/** README !!!
 * You are given an undirected weighted graph of n nodes.
 * The nodes are numbered from 1 to n.
 * All the edge weights are positive integers.
 * The graph is given in the form of a list (called "Edges") of the edges with their weights.
 * 
 * You are also given a starting node (called "src") and a destination node (called "dest").
 * A list (called "ExtraEdges") of 'extra' edges is also given.
 * 
 * We define the weight of a path as the sum of the weights of the edges in the path.
 * 
 * Your task is to print the minimum possible weight of a path from "src" to "dest",
 * provided you can add a maximum of 1 'extra' edge (from "ExtraEdges") to the graph.
 * If "dest" can't reached from "src", print -1.
 * 
 * Mind that there can be multiple edges between two nodes.
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - 1 <= |Edges| <= 10^5
 * - 1 <= |ExtraEdges| <= 10^5
 * - 1 <= src, dest <= n
 * - 1 <= weight of any edge <= 10^9
 * 
 * You have to complete Testcase::getMinWeight() function in `useful-extra-edges.cpp`.
 * "n", "src", "dest", "Edges" and "ExtraEdges" are member variables of the Testcase class.
 * NO new "#include"s allowed.
 * DO NOT MODIFY ANY FILE OTHER THAN `useful-extra-edges.cpp`.
 * You can define any helper functions in `useful-extra-edges.cpp`.
 * 
 * See the `testcases/` folder for public testcases and their expected outputs.
 * Run `make` to compile and run the public testcases.
 * See some explanation regarding the public testcases in `explanation.txt`.
 */

#include "common.h"

class Testcase {
private:
    int n;
    int src, dest;
    // Each edge is represented by a vector of 3 integers: {u, v, weight}
    std::vector<std::vector<int>> Edges;
    std::vector<std::vector<int>> ExtraEdges;

    void addEdge(int u, int v, int edge_weight) {
        Edges.push_back({u, v, edge_weight});
    }

    void addExtraEdge(int u, int v, int edge_weight) {
        ExtraEdges.push_back({u, v, edge_weight});
    }
    
public:
    Testcase();
    void getMinWeight(); // You have to complete this function
};
