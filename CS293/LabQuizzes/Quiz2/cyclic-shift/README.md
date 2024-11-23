# Cyclic Shifts

!PLEASE READ THIS FILE CAREFULLY TILL THE END!

Some hints are provided but you are not obliged to use them

## Problem Statement

Given a string `s`, we can define a cyclic shift of `s` to be an operation which takes the first `1 <= k <= |s|` characters of `s` from the start and moves them to the end of `s` in a circular manner.


The pseudocode for cyclic shift is as follows:-
```
define cyclic-shift(s, k):
	return s[k+1 to |s|] + s[1 to k]
```
where `s[i to j]` denotes the substring of `s` from `i` to `j` (1-based indexing) and `+` means string concatenation.


For example:

If `s = "abcdabcd"` then,

- `cyclic-shift(s, 1) = "bcdabcda"`
- `cyclic-shift(s, 2) = "cdabcdab"`
- `cyclic-shift(s, 3) = "dabcdabc"`
- `cyclic-shift(s, 4) = "abcdabcd"`
...
- `cyclic-shift(s, 8) = "abcdabcd"`

Note that we always have `cyclic-shift(s, |s|) = s`.


You need to determine the number of cyclic shifts of `s` which give the same string as `s`.

Formally, you need to find **number of integers** `k` such that `1 <= k <= |s|` and `cyclic-shift(s, k) = s`.


## Sample Testcase

If `s = "abcdabcd"` from the above example, we can see that `s = cyclic-shift(s, 4) = cyclic-shift(s, 8)` and hence the answer is `2`.

You can check that for other values of `k`, `cyclic-shift(s, k)` is not equal to `s`.

## Task Description

Complete the function `cyclic_shifts` in the file `cyclic.cpp` which returns an integer giving the **number of values** of such `k` for given string `s`.

Feel free to define your own extra classes or functions in the same file if needed.

## Time and Memory Limit

You are expected to write code which computes the function in `O(|s|)` worst-case time complexity.

Note that allocating a large amount of memory for integer arrays might give a segmentation fault for some larger inputs.

HINT: String comparison is `O(|s|)` but you can use **hashing** to compare strings in `O(1)` time. Recall the definition of **polynomial hashes** and try to efficiently use them to compare strings quickly. Don't forget to use `long long` or `uint64_t`. A function to compute modular inverse is also provided for you if needed.

## Scoring

Note that we will use different testcases (but similar to the ones provided) while grading.

Total = 10 marks

You can use `make short` and `make long` to test your code. 

Note that currently the code is only tested for correctness but not for time complexity. That will be checked later.

We will reward implementations for efficiency.