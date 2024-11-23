#include "server_requests.h"

#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// You should NOT modify ANYTHING in this file.

extern bool __evaluate_testcase_one(void);
extern bool __evaluate_testcase_two(void);
extern bool __evaluate_testcase_three(void);

void __handle_sigchld(int __sig) {
    int status;
    waitpid(-1, &status, WNOHANG);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGALRM) {
            exit(3);
        } else {
            exit(2);
        }
    }
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            exit(0);
        }
        exit(1);
    }
    exit(4);
}

void __execute_testcase(std::function<bool(void)> testcase_function, 
        std::string testcase_name, double time_limit) {
    signal(SIGCHLD, __handle_sigchld);
    int pid;
    if ((pid = fork()) == 0) {
        exit(1 - static_cast<int>(testcase_function()));
    }
    usleep(static_cast<long long>(time_limit * 1.0e+6));
    kill(pid, SIGALRM);
    exit(3);
}

void __testcase_wrapper(std::function<bool(void)> testcase_function, 
        std::string testcase_name, double time_limit) {
    int pid;
    if ((pid = fork()) == 0) {
        __execute_testcase(testcase_function, testcase_name, time_limit);
    }
    int status;
    waitpid(pid, &status, 0);
    if (!WIFEXITED(status)) {
        std::cerr << "Unknown error in " << testcase_name << std::endl;
        exit(1);
    }
    switch (WEXITSTATUS(status)) {
    case 0:
        std::cout << testcase_name << " passed!" << std::endl;
        break;
    case 1:
        std::cerr << "Wrong answer in " << testcase_name << std::endl;
        break;
    case 2:
        std::cerr << "Runtime error in " << testcase_name << std::endl;
        break;
    case 3:
        std::cerr << "Time limit exceeded in " << testcase_name << std::endl;
        break;
    default:
        std::cerr << "Unknown error in " << testcase_name << std::endl;
        break;
    }
}

int main(void) {
    __testcase_wrapper(__evaluate_testcase_one, "Testcase 1", 1.0);
    __testcase_wrapper(__evaluate_testcase_two, "Testcase 2", 1.0);
    __testcase_wrapper(__evaluate_testcase_three, "Testcase 3", 10.0);
    return 0;
}
