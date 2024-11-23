/* 
    PROBLEM:
        Given an array A of size n, and a sequence of balanced parenthesis, we define the score of the sequence as the 
        the sum of |A[i] - A[j]| for all pairs of matching brackets (i,j) in the sequence. If the sequence of parenthesis
        are unbalanced return -1 score.

        eg. A = [1,2,3,4,5,6]
            s = "((()))"
            score = |1-6| + |2-5| + |3-4| = 9

            A = [1,2,3,4]
            s = "()()"
            score = |1-2| + |3-4| = 2

            A = [1,2,3,4,5]
            s = "((())"
            score = -1 (not balanced)

        This problem has 2 parts. 
        1. Given an array A of size n, and a sequence of balanced parenthesis, find it's score. Remember to take care of 
           large numbers. [3 points]

        2. Given an array A of size n, find the sequence of balanced parenthesis that maximises the score [8 points]
           Note that there may be more than 1 possible answers. You can output any of them.

           eg. A = [1,2,3,4,5,6]
               ans = "((()))"
               score = 9

               A = [1,1,1,1]
                ans = "()()" or
                ans = "(())"
                score = 0

    INPUT:
        The first line of input contains an integer n (1 ≤ n ≤ 10^5) — the size of the array A.
        The next n lines of input contain n integers A1, A2, ..., An (1 ≤ Ai ≤ 10^9) — the elements of the array A.
        The next line of input contains a string s of length n — the sequence of balanced parenthesis that consists of characters '(' and ')', not space separated.

    OUTPUT:
        PART-1: 
            The output contains a single line containing the score of the given sequence of balanced parenthesis.

        PART-2:
            The output should contain 2 lines.
            The first line should contain the sequence of balanced parenthesis that maximises the score.
            The second line should contain the score of the sequence of balanced parenthesis that maximises the score.

    TEST:
        To test your code, run make score or make seq in the terminal.
*/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

// given a balanced bracket sequence and an array A calculate its score, return -1 if the sequence is not balanced
long long score(vector<int> A, int n, string balanced_parentheses){
}

// given an array A, return the balanced parenthesis that maximises the score, return an empty string if not possible
string max_balanced_parentheses(vector<int> A, int n){
}