/**
 * @file matrix_chain_multiplication.cpp
 * @brief Solves the Matrix Chain Multiplication problem using Dynamic Programming.
 * * The goal is to find the minimum number of scalar multiplications required to multiply
 * a chain of matrices. The dimensions are stored in an array 'P', where matrix Ai has
 * dimension P[i-1] x P[i].
 * * DP State: M[i][j] = Minimum cost to compute the product A[i]...A[j].
 * Recurrence: M[i][j] = min( M[i][k] + M[k+1][j] + P[i-1]*P[k]*P[j] ) for i <= k < j
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>

// Global constant for infinity
const int INF = INT_MAX;

/**
 * @brief Prints the optimal parenthesization of the matrix chain product.
 * @param S The matrix holding the optimal split points (k).
 * @param i The starting matrix index (1-based).
 * @param j The ending matrix index (1-based).
 */
void printOptimalParenthesization(const std::vector<std::vector<int>>& S, int i, int j) {
    // Base case: A single matrix
    if (i == j) {
        std::cout << "A" << i;
    } else {
        std::cout << "(";
        // Recursively print the first part of the product, split at S[i][j]
        printOptimalParenthesization(S, i, S[i][j]);
        // Recursively print the second part of the product, split at S[i][j] + 1
        printOptimalParenthesization(S, S[i][j] + 1, j);
        std::cout << ")";
    }
}


/**
 * @brief Solves the Matrix Chain Multiplication problem.
 * * @param P Vector of matrix dimensions. P[i-1] x P[i] defines matrix i.
 * @return The minimum number of scalar multiplications required.
 */
long long matrixChainOrder(const std::vector<int>& P) {
    // N is the number of dimensions, P has size N.
    // The number of matrices is N - 1. We use 1-based indexing for matrices A1...A(N-1).
    int N = P.size(); 

    // M[i][j]: Stores the minimum number of scalar multiplications needed for A[i..j].
    // S[i][j]: Stores the optimal split point k (index where the chain should be split).
    // We size the vectors to N x N, using indices 1 to N-1.
    std::vector<std::vector<long long>> M(N, std::vector<long long>(N, 0));
    std::vector<std::vector<int>> S(N, std::vector<int>(N, 0));

    // Base Case: M[i][i] = 0 (Cost of multiplying a single matrix is zero)
    // This is handled by initialization and loop structure.

    // L is the chain length (number of matrices in the subproblem)
    for (int L = 2; L < N; ++L) {
        // i is the starting matrix index
        for (int i = 1; i <= N - L; ++i) {
            // j is the ending matrix index
            int j = i + L - 1;
            M[i][j] = INF;

            // k is the split point: split A[i..j] into A[i..k] and A[k+1..j]
            for (int k = i; k <= j - 1; ++k) {
                // Cost calculation: Cost(A[i..k]) + Cost(A[k+1..j]) + Cost(A[i..k] * A[k+1..j])
                long long q = M[i][k] + M[k + 1][j] + (long long)P[i - 1] * P[k] * P[j];

                // Dynamic Programming step: find the minimum cost (q)
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k; // Store the optimal split point
                }
            }
        }
    }

    // Output the results
    std::cout << "Optimal Parenthesization (A1..." << "A" << N-1 << "): ";
    printOptimalParenthesization(S, 1, N - 1);
    std::cout << std::endl;
    
    // Return the minimum cost for the entire chain A[1..N-1]
    return M[1][N - 1];
}

int main() {
    // P = {p0, p1, p2, p3, p4, p5}
    // Matrices: 
    // A1: p0 x p1 (30x35)
    // A2: p1 x p2 (35x15)
    // A3: p2 x p3 (15x5)
    // A4: p3 x p4 (5x10)
    // A5: p4 x p5 (10x20)
    
    std::vector<int> P = {30, 35, 15, 5, 10, 20}; // N=6 dimensions, 5 matrices
    int num_matrices = P.size() - 1;

    std::cout << "--- Matrix Chain Multiplication (Dynamic Programming) ---" << std::endl;
    std::cout << "Matrix Dimensions:" << std::endl;
    for(int i = 1; i <= num_matrices; ++i) {
        std::cout << "A" << i << ": " << P[i-1] << " x " << P[i] << std::endl;
    }
    std::cout << "---------------------------------------------------------" << std::endl;

    long long min_cost = matrixChainOrder(P);

    std::cout << "Minimum scalar multiplications required: " << min_cost << std::endl; 
    // Expected result for this example: 10500
    
    return 0;
}
