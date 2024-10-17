#include "optimum_path.h"

#include <fstream>
#include <sstream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// You should NOT modify ANYTHING in this file.

optimum_path_querier<std::string, int>
shortest_routes_from_town_hall(const graph_t<std::string, int>& graph, 
        const int& town_hall_id);
optimum_path_querier<std::string, double, std::greater<double>>
widest_road_routes_from_town_hall(const graph_t<std::string, double>& graph, 
        const int& town_hall_id);
optimum_path_querier<std::pair<std::string, double>, double>
least_time_routes_from_town_hall_with_junction_waits(
        const graph_t<std::pair<std::string, double>, double>& graph, 
        const int& town_hall_id);

namespace tester {
    bool test_shortest_routes(void);
    bool test_widest_road_routes(void);
    bool test_least_time_routes(void);
}

bool tester::test_shortest_routes(void) {
    if (fork() != 0) {
        int status;
        wait(&status);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    } 
    std::ifstream f_in("testcases/shortest_routes.txt");
    std::string line;
    std::string temp;
    std::getline(f_in, line);
    std::vector<std::string> vertices;
    std::istringstream iss(line);
    while (iss >> temp) {
        vertices.push_back(temp);
    }
    graph_t<std::string, int> graph(vertices);
    while (std::getline(f_in, line)) {
        std::istringstream iss(line);
        int from, to;
        iss >> from >> to;
        graph.add_edge(from, to, 1);
    }
    f_in.close();
    std::ifstream q_in("queries/shortest_routes.txt");
    std::ifstream exp("expected/shortest_routes.txt");
    decltype(auto) querier = shortest_routes_from_town_hall(graph, 0);
    while (std::getline(q_in, line)) {
        std::vector<int> result = querier.get_optimum_path(std::stoi(line));
        std::vector<int> expected;
        std::getline(exp, line);
        std::istringstream iss(line);
        while (iss >> temp) {
            expected.push_back(std::stoi(temp));
        }
        if (expected != result) {
            for (auto& i : expected) {
                std::cout << i << " ";
            }
            std::cout << " != ";
            for (auto& i : result) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            q_in.close();
            exp.close();
            exit(1);
        }
    }
    q_in.close();
    exp.close();
    exit(0);
}

bool tester::test_widest_road_routes(void) {
    if (fork() != 0) {
        int status;
        wait(&status);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    } 
    std::ifstream f_in("testcases/widest_road_routes.txt");
    std::string line;
    std::string temp;
    std::getline(f_in, line);
    std::vector<std::string> vertices;
    std::istringstream iss(line);
    while (iss >> temp) {
        vertices.push_back(temp);
    }
    graph_t<std::string, double> graph(vertices);
    while (std::getline(f_in, line)) {
        std::istringstream iss(line);
        int from, to;
        double cost;
        iss >> from >> to >> cost;
        graph.add_edge(from, to, cost);
    }
    f_in.close();
    std::ifstream q_in("queries/widest_road_routes.txt");
    std::ifstream exp("expected/widest_road_routes.txt");
    decltype(auto) querier = widest_road_routes_from_town_hall(graph, 0);
    while (std::getline(q_in, line)) {
        std::vector<int> result = querier.get_optimum_path(std::stoi(line));
        std::vector<int> expected;
        std::getline(exp, line);
        std::istringstream iss(line);
        while (iss >> temp) {
            expected.push_back(std::stoi(temp));
        }
        if (expected != result) {
            for (auto& i : expected) {
                std::cout << i << " ";
            }
            std::cout << " != ";
            for (auto& i : result) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            q_in.close();
            exp.close();
            exit(1);
        }
    }
    q_in.close();
    exp.close();
    exit(0);
}

bool tester::test_least_time_routes(void) {
    if (fork() != 0) {
        int status;
        wait(&status);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    } 
    std::ifstream f_in("testcases/least_time_routes.txt");
    std::string line;
    std::string temp;
    std::getline(f_in, line);
    std::vector<std::pair<std::string, double>> vertices;
    std::istringstream iss(line);
    while (iss >> temp) {
        vertices.push_back({temp, 0});
    }
    std::getline(f_in, line);
    std::istringstream iss2(line);
    for (size_t i = 0; i < vertices.size(); i++) {
        iss2 >> vertices[i].second;
    }
    graph_t<std::pair<std::string, double>, double> graph(vertices);
    while (std::getline(f_in, line)) {
        std::istringstream iss(line);
        int from, to;
        double cost;
        iss >> from >> to >> cost;
        graph.add_edge(from, to, cost);
    }
    f_in.close();
    std::ifstream q_in("queries/least_time_routes.txt");
    std::ifstream exp("expected/least_time_routes.txt");
    decltype(auto) querier = 
        least_time_routes_from_town_hall_with_junction_waits(graph, 0);
    while (std::getline(q_in, line)) {
        std::vector<int> result = querier.get_optimum_path(std::stoi(line));
        std::vector<int> expected;
        std::getline(exp, line);
        std::istringstream iss(line);
        while (iss >> temp) {
            expected.push_back(std::stoi(temp));
        }
        if (expected != result) {
            for (auto& i : expected) {
                std::cout << i << " ";
            }
            std::cout << " != ";
            for (auto& i : result) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            q_in.close();
            exp.close();
            exit(1);
        }
    }
    q_in.close();
    exp.close();
    exit(0);
}

int main(void) {
    int score = 0;
    if (tester::test_shortest_routes()) {
        std::cout << "Shortest routes from town hall: PASS" << std::endl;
        score++;
    } else {
        std::cout << "Shortest routes from town hall: FAIL" << std::endl;
    }
    if (tester::test_widest_road_routes()) {
        std::cout << "Widest road routes from town hall: PASS" << std::endl;
        score++;
    } else {
        std::cout << "Widest road routes from town hall: FAIL" << std::endl;
    }
    if (tester::test_least_time_routes()) {
        std::cout << 
            "Least time routes from town hall with junction waits: PASS" 
            << std::endl;
        score++;
    } else {
        std::cout << 
            "Least time routes from town hall with junction waits: FAIL" 
            << std::endl;
    }
    std::cout << "RESULTS: " << score << " / 3" << std::endl;
}