#include <iostream>
#include <queue>
#include <vector>
#include <limits>
const int kMax = 1e6;
struct Edge {
    int to;   
    int cost;  
};
class Graph {
private:
    int num_vertices_; 
    std::vector<std::vector<Edge>> adj_list_; 

public:
    explicit Graph(int n) : num_vertices_(n), adj_list_(n + 1) {}
    void AddEdge(int from, int to, int cost) {
        adj_list_[from].push_back({to, cost});
    }
    const std::vector<std::vector<Edge>>& GetAdjList() const {
        return adj_list_;
    }
    int GetNumVertices() const {
        return num_vertices_;
    }
};
int Dijkstra(int n, const Graph& graph, int k, int start, int end) {
    std::vector<std::vector<int>> distances(n + 1, std::vector<int>(k + 1, kMax));
    distances[start][0] = 0;
    std::priority_queue<std::pair<int, std::pair<int, int>>,
                        std::vector<std::pair<int, std::pair<int, int>>>,
                        std::greater<>> pq;
    pq.push({0, {start, 0}});

    while (!pq.empty()) {
        int cost = pq.top().first;             
        int current = pq.top().second.first; 
        int flights_taken = pq.top().second.second; 
        pq.pop();
        if (current == end) {
            return cost;
        }
        if (flights_taken < k) {
            for (const Edge& edge : graph.GetAdjList()[current]) {
                int new_cost = cost + edge.cost;
                if (new_cost < distances[edge.to][flights_taken + 1]) {
                    distances[edge.to][flights_taken + 1] = new_cost;
                    pq.push({new_cost, {edge.to, flights_taken + 1}});
                }
            }
        }
    }
    return -1;
}

int main() {
    int n;     
    int m;     
    int k;     
    int start; 
    int end;   
    std::cin >> n >> m >> k >> start >> end;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        graph.AddEdge(from, to, cost);
    }
    int result = Dijkstra(n, graph, k, start, end);
    std::cout << result;
    return 0;
}