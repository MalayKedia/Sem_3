#include "shortest_walk.cpp"

int main()
{
    int part;
    cin >> part;
    int no_of_vertices, no_of_edges;
    // reading the number of vertices and edges 
    cin >> no_of_vertices >> no_of_edges;
    // reading the edges
    vector<pair<int,int> > edges;
    for(int i = 0; i < no_of_edges; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back(make_pair(u,v));
    }
    // creating the graph
    Graph g(no_of_vertices, edges);
    unordered_map<int, int> parent;
    vector<int> stations;
    int no_of_stations;
    int source;
    vector<int> path_;
    // reading the source vertex
    switch(part)
    {
    case 1:
        /* code */
        
        cin >> source;
        // calling the bfs function
        
        bfs(g, source,parent);
        // printing parent array
        for(int i=0;i<no_of_vertices;i++)
        {
        cout << parent[i] << endl;
        }
        break;
    case 2:
        
        cin >> no_of_stations;
        for(int i = 0; i < no_of_stations; i++)
        {
        int station;
        cin >> station;
        stations.push_back(station);
        }
        
        shortest_walk(g, stations, path_);
        for(int i = 0; i < path_.size(); i++)
        {
            cout << path_[i] << " ";
        }
    default:
        break;
    }
}