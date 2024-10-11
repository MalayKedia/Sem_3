// ----------------------------
//       DO NOT MODIFY
// ----------------------------

#include <iostream>
#include "island-count.cpp"

// count islands
int countIslands(std::vector<std::vector<int>> M) {
    // visited matrix
	std::vector<std::vector<bool>> visited(M.size(),std::vector<bool>(M[0].size(),0));
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[0].size(); j++) {
            visited[i][j] = false;
        }
    }
    int count = 0;
	for (int i = 0; i < M.size(); ++i) {
		for (int j = 0; j < M[0].size(); ++j) {
			if (M[i][j] && !visited[i][j]) {
                // unvisited island
                DFS D;
                // here both T1 and T2 are matrices
                D.dfs(M, i, j, visited);
                // island visited
				++count;
			}
        }
    }
	return count;
}

int main() {
    // input matrix
	std::vector<std::vector<int>> M = {
        { 1, 1, 0, 0, 0 },
        { 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 1 }
    };
	std::cout << "Number of islands is: " << countIslands(M) << std::endl;
}
