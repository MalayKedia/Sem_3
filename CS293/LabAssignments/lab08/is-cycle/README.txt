************************************ Problem (Exam 2023) ************************************ 

DO NOT CHANGE ANYTHING IN FILES EXCEPT isCyclePresent.cpp AS WE WILL ONLY TAKE YOUR isCyclePresent.cpp FILE FOR EVALUATION.


In this problem, you have to find whether a given undirected graph contains a cycle or not.
Recall, that a cycle is a path v1, ...., vn such that v1, ...., vn-1 is a simple path and v1 = vn. ( Direct from the slides :) )

1. Complete the class function isCyclePresent() of class Graph in isCyclePresent.cpp file. 
2. The function isCyclePresent() takes no arguments and returns a boolean value. 
   It returns true if the graph contains a cycle and false otherwise.
3. Important : Note that graph can be disconnected as well. (see testcase 6)
4. You have been provided with 6 sample testcases (inputs and outputs directory). 
   These testcases by no means cover all possible testcases. 
   You are encouraged to write your own testcases to test your code.
5. Check for all possible corner cases.
6. The I/O part has been already done in main.cpp file. 
   Input format:  First line contains one integer e, denoting the number of edges in the graph.
                  Next e lines contain two integers u and v, denoting an edge between u and v.
   Output format: If the graph contains a cycle, print "Cycle is present" (without quotes) in a single line 
                  and if the graph does not contain a cycle, print "Cycle is not present" (without quotes) in a single line.
7. Note that there is no constraint on the number of nodes or edges in the graph. 
8. To auto-test your code on given test cases, run the following command:
   make test

Note:
We are looking for solutions that have both efficient running time and minimal auxiliary space complexity.
