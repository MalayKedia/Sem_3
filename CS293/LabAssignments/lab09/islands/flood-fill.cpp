#include "dfs.h"
// here T1 is a matrix (2D vector of char) and T2 is a char

// validate
// check the indices and additional conditions after which you would use dfs
template <typename T1, typename T2> bool DFS::validate(T1& M, int i, int j, T2& v) {
    
}

// terminate
// this is for premature termination of a dfs run depending on some condition
template <typename T1, typename T2> bool DFS::terminate(T1& M, int i, int j, T2& v) {
    
}

// dfs
// modify the data structure (matrix M) as needed
// check for terminate if required
// use the row and col vectors to access neighbors of (i,j)
// validate the neighbour before you use dfs
// you may need to use one extra variable for temporarily storing a value
template <typename T1, typename T2> void DFS::dfs(T1& M, int i, int j, T2& v) {
    
}
