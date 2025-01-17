#include <iostream>
#include <vector>
const int kMax = 1e5;
const int kLogMax = 20;
class Tree {
private:
    std::vector<std::vector<int>> adj_;
    std::vector<int> entry_, exit_;
    std::vector<std::vector<int>> up_;
    int timer_;
    void Dfs(int node, int parent = 0) {
        entry_[node] = timer_++;
        up_[node][0] = parent;
        for (int i = 1; i < kLogMax; i++) {
            up_[node][i] = up_[up_[node][i - 1]][i - 1];
        }
        for (int child : adj_[node]) {
            if (child != parent) {
                Dfs(child, node);
            }
        }
        exit_[node] = timer_++;
    }
    bool IsAncestor(int a, int b) {
        return (entry_[a] <= entry_[b]) && (exit_[a] >= exit_[b]);
    }
public:
    explicit Tree(int n) {
        adj_.resize(n);
        entry_.resize(n);
        exit_.resize(n);
        up_.resize(n, std::vector<int>(kLogMax));
        timer_ = 0;
    }
    void AddEdge(int parent, int child) {
        adj_[parent].push_back(child);
    }
    void BuildTree() {
        Dfs(0);
    }
    int LCA(int a, int b) {
        if (IsAncestor(a, b)) {
            return a;
        }
        if (IsAncestor(b, a)) {
            return b;
        }
        for (int i = kLogMax - 1; i >= 0; i--) {
            if (!IsAncestor(up_[a][i], b)) {
                a = up_[a][i];
            }
        }
        return up_[a][0];
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Tree tree(n);
    for (int i = 1; i < n; i++) {
        int parent;
        std::cin >> parent;
        tree.AddEdge(parent, i);
    }
    tree.BuildTree();
    int a1, a2, x, y, z;
    std::cin >> a1 >> a2 >> x >> y >> z;
    long long sum = 0;
    int v = 0;
    for (int i = 0; i < m; i++) {
        v = tree.LCA((a1 + v) % n, a2);
        sum += v;
        a1 = (1LL * x * a1 + 1LL * y * a2 + z) % n;
        a2 = (1LL * x * a2 + 1LL * y * a1 + z) % n;
        std::cerr << "Iteration " << i + 1 << ": a1=" << a1 
                  << ", a2=" << a2 << ", v=" << v 
                  << ", sum=" << sum << std::endl;
    }
    std::cout << sum << std::endl;
    return 0;
}