#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <signal.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

// You should NOT modify ANYTHING in this file.

extern bool are_these_equations_satisfiable(std::string &all_equations,
        std::function<std::vector<std::string>(std::string &)> get_equations,
        std::function<std::array<std::string, 3>(std::string)> parse_equation);

namespace evaluator {
    std::vector<std::string> get_equations(std::string &all_equations);
    std::array<std::string, 3> parse_equation(std::string equation);
    std::string read_all_equations_from_file(std::string filename);
    int evaluate_testcase(void);
    void handle_sigchld(int sig);
    std::string testcase_name;
    int test_pid;
}

std::vector<std::string> evaluator::get_equations(std::string &all_equations) {
    std::vector<std::string> equations;
    std::string equation;
    for (auto c : all_equations) {
        if (c == '\n') {
            equations.push_back(equation);
            equation = "";
        } else {
            equation += c;
        }
    }
    if (equation != "") {
        equations.push_back(equation);
    }
    return equations;
}

std::array<std::string, 3> evaluator::parse_equation(std::string equation) {
    std::array<std::string, 3> parsed_equation;
    size_t i = 0;
    while (i < equation.length() && 
            equation[i] != ' ' && equation[i] != '=' && equation[i] != '!') {
        parsed_equation[1] += equation[i++];
    }
    while (i < equation.length() && equation[i] == ' ') {
        i++;
    }
    parsed_equation[0] += equation[i++];
    parsed_equation[0] += equation[i++];
    while (i < equation.length() && equation[i] == ' ') {
        i++;
    }
    while (i < equation.length() &&
            equation[i] != ' ' && equation[i] != '=' && equation[i] != '!') {
        parsed_equation[2] += equation[i++];
    }
    return parsed_equation;
}

std::string evaluator::read_all_equations_from_file(std::string filename) {
    std::ifstream file(filename);
    std::string all_equations;
    std::string line;
    while (std::getline(file, line)) {
        all_equations += line + "\n";
    }
    return all_equations;
}

int evaluator::evaluate_testcase(void) {
    std::string all_equations = evaluator::read_all_equations_from_file(
            "testcases/" + evaluator::testcase_name + ".txt");
    bool result = are_these_equations_satisfiable(all_equations, 
            evaluator::get_equations, evaluator::parse_equation);
    std::ifstream expected("expected/" + evaluator::testcase_name + ".txt");
    bool expected_result;
    expected >> std::boolalpha >> expected_result;
    return (result == expected_result) ? 0 : 2;
}

void evaluator::handle_sigchld(int sig) {
    int status;
    waitpid(evaluator::test_pid, &status, WNOHANG);
    std::cerr << WIFSIGNALED(status) << " " << sig << std::endl;
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGALRM) {
            std::cout << "Time Limit Exceeded in testcase " << 
                evaluator::testcase_name << std::endl;
            exit(5);
        } else {
            std::cout << "Runtime Error in testcase " << 
                evaluator::testcase_name << std::endl;
            exit(4);
        }
    }
    switch (WEXITSTATUS(status)) {
        case 0:
            std::cout << "Testcase " << evaluator::testcase_name << 
                " Passed" << std::endl;
            exit(0);
        case 1:
            std::cout << "Runtime Error or Memory leak in testcase " << 
                evaluator::testcase_name << std::endl;
            exit(4);
        default:
            std::cout << "Wrong answer in testcase " << 
                evaluator::testcase_name << std::endl;
            exit(2);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage : " << argv[0] << 
            " <testcase_name> <time_limit>" << std::endl;
        exit(3);
    }
    signal(SIGCHLD, evaluator::handle_sigchld);
    double score = 0.0;
    evaluator::testcase_name = argv[1];
    if ((evaluator::test_pid = fork()) == 0) {
        int exit_code = evaluator::evaluate_testcase();
        if (exit_code) exit(exit_code);
        else return 0;
    }
    usleep(static_cast<long>(std::stod(argv[2]) * 1.0e+6));
    kill(evaluator::test_pid, SIGALRM);
    exit(5);
}