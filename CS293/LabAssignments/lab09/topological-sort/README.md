# Graph DFS and Topological Sort

An implementation of the Graph class has been provided in [graph.cpp](./graph.cpp).
You can check the [graph.h](./graph.h) for the abstraction of the class.

The visited boolean in the Graph node is false by default. You can use that as you
wish. To set the visited boolean back to false, call resetVisit function.

The adj in GraphNode is the adjacency list for each node. It contains pairs of values
which indicate the label of the node (first value) and the weight of the edge (second
value). The weights do not matter for this lab. All edges are directed.

The nodes map present in the Graph class is a mapping from the node label to a pointer
to that node. The stack S is a structure to store the output of topological sort.

The addNode, addNgbr and addEdge functions do what they say.

Your task is to implement the function topoSort. This function should do a topological
sort of the given Graph. Topological ordering of a directed graph is a linear ordering
of its vertices such that for every directed edge u->v from vertex u to vertex v, u comes
before v in the ordering.

The output should be stored into the stack such that the print function can
appropriately print it. You can use the dfs function that has been added to
the class, but you cannot add/remove any functions from the Graph class.

To check your implementation, run "make". There could be more than one correct
topological sort outputs in general, but assume that the input will be such that
all adjacency lists will have labels in increasing order.

Input format:
N
E
x1 y1
x2 y2
.
.
xE yE

Output format is the topologically sorted node labels.


Look at course page for DFS slides. It has algorithms for DFS and topological sort.