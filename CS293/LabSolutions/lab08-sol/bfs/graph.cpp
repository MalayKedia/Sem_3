#include<unordered_map>
#include<vector>
#include<iostream>
#include<utility>
#include<queue>
using namespace std;

// Implement a node struct if you feel it necessary
struct  Node
{
  bool visited=false;
  vector<int> adj_list;
  /* data */
};


// Implement the graph class
class Graph
{
  public:
  Node *nodes;
  int no_of_vertices;
        Graph(int no_of_vertices, vector<pair<int,int> > edges){
          this->no_of_vertices=no_of_vertices;
          nodes = new Node[no_of_vertices];
          for(int i=0;i<no_of_vertices;i++){
            nodes[i].visited=false;
          }
          for(int i=0;i<edges.size();i++){
            nodes[edges[i].first].adj_list.push_back(edges[i].second);
            nodes[edges[i].second].adj_list.push_back(edges[i].first);
          }
        };
        void clear_visited(){
          for(int i=0;i<no_of_vertices;i++){
            nodes[i].visited=false;
          }
        };
};


void bfs(Graph g, int source,unordered_map<int, int>& parent)
{
  parent[source]=-1;
  g.nodes[source].visited=true;
  queue<int> q;
  q.push(source);
  while(!q.empty()){
    int u=q.front();
    q.pop();
    for (auto i: g.nodes[u].adj_list){
       if (g.nodes[i].visited==false){
         g.nodes[i].visited=true;
       
         parent[i]=u;
       
         q.push(i);
       }
    }
  }
};
