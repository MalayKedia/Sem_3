#include "../clash-of-paths.h"

Testcase::Testcase() {
    A = 0;
    B = 6;
    AdjacencyList.resize(7);
    addEdge(0, 1, 1);
    addEdge(0, 2, 1);
    addEdge(0, 3, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 1);
    addEdge(3, 4, 1);
    addEdge(3, 5, 1);
    addEdge(3, 6, 2);
    addEdge(4, 6, 1);
    addEdge(5, 6, 1);
}