// ** DO NOT MODIFY THIS FILE **
// Please read this file carefully.

#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

//  Constructor of graph
Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];

  // Initialising all indegree with 0
  for (int i = 0; i < V; i++)
    indegree.push_back(0);

  visited = new bool[V];
  for (int i = 0; i < V; i++)
    visited[i] = false;

}

//  Utility function to add edge
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v's list.
    indegree[w]++;       // increasing inner degree of w by 1
}

void Graph::dump_dot() {
  ofstream output("g.dot");
  output << "digraph graphname {\n";
  for (int v = 0; v < V; v++) {
    auto& ws = adj[v];
    for( auto w : ws) {
      output << v << "->" << w << "\n";
    }
  }
  output << "}\n";
}

void Graph::report_a_sorted_order() {
  for (int i = 0; i < sorted.size(); i++)
    cout << sorted[i] << " ";
  cout << endl;
}

void Graph::report_failed_to_sort() {
  if( found_cycle == false)
    cout << "-1" << endl;
  found_cycle = true;
}


// Driver program to test above functions
int main()
{
  int V,E,u,v;
  // Read from the file
  cin >> V;
  cin >> E;
  Graph g(V);
  for( int i = 0; i < E; i++) {
    cin >> u;
    cin >> v;
    g.addEdge(u, v);
  }
  g.dump_dot();

  g.alltopologicalSort();

  return 0;
}
