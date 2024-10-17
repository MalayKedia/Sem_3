#include "graph.h" // needed

// you may or may not use this dfs function
// but the end result has to be stored in stack Graph::S
void Graph::dfs(int s) {
    nodes[s]->visited = true;
    for (auto &e: nodes[s]->adj) {
        if (!(nodes[e.first]->visited)) {
            dfs(e.first);
        }
    }
    S.push(s);
}

// this function is to be implemented
void Graph::topoSort() {
    resetVisit();
    for (int i = 0; i < nodes.size(); i++) {
        if (!nodes[i]->visited) {
            dfs(i);
        }
    }
}
