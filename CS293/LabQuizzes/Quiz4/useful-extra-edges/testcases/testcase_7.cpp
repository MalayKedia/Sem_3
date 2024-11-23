#include "../useful-extra-edges.h"

Testcase::Testcase() {
    n = 100000;
    src = 1;
    dest = 100000;

    // Edges
    for(int i = 1; i < n; i++) {
        addEdge(i, i+1, 1000000000);
    }

    // Extra Edges
    for(int i = 1; i < n-2; i++) {
        addExtraEdge(i, i+1, 2);
    }
    addExtraEdge(10, 100, 10);
    addExtraEdge(100, 1000, 100);
}