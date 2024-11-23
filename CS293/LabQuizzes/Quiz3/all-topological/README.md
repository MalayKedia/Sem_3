# Topological sorting

## PLEASE READ THIS FILE CAREFULLY!

### PROBLEM STATEMENT

You are given:
    > Number of vertices in the graph: V
    > Number of edges in the graph: E
    > E number of vertex pairs or edges (u,v)

You need to complete the `alltopologicalSort()` function to print all possible topological orderings of the given graph.


You need to PRINT all topological orderings. Each time you find a topological ordering you need to put it on vector sorted (already declared in graph.h) and call report_a_sorted_order(). If there is no such ordering please call report_failed_to_sort(). The functions will do the needed printing.
You will NOT be able to print anything yourself because iostream is not included.


## Algorithm

You must have seen an algorithm for topological sort in CS105. C105 slides are included for your reference. The idea is to pick one of the minimum elements, remove it from the graph, and keep doing it. To turn this algorithm for all topological sorts, you need to enumerate all possible choices of minimum.

Here is one way of implementing this.

We can go through all possible ordering via backtracking, the algorithm steps are as follows : 

- Initialize all vertices as unvisited and create a count of incoming edges in indegree vector.

- Now choose a vertex that is unvisited and has zero indegree and decrease the indegree of all its neighbor vertices by 1 (corresponding to removing edges). 

- Add this vertex to the sorted order and call this recursive function again.

- After returning from function reset values of visited, sorted, and indegree for enumeration of other possibilities.

You can design the algorithm differently.


## 


## SOLUTION NEEDS TO BE WRITTEN INSIDE THE all-topologica-sort.cpp FILE and the rest of the files should be left unchanged.

## YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER HEADER FILES in a


### INPUT FORMAT

First line contains 2 space seperated integers, first one being the number of vertices (V) and the second one being the number of edges (E).

Next E lines contain vertex pairs with 2 space seperated integers (u,v) in each row representing edge between those two vertices directed from u to v.
#### Example Input 1:
6 6
5 2
5 0
4 0
4 1
2 3
3 1


#### Expected output:
4 5 0 2 3 1 
4 5 2 0 3 1 
4 5 2 3 0 1 
4 5 2 3 1 0 
5 2 3 4 0 1 
5 2 3 4 1 0 
5 2 4 0 3 1 
5 2 4 3 0 1 
5 2 4 3 1 0 
5 4 0 2 3 1 
5 4 2 0 3 1 
5 4 2 3 0 1 
5 4 2 3 1 0 


 
### VIEWING GRAPH

Function dump_graph() in class graph, creates a file g.dot. You can open the file using using xdot.

$xdot g.dot

### SAMPLE TESTCASES

Some test cases are provided for you to check if your implementation of the problem is correct. They are not a representative of the problem. They may miss some corner cases.

## SCORING

Use `make runtests` to test your implementation on the provided test cases.

-- We will be using different test cases (but similar to the ones provided) while grading.
-- We will be checking the efficiency of your code 



