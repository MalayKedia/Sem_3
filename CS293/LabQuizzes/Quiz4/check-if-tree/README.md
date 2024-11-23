# Check if Tree

In this problem you need to identify if a given distance matrix is for a tree or not.

Please check examples below for better understanding.

Lot of testcases have been provided to help you test your code.

A graph vizualization tool has been provided in `./draw-graph/` to help you visualize the graph.

## Problem Description

The distance matrix of a graph with `n` vertices (labelled `0` to `n-1`) is a `n x n` matrix `D` such that `D[i][j]` is the length of shortest path between vertices `i` and `j` in the graph.

Note that length of a path is the sum of weights of the edges in the path.

You are given a matrix `dist` of size `n x n` of **non-negative integers**. You need to determine if there exists a **weighted tree** with `n` vertices such that `dist` is the distance matrix of that tree. Edge weights in the tree should be **positive integers**.

## Your Task

In the file `check-tree.cpp`, complete the function `bool check_tree(int n, vector<vector<int>> dist, vector<tuple<int, int, int>> &found_tree)` which takes an integer `n` and a `n x n` matrix `dist` as input.

If such a tree exists, return `true` and set the `found_tree` in given output format. Otherwise, return `false`.

## Running the code

Write `make` to compile and run the code on given testcases.

NOTE - During the exam your code will only be tested for the `true/false` return value and not the found tree. That will be checked later during autograding.

## Input Format

- First line of input contains an integer `n` representing the number of vertices in the graph.

- The next `n` lines contain `n` integers each, representing the distance matrix `dist[i][j]`.

## Output Format

Return `true` if a tree exists with the given distance matrix. You need to store the found tree in `vector<tuple<int, int, int>> &found_tree` parameter.

If a tree exists, set `found_tree` to contain the following:

- Exactly `n-1` elements, each a tuple of three integers `u`, `v` and `w` representing an edge between vertices `u` and `v` with a weight `w`.

- Edges can be stored in any order.

- If there are multiple trees possible, store any one of them.

Return `false` if no such tree exists. You do not need to modify `found_tree` in this case.

## Constraints

- `2 ≤ n ≤ 100`
- `1 ≤ dist[i][j] ≤ 10^6`
- Nodes are labelled from `0` to `n-1`

## Examples

### Example 0

Input:
```
    2
    0 1
    1 0
```

Output:

Return = `true`

`found_tree` =
```
    0 1 1
```

### Example 1

Input:
```
    3
    0 2 7
    2 0 9
    7 9 0
```

Output:

Return = `true`

`found_tree` =
```
    0 1 2
    0 2 7
```

### Example 2

Input:
```
    4
    0 1 1 1
    1 0 1 1
    1 1 0 1
    1 1 1 0
```

Output:

Return = `false`

You can check that this is a fully connected graph and not a tree.

### Example 3

Input:
```
    4
    0 1 2 3 
    1 0 3 4 
    2 3 0 5 
    3 4 5 0
```

Output:

Return = `true`

`found_tree` =
```
    0 1 1
    0 2 2
    0 3 3
```

### Example 4

Input:
```
    5
    0 102 1 100 103 
    102 0 103 2 5 
    1 103 0 101 104 
    100 2 101 0 3 
    103 5 104 3 0 
```

Output:

Return = `true`

`found_tree` =
```
    0 2 1
    1 3 2
    3 4 3
    0 3 100
```

## Expected Time Complexity

Any correct polynomial time algorithm will be accepted.