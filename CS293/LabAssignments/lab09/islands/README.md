# DFS Puzzles

A template DFS class has been provided. It contains the adjacent neighbour vectors
(the 8 neighbours of a square at (a,b) in a grid are accessible using the indexing
(a+row[i],b+col[i])).

There are three template functions: validate, terminate and dfs. This class is common
to both the puzzles that are to be solved. The idea for these functions is that they
are using two template types T1 and T2 which essentially represent information of the
puzzle.

For example, in the Islands Count puzzle, the first argument (T1 M) represents
the 2D matrix that has been given as input, while the fourth argument (T2 v) is the
visited boolean matrix representing whichever positions were visited (initially all
false).

Both these arguments are passed by reference (indicated by the &) and so any changes
will reflect across any and all accesses to both these variables.

Your task is to complete the implementation of these three functions for both puzzles.
You need to add your implementation to the files [flood-fill.cpp](./flood-fill.cpp)
and [island-count.cpp](./island-count.cpp). The simplest of the 6 implementations has
been done for you :).

The key here is to break the given problem into conditions for validating a particular
position (i,j) and then using dfs recursively over all the neighbours of that position.
Use the validate function to check the invariant for each puzzle and then the dfs call
will follow. The changes to the matrix in dfs call should happen at the (i,j) position.

The details of both the puzzles are as below:

## ISLAND COUNT
Given a binary 2D matrix, find the number of islands. A group of connected 1s forms
an island. This is a variation of the standard problem: Counting the number of connected
components in an undirected graph.

Example:
Input: {
    {1, 1, 0, 0, 0},
    {0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0}
}
Output: 4

## FLOOD FILL
Flood fill (also known as seed fill) is an algorithm that determines the area connected
to a given node in a multi-dimensional array. It is used in the 'bucket' fill tool of a
paint program to fill connected, similarly colored areas with a different color and in
games such as Go and Minesweeper for determining which pieces are cleared.

The flood fill algorithm takes three parameters: a start node, a target color, and a
replacement color.

Consider the following matrix below: if the start node is (3, 9), target color is
'BLACK' (X) and replacement color is 'CANARY' (C), the algorithm looks for all nodes in
the matrix that are connected to the start node by a path of the target color and
changes them to the replacement color.

Example:
Input: {
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
}
Target: X, Replacement: C
Output:
 Y Y Y G G G G G G G
 Y Y Y Y Y Y G C C C
 G G G G G G G C C C
 W W W W W G G G G C
 W R R R R R G C C C
 W W W R R G G C C C
 W B W R R R R R R C
 W B B B B R R C C C
 W B B C B B B B C C
 W B B C C C C C C C

To check your implementations, run "make ic" or "make ff" appropriately. To check both
together, run "make".
