# Part 3

## Thief Chase

A famous Thief is trying to escape from a Police officer chasing him. The city is modeled as a graph with `n` vertices labeled from `0` to `n-1`.

The graph is provided as an `adjacency list` where `graph[i]` is a list of all the vertices you can reach from vertex `i` (i.e., there is an edge between `i` and `graph[i][j]`).

Both take alternate turns to travel through the city. The Thief starts at node 1 and goes first, the Officer starts at node 2 and goes second, and there is a safe house at node 0. Obviously, the Thief wants to reach the safe house before the Officer catches him and the Officer wants to catch the Thief before he reaches the **safe-house**.

During each player's turn, they must travel along one edge of the graph from the node they are currently at. Additionally, it is not allowed for the Officer to travel to the **safe-house** (node 0).

State of the game is defined as a tuple containing the current positions of the Thief and the Officer and the current player who has to move. Hence the game starts with the initial state `(1, 2, Thief)`.

Then, the game can end in three ways:
1. If ever the Officer occupies the same node as the Thief, the Officer wins.
2. If ever the Thief reaches the safe-house, the Thief wins.
3. If the game ever reaches a repeated state (i.e., state that has occurred before), the game is a draw.

Given the graph, and assuming both players play optimally, return:
- 1 if the Thief wins the game,
- 2 if the Officer wins the game, or
- 0 if the Thief is a draw.

## Task

You need to implement the function `int solve(vector<vector<int>>& graph)` in `solution.cpp`. The return value of this function is the result of the game as described above.

As explained above, the city layout is passed as an adjacency list `graph` from the code in `main.cpp`.

Vertices are indexed starting from 0.

## Input Format

The input to `main.cpp` has the format:
- The first line contains an integer `n` (3 ≤ n ≤ 50) - the number of vertices in the graph.
- The second line contains an integer `m` (1 ≤ m  2000) - the number of edges in the graph.
- The next `m` lines contain two integers `u` and `v` (0 ≤ u, v < n) - denoting an edge between vertices `u` and `v`.

## Output Format

The output from the `solve` function in `solution.cpp` should be a single integer - the result of the game.

