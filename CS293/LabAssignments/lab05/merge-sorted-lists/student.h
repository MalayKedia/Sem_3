#include <memory>
#include <string>

#include "list.h"
#pragma once

struct student_t {
    // Do NOT modify this structure.
    std::string name = "";
    size_t roll_no = 0;
    double height = 0.0;

    student_t() = default;
    student_t(const std::string& new_name, size_t roll, double ht)
        : name(new_name), roll_no(roll), height(ht) {}
    ~student_t() = default;
};

/* You should NOT add ANY other includes in this file.
 * Do not add `using namespace std;` in header files as it is a bad practice.
 *
 * You have students of multiple classes, standing for the morning prayer.
 * Each class has a list of students standing in a line, sorted by their
 * heights, such that the shortest student is at the front and the tallest
 * student is at the back.
 *
 * You are to merge the lines into a single long line, with a similar ordering.
 * The function `merge_sorted_lists` should return a single linked list which
 * is sorted similar to the input lists, is in file `merge-sorted-lists.h`.
 * But, it requires a comparator class as its template.
 *
 * You are to implement the comparator class `compare_by_heights` below.
 * Note that comp(a, b) should return true iff `a` is shorter than `b`.
 * Also, this is the comparator that is going to be used in the min-heap,
 * when called in function `merge_sorted_lists`. Think about what structures
 * you want to store in the heap in your implementation in `merge_sorted_lists`
 * and implement the comparator with the appropriate `bool operator ()`.
 *
 * Go to file `heap.h` to see an more about comparator classes in C++ AND to
 * implement the class `heap_t`, a min-heap data structure used in this task.
 * 
 * Note that your task involves completing this class as well as
 * completing the tasks in files "heap.h" and "merge-sorted-lists.h".
 */

class compare_by_heights {
public:
    // TODO: Write your code here.
    
     // End TODO
};

