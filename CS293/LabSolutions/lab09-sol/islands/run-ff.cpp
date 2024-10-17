// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <iostream>
#include "flood-fill.cpp"

// printing the matrix
void printMatrix(std::vector<std::vector<char>> const &mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            std::cout << " " << mat[i][j];
        }
        std::cout << std::endl;
    }
}

// main function
int main() {
    // input grid
    std::vector<std::vector<char>> mat = {
        { 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
        { 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
        { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
        { 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
        { 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
    };
    int x = 3, y = 9; // target character
    char replacement = 'C'; // replacement
    DFS D;
    // here T1 is a matrix, T2 is a char
    D.dfs(mat, x, y, replacement);
    printMatrix(mat);
}
