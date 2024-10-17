#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

// You should NOT add ANY other includes.
// DO NOT add "using namespace std;" as it is a bad practice.

template <typename T>
concept numeric = std::is_arithmetic_v<T>;

template <typename Value, numeric Cost>
class graph_t {
    // You should NOT modify ANYTHING in this structure.
public:
    class std::vector<Value> vertices;
    class std::vector<std::vector<std::pair<int, Cost>>> edges;
    graph_t() = default;
    graph_t(const std::vector<Value>& __vertices) : 
        vertices(__vertices), edges(__vertices.size()) {}
    graph_t(const std::vector<Value>& __vertices, 
            const std::vector<std::tuple<int, int, Cost>>& __edges) : 
        vertices(__vertices), edges(__vertices.size()) {
        for (const auto& [from, to, cost] : __edges) {
            add_edge(from, to, cost);
        }
    }
    graph_t(const graph_t&) = default;
    graph_t(graph_t&&) = default;
    graph_t& operator=(const graph_t&) = default;
    graph_t& operator=(graph_t&&) = default;
    virtual ~graph_t() = default;
    void add_edge(const int& from, const int& to, const Cost& cost) {
        this->edges[from].push_back({to, cost});
    }
};

template <typename Value, numeric Cost, class Compare = std::less<Cost>>
class optimum_path_querier {
    // You should NOT modify public function signatures and constructors.
public:
    optimum_path_querier(const graph_t<Value, Cost> &graph, const int& start, 
        std::function<Cost(const Cost&, const Value&, const Cost&)> add_costs);
    std::vector<int> get_optimum_path(const int& end);
protected:
    // TODO: Write your data structures and subroutines here
    class std::vector<std::pair<Cost, int>> optimum_path_step;
    // End TODO
};

template <typename Value, numeric Cost, class Compare>
optimum_path_querier<Value, Cost, Compare>::optimum_path_querier(
        const graph_t<Value, Cost> &graph, const int& start, 
        std::function<Cost(const Cost&, const Value&, const Cost&)> add_costs) {
    // TODO: Write your code here
    Compare compare;
    std::priority_queue<std::pair<Cost, int>, std::vector<std::pair<Cost, int>>, 
            std::function<bool(const std::pair<Cost, int>&,
                                 const std::pair<Cost, int>&)>>
    costs_to([&compare](const std::pair<Cost, int>& a,
                        const std::pair<Cost, int>& b) {
        return !compare(a.first, b.first);
    });
    if (compare(0, std::numeric_limits<Cost>::max())) {
        costs_to.push({0, start});
        this->optimum_path_step.resize(graph.vertices.size(),
                std::make_pair(std::numeric_limits<Cost>::max(), -1));
        this->optimum_path_step[start] = std::make_pair(0, start);
    } else {
        costs_to.push({std::numeric_limits<Cost>::max(), start});
        this->optimum_path_step.resize(graph.vertices.size(),
                std::make_pair(0, -1));
        this->optimum_path_step[start] = std::make_pair(
                std::numeric_limits<Cost>::max(), start);
    }
    while (!costs_to.empty()) {
        auto [cost, from] = costs_to.top();
        costs_to.pop();
        for (const auto& [to, edge_cost] : graph.edges[from]) {
            Cost new_cost = add_costs(cost, graph.vertices[from], edge_cost);
            if (!compare(new_cost, this->optimum_path_step[to].first)) {
                continue;
            }
            this->optimum_path_step[to] = {new_cost, from};
            costs_to.push({new_cost, to});
        }
    }
    // End TODO
}

template <typename Value, numeric Cost, class Compare>
std::vector<int> optimum_path_querier<Value, Cost, Compare>::get_optimum_path(
        const int& end) {
    // TODO: Write your code here
    if (this->optimum_path_step[end].second == -1) {
        return {};
    }
    std::vector<int> path;
    int current = end;
    for (; this->optimum_path_step[current].second != current; 
            current = this->optimum_path_step[current].second) {
        path.push_back(current);
    }
    path.push_back(current);
    std::reverse(path.begin(), path.end());
    return path;
    // End TODO
}