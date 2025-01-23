#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
template <typename T>
class Graph {
 public:
  explicit Graph(int vertices)
      : num_vertices(vertices),
        adjacency_list(vertices),
        reverse_adjacency_list(vertices) {}
  void AddEdge(T source, T destination) {
    adjacency_list[source].push_back(destination);
    reverse_adjacency_list[destination].push_back(source);
  }
  std::vector<std::vector<T>> FindStronglyConnectedComponents() {
    std::stack<T> finish_stack;
    std::vector<bool> visited(num_vertices, false);
    for (T i = 0; i < num_vertices; ++i) {
      if (!visited[i]) {
        PerformDFS(i, visited, finish_stack);
      }
    }
    visited.assign(num_vertices, false);
    std::vector<std::vector<T>> scc_list;
    while (!finish_stack.empty()) {
      T current = finish_stack.top();
      finish_stack.pop();
      if (!visited[current]) {
        std::vector<T> scc;
        ExtractSCC(current, visited, scc);
        scc_list.push_back(scc);
      }
    }
    return scc_list;
  }
  Graph<T> CondenseGraph(const std::vector<std::vector<T>>& scc_list) {
    int condensed_size = scc_list.size();
    Graph<T> condensed_graph(condensed_size);
    for (size_t i = 0; i < scc_list.size(); ++i) {
      for (T vertex : scc_list[i]) {
        for (T neighbor : adjacency_list[vertex]) {
          int source_scc = GetComponentIndex(scc_list, vertex);
          int target_scc = GetComponentIndex(scc_list, neighbor);
          if (source_scc != target_scc) {
            condensed_graph.AddEdge(source_scc, target_scc);
          }
        }
      }
    }
    return condensed_graph;
  }
  std::pair<int, int> CalculateDegrees() {
    std::vector<int> in_degree(num_vertices, 0);
    std::vector<int> out_degree(num_vertices, 0);
    for (T u = 0; u < num_vertices; ++u) {
      for (T v : adjacency_list[u]) {
        out_degree[u]++;
        in_degree[v]++;
      }
    }
    int zero_in_degree = std::count(in_degree.begin(), in_degree.end(), 0);
    int zero_out_degree = std::count(out_degree.begin(), out_degree.end(), 0);
    return {zero_in_degree, zero_out_degree};
  }
 private:
  int num_vertices;  
  std::vector<std::vector<T>> adjacency_list;  
  std::vector<std::vector<T>> reverse_adjacency_list;  
  void PerformDFS(T vertex, std::vector<bool>& visited, std::stack<T>& finish_stack) {
    visited[vertex] = true;
    for (T neighbor : adjacency_list[vertex]) {
      if (!visited[neighbor]) {
        PerformDFS(neighbor, visited, finish_stack);
      }
    }
    finish_stack.push(vertex);
  }
  void ExtractSCC(T vertex, std::vector<bool>& visited, std::vector<T>& scc) {
    visited[vertex] = true;
    scc.push_back(vertex);
    for (T neighbor : reverse_adjacency_list[vertex]) {
      if (!visited[neighbor]) {
        ExtractSCC(neighbor, visited, scc);
      }
    }
  }
  int GetComponentIndex(const std::vector<std::vector<T>>& scc_list, T vertex) const {
    for (size_t i = 0; i < scc_list.size(); ++i) {
      if (std::find(scc_list[i].begin(), scc_list[i].end(), vertex) != scc_list[i].end()) {
        return static_cast<int>(i);
      }
    }
    return -1;
  }
};

int main() {
  int vertices, edges;
  std::cin >> vertices >> edges;
  Graph<int> city_graph(vertices);
  for (int i = 0; i < edges; ++i) {
    int from, to;
    std::cin >> from >> to;
    city_graph.AddEdge(from - 1, to - 1);  
  }
  auto sccs = city_graph.FindStronglyConnectedComponents();
  if (sccs.size() <= 1) {
    std::cout << 0 << std::endl;
    return 0;
  }
  Graph<int> condensed_graph = city_graph.CondenseGraph(sccs);
  auto [zero_in, zero_out] = condensed_graph.CalculateDegrees();
  std::cout << std::max(zero_in, zero_out) << std::endl;
  return 0;
}