#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000003;

vector<vector<int>> multiply(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    int n = a.size(); 
    vector<vector<int>> product(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                product[i][j] = (product[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return product;
}

vector<vector<int>> matrixExponentiation(vector<vector<int>> base, unsigned long long exp) {
    int n = base.size(); 
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }

    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = multiply(result, base);
        }
        base = multiply(base, base); 
        exp /= 2; 
    }
    return result;
}

int main() {
    unsigned long long n;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    vector<vector<int>> transitionMatrix = {
        {1, 1, 1, 1, 1}, 
        {1, 0, 0, 0, 0}, 
        {0, 1, 0, 0, 0}, 
        {0, 0, 1, 0, 0}, 
        {0, 0, 0, 1, 0}  
    };

    vector<int> initialState = {1, 0, 0, 0, 0};

    vector<vector<int>> matrixPower = matrixExponentiation(transitionMatrix, n - 1);

    int finalResult = 0;
    for (int i = 0; i < 5; ++i) {
        finalResult = (finalResult + 1LL * matrixPower[0][i] * initialState[i]) % MOD;
    }

    cout << finalResult << endl;
    return 0;
}