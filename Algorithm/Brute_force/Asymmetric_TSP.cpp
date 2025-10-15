#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <numeric>

// Define the number of cities. N=4 means cities are indexed 0, 1, 2, 3.
const int N = 4;
const int start_city = 0;

// --- ASYMMETRIC DISTANCE MATRIX ---
// DIST[i][j] is the cost from city i TO city j.
// The costs are intentionally asymmetric (e.g., DIST[1][0] != DIST[0][1]).
int DIST[N][N] = {
    //   0   1   2   3  <- To City
    {  0, 10, 15, 20 }, // From City 0
    { 12,  0, 35, 25 }, // From City 1 (Cost 1->0 is 12, but 0->1 is 10)
    { 17, 45,  0, 30 }, // From City 2 (Cost 2->0 is 17, but 0->2 is 15)
    { 22, 27, 40,  0 }  // From City 3
};

/**
 * @brief Implements the brute-force solution for the Asymmetric TSP.
 * * It checks every possible path permutation (N-1)! and calculates the cost
 * using the asymmetric distance matrix.
 */
void solveATSP() {
    // Create a vector of all cities except the starting city (1, 2, 3).
    std::vector<int> intermediate_cities;
    for (int i = 0; i < N; i++) {
        if (i != start_city) {
            intermediate_cities.push_back(i);
        }
    }

    // Initialize minimum path cost to the maximum possible integer value.
    int min_path_cost = std::numeric_limits<int>::max();
    std::vector<int> optimal_path;

    // The total number of permutations is (N-1)!, which is 3! = 6 for N=4.
    // std::next_permutation iterates through all of them.
    
    // Sort the intermediate cities to ensure std::next_permutation starts correctly.
    std::sort(intermediate_cities.begin(), intermediate_cities.end());

    // Loop through every single permutation of the intermediate cities.
    do {
        int current_path_cost = 0;
        std::vector<int> current_path;

        // 1. Start at the fixed city (0).
        int current_city = start_city;
        current_path.push_back(start_city);

        // 2. Traverse the intermediate cities in the current permutation.
        for (int next_city : intermediate_cities) {
            // Crucially, this uses the ASYMMETRIC cost: DIST[i][j]
            current_path_cost += DIST[current_city][next_city];
            current_city = next_city;
            current_path.push_back(current_city);
        }

        // 3. Complete the cycle: return to the starting city (0).
        // This also uses the ASYMMETRIC return cost: DIST[last_city][start_city]
        current_path_cost += DIST[current_city][start_city];
        current_path.push_back(start_city); // Add the final city to the path visualization

        // Update the minimum cost and the optimal path if a shorter route is found.
        if (current_path_cost < min_path_cost) {
            min_path_cost = current_path_cost;
            optimal_path = current_path;
        }

    } while (std::next_permutation(intermediate_cities.begin(), intermediate_cities.end()));

    // --- Output Results ---
    std::cout << "--- Asymmetric Traveling Salesperson Problem (ATSP) ---\n";
    std::cout << "Starting City: " << start_city << " (Cities are 0, 1, 2, 3)\n";
    std::cout << "Total permutations checked: " << (N-1) << "! = 6\n\n";

    std::cout << "Optimal Path Found:\n";
    for (size_t i = 0; i < optimal_path.size(); ++i) {
        std::cout << optimal_path[i];
        if (i < optimal_path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n\nMinimum Total Cost: " << min_path_cost << "\n";
}

int main() {
    solveATSP();
    return 0;
}
