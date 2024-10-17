#include "graph.cpp"

void path_(vector<int>& path,unordered_map<int, int> &parent, int source, int destination);
void shortest_walk(Graph g,vector<int>&stations, vector<int>& path)
{
    path.push_back(stations[0]);
    for (int i=0;i<stations.size()-1;i++){
      unordered_map<int, int> parent;
      parent.clear();
      g.clear_visited();
      bfs(g,stations[i],parent);
     
      vector<int> temp;
      path_(temp,parent,stations[i],stations[i+1]);
      path.insert(path.end(),temp.begin(),temp.end());
    }
    return;
}

void path_(vector<int>& path,unordered_map<int, int> &parent, int source, int destination)
{

  vector<int> temp;
  int i=destination;
  while(i!=source){
   
    temp.push_back(i);
    i=parent[i];
  }
  for (size_t i = 0; i < temp.size(); i++)
  {
    path.push_back(temp[temp.size()-i-1]);
  }
  return;
}