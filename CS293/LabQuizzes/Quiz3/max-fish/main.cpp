// ----------------------------------------------------------------
// DO NOT UPDATE ANYTHING IN THIS FILE
// ----------------------------------------------------------------
#include <iostream>
#include <vector>
#include "fish.cpp"

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> grid[i][j];
        }
    }

    Solution solution;

    int result = solution.findMaxFish(grid);
    cout << result;

    return 0;
}
