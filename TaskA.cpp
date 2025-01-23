#include <iostream>
using namespace std;

const int MOD = 1000003;

// Function to multiply two 2x2 matrices under modulo MOD
void matrixMultiply(long long A[2][2], long long B[2][2]) {
    long long a = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % MOD;
    long long b = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % MOD;
    long long c = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % MOD;
    long long d = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % MOD;

    A[0][0] = a;
    A[0][1] = b;
    A[1][0] = c;
    A[1][1] = d;
}

// Function to compute the matrix raised to the power of n using binary exponentiation
void matrixPower(long long A[2][2], long long n) {
    if (n == 0 || n == 1) 
        return;

    long long baseMatrix[2][2] = {{1, 1}, {1, 0}};

    matrixPower(A, n / 2); // Recurse to square the matrix
    matrixMultiply(A, A); // A = A * A

    if (n % 2 != 0) // If n is odd, multiply with the base matrix one more time
        matrixMultiply(A, baseMatrix);
}

// Function to calculate the nth Fibonacci number modulo MOD
int getFibonacci(long long n) {
    if (n == 1) return 0; // Base case F(1) = 0
    if (n == 2) return 1; // Base case F(2) = 1

    long long F[2][2] = {{1, 1}, {1, 0}};
    matrixPower(F, n - 2); // Calculate F^(n-2)

    return F[0][0]; // Return the nth Fibonacci number
}

int main() {
    long long n;
    cin >> n;
    cout << getFibonacci(n) << "\n";
    return 0;
}