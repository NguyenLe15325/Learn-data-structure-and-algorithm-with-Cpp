#include <iostream>
#include <vector>
#include <numeric>

// Type alias for clarity and convenience
using ll = long long;

// --- 1. Dynamic Programming with Memoization (Top-Down) ---

/**
 * @brief Calculates the n-th Fibonacci number using memoization (top-down DP).
 *
 * @param n The index of the Fibonacci number to calculate (n >= 0).
 * @param memo A vector used for memoization, initialized with -1.
 * @return The n-th Fibonacci number.
 */
ll fibonacci_memo(int n, std::vector<ll>& memo) {
    // Base cases
    if (n <= 1) {
        return n;
    }

    // Check if the result is already computed
    if (memo[n] != -1) {
        return memo[n];
    }

    // Compute and store the result (Memoization step)
    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo);

    return memo[n];
}

// Wrapper function to initialize the memoization vector
ll solve_fib_memo(int n) {
    if (n < 0) return 0; // Handle negative input
    // Initialize memoization table (size n+1) with -1 to indicate uncomputed
    std::vector<ll> memo(n + 1, -1);
    return fibonacci_memo(n, memo);
}

// -----------------------------------------------------------------

// --- 2. Dynamic Programming with Tabulation (Bottom-Up) ---

/**
 * @brief Calculates the n-th Fibonacci number using tabulation (bottom-up DP).
 *
 * @param n The index of the Fibonacci number to calculate (n >= 0).
 * @return The n-th Fibonacci number.
 */
ll fibonacci_tab(int n) {
    if (n <= 1) {
        return n;
    }

    // Create DP table/array (size n+1) to store results
    std::vector<ll> dp(n + 1);

    // Base cases
    dp[0] = 0; // F(0)
    dp[1] = 1; // F(1)

    // Fill the DP table iteratively (Tabulation step)
    for (int i = 2; i <= n; ++i) {
        // F(i) = F(i-1) + F(i-2)
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// -----------------------------------------------------------------

// --- 3. Space-Optimized Tabulation (O(1) Space) ---

/**
 * @brief Calculates the n-th Fibonacci number using space-optimized bottom-up DP.
 *
 * @param n The index of the Fibonacci number to calculate (n >= 0).
 * @return The n-th Fibonacci number.
 */
ll fibonacci_opt(int n) {
    if (n <= 1) {
        return n;
    }

    ll a = 0; // Represents F(i-2)
    ll b = 1; // Represents F(i-1)
    ll c;     // Represents F(i)

    // Iterate from i=2 up to n
    for (int i = 2; i <= n; ++i) {
        c = a + b; // Calculate current F(i)
        a = b;     // Update F(i-2) to F(i-1)
        b = c;     // Update F(i-1) to F(i)
    }

    return b; // After the loop, b holds F(n)
}

// -----------------------------------------------------------------

int main() {
    // Example value for calculation
    const int N = 45; // Using a larger value to show the benefit of ll (long long)

    std::cout << "--- Fibonacci Sequence (N=" << N << ") using Dynamic Programming ---" << std::endl;

    // 1. Memoization (Top-Down)
    ll result_memo = solve_fib_memo(N);
    std::cout << "1. Memoization (Top-Down): F(" << N << ") = " << result_memo << std::endl;

    // 2. Tabulation (Bottom-Up)
    ll result_tab = fibonacci_tab(N);
    std::cout << "2. Tabulation (Bottom-Up): F(" << N << ") = " << result_tab << std::endl;

    // 3. Space-Optimized Tabulation (O(1) Space)
    ll result_opt = fibonacci_opt(N);
    std::cout << "3. Space-Optimized:      F(" << N << ") = " << result_opt << std::endl;

    // Note: The N=45th Fibonacci number is 1,134,903,170.
    // Using 'long long' is important here, as 'int' would overflow at N=47.

    return 0;
}