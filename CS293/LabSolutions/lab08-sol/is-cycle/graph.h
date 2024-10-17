/***********************************************
       DO NOT MODIFY ANYTHING IN THIS FILE
***********************************************/

#include <vector>
#include <stack>
#include <queue>
#include <map>

class GraphNode {
public:
    // label
    int label;
    
    // adjacency list
    std::vector<int> adj;

    // constructors
    GraphNode();
    GraphNode(int v);

    // add neighbour
    void addNeighbour(int n);
};


class Graph {
    // variables
    std::map<int, GraphNode *> nodes;

public:

    // constructor
    Graph();

    // add node in graph
    void addNode(int v);

    // add edge in graph
    void addEdge(int s, int t);

    // check if cycle is present
    bool isCyclePresent();
};