#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>
const uint64_t INF = 1e8;
class Graph {
private:
    uint64_t num_vertices_;  
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> adj_list_; 
public:
    explicit Graph(uint64_t vertices)
        : num_vertices_(vertices), adj_list_(vertices) {}
    void AddEdge(uint64_t from, uint64_t to, uint64_t weight) {
        adj_list_[from].emplace_back(to, weight);
    }
    const std::vector<std::vector<std::pair<uint64_t, uint64_t>>>& GetAdjList() const {
        return adj_list_;
    }
    uint64_t GetNumVertices() const {
        return num_vertices_;
    }
};
uint64_t MinBottlesLemonade(const Graph& graph, uint64_t start, uint64_t target) {
    uint64_t num_vertices = graph.GetNumVertices();
    if (start == target) {
        return 0;
    }
    std::vector<uint64_t> min_cost(num_vertices, INF);
    min_cost[start] = 0;
    std::queue<uint64_t> bfs_queue;
    bfs_queue.push(start);
    while (!bfs_queue.empty()) {
        uint64_t current = bfs_queue.front();
        bfs_queue.pop();
        for (const auto& edge : graph.GetAdjList()[current]) {
            uint64_t next = edge.first;
            uint64_t weight = edge.second;
            if (min_cost[next] > min_cost[current] + weight) {
                min_cost[next] = min_cost[current] + weight;
                bfs_queue.push(next);
            }
        }
    }
    return min_cost[target];
}
int main() {
    uint64_t cost_type1;  
    uint64_t cost_type2;  
    uint64_t num_universes; 
    uint64_t start_universe; 
    uint64_t target_universe;
    std::cin >> cost_type1 >> cost_type2 >> num_universes >> start_universe >> target_universe;
    Graph graph(num_universes);
    for (uint64_t i = 0; i < num_universes; ++i) {
        graph.AddEdge(i, (i + 1) % num_universes, cost_type1);
        graph.AddEdge(i, (i * i + 1) % num_universes, cost_type2);
    }
    uint64_t result = MinBottlesLemonade(graph, start_universe, target_universe);
    std::cout << result << std::endl;
    return 0;
}