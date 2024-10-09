#include "tree.h"

/* You should NOT add ANY other includes to this file.
 * Your task is to implement the "encode_tree" function as described
 * in the file "tree.h". Read the instructions there.
 * */

namespace encoder {
    std::string encode_n_ary_tree(std::shared_ptr<node_t> root);
    template <size_t N> std::string encode_fixed_tree(
                                    std::shared_ptr<node_t> root);
    template <size_t N> 
    typename std::enable_if<std::is_lteq(N <=> MAX_SIZE), std::string>::type
    encode_fixed_tree_tester(std::shared_ptr<node_t> root);
    template <size_t N> 
    typename std::enable_if<std::is_gt(N <=> MAX_SIZE), std::string>::type
    encode_fixed_tree_tester(std::shared_ptr<node_t> root);
};

std::string encoder::encode_n_ary_tree(std::shared_ptr<node_t> root) {
    std::string result = "[" + std::to_string(root->val);
    std::shared_ptr<n_ary_node_t> __root = 
            std::dynamic_pointer_cast<n_ary_node_t>(root);
    for (std::shared_ptr<struct node_t> child : __root->children) {
        result += encoder::encode_n_ary_tree(child);
    }
    result += "]";
    return result;
}

template <size_t N> std::string encoder::encode_fixed_tree(
                                    std::shared_ptr<node_t> root) {
    if (root == nullptr) return "(NULL)";
    std::shared_ptr<fixed_node_t<N>> __root = 
            std::dynamic_pointer_cast<fixed_node_t<N>>(root);
    std::string result = "(" + std::to_string(root->val);
    for (std::shared_ptr<struct node_t> child : __root->children)
    {
        result += encoder::encode_fixed_tree<N>(child);
    }
    result += ")";
    return result;
}

template <size_t N> 
typename std::enable_if<std::is_lteq(N <=> MAX_SIZE), std::string>::type 
encoder::encode_fixed_tree_tester(std::shared_ptr<node_t> root) {
    if (std::dynamic_pointer_cast<fixed_node_t<N>>(root) == nullptr) {
        return encoder::encode_fixed_tree_tester<N + 1>(root);
    } else {
        return std::to_string(N) + encoder::encode_fixed_tree<N>(root);
    }
}

template <size_t N> 
typename std::enable_if<std::is_gt(N <=> MAX_SIZE), std::string>::type
encoder::encode_fixed_tree_tester(std::shared_ptr<node_t> root) {
    throw std::invalid_argument("Invalid tree");
}

std::string encode_tree(std::shared_ptr<node_t> root) {
    // TODO: Write your code here
    if (std::dynamic_pointer_cast<n_ary_node_t>(root)) {
        return encoder::encode_n_ary_tree(root);
    } else {
        return encoder::encode_fixed_tree_tester<1>(root);
    }
    // End TODO
}