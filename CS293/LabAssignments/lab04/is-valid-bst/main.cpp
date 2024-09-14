#include "is-valid-bst.h"
#include "employee.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define NUM_TESTCASES 3

// You should NOT modify ANYTHING in this file
// This is just a test file to check the correctness of your code.

namespace test_code {
    std::shared_ptr<struct node_t<struct employee_t>> 
        read_employee_tree(std::string &filename);
    std::vector<std::shared_ptr<struct node_t<struct employee_t>>>
        read_employee_tree_level(std::string &line);
    std::vector<std::shared_ptr<struct node_t<struct employee_t>>> 
        update_next_level(std::string &line,
                std::vector<std::shared_ptr<struct node_t<struct employee_t>>>
                                                                &this_level);
    bool execute_testcase(std::string testcase_name);
};

std::vector<std::shared_ptr<struct node_t<struct employee_t>>>
test_code::read_employee_tree_level(std::string &line) {
    std::vector<std::shared_ptr<struct node_t<struct employee_t>>> level;
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        if (token.empty()) {
            continue;
        }
        if (token == "null") {
            level.push_back(nullptr);
            continue;
        } 
        std::istringstream token_iss(token);
        std::string name, department_name, id_in_department, job_title, salary;
        std::getline(token_iss, name, ',');
        std::getline(token_iss, department_name, ',');
        std::getline(token_iss, id_in_department, ',');
        std::getline(token_iss, job_title, ',');
        std::getline(token_iss, salary, ',');

        level.push_back(std::make_shared<struct node_t<struct employee_t>>(
                employee_t{name, department_name, std::stol(id_in_department), 
                            job_title, std::stod(salary)}));
    }
    return level;
}

std::vector<std::shared_ptr<struct node_t<struct employee_t>>> 
test_code::update_next_level(std::string &line,
        std::vector<std::shared_ptr<struct node_t<struct employee_t>>> 
                                                        &this_level) {
    std::vector<std::shared_ptr<struct node_t<struct employee_t>>> next_level;
    int index = 0;
    for (auto node : test_code::read_employee_tree_level(line)) {
        if (!node) {
            index++;
            continue;
        }
        if (index % 2 == 0) {
            this_level[index / 2]->left_child = node;
            node->parent = this_level[index / 2];
        } else {
            this_level[index / 2]->right_child = node;
            node->parent = this_level[index / 2];
        }
        next_level.push_back(node);
        index++;
    }
    return next_level;
}

std::shared_ptr<struct node_t<struct employee_t>> 
test_code::read_employee_tree(std::string &input_file) {
    std::ifstream read_file(input_file);
    if (!read_file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::shared_ptr<struct node_t<struct employee_t>> root;
    std::vector<std::shared_ptr<struct node_t<struct employee_t>>> this_level;
    std::string line;
    std::getline(read_file, line);
    this_level = read_employee_tree_level(line);
    root = this_level[0];
    while (std::getline(read_file, line)) {
        this_level = update_next_level(line, this_level);
    }
    return root;
}

bool test_code::execute_testcase(std::string testcase_name) {
    std::string input_file = "testcases/" + testcase_name + ".txt";
    std::string expected_file = "expected/" + testcase_name + ".txt";
    std::shared_ptr<struct node_t<struct employee_t>> root = 
        test_code::read_employee_tree(input_file);
    std::ifstream expected_read(expected_file);
    if (!expected_read.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    bool result = is_valid_bst(root);
    bool expected_result;
    expected_read >> std::boolalpha >> expected_result;
    return result == expected_result;
}

int main(void) {
    std::vector<std::string> testcases = {
        "testcase1",
        "testcase2",
        "testcase3",
    };
    int num_passed = 0;
    for (int i = 0; i < NUM_TESTCASES; i++) {
        if (test_code::execute_testcase(testcases[i])) {
            std::cout << "Testcase " << i + 1 << " passed" << std::endl;
            num_passed++;
        } else {
            std::cout << "Testcase " << i + 1 << " failed" << std::endl;
        }
    }
    std::cout << "RESULTS: " << num_passed << " / " << NUM_TESTCASES << 
        " passed" << std::endl;
    return 0;
}
