#include "dfs.h"
// here T1 is a matrix (2D vector of char) and T2 is a char

// validate
// check the indices and additional conditions after which you would use dfs
template <typename T1, typename T2> bool DFS::validate(T1& M, int i, int j, T2& v) {
    return (i >= 0 && i < M.size()) && (j >= 0 && j < M[0].size()) && M[i][j] == v;
}

// terminate
// this is for premature termination of a dfs run depending on some condition
template <typename T1, typename T2> bool DFS::terminate(T1& M, int i, int j, T2& v) {
    if (M.size() == 0 || M[i][j] == v) {
        return true;
    }
    return false;
}

// dfs
// modify the data structure (matrix M) as needed
// check for terminate if required
// use the row and col vectors to access neighbors of (i,j)
// validate the neighbour before you use dfs
// you may need to use one extra variable for temporarily storing a value
template <typename T1, typename T2> void DFS::dfs(T1& M, int i, int j, T2& v) {
    if (terminate(M,i,j,v)) {
        return;
    }
    auto t = M[i][j];
    M[i][j] = v;
    for (int k = 0; k < 8; k++) {
        if (validate(M,i + row[k],j + col[k],t)) {
            dfs(M, i + row[k], j + col[k], v);
        }
    }
}
