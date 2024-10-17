#include <bits/stdc++.h>
using namespace std;

int solve(vector<vector<int>>& graph) {
    enum class State { Draw, MouseWin, CatWin };
    const int n = static_cast<int>(graph.size());
    State states[50][50][2];
    int out_degree[50][50][2] = {};
    std::memset(states, 0, sizeof(states));
    std::queue<std::tuple<int, int, int, State> > q;
    for (int cat = 0; cat < n; ++cat)
    {
        for (int mouse = 0; mouse < n; ++mouse)
        {
            auto hole = std::count(graph[cat].begin(), graph[cat].end(), 0);
            out_degree[cat][mouse][0] = static_cast<int>(graph[mouse].size());
            out_degree[cat][mouse][1] = static_cast<int>(graph[cat].size())
                                    - static_cast<int>(hole);
        }
    }
    for (int cat = 1; cat < n; ++cat)
        for (int move = 0; move < 2; ++move)
            q.emplace(cat, 0, move, states[cat][0][move] = State::MouseWin),
            q.emplace(cat, cat, move, states[cat][cat][move] = State::CatWin);
    while (!q.empty())
    {
        const auto [cat, mouse, move, state] = q.front();
        q.pop();
        if ((cat == 2) && (mouse == 1) && (move == 0))
            return static_cast<int>(state);
        const int prevMove = move ^ 1;
        for (const int prev : graph[prevMove?cat:mouse])
        {
            const int prevCat = prevMove?prev:cat;
            if (prevCat == 0) continue;
            const int prevMouse = prevMove?mouse:prev;
            if (states[prevCat][prevMouse][prevMove] != State::Draw) continue;
            if (((prevMove == 0) && (state == State::MouseWin))
            ||  ((prevMove == 1) && (state == State::CatWin))
            || (--out_degree[prevCat][prevMouse][prevMove] == 0))
                states[prevCat][prevMouse][prevMove] = state,
                q.emplace(prevCat, prevMouse, prevMove, state);
        }
    }
    return static_cast<int>(states[2][1][0]);
}
