#include "list.h"
#include "heap.h"

/* You should NOT add ANY other includes in this file.
 * Do not add `using namespace std;` in header files as it is a bad practice.
 *
 * Your task is to implement the function `merge_sorted_lists` below.
 * You are given a vector of doubly linked lists. You should return
 * a single doubly linked list which contains all the elements of all
 * the lists in a sorted order, according to comparator `Compare`.
 * It is guaranteed that for any node `a` in the list, if `b` is the next
 * node, then a->data.height <= b->data.height.
 * Read up more on comparators in C++, in file "heap.h".
 * 
 * Note that your task involves completing this function as well as
 * completing the tasks in files "student.h" and "heap.h".
 */

template <typename T, class Compare>
std::shared_ptr<struct list_node_t<T>> merge_sorted_lists(
        std::vector<std::shared_ptr<struct list_node_t<T>>> lists) {
    // TODO: Write your code here
    return nullptr; // dummy return
    // End TODO
}
