#include "../clash-of-paths.h"

Testcase::Testcase() {
    A = 0;
    B = 5;
    AdjacencyList.resize(6);
    addEdge(0, 1, 1);
    addEdge(0, 5, 4);
    addEdge(1, 2, 1);
    addEdge(1, 3, 1);
    addEdge(2, 4, 1);
    addEdge(3, 4, 1);
    addEdge(4, 5, 1);
}