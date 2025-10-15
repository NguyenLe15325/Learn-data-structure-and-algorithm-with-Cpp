#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

// Define a large number for infinity, used for initialization
const int INF = std::numeric_limits<int>::max();

/**
 * @brief Brute force solution for the Traveling Salesperson Problem (TSP).
 * * =========================================================================
 * TSP (BRUTE FORCE)
 * =========================================================================
 * This solution examines every permutation of cities to find the one with the 
 * minimum total cost (distance). It fixes the starting city (city 0) and 
 * permutes the remaining N-1 cities.
 * * * Time Complexity: O(N!)
 * * @param dist The adjacency matrix where dist[i][j] is the distance from city i to city j.
 * @param N The total number of cities (size of the matrix).
 * @return The minimum possible tour cost.
 */
int bruteForceTSP(const std::vector<std::vector<int>>& dist, int N) {
    if (N < 2) {
        return 0; // Trivial case: 0 or 1 city
    }

    // 1. Create a vector representing the intermediate cities (all cities except the starting city 0)
    std::vector<int> path;
    for (int i = 1; i < N; ++i) {
        path.push_back(i); // path = {1, 2, 3, ... N-1}
    }

    // Initialize the minimum cost to infinity
    int min_cost = INF;

    // 2. Iterate through all possible permutations of the intermediate cities
    // std::next_permutation is a standard library function that generates the next 
    // lexicographically greater permutation.
    do {
        // Calculate the cost of the current tour (which starts and ends at city 0)
        // Tour sequence: 0 -> path[0] -> path[1] -> ... -> path[N-2] -> 0
        
        int current_cost = 0;
        int current_city = 0; // Start at city 0

        // A. Add cost from start city (0) to the first city in the path
        current_cost += dist[current_city][path[0]];
        current_city = path[0];

        // B. Add cost between all intermediate cities in the current permutation
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int next_city = path[i+1];
            current_cost += dist[current_city][next_city];
            current_city = next_city;
        }

        // C. Add cost from the last city in the path back to the starting city (0)
        current_cost += dist[current_city][0];

        // 3. Update the minimum cost found so far
        min_cost = std::min(min_cost, current_cost);

    } while (std::next_permutation(path.begin(), path.end())); // Continue until all permutations are checked

    return min_cost;
}

int main() {
    // Example: A 4x4 distance matrix for 4 cities (0, 1, 2, 3)
    // Distance from i to j. dist[i][i] is always 0.
    std::vector<std::vector<int>> distances = {
        // 0   1   2   3  (To City)
        {  0, 10, 15, 20 }, // From City 0
        { 10,  0, 35, 25 }, // From City 1
        { 15, 35,  0, 30 }, // From City 2
        { 20, 25, 30,  0 }  // From City 3
    };

    int num_cities = distances.size();

    std::cout << "--- Traveling Salesperson Problem (Brute Force O(N!)) ---" << std::endl;
    std::cout << "Number of cities: " << num_cities << std::endl;

    if (num_cities > 1) {
        // Find the shortest tour cost
        int shortest_tour_cost = bruteForceTSP(distances, num_cities);

        std::cout << "Total permutations checked: " << tgamma(num_cities) << " (N!)" << std::endl;
        std::cout << "\nMinimum tour cost found: " << shortest_tour_cost << std::endl;
        // The minimum tour is 0 -> 1 -> 3 -> 2 -> 0, cost: 10 + 25 + 30 + 15 = 80
    } else {
        std::cout << "\nCannot solve TSP with less than 2 cities." << std::endl;
    }

    return 0;
}
