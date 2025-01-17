#include <iostream>
#include <vector>

template <typename T>
class TopologicalSort {
 public:
  explicit TopologicalSort(int vertices)
      : num_vertices(vertices),
        adjacency_list(vertices),
        in_degree(vertices, 0) {}
  void AddEdge(T from, T to) {
    adjacency_list[from].push_back(to);
    ++in_degree[to];
  }
  bool PerformSort(std::vector<T>& sorted_order) {
    std::vector<T> zero_in_degree; 
    for (T i = 0; i < num_vertices; ++i) {
      if (in_degree[i] == 0) {
        zero_in_degree.push_back(i);
      }
    }
    int processed_count = 0;
    while (!zero_in_degree.empty()) {
      T current = zero_in_degree.back();
      zero_in_degree.pop_back();
      sorted_order.push_back(current);
      for (T neighbor : adjacency_list[current]) {
        if (--in_degree[neighbor] == 0) {
          zero_in_degree.push_back(neighbor);
        }
      }
      ++processed_count;
    }
    return processed_count == num_vertices;
  }
 private:
  T num_vertices;                        
  std::vector<std::vector<T>> adjacency_list; 
  std::vector<int> in_degree;           
};
int main() {
  int vertices, edges;
  std::cin >> vertices >> edges;
  TopologicalSort<int> graph(vertices);
  std::vector<int> sorted_order;
  for (int i = 0; i < edges; ++i) {
    int from, to;
    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }
  if (graph.PerformSort(sorted_order)) {
    std::cout << "YES\n";
    for (int node : sorted_order) {
      std::cout << node << " ";
    }
  } else {
    std::cout << "NO";
  }
  return 0;
}