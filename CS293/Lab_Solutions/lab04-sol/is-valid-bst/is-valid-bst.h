#include "tree.h"

/**
 * @brief Check if a binary tree is a valid binary search tree
 * 
 * @param root The root of the binary tree
 * @return true If the binary tree is a valid binary search tree
 * @return false If the binary tree is not a valid binary search tree
 *
 * Your task is to check if the tree indexing all the values of type T is a
 * valid binary search tree, which implies that for each node in the tree,
 * all the values in its left subtree are less than the value of that node, and
 * all the values in its right subtree are greater than the value of that node.
 *
 * You can add helper functions or data structures, but you should not modify
 * the existing function signature. Note that this requiress knowledge about
 * the concpet of smart pointers in C++.
 *
 * Lastly, do not add `using namespace std;` as it is a bad practice.
 * The full problem involves the above task AND the task in the file
 * "employee.h". You should complete both tasks.
 */

namespace bst_check {
    template <std::totally_ordered T>
        bool validate_range_subtree(std::shared_ptr<struct node_t<T>> root,
                                    T min_val, T max_val);
    template <std::totally_ordered T>
        bool validate_min_subtree(std::shared_ptr<struct node_t<T>> root,
                                    T min_val);
    template <std::totally_ordered T>
        bool validate_max_subtree(std::shared_ptr<struct node_t<T>> root,
                                    T max_val);
};

template <std::totally_ordered T>
bool bst_check::validate_range_subtree(std::shared_ptr<struct node_t<T>> root, 
                                        T min_val, T max_val) {
    if (!root) {
        return true;
    }
    if (root->value <= min_val || root->value >= max_val) {
        return false;
    }
    return validate_range_subtree(root->left_child, min_val, root->value) &&
            validate_range_subtree(root->right_child, root->value, max_val);
}

template <std::totally_ordered T>
bool bst_check::validate_min_subtree(std::shared_ptr<struct node_t<T>> root, 
                                        T min_val) {
    if (!root) {
        return true;
    }
    if (root->value <= min_val) {
        return false;
    }
    return validate_range_subtree(root->left_child, min_val, root->value) &&
            validate_min_subtree(root->right_child, root->value);
}

template <std::totally_ordered T>
bool bst_check::validate_max_subtree(std::shared_ptr<struct node_t<T>> root, 
                                        T max_val) {
    if (!root) {
        return true;
    }
    if (root->value >= max_val) {
        return false;
    }
    return validate_max_subtree(root->left_child, root->value) &&
            validate_range_subtree(root->right_child, root->value, max_val);
}

template <std::totally_ordered T>
bool is_valid_bst(std::shared_ptr<struct node_t<T>> root) {
    // TODO: Write your code here
    if (!root) {
        return true;
    }
    return bst_check::validate_max_subtree(root->left_child, root->value) &&
            bst_check::validate_min_subtree(root->right_child, root->value);
    // End TODO
}
