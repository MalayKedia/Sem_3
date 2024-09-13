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
    heap_t<std::shared_ptr<struct list_node_t<T>>, Compare> heap;
    for (auto& list : lists) {
        if (list) {
            heap.push(list);
        }
    }
    std::shared_ptr<struct list_node_t<T>> head = nullptr;
    std::shared_ptr<struct list_node_t<T>> ptr = nullptr;
    while (!heap.empty()) {
        auto node = heap.top();
        heap.pop();
        if (node->next) {
            heap.push(node->next);
        }
        if (!head) {
            head = std::make_shared<struct list_node_t<T>>(*node);
            ptr = head;
        } else {
            ptr->next = std::make_shared<struct list_node_t<T>>(*node);
            ptr->next->prev = head;
            ptr = ptr->next;
        }
    }
    return head;
    // End TODO
}
