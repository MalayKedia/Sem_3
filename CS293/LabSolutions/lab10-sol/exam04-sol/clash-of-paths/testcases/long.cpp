#include "../clash-of-paths.h"

Testcase::Testcase() {
    int n = 100000;
    A = 0;
    B = n - 1;

    AdjacencyList.resize(n);

    for (int i = 0; i < n - 1; ++i) {
        addEdge(i, i + 1, 1); // Connect each node to the next
    }

    for (int i = 0; i < n - 2; ++i) {
        addEdge(i, i + 2, 2); // Connect each node to the node 2 steps ahead with edge weight 2
    }
}