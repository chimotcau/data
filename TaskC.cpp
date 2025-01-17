#include <algorithm>
#include <iostream>
#include <vector>
const int  MAX_NODES= 53;
int adjMatrix[MAX_NODES][MAX_NODES];
void exploreComponent(int node, std::vector<bool>& visitedNodes, std::vector<int>& component) {
  visitedNodes[node] = true;
  component.push_back(node);
  for (int neighbor = 0; neighbor < MAX_NODES; ++neighbor) {
    if (adjMatrix[node][neighbor] == 1 && !visitedNodes[neighbor]) {
      exploreComponent(neighbor, visitedNodes, component);
    }
  }
}
std::vector<int> findLargestConnectedSubset(int n) {
  std::vector<bool> isSubsetValid(1 << n, false);  
  std::vector<int> adjacencyMask(n, 0);            
  std::vector<int> largestGroup;                   
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (adjMatrix[i][j] == 1) {
        adjacencyMask[i] |= (1 << j);
      }
    }
  }
  for (int subset = 1; subset < (1 << n); ++subset) {
    if ((subset & (subset - 1)) == 0) {  
      isSubsetValid[subset] = true;
    } else {
      int newNode = __builtin_ctz(subset); 
      int subsetExcludingNode = subset ^ (1 << newNode);
      if (isSubsetValid[subsetExcludingNode] &&
          (subsetExcludingNode & adjacencyMask[newNode]) == subsetExcludingNode) {
        isSubsetValid[subset] = true;
      }
    }
  }
  for (int subset = 1; subset < (1 << n); ++subset) {
    if (isSubsetValid[subset] && __builtin_popcount(subset) > largestGroup.size()) {
      largestGroup.clear();
      for (int i = 0; i < n; ++i) {
        if (subset & (1 << i)) {
          largestGroup.push_back(i);
        }
      }
    }
  }
  return largestGroup;
}
std::vector<int> findLargestGroup(int n) {
  bool isComplete = true;
  for (int i = 0; i < n && isComplete; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && adjMatrix[i][j] != 1) {
        isComplete = false;
        break;
      }
    }
  }
  if (isComplete) {
    std::vector<bool> visited(MAX_NODES, false);
    std::vector<int> largestGroup;
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        std::vector<int> component;
        exploreComponent(i, visited, component);
        if (component.size() > largestGroup.size()) {
          largestGroup = std::move(component);
        }
      }
    }
    return largestGroup;
  } else {
    return findLargestConnectedSubset(n);
  }
}
int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> adjMatrix[i][j];
    }
  }
  std::vector<int> largestGroup = findLargestGroup(n);
  std::sort(largestGroup.begin(), largestGroup.end());
  for (size_t i = 0; i < largestGroup.size(); ++i) {
    std::cout << largestGroup[i];
    if (i < largestGroup.size() - 1) {
      std::cout << " ";
    }
  }
  return 0;
}