// #include <bits/stdc++.h>
using namespace std;
#include <vector>
#include <list>

class Graph {
public:
  //------------------------
  // Basic graph utilities
  //------------------------
  // No. of vertices
  int V;
  // Pointer to an array containing adjacency list
  list<int> *adj;
  // Vector to store indegree of vertices
  vector<int> indegree;
  // Constructor
  Graph(int V);
  // function to add an edge to graph
  void addEdge(int v, int w);
  // Dump graph as dotty file
  // To see the graph, use $xdot g.dot
  void dump_dot();



  //------------------------
  // Interaface for topological sort
  // supporting variables
  //------------------------

  // Prints all Topological Sorts
  void alltopologicalSort();
  bool *visited;

  // Store a sorted sequence of nodes. Use it to print on stdout
  // You do not have access to cout in all-topological-sort.cpp
  vector<int> sorted;
  // the following two functions are for printing the results
  void report_failed_to_sort();
  void report_a_sorted_order();
  // Flag that search has found a cycle
  int found_cycle = false;
};
