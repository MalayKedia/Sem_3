// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <iostream>
#include "graph.h"

int main (int argc, char* argv[]) {
    int N, E;
    std::cin >> N >> E;
    Graph g;
    for (int i = 0; i < E; i++) {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v, 1);
    }
    g.topoSort();
    g.print();
}
