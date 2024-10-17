Part 1
------

Implement a Class Graph.
Takes constructor argument as no of nodes, followed by a
vector of pairs representing a edge list.

Implement a function called `bfs()` that takes two arguments:
* A node x in the graph G
* A graph G

The function `bfs()` should perform a breadth-first search on the graph G starting from the node x, and should return a map containing the following information:
* The key of each entry in the map should be a node in the graph G.
* The value of each entry in the map should be the parent of the
  corresponding node in the breadth-first search tree.

[We have not done BFS in the class. However, slides have been uploaded for BFS.]

The parent of the root node of the breadth-first search tree is -1. 

Example:  
Input: 
* 1 // part-1
* 5 5 // no of nodes and edges
* 0 1
* 0 2
* 2 3
* 2 4
* 3 4 
* 0   // source vertex 

Output: 

* -1
* 0
* 0
* 2
* 2  

This is the output of `bfs()` on the graph G starting from the node 0. The parent of the node 0 is -1, the parent of the node 1 is 0, and so on. 


***
Part 2
------

Suppose you want to go from A->B->C->D->E in a graph, where A,...,E are arbitrary nodes in our graph. How will you do it?  
Let's answer this question: We will take shortest route from (A-B) (B-C) (C-D) (D-E). 
Combining the above 4 routes we will get the shortest walk going from A-B-C-D-E. 

For this part Using part-1 as a subroutine, Implement a function `shortest_walk()` that takes input as a list of nodes to visit in order, and you have to return the shortest walk as a list of nodes visited during that walk. 

Define a relation R on pairs of nodes such that two nodes x and y are related iff one of them is an ancestor of the other. Now, if `xRy`, the shortest path between x and y in the original graph is just the path between x and y in the BFS tree. (Do you see why?)

Using this, you might be able to avoid some unnecessary calls to `bfs()`, thereby optimising the search.


Example:
Input:
* 2 // part-2
* 5 5// no of nodes and edges
* 0 1
* 0 2
* 2 3
* 2 4
* 3 4 
* 6 // no of stations
* 0 1 4 1 4 1 

Output: 
* 0 1 0 2 4 2 0 1 0 2 4 2 0 1

***