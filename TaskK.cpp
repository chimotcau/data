#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;

void buildSparseTable(const vector<int>& arr, vector<vector<pair<int, int>>>& sparse_table) {
    int n = arr.size();
    int max_log = log2(n) + 1;

    sparse_table.assign(n, vector<pair<int, int>>(max_log, {INF, INF}));
    for (int i = 0; i < n; ++i) {
        sparse_table[i][0] = {arr[i], INF};
    }

    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            auto left = sparse_table[i][j - 1];
            auto right = sparse_table[i + (1 << (j - 1))][j - 1];

            vector<int> candidates = {left.first, left.second, right.first, right.second};
            sort(candidates.begin(), candidates.end());
            candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

            sparse_table[i][j].first = candidates[0];
            sparse_table[i][j].second = (candidates.size() > 1) ? candidates[1] : INF;
        }
    }
}

int query(const vector<vector<pair<int, int>>>& sparse_table, int l, int r) {
    int length = r - l + 1;
    int log = log2(length);

    auto left = sparse_table[l][log];
    auto right = sparse_table[r - (1 << log) + 1][log];

    vector<int> candidates = {left.first, left.second, right.first, right.second};
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

    if (candidates.size() < 2) return INF;
    return candidates[1];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<vector<pair<int, int>>> sparse_table;
    buildSparseTable(arr, sparse_table);

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;

        int result = query(sparse_table, l, r);
        if (result == INF) {
            cout << -1 << endl;
        } else {
            cout << result << endl;
        }
    }

    return 0;
}
