// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <vector>

// DFS template class
class DFS {

    // these are for moving the index pair (i,j)
    // all 8 adjacent vertices can be accessed
    std::vector<int> row, col;

public:

    // constructor
    DFS() {
        row = {-1, -1, -1,  0, 0,  1, 1, 1};
        col = {-1,  0,  1, -1, 1, -1, 0, 1};
    }

    // validate function
    template <typename T1, typename T2>
    bool validate(T1 &M, int i, int j, T2 &v);

    // terminate function
    template <typename T1, typename T2>
    bool terminate(T1 &M, int i, int j, T2 &v);

    // dfs function
    template <typename T1, typename T2>
    void dfs(T1 &M, int i, int j, T2 &v);
};
