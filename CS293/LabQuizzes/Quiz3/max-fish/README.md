# Maximum Fish Catching

## PLEASE READ THIS FILE CAREFULLY!

### PROBLEM STATEMENT

You are given a 0-indexed 2D matrix `grid` of size `m x n`, where `(r, c)` represents:

- A land cell if `grid[r][c] = 0`, or
- A water cell containing `grid[r][c]` fish if `grid[r][c] > 0`.

A fisherman can start at any water cell `(r, c)` and can perform the following operations any number of times:

1. Catch all the fish at cell `(r, c)`.
2. Move to any adjacent water cell.

Your task is to return the maximum number of fish the fisherman can catch if he chooses his starting cell optimally, or return 0 if no water cell exists.

## SOLUTION NEEDS TO BE WRITTEN INSIDE THE fish.cpp FILE

## YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER HEADER FILES INSIDE THE fish.cpp!

### INPUT FORMAT

The input will be a 2D matrix represented as a list of lists, where each element represents either a land cell or a water cell containing fish.

#### Example Input 1:

grid = [
[0, 2, 1, 0],
[4, 0, 0, 3],
[1, 0, 0, 4],
[0, 3, 2, 0]
]

#### Expected output: 7

#### Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.

### SAMPLE TESTCASES

Some testcases are provided for you to check if your implementation of the problem is correct.

### CUSTOM TESTCASES

You can run your implementation on custom testcases using command: `make custom file=<input_filename>`

## SCORING

Use `make runtests` to test your implementation on the provided testcases.

We will be using different testcases (but similar to the ones provided) while grading.
