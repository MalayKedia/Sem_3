#include "../useful-extra-edges.h"

Testcase::Testcase() {
    n = 5;
    src = 2;
    dest = 5;

    // Edges
    addEdge(1, 2, 2);
    addEdge(2, 4, 1);
    addEdge(3, 4, 2);

    // ExtraEdges
    addExtraEdge(2, 3, 1);
    addExtraEdge(1, 4, 1);
}