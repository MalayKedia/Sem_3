#include <compare>
#include <concepts>
#include <memory>
#pragma once

/* This file defines the structure of a node in a binary tree.
 * Your task is present in the files "employee.h", and "is_valid_bst.h".
 * You should complete both tasks, without modifying anything in this file.
 *
 * BONUS: If you change "weak_ptr" to "shared_ptr" in the member "parent",
 * what do you think will happen? Why?
 */

template <std::totally_ordered T>
struct node_t {
    T value;
    std::shared_ptr<struct node_t> left_child = nullptr;
    std::shared_ptr<struct node_t> right_child = nullptr;
    std::weak_ptr<struct node_t> parent;

    node_t() = default;
    node_t(T val) : value(val) {}
    ~node_t() = default;
};
