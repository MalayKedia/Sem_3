#include <fstream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tree.h"

/* You should NOT modify anything in this file.
 * Read the file "tree.h" for your tasks, and do them in files "encode_tree.cpp"
 * and "decode_tree.cpp". This file tests your code.
 * */

namespace tester {
    void write_to_file(std::string f_name, std::string encoded);
    std::string read_from_file(std::string f_name);
    template <size_t N> bool compare_fixed_trees(
                                std::shared_ptr<node_t> root1, 
                                std::shared_ptr<node_t> root2);
    bool compare_n_ary_trees(std::shared_ptr<node_t> root1, 
                                std::shared_ptr<node_t> root2);
    bool compare_trees(std::shared_ptr<node_t> root1, 
                                std::shared_ptr<node_t> root2);
    bool test_encoding(std::shared_ptr<node_t> root);
    template <size_t N> std::shared_ptr<node_t> read_fixed_testcase(
                                std::ifstream &f_in);
    std::shared_ptr<node_t> read_n_ary_testcase(std::ifstream &f_in);
    std::shared_ptr<node_t> read_testcase(std::string f_name);
};

void tester::write_to_file(std::string f_name, std::string encoded) {
    std::ofstream f_out(f_name);
    f_out << encoded << std::endl;
    f_out.close();
    return;
}

std::string tester::read_from_file(std::string f_name) {
    std::ifstream f_in(f_name);
    std::string encoded;
    std::getline(f_in, encoded);
    f_in.close();
    return encoded;
}

template <size_t N> bool tester::compare_fixed_trees(
    std::shared_ptr<node_t> root1, std::shared_ptr<node_t> root2) {
    if (!root1) return !root2;
    if (root1 == root2 || root1->val != root2->val) return false;
    
    std::shared_ptr<fixed_node_t<N>> __root1 = 
        std::dynamic_pointer_cast<fixed_node_t<N>>(root1);
    std::shared_ptr<fixed_node_t<N>> __root2 = 
        std::dynamic_pointer_cast<fixed_node_t<N>>(root2);
    for (size_t i = 0; i < N; i++) {
        if (!tester::compare_fixed_trees<N>(
            __root1->children[i], __root2->children[i])) return false;
    }
    return true;
}

bool tester::compare_n_ary_trees(std::shared_ptr<node_t> root1, 
                                    std::shared_ptr<node_t> root2) {
    if (!root1) return !root2;
    if (root1 == root2 || root1->val != root2->val) return false;
    std::shared_ptr<n_ary_node_t> __root1 = 
        std::dynamic_pointer_cast<n_ary_node_t>(root1);
    std::shared_ptr<n_ary_node_t> __root2 = 
        std::dynamic_pointer_cast<n_ary_node_t>(root2);
    if (__root1->children.size() != __root2->children.size()) return false;
    for (size_t i = 0; i < __root1->children.size(); i++) {
        if (!tester::compare_n_ary_trees(
            __root1->children[i], __root2->children[i])) return false;
    }
    return true;
}

bool tester::compare_trees(std::shared_ptr<node_t> root1, 
                                std::shared_ptr<node_t> root2) {
    if (!root1 || !root2 || (root1 == root2)) return false;
    if (std::dynamic_pointer_cast<n_ary_node_t>(root1)) {
        if (!std::dynamic_pointer_cast<n_ary_node_t>(root2)) return false;
        return tester::compare_n_ary_trees(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<1>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<1>>(root2)) return false;
        return tester::compare_fixed_trees<1>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<2>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<2>>(root2)) return false;
        return tester::compare_fixed_trees<2>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<3>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<3>>(root2)) return false;
        return tester::compare_fixed_trees<3>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<4>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<4>>(root2)) return false;
        return tester::compare_fixed_trees<4>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<5>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<5>>(root2)) return false;
        return tester::compare_fixed_trees<5>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<6>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<6>>(root2)) return false;
        return tester::compare_fixed_trees<6>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<7>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<7>>(root2)) return false;
        return tester::compare_fixed_trees<7>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<8>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<8>>(root2)) return false;
        return tester::compare_fixed_trees<8>(root1, root2);
    } else if (std::dynamic_pointer_cast<fixed_node_t<9>>(root1)) {
        if (!std::dynamic_pointer_cast<fixed_node_t<9>>(root2)) return false;
        return tester::compare_fixed_trees<9>(root1, root2);
    } else {
        return false;
    }
}

bool tester::test_encoding(std::shared_ptr<node_t> root) {
    if (!root) return false;
    int status;
    if (fork() == 0) {
        std::string encoded = encode_tree(root);
        tester::write_to_file("tmp.txt", encoded);
        exit(0);
    }
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status)) return false;
    if (fork() == 0) {
        std::string encoded = tester::read_from_file("tmp.txt");
        std::shared_ptr<node_t> __root = decode_tree(encoded);
        exit(1 - tester::compare_trees(root, __root));
    }
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status)) return false;
    return true;
}

template <size_t N> std::shared_ptr<node_t> tester::read_fixed_testcase(
                                std::ifstream &f_in) {
    std::string line;
    std::getline(f_in, line);
    if (line == "NULL") return nullptr;
    std::shared_ptr<fixed_node_t<N>> root = std::make_shared<fixed_node_t<N>>();
    root->val = std::stol(line);
    for (size_t i = 0; i < N; i++) {
        root->children[i] = tester::read_fixed_testcase<N>(f_in);
    }
    return std::dynamic_pointer_cast<node_t>(root);
}

std::shared_ptr<node_t> tester::read_n_ary_testcase(std::ifstream &f_in) {
    std::string line;
    std::getline(f_in, line);
    std::shared_ptr<n_ary_node_t> root = std::make_shared<n_ary_node_t>();
    root->val = std::stol(line);
    std::getline(f_in, line);
    for (size_t i = 0; i < std::stoul(line); i++) {
        root->children.push_back(tester::read_n_ary_testcase(f_in));
    }
    return std::dynamic_pointer_cast<node_t>(root);
}

std::shared_ptr<node_t> tester::read_testcase(std::string f_name) {
    std::ifstream f_in(f_name);
    if (!f_in) return nullptr;
    std::string line;
    std::getline(f_in, line);
    std::shared_ptr<node_t> root = nullptr;
    switch(std::stoul(line)) {
    case 0: root = tester::read_n_ary_testcase(f_in); break;
    case 1: root = tester::read_fixed_testcase<1>(f_in); break;
    case 2: root = tester::read_fixed_testcase<2>(f_in); break;
    case 3: root = tester::read_fixed_testcase<3>(f_in); break;
    case 4: root = tester::read_fixed_testcase<4>(f_in); break;
    case 5: root = tester::read_fixed_testcase<5>(f_in); break;
    case 6: root = tester::read_fixed_testcase<6>(f_in); break;
    case 7: root = tester::read_fixed_testcase<7>(f_in); break;
    case 8: root = tester::read_fixed_testcase<8>(f_in); break;
    case 9: root = tester::read_fixed_testcase<9>(f_in); break;
    }
    f_in.close();
    return root;
}

int main(void) {
    int score = 0;
    if (tester::test_encoding(tester::read_testcase("testcases/one.txt"))) {
        score++;
        std::cout << "Testcase 1 passed" << std::endl;
    } else {
        std::cout << "Testcase 1 failed" << std::endl;
    }
    if (tester::test_encoding(tester::read_testcase("testcases/two.txt"))) {
        score++;
        std::cout << "Testcase 2 passed" << std::endl;
    } else {
        std::cout << "Testcase 2 failed" << std::endl;
    }
    if (tester::test_encoding(tester::read_testcase("testcases/three.txt"))) {
        score++;
        std::cout << "Testcase 3 passed" << std::endl;
    } else {
        std::cout << "Testcase 3 failed" << std::endl;
    }
    if (fork() == 0) {
        char** args = new char * [3];
        args[0] = "rm";
        args[1] = "tmp.txt";
        args[2] = NULL;
        execvp((char const*)args[0], (char* const*)args);
        delete [] args;
        exit(0);
    }
    wait(NULL);
    std::cout << "RESULTS: " << score << " / 3" << std::endl;
    return 0;
}