#include "../useful-extra-edges.h"

Testcase::Testcase() {
    n = 4;
    src = 1;
    dest = 4;

    // Edges
    addEdge(1, 2, 2);
    addEdge(2, 4, 3);
    addEdge(1, 3, 10);
    addEdge(3, 4, 2);

    // ExtraEdges
    addExtraEdge(2, 3, 1);
    addExtraEdge(1, 3, 1);
    addExtraEdge(2, 4, 2);
}