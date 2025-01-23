#include <climits>
#include <iostream>
#include <queue>
#include <vector>
template <typename T>
class Graph {
 public:
  explicit Graph(int vertex_count) {
    adj_list.resize(vertex_count);
  }
  void AddEdge(T from, T to) {
    adj_list[from].push_back(to);
    adj_list[to].push_back(from);  
  }
  T FindShortestPath(T src1, T src2, T target, int total_nodes) {
    std::vector<T> dist_from_src1(total_nodes, INT_MAX);
    std::vector<T> dist_from_src2(total_nodes, INT_MAX);
    std::vector<T> dist_from_target(total_nodes, INT_MAX);
    BFS(src1, total_nodes, dist_from_src1);
    BFS(src2, total_nodes, dist_from_src2);
    BFS(target, total_nodes, dist_from_target);
    return ComputeMinimumDistance(total_nodes, dist_from_src1, dist_from_src2, dist_from_target);
  }
 private:
  std::vector<std::vector<T>> adj_list;
  void BFS(T start, int total_nodes, std::vector<T>& distances) {
    std::priority_queue<std::pair<T, T>, std::vector<std::pair<T, T>>, std::greater<>> pq;
    std::vector<bool> visited(total_nodes, false);
    distances[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
      T current_node = pq.top().second;
      pq.pop();
      if (visited[current_node]) continue;
      visited[current_node] = true;
      for (const T& neighbor : adj_list[current_node]) {
        if (distances[current_node] + 1 < distances[neighbor]) {
          distances[neighbor] = distances[current_node] + 1;
          pq.emplace(distances[neighbor], neighbor);
        }
      }
    }
  }
  static T ComputeMinimumDistance(int total_nodes, const std::vector<T>& dist1,
                                   const std::vector<T>& dist2, const std::vector<T>& dist3) {
    T min_distance = INT_MAX;
    for (int i = 0; i < total_nodes; ++i) {
      min_distance = std::min(min_distance, dist1[i] + dist2[i] + dist3[i]);
    }
    return min_distance;
  }
};

int main() {
  int nodes, edges, leon, matilda, destination;
  std::cin >> nodes >> edges >> leon >> matilda >> destination;
  Graph<int> city_graph(nodes + 1);
  for (int i = 0; i < edges; ++i) {
    int u, v;
    std::cin >> u >> v;
    city_graph.AddEdge(u, v);
  }
  std::cout << city_graph.FindShortestPath(leon, matilda, destination, nodes + 1);
  return 0;
}