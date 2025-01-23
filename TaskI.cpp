#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

// Structure to represent a graph edge with destination and success probability
struct Edge {
    int destination;          // Target node
    double success_probability; // Success probability of the edge
};

// Class representing an undirected graph using an adjacency list
class Graph {
private:
    std::vector<std::vector<Edge>> adjacency_list_; // List of edges for each node
public:
    // Constructor to initialize the graph with a given number of nodes
    explicit Graph(int nodes) : adjacency_list_(nodes + 1) {}

    // Method to add an undirected edge with a success probability
    void AddEdge(int from, int to, double success_probability) {
        adjacency_list_[from].push_back({to, success_probability});
        adjacency_list_[to].push_back({from, success_probability});
    }

    // Getter for the adjacency list
    const std::vector<std::vector<Edge>>& GetAdjacencyList() const {
        return adjacency_list_;
    }
};

// Function to compute the maximum success probability between two nodes using a modified Dijkstra's algorithm
double Dijkstra(const std::vector<std::vector<Edge>>& graph, int start_node, int end_node) {
    int n = graph.size(); // Total number of nodes
    std::vector<double> max_probability(n, 0.0); // Maximum success probability for each node
    max_probability[start_node] = 1.0; // Start node has 100% success initially

    // Priority queue to process nodes in descending order of success probability
    std::priority_queue<std::pair<double, int>> priority_queue;
    priority_queue.push({1.0, start_node}); // Start with the start node

    while (!priority_queue.empty()) {
        double current_probability = priority_queue.top().first; // Current node's probability
        int current_node = priority_queue.top().second;          // Current node
        priority_queue.pop();

        // If we reach the target node, return the maximum probability
        if (current_node == end_node) {
            return current_probability;
        }

        // Explore all neighbors of the current node
        for (const Edge& edge : graph[current_node]) {
            double new_probability = current_probability * edge.success_probability;

            // If a higher probability path to the destination is found
            if (new_probability > max_probability[edge.destination]) {
                max_probability[edge.destination] = new_probability;
                priority_queue.push({new_probability, edge.destination});
            }
        }
    }

    // If there's no path to the target node, return 0.0
    return 0.0;
}

int main() {
    int num_nodes;      // Total number of nodes
    int num_edges;      // Total number of edges
    int start_node;     // Source node
    int end_node;       // Destination node

    // Input the number of nodes, edges, start node, and end node
    std::cin >> num_nodes >> num_edges >> start_node >> end_node;

    Graph graph(num_nodes); // Create a graph instance

    // Input each edge with its success probability
    for (int i = 0; i < num_edges; ++i) {
        int source_node, target_node;
        double success_percentage;
        std::cin >> source_node >> target_node >> success_percentage;

        // Add the edge to the graph (convert percentage to a decimal)
        graph.AddEdge(source_node, target_node, success_percentage / 100.0);
    }

    // Get the adjacency list of the graph
    const auto& adjacency_list = graph.GetAdjacencyList();

    // Compute the maximum success probability
    double result = Dijkstra(adjacency_list, start_node, end_node);

    // Print the result with two decimal places
    std::cout << std::fixed << std::setprecision(2) << result << std::endl;

    return 0;
}
