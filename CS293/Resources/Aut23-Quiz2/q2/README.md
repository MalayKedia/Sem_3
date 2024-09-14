# How the STL sorts: Introsort

The STL uses a sorting algorithm called Introsort. Introsort is a hybrid sorting algorithm that uses three sorting algorithms - quicksort, heapsort and insertion sort - to sort a list of elements. Your task is to implement the fastest version of introsort that you can.

Introsort is a recursive algorithm like quicksort - it partitions, and sorts the smaller instances recursively. This has the obvious drawback that the recursion depth at some point may be linear in the worst case, like quicksort. To avoid this, introsort uses a heuristic to **switch to heapsort** when the recursion depth exceeds a certain threshold. This ensures that the worst case time complexity of introsort is O(nlogn). There is another optimization: it switches to **insertion sort** when the number of elements to be sorted is small enough (in practice, smaller than 16). This is because insertion sort is faster than quicksort for small lists.

Your task is to implement the heapsort algorithm and the partition (same as that used in quicksort) auxiliary function. You may consider any element as the pivot for the paritioning. Your task also is to identify the value of threshold that produces best performance. 


## Running instructions:

Write the code for introsort in ```introsort.cpp```, the code for heapsort in ```hsort.cpp``` and the code for partition in ```partition.cpp```. Function signatures are provided in the respective files. Please do not change any other file. The sorting must be in-place (you must modify the same array) and you must not use any extra memory (other than due to the recursion stack).

You are not permitted to use any STL modules other than those already included in the corresponding files.

To test, simply run ```make test```. This will run your code on a few small examples. To manually test, run ```make```, and run the executable as ```./exec <input file> <output file>```. The input file contains the elements to be sorted, one on each line. The output file contains the elements of the vector after the call to introsort (ideally, it should contain a sorted list of the elements), one element on each line.

To generate large file with random numbers, use ```make random```.
