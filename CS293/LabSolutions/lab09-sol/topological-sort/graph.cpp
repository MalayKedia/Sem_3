// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <cstdio>
#include "graph.h"

// default constructor
GraphNode::GraphNode() {
    label = -1;
    visited = false;
    adj = std::vector<std::pair<int, int>>();
}

// value initialization
GraphNode::GraphNode(int v) {
    label = v;
    visited = false;
    adj = std::vector<std::pair<int, int>>();
}

// add neighbour node via edge
void GraphNode::addNgbr(int d, int w) {
    adj.push_back({d, w});
}

// constructor
Graph::Graph() {
    nodes = std::map<int, GraphNode *>();
}

// add node to graph
void Graph::addNode(int s) {
    if (nodes.find(s) == nodes.end()) {
        nodes[s] = new GraphNode(s);
    }
}

// add edge
void Graph::addEdge(int s, int d, int w) {
    addNode(s);
    addNode(d);
    nodes[s]->addNgbr(d, w);
}

// reset visits
void Graph::resetVisit() {
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->visited = false;
    }
}

// print toposort
void Graph::print() {
    while (!S.empty()) {
        printf("%d ", S.top());
        S.pop();
    }
}
