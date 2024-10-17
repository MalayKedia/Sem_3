/***********************************************
       DO NOT MODIFY ANYTHING IN THIS FILE
***********************************************/

#include "graph.h"

// default constructor
GraphNode::GraphNode() {
    label = -1;
    adj = std::vector<int>();
}

// constructor with label
GraphNode::GraphNode(int v) {
    label = v;
    adj = std::vector<int>();
}

// add neighbour to node
void GraphNode::addNeighbour(int n) {
    adj.push_back(n);
}

// default constructor
Graph::Graph() {
    nodes = std::map<int, GraphNode *>();
}

// add node in graph if not already present
void Graph::addNode(int v) {
    if (nodes.find(v) == nodes.end()) {
        nodes[v] = new GraphNode(v);
    }
}

// add edge in graph if not already present
void Graph::addEdge(int s, int t) {
    addNode(s);
    addNode(t);
    if(std::ranges::find(nodes[s]->adj.begin(), nodes[s]->adj.end(), t) != nodes[s]->adj.end())
        return;

    nodes[s]->addNeighbour(t);
    nodes[t]->addNeighbour(s);
}


