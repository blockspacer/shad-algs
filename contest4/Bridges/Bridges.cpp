#include <vector>
#include <iostream>
#include <algorithm>


struct to_and_price {
    int64_t to;
    int64_t price;
    to_and_price(int64_t to, int64_t price) : to(to), price(price) {}
};

void DeepthFirstSearch(int64_t vertex,
                       const std::vector<std::vector<to_and_price>>& graph,
                       std::vector<size_t>* time_in,
                       std::vector<int64_t>* whats_up,
                       std::vector<bool>* used,
                       size_t* timer,
                       int64_t* min,
                       int64_t pred = -1
                       ) {
    // std::cout << vertex << ' ' << *timer << ' ' << p << '\n';
    (*used)[vertex] = true;
    (*time_in)[vertex] = (*whats_up)[vertex] = (*timer)++;
    for (size_t ii = 0; ii < graph[vertex].size(); ++ii) {
        int64_t to = graph[vertex][ii].to;
        int64_t price = graph[vertex][ii].price;
        if (to != pred) {
            if ((*used)[to]) {
                (*whats_up)[vertex] = std::min((*whats_up)[vertex],
                                               static_cast<int64_t>((*time_in)[to]));
            } else {
                DeepthFirstSearch(to, graph, time_in, whats_up, used, timer, min, vertex);
                (*whats_up)[vertex] = std::min((*whats_up)[vertex], (*whats_up)[to]);
                if ((*whats_up)[to] > static_cast<int64_t>((*time_in)[vertex])) {
                    if (*min == -1) {
                        *min = price;
                    } else if (*min > price) {
                        *min = price;
                    }
                } else {
                    // std::cout << vertex + 1 << ' ' << to + 1 << " is not a bridge\n";
                }
            }
        }
    }
}

void FindBridges(const std::vector<std::vector<to_and_price>>& graph) {
    std::vector<size_t> time_in(graph.size(), 0);
    std::vector<int64_t> whats_up(graph.size(), 0);
    std::vector<bool> used(graph.size(), false);
    size_t timer = 0;
    int64_t min = -1;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!used[i]) {
            // std::cout << "started from " << i << '\n';
            DeepthFirstSearch(i, graph, &time_in, &whats_up, &used, &timer, &min, -1);
        }
    }
    std::cout << min << '\n';
}

void TaskFunc() {
    std::vector<std::vector<to_and_price>> graph;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t num_of_cities;
    std::cin >> num_of_cities;
    graph.resize(num_of_cities);
    size_t num_of_roads;
    std::cin >> num_of_roads;
    size_t ind_f, ind_s;
    int64_t cost;
    // std::cout << "in here\n";
    for (size_t i = 0; i < num_of_roads; ++i) {
        std::cin >> ind_f >> ind_s >> cost;
        graph[ind_f - 1].push_back(to_and_price(ind_s - 1, cost));
        graph[ind_s - 1].push_back(to_and_price(ind_f - 1, cost));
    }
    // std::cout << "in here\n";
    FindBridges(graph);
}

int main() {
    TaskFunc();
    return 0;
}
