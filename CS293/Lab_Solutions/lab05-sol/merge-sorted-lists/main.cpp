#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>

#include "heap.h"
#include "merge-sorted-lists.h"
#include "student.h"

// You should NOT modify ANYTHING in this file.
// The purpose of this is to test your code.
// Complete the tasks in files "heap.h", "student.h" and "merge-sorted-lists.h".

namespace test_cases {
    bool match_outputs(std::string file1, std::string file2);
    bool test_heap();
    std::shared_ptr<struct list_node_t<struct student_t>> read_list(
                                                        std::ifstream& input);
    bool test_merge_sorted_lists();
};

bool test_cases::match_outputs(std::string file1, std::string file2) {
    if (fork() == 0) {
        execlp("diff", "diff", "-Bw", file1.c_str(), file2.c_str(), NULL);
        exit(0);
    } else {
        int status;
        wait(&status);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    }
}

bool test_cases::test_heap() {
    std::ifstream input("testcases/heap.txt");
    std::ofstream output("outputs/heap.txt");
    if (!input.is_open()) {
        std::cerr << "Could not open testcases/heap.txt\n";
        return false;
    }
    if (!output.is_open()) {
        std::cerr << "Could not open outputs/heap.txt\n";
        return false;
    }
    class heap_t<int> heap;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "push") {
            int value;
            iss >> value;
            heap.push(value);
        } else if (command == "pop") {
            output << heap.pop() << '\n';
        } else if (command == "top") {
            output << heap.top() << '\n';
        } else if (command == "size") {
            output << heap.size() << '\n';
        } else if (command == "empty") {
            output << heap.empty() << '\n';
        } else if (command == "clear") {
            heap.clear();
        }
    }
    input.close();
    output.close();
    return test_cases::match_outputs("outputs/heap.txt", "expected/heap.txt");
}

std::shared_ptr<struct list_node_t<struct student_t>> test_cases::read_list(
                                                        std::ifstream& input) {
    std::shared_ptr<struct list_node_t<struct student_t>> head = nullptr;
    std::shared_ptr<struct list_node_t<struct student_t>> prev = nullptr;
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        struct student_t student;
        iss >> student.name >> student.roll_no >> student.height;
        std::shared_ptr<struct list_node_t<struct student_t>> node =
            std::make_shared<struct list_node_t<struct student_t>>(
                    list_node_t<struct student_t>(student));
        node->data = student;
        if (!head) {
            head = node;
        } else {
            prev->next = node;
            node->prev = prev;
        }
        prev = node;
    }
    return head;
}

bool test_cases::test_merge_sorted_lists() {
    std::ifstream ninth("testcases/ninth_class.txt");
    std::ifstream tenth("testcases/tenth_class.txt");
    std::ifstream eleventh("testcases/eleventh_class.txt");
    std::ifstream twelfth("testcases/twelfth_class.txt");
    std::ofstream output("outputs/merge_sorted_lists.txt");
    if (!ninth.is_open()) {
        std::cerr << "Could not open testcases/ninth_class.txt\n";
        return false;
    }
    if (!tenth.is_open()) {
        std::cerr << "Could not open testcases/tenth_class.txt\n";
        return false;
    }
    if (!eleventh.is_open()) {
        std::cerr << "Could not open testcases/eleventh_class.txt\n";
        return false;
    }
    if (!twelfth.is_open()) {
        std::cerr << "Could not open testcases/twelfth_class.txt\n";
        return false;
    }
    if (!output.is_open()) {
        std::cerr << "Could not open outputs/merge_sorted_lists.txt\n";
        return false;
    }
    std::vector<std::shared_ptr<struct list_node_t<struct student_t>>> classes;
    classes.push_back(test_cases::read_list(ninth));
    classes.push_back(test_cases::read_list(tenth));
    classes.push_back(test_cases::read_list(eleventh));
    classes.push_back(test_cases::read_list(twelfth));
    std::shared_ptr<struct list_node_t<struct student_t>> full_line = 
        merge_sorted_lists<struct student_t, class compare_by_heights>(classes);
    for (auto head = full_line; head != nullptr; head = head->next) {
        output << head->data.name << " " << head->data.roll_no << " " <<
            head->data.height << std::endl;
    }
    ninth.close();
    tenth.close();
    eleventh.close();
    twelfth.close();
    output.close();
    return test_cases::match_outputs("outputs/merge_sorted_lists.txt", 
                                    "expected/merge_sorted_lists.txt");
}

int main(void) {
    if (test_cases::test_heap()) {
        std::cout << "Min-Heap Testcase Passed" << std::endl;
    } else {
        std::cout << "Min-Heap Testcase Failed" << std::endl;
    }
    if (test_cases::test_merge_sorted_lists()) {
        std::cout << "Merge-Sorted-Lists Testcase Passed" << std::endl;
    } else {
        std::cout << "Merge-Sorted-Lists Testcase Failed" << std::endl;
    }
    return 0;
}
