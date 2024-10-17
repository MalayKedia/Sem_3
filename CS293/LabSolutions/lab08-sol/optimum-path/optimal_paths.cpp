#include "optimum_path.h"

optimum_path_querier<std::string, int>
shortest_routes_from_town_hall(const graph_t<std::string, int>& graph, 
        const int& town_hall_id) {
    // TODO: Write your code here
    return optimum_path_querier<std::string, int>(
        graph, town_hall_id, 
        [](const int& a, const std::string& b, const int& c) {
            return a + c;
        });
    // End TODO
}

optimum_path_querier<std::string, double, std::greater<double>>
widest_road_routes_from_town_hall(const graph_t<std::string, double>& graph, 
        const int& town_hall_id) {
    // TODO: Write your code here
    return optimum_path_querier<std::string, double, std::greater<double>>(
        graph, town_hall_id, 
        [](const double& a, const std::string& b, const double& c) {
            return std::min(a, c);
        });
    // End TODO
}

optimum_path_querier<std::pair<std::string, double>, double>
least_time_routes_from_town_hall_with_junction_waits(
        const graph_t<std::pair<std::string, double>, double>& graph, 
        const int& town_hall_id) {
    // TODO: Write your code here
    return optimum_path_querier<std::pair<std::string, double>, double>(
        graph, town_hall_id, 
        [](const double& a, const std::pair<std::string, double>& b, 
                const double& c) {
            return a + b.second + c;
        });
    // End TODO
}