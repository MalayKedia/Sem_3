// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <vector>
#include <stack>
#include <map>

class GraphNode {
public:
    // variables
    int label;
    bool visited;
    // adjacency
    std::vector<std::pair<int, int>> adj;

    // constructors
    GraphNode();
    GraphNode(int v);

    // add neighbour
    void addNgbr(int d, int w);
};

class Graph {

    // variables
    std::map<int, GraphNode *> nodes;

    // topo sort result
    std::stack<int> S;

public:

    // constructors
    Graph();

    // add node
    void addNode(int s);

    // add edge
    void addEdge(int s, int d, int w);

    // reset visits
    void resetVisit();

    // topological sort
    void dfs(int s);
    void topoSort();
    void print();
};
