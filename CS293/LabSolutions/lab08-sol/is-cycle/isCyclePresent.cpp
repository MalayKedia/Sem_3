#include "graph.h"

// Implement this function to check if there is a cycle present in the graph
bool Graph::isCyclePresent(){
    int n = nodes.size();

    // if no nodes, no cycle
    if(n == 0) 
        return false;


    /*** We will use BFS to check for cycles ***/

    // need to keep track of parent of each node
    std::map<int, int> parent;
    // need to keep track of visited nodes
    std::map<int, bool> visited;


    // initialize all nodes as unvisited and parent as -1
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        visited[it->first] = false;
        parent[it->first] = -1;
    }

    // search through all connected components of given graph
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        if(!visited[it->first]){
            std::queue<int> q;
            q.push(it->first);
            visited[it->first] = true;

            // while queue is not empty
            while(!q.empty()){
                // get the front node
                int curr = q.front();
                q.pop();

                // for all neighbours of curr
                for(unsigned long i = 0; i < nodes[curr]->adj.size(); i++){
                    int neighbour = nodes[curr]->adj[i];

                    // if neighbour is not visited, add it to queue
                    if(!visited[neighbour]){
                        q.push(neighbour);
                        visited[neighbour] = true;
                        parent[neighbour] = curr;
                    }
                    // if neighbour is visited and is not parent of curr, cycle is present
                    else if(parent[curr] != neighbour)
                        return true;

                }
            }
        }
    }
    
    // if no cycle found, return false
    return false;
    
}
