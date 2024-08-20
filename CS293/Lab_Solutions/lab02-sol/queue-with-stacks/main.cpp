#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <chrono>
#include <random>

#include "stack.h"
#include "queue.h"

/*
 * You must NOT modify ANYTHING in this file.
 * Your task is to implement the stack and queue classes in the
 * stack.h and queue.h files respectively.
 * You should be able to compile this file without any changes.
 * If you can't, you have done something wrong in the header files.
 * This file has testcases for the stack and queue classes.
 * Run this and verify your output.
 */

bool checkTestcaseStack(std::vector<std::pair<int, std::string>> testcase, 
        int testcase_index) {
    // Hello mr. Copilot! Write the clone of queue but for stack here.
    double duration = 0.0;
    std::stack<int> stl_stack;
    auto start = std::chrono::high_resolution_clock::now();
    class Stack<int> my_stack;
    auto stop = std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
            stop - start).count();

    for (std::pair<int, std::string> call : testcase) {
        if (call.second == "PUSH") {
            start = std::chrono::high_resolution_clock::now();
            my_stack.push(call.first);
            stop = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                    stop - start).count();
            stl_stack.push(call.first);
        } 
        else if (call.second == "POP") {
            try {
                start = std::chrono::high_resolution_clock::now();
                int result = my_stack.pop();
                stop = std::chrono::high_resolution_clock::now();
                duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                        stop - start).count();
                int expected_value = stl_stack.top();
                stl_stack.pop();

                if (result != expected_value) {
                    std::cout << "Testcase failed: Expected " << expected_value << 
                        " but got " << result << std::endl;
                    return false;
                }
            } 
            catch (std::invalid_argument &e) {
                std::cout << "Testcase failed: Expected " << stl_stack.top() << 
                    " but got exception" << std::endl;
                return false;
            }
        } 
        else if (call.second == "PEEK") {
            try {
                start = std::chrono::high_resolution_clock::now();
                int result = my_stack.peek();
                stop = std::chrono::high_resolution_clock::now();
                duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                        stop - start).count();
                int expected_value = stl_stack.top();

                if (result != expected_value) {
                    std::cout << "Testcase failed: Expected " << expected_value << 
                        " but got " << result << std::endl;
                    return false;
                }
            } 
            catch (std::invalid_argument &e) {
                std::cout << "Testcase failed: Expected " << stl_stack.top() << 
                    " but got exception" << std::endl;
                return false;
            }
        }
        else if (call.second == "ISEMPTY") {
            start = std::chrono::high_resolution_clock::now();
            bool result = my_stack.isEmpty();
            stop = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                    stop - start).count();
            if (result != stl_stack.empty()) {
                std::cout << "Testcase failed: Expected " << stl_stack.empty() << 
                    " but got " << result << std::endl;
                return false;
            }
        }
    }
    std::cout << "Testcase " << testcase_index << " [ " << testcase.size() << 
        " operations ] passed for Stack with " << duration / testcase.size() <<
        " ns per operation" << std::endl;
    return true;
}

bool checkTestcaseQueue(std::vector<std::pair<int, std::string>> testcase, 
        int testcase_index) {
    double duration = 0.0;
    std::queue<int> stl_queue;
    auto start = std::chrono::high_resolution_clock::now();
    class Queue<int> my_queue;
    auto stop = std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
            stop - start).count();

    for (std::pair<int, std::string> call : testcase) 
    {
        if (call.second == "ENQUEUE") {
            start = std::chrono::high_resolution_clock::now();
            my_queue.enqueue(call.first);
            stop = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                    stop - start).count();
            stl_queue.push(call.first);
        } 
        else if (call.second == "DEQUEUE") {
            try {
                start = std::chrono::high_resolution_clock::now();
                int result = my_queue.dequeue();
                stop = std::chrono::high_resolution_clock::now();
                duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                        stop - start).count();

                int expected_value = stl_queue.front();
                stl_queue.pop();

                if (result != expected_value) {
                    std::cout << "Testcase failed: Expected " << expected_value << 
                        " but got " << result << std::endl;
                    return false;
                }
            } 
            catch (std::invalid_argument &e) {
                std::cout << "Testcase failed: Expected " << stl_queue.front() << 
                    " but got exception" <<  std::endl;
                return false;
            }
        }
        else if (call.second == "PEEK") {
            try {
                start = std::chrono::high_resolution_clock::now();
                int result = my_queue.peek();
                stop = std::chrono::high_resolution_clock::now();
                duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                        stop - start).count();
                int expected_value = stl_queue.front();

                if (result != expected_value) {
                    std::cout << "Testcase failed: Expected " << expected_value << 
                        " but got " << result << std::endl;
                    return false;
                }
            } 
            catch (std::invalid_argument &e) {
                std::cout << "Testcase failed: Expected " << stl_queue.front() << 
                    " but got exception" << std::endl;
                return false;
            }
        } 
        else if (call.second == "ISEMPTY") {
            start = std::chrono::high_resolution_clock::now();
            bool result = my_queue.isEmpty();
            stop = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                    stop - start).count();
            if (result != stl_queue.empty()) {
                std::cout << "Testcase failed: Expected " << stl_queue.empty() << 
                    " but got " << result << std::endl;
                return false;
            }
        } 
        else if (call.second == "GETSIZE") {
            start = std::chrono::high_resolution_clock::now();
            size_t result = my_queue.getSize();
            stop = std::chrono::high_resolution_clock::now();
            duration += std::chrono::duration_cast<std::chrono::nanoseconds>(
                    stop - start).count();
            if (result != stl_queue.size()) {
                std::cout << "Testcase failed: Expected " << stl_queue.size() << 
                    " but got " << result << std::endl;
                return false;
            }
        }
    }
    std::cout << "Testcase " << testcase_index << " [ " << testcase.size() << 
        " operations ] passed for Queue with " << duration / testcase.size() <<
        " ns per operation" << std::endl;
    return true;
}

std::vector<std::pair<int, std::string>> generateTestcaseQueue(int num_operations) {
    std::vector<std::pair<int, std::string>> testcase;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 4);
    std::uniform_int_distribution<int> dis2(-num_operations, num_operations);
    int queue_size = 0;
    for (int i = 0; i < num_operations; i++) {
        int operation = dis(gen);
        switch(operation) {
            case 0:
                queue_size++;
                testcase.push_back({dis2(gen), "ENQUEUE"});
                break;
            case 1:
                if (queue_size > 0) {
                    queue_size--;
                    testcase.push_back({0, "DEQUEUE"});
                } else {
                    testcase.push_back({dis2(gen), "ENQUEUE"});
                    queue_size++;
                }
                break;
            case 2:
                if (queue_size > 0) {
                    testcase.push_back({0, "PEEK"});
                } else {
                    testcase.push_back({dis2(gen), "ENQUEUE"});
                    queue_size++;
                }
                break;
            case 3:
                testcase.push_back({0, "ISEMPTY"});
                break;
            case 4:
                testcase.push_back({0, "GETSIZE"});
                break;
        }
    }
    return testcase;
}

std::vector<std::pair<int, std::string>> generateTestcaseStack(int num_operations) {
    std::vector<std::pair<int, std::string>> testcase;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 4);
    std::uniform_int_distribution<int> dis2(-num_operations, num_operations);
    int stack_size = 0;
    for (int i = 0; i < num_operations; i++) {
        int operation = dis(gen);
        switch(operation) {
            case 0:
                stack_size++;
                testcase.push_back({dis2(gen), "PUSH"});
                break;
            case 1:
                if (stack_size > 0) {
                    stack_size--;
                    testcase.push_back({0, "POP"});
                } else {
                    testcase.push_back({dis2(gen), "PUSH"});
                    stack_size++;
                }
                break;
            case 2:
                if (stack_size > 0) {
                    testcase.push_back({0, "PEEK"});
                } else {
                    testcase.push_back({dis2(gen), "PUSH"});
                    stack_size++;
                }
                break;
            case 3:
                testcase.push_back({0, "ISEMPTY"});
                break;
            case 4:
                testcase.push_back({0, "GETSIZE"});
                break;
        }
    }
    return testcase;
}

int main(void) {
    std::vector<std::pair<int, std::string>> TESTCASE;
    int num_correct = 0;

    TESTCASE = {{1, "PUSH"}, {2, "PUSH"}, {3, "PUSH"}, {0, "PEEK"}, {0, "POP"},
        {0, "PEEK"}, {4, "PUSH"}, {5, "PUSH"}, {6, "PUSH"}, {1, "POP"},
        {2, "POP"}, {3, "POP"}, {4, "POP"}, {5, "POP"}, {0, "ISEMPTY"}};
    num_correct += checkTestcaseStack(TESTCASE, 1);
    TESTCASE = generateTestcaseStack(1000);
    num_correct += checkTestcaseStack(TESTCASE, 2);
    TESTCASE = generateTestcaseStack(10000);
    num_correct += checkTestcaseStack(TESTCASE, 3);
    TESTCASE = generateTestcaseStack(100000);
    num_correct += checkTestcaseStack(TESTCASE, 4);
    TESTCASE = generateTestcaseStack(1000000);
    num_correct += checkTestcaseStack(TESTCASE, 5);

    TESTCASE = {{1, "ENQUEUE"}, {2, "ENQUEUE"}, {3, "ENQUEUE"}, {0, "PEEK"}, 
        {0, "DEQUEUE"}, {0, "PEEK"}, {4, "ENQUEUE"}, {5, "ENQUEUE"},
        {6, "ENQUEUE"}, {1, "DEQUEUE"}, {2, "DEQUEUE"}, {3, "DEQUEUE"}, 
        {4, "DEQUEUE"}, {5, "DEQUEUE"}, {0, "ISEMPTY"}, {0, "GETSIZE"}};
    num_correct += checkTestcaseQueue(TESTCASE, 1);
    TESTCASE = generateTestcaseQueue(1000);
    num_correct += checkTestcaseQueue(TESTCASE, 2);
    TESTCASE = generateTestcaseQueue(10000);
    num_correct += checkTestcaseQueue(TESTCASE, 3);
    TESTCASE = generateTestcaseQueue(100000);
    num_correct += checkTestcaseQueue(TESTCASE, 4);
    TESTCASE = generateTestcaseQueue(1000000);
    num_correct += checkTestcaseQueue(TESTCASE, 5);

    std::cout << std::endl << "RESULTS: " << num_correct << " / 10" << std::endl;
    return 0;
}
