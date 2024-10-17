Howdy fellas!

There is a tutorial problem called "find the shortest path to the destination
from the source, and all shortest paths". We expect you to solve this, but with
a twist. That is, we expect you to implement the templated class called
"optimum_path_querier", that computes the optimum paths from the source,
to all destinations; and, can return on query, a vector that represents a path 
from the source to the destination (query point), including both ends.

To find the optimum route given a method to add costs of routes to get costs of
net routes, we use Dijkstra's algorithm, a variant of BFS but with priority
queues instead of normal queues. Assuming that we want to minimize the costs,
we use a minheap, each element being the vertex and the cost to reach the same
from the starting point, which is passed as an argument. 

As and when we pop vertices from it, we look at all the neighbors of the popped 
vertices, just like in BFS; we push them alongwith the costs to reach them, 
as long as the costs to reach them are less than the existing costs to reach 
them (there is no point in pushing a path that is less optimum than what is 
already known). Note that the cost pushed to the heap alongwith the node is the 
net cost of the path joining the (optimum) path from start to the original node,
and the edge from the original node (popped) to this new node. 

Also, if a node has its cost already computed and it is encountered again, 
it is avoided. Specifically, when we push a sub-optimum path to the heap first 
and then discover a better path, we push the node again with the more optimum 
cost. When we pop that node first, the minheap property proves that we pop it 
with the optimum cost. When we pop it later on with the suboptimum cost, 
we ignore it, also making the algorithm efficient, resulting in a 
net time complexity of O(V + E log V).

We repeat this till the heap is empty. Naturally, we push the start node with
cost zero at the beginning, and maintain all costs to reach for nodes other than
the start, as infinity. If we want to maximize the cost (then it is not really
a cost, but still) then we keep the cost for the start node as infinity and the
costs for all other nodes initialized to zero. It is guaranteed that the cost
is numeric and is non-negative, though.

Your task is to implement this in the file "optimum_path.h". Account for both
cases -- to minimize the cost or to maximize it. The comparator is provided for
this exact reason -- the default value, Compare = std::less<Cost> is an 
indication that by default, we want to minimize the cost. It is guaranteed that
the type Compare is either this or std::greater<Cost>.

Note that the graph itself comprises of vertices that store values with them
(could represent node names), but have ID pre-determined by the indices
in which they exist in the vector passed as parameter during constructor.
An edge is a tuple of the start vertex, end vertex and the cost associated 
with it. Further, the graph uses adjacency-list (vector-based) storage of edges.

FUNCTIONAL PROGRAMMING ALERT!
The costs themselves are integers or floating points, but could very well
represent something else, like road widths (the more the merrier) or times to
reach the nodes (the less the better). To express this variance in associativity
better, we use a comparator. Further, costs may not add as such.

In the minimum road width case, we take the road width of a joint path as the 
minimum of the road widths of both paths, mimicing the reality of bottlenecks
in traffic due to narrow roads. In order to account for this call for 
flexibility, the constructor  to your graph has an object of type 
std::function (a lambda function) passed as a parameter.

std::function<<return_type>(<typed_parameters>)> is the c++ STL 
datatype for storing lambdas -- functions that can be created during runtime, 
can capture variables on creation and can be called to return a value anytime.
This is somewhat like function pointers; better put, this invokes the functional
paradigm in that we can pass procedures and return procedures around, via
higher-order functions. Except, this also involves object-oriented and
imperative programming paradigms (not just functional).

In one of the previous labs on priority queues, we worked on heaps that used
comparator classes. std::priority_queue allows such overloading, AND allows
its comparator to instead be of type std::function<bool(T, T)> where T is the
type of object stored in the priority_queue. In this case, you have the 
flexibility of constructing it with a lambda as comparator, the lambda being
defined during runtime. The (std::function) lambda object is created like this:
[<variables_from_environment_captured>](<typed_parameters>) {
    <the_implementation_with_return_value_of_appropriate_type>;
}; Read up more about lambdas if you can.

MORE ON TEMPLATES AND CONCEPTS
The cost of of type int or float, could represent path lengths (no. of hops
or weighted lengths) or other parameters too. To restrict the template class
type, we use the concept numeric defined above. The code will raise compilation
errors if we use some other datatype for "Cost". Read up more on concepts
and constraints in C++20. This also uses comparators, as mentioned above.

INFO ON TESTCASES
Further, as far as testcases and usage is concerned, you can assume that
the value of cost is ALWAYS non-negative (>= 0) and is less than INT_MAX.
Same for any node id: non-negative (>= 0), and it is always valid.
The graph is directed, with at most one edge per (start != end) pair.
These testcases are designed such that there is a unique answer (optimum)
but in events where there are multiple paths with same cost (that being the
optimum cost), then all are equally correct.

Your task is to implement the class "optimum_path_querier" (task 0) in file
"shortest_path.h" AND to implement these tasks in file "optimal_paths.cpp",
all three of which return an object of type "optimum_path_querier":

TASK 1 -- PLAIN SHORTEST PATHS
Yep, just that. Since each node is a junction, we store names as strings.
The graph is a template class; but here, we talk just about number of hops
as the path lengths. So, all weights are 1 (unweighted practically).
Return a class such that, we can query from any node (junction) in the city
and we will get the shortest route from the town hall to that city.

TASK 2 -- WIDEST ROUTES
Uggh! The roads in the city are narrow! Here, we do not care about travel 
time, number of junctions in routes -- but we want the route from the town hall
to the destination (queried from the returned object) that computes the 
route with the widest value of the narrowest road on the path. Here,
the Cost parameter refers to the road width. We want to minimize narrow road
bottlenecks. Do you see the use of the comparator class here?

TASK 3 -- LEAST TIME ROUTES
Here's a twist: each road has a travel time. Further, the junctions have
wait times associated with them. Thankfully, the templated class has a measure
to accomodate this: the lambda passed as a parameter itself has a parameter
of type "Value"; Here, the value is a pair of a string (junction name) and
a wait time. With this and the class implemented, return an object that on
querying, returns the route with least travel time from town hall to the
destination. Note that the wait times of town hall and destination themselves
are not to be considered; take care of this when you work on the
templated class.