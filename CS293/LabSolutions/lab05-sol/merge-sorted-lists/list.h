#include <memory>
#pragma once

// You should NOT modify ANYTHING in this file.
// This is the definition of the struct list_node_t.
// That is, doubly linked list node.
// In case you do not know, the purpose of `#pragma once` is to ensure that
// this file is included only once in the compilation of a source file
// even if it is included multiple times across multiple headers.
// Complete the tasks in files "heap.h", "student.h" and "merge-sorted-lists.h".

template <typename T>
struct list_node_t {
    T data;
    std::shared_ptr<list_node_t<T>> next = nullptr;
    std::weak_ptr<list_node_t<T>> prev;

    list_node_t() = default;
    list_node_t(const T& val) : data(val) {}
    ~list_node_t() = default;
};
