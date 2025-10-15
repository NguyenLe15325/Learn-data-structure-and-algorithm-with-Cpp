#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * @brief Implements the brute force recursive solution for the 0/1 Knapsack Problem.
 * * =========================================================================
 * KNAPSACK PROBLEM (0/1 BRUTE FORCE)
 * =========================================================================
 * This function explores all possible subsets of items using recursion.
 * At each item 'index', it creates two branches: one where the item is included 
 * (if it fits) and one where it is excluded.
 * * * Brute Force Strategy:
 * Check every one of the 2^N possible combinations of items and find the one 
 * with the highest value that satisfies the weight constraint.
 * * * Time Complexity: O(2^N)
 * The recursive tree has a depth of N, and at each level, two branches are 
 * usually taken, leading to 2^N total computations in the worst case.
 * * @param weights A vector of item weights.
 * @param values A vector of item values.
 * @param remaining_capacity The current weight capacity remaining in the knapsack.
 * @param index The index of the item currently being considered (0 to N-1).
 * @return The maximum value that can be achieved from the remaining items.
 */
int bruteForceKnapsack(
    const std::vector<int>& weights,
    const std::vector<int>& values,
    int remaining_capacity,
    int index
) {
    // Base Case 1: If we have processed all items, stop and return 0 value.
    if (index == weights.size()) {
        return 0;
    }

    // --- Branch 1: EXCLUDE the current item ---
    // Calculate the maximum value achievable if we SKIP the current item and move to the next.
    int value_if_excluded = bruteForceKnapsack(weights, values, remaining_capacity, index + 1);

    // --- Branch 2: INCLUDE the current item (Check constraint first) ---
    int value_if_included = 0;
    
    // Check if the current item is light enough to fit in the remaining capacity.
    if (weights[index] <= remaining_capacity) {
        
        // If it fits, calculate the total value:
        // (Value of current item) + (Max value from the rest of the items with reduced capacity)
        value_if_included = values[index] + bruteForceKnapsack(
            weights, 
            values, 
            remaining_capacity - weights[index], // Capacity is reduced by the item's weight
            index + 1                           // Move to the next item
        );
    }

    // The brute force choice is the best result from the two branches.
    return std::max(value_if_included, value_if_excluded);
}

int main() {
    // Item data: Wt. | Value
    std::vector<int> weights = {10, 20, 30};
    std::vector<int> values = {60, 100, 120};
    int capacity = 50;
    int num_items = weights.size();

    std::cout << "--- 0/1 Knapsack Brute Force (O(2^N)) ---" << std::endl;
    std::cout << "Available Items:" << std::endl;
    for (size_t i = 0; i < num_items; ++i) {
        std::cout << "  Item " << i + 1 << ": Weight=" << weights[i] << ", Value=" << values[i] << std::endl;
    }
    std::cout << "Knapsack Capacity (W): " << capacity << std::endl;

    // Start the recursive process from the first item (index 0)
    int max_value = bruteForceKnapsack(weights, values, capacity, 0);

    std::cout << "\nMaximum value achievable: " << max_value << std::endl;
    // Expected result: 220 (taking items with weights 20 and 30, value 100 + 120)

    // Example 2: More items to show the exponential nature
    std::vector<int> w2 = {2, 5, 1, 3, 4};
    std::vector<int> v2 = {3, 7, 2, 4, 5};
    int c2 = 7;
    
    int max_value2 = bruteForceKnapsack(w2, v2, c2, 0);
    std::cout << "\n--- Example 2 (Capacity 7) ---" << std::endl;
    std::cout << "Maximum value achievable: " << max_value2 << std::endl;
    // Expected result: 11 (taking items with weights 5 and 1, value 7 + 2, and 1, value 4. or w=5(v=7) + w=2(v=3) = 10, or w=3(v=4) + w=4(v=5) = 9. w=2(v=3) + w=5(v=7) is best)

    return 0;
}
