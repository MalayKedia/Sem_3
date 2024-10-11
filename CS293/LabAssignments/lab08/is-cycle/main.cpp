/***********************************************
       DO NOT MODIFY ANYTHING IN THIS FILE
***********************************************/

#include <iostream>
#include "graph.h"

int main () {
    int E;
    std::cin >> E;
    Graph g;
    for (int i = 0; i < E; i++) {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v);
    }
    bool result = g.isCyclePresent();
    if (result) {
        std::cout << "Cycle is present" << std::endl;
    } else {
        std::cout << "Cycle is not present" << std::endl;
    }
}