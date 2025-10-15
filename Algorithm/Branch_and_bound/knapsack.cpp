/**
 * @file knapsack_branch_and_bound.cpp
 * @brief Solves the 0/1 Knapsack Problem using the Branch and Bound technique 
 * with a Best-First Search guided by an Upper Bound.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>

// --- Data Structures ---

/**
 * @brief Represents an item with weight, value, and calculated value-to-weight ratio.
 */
struct Item {
    int weight;
    int value;
    double ratio;
};

/**
 * @brief Represents a node in the search space tree.
 */
struct Node {
    int level;          // Index of the item currently being considered (-1 for root)
    int profit;         // Profit accumulated up to this node
    int weight;         // Weight accumulated up to this node
    double bound;       // The optimistic upper bound on max profit achievable from this node
};

/**
 * @brief Comparator function to sort items by value-to-weight ratio (descending).
 * This is the required greedy pre-sorting step for effective bounding.
 */
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

/**
 * @brief Comparator for the Max-Priority Queue.
 * We want the node with the highest 'bound' to be at the top (Best-First Search).
 */
struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        // Returns true if 'a' has lower priority (smaller bound) than 'b'
        return a.bound < b.bound;
    }
};

// --- Bounding Function ---

/**
 * @brief Calculates the upper bound of the total profit achievable from the given node.
 * This is done by solving the Fractional Knapsack Problem for the remaining items.
 * * @param u The current node.
 * @param W The total knapsack capacity.
 * @param arr The sorted list of all items.
 * @return The optimistic upper bound (double).
 */
double bound(Node u, int W, const std::vector<Item>& arr) {
    // If the current node's weight already exceeds capacity, the bound is 0 (or infinite negative).
    if (u.weight >= W) {
        return 0;
    }

    double result_bound = u.profit;
    int j = u.level + 1; // Start checking from the next item
    int current_weight = u.weight;
    int n = arr.size();

    // Fill the remaining capacity greedily using the remaining items (Fractional Knapsack)
    while (j < n && current_weight + arr[j].weight <= W) {
        current_weight += arr[j].weight;
        result_bound += arr[j].value;
        j++;
    }

    // If there are still items left, take a fraction of the next item to fill the gap
    if (j < n) {
        int remaining_capacity = W - current_weight;
        // Add the fractional value: (capacity remaining * ratio)
        result_bound += (double)remaining_capacity * arr[j].ratio;
    }

    return result_bound;
}

// --- Main Branch and Bound Function ---

/**
 * @brief Solves the 0/1 Knapsack Problem using the Branch and Bound technique.
 *
 * @param W Knapsack capacity.
 * @param items Vector of Item structures.
 * @return The maximum profit (int).
 */
int knapsackBB(int W, std::vector<Item>& items) {
    int n = items.size();

    // 1. Pre-sort items by value-to-weight ratio (Greedy Pre-processing)
    for (int i = 0; i < n; ++i) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    std::sort(items.begin(), items.end(), compareItems);

    // 2. Initialize Max-Priority Queue (Best-First Search)
    std::priority_queue<Node, std::vector<Node>, CompareNode> pq;

    // Initialize the root node (level -1, no items taken)
    Node u;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, W, items);

    pq.push(u);

    int max_profit = 0; // Tracks the best integer solution found so far (our incumbent)

    // 3. Core B&B Loop
    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        // PRUNING CHECK: If the node's bound is worse than the current max_profit, 
        // we can safely discard this branch entirely.
        if (u.bound < max_profit) {
            continue; 
        }

        // Branching: Move to the next item
        int level = u.level + 1;

        if (level == n) {
            // Reached a leaf node (all items considered). This is the end of a full solution.
            if (u.profit > max_profit) {
                max_profit = u.profit;
            }
            continue;
        }

        // --- BRANCH 1: INCLUDE the current item (left child) ---
        Node v = u; // Create the 'include' child node
        v.level = level;

        // Check feasibility: only include if capacity allows
        if (u.weight + items[level].weight <= W) {
            v.weight = u.weight + items[level].weight;
            v.profit = u.profit + items[level].value;

            // Update max_profit if we found a better, complete solution
            if (v.profit > max_profit) {
                max_profit = v.profit;
            }

            // Calculate bound for the included branch and push to PQ
            v.bound = bound(v, W, items);
            if (v.bound > max_profit) { // Check if this new branch is promising
                 pq.push(v);
            }
        }
        
        // --- BRANCH 2: EXCLUDE the current item (right child) ---
        Node v2 = u; // Create the 'exclude' child node
        v2.level = level;
        // Weight and profit remain the same as parent u (since item is excluded)

        // Calculate bound for the excluded branch and push to PQ
        v2.bound = bound(v2, W, items);
        if (v2.bound > max_profit) { // Check if this new branch is promising
             pq.push(v2);
        }
    }

    return max_profit;
}

int main() {
    // Capacity W
    int W = 10; 
    
    // Items: {Weight, Value}
    // Note: Items are defined here but will be sorted by ratio inside knapsackBB.
    std::vector<Item> raw_items = {
        {2, 10},  // Ratio: 5.0
        {5, 20},  // Ratio: 4.0
        {3, 15},  // Ratio: 5.0
        {7, 14}   // Ratio: 2.0
    };

    std::cout << "--- 0/1 Knapsack Problem (Branch and Bound) ---" << std::endl;
    std::cout << "Knapsack Capacity (W): " << W << std::endl;
    std::cout << "Available Items:" << std::endl;
    std::cout << "  | Wgt | Val | Ratio" << std::endl;
    std::cout << "  |-----|-----|-------" << std::endl;
    for (const auto& item : raw_items) {
        std::cout << "  | " << std::setw(3) << item.weight 
                  << " | " << std::setw(3) << item.value 
                  << " | " << std::fixed << std::setprecision(1) 
                  << (double)item.value / item.weight << std::endl;
    }
    std::cout << std::endl;

    // Ensure items used for the B&B function are copies of the raw data 
    // to allow internal sorting without affecting the printed list.
    std::vector<Item> sorted_items = raw_items; 
    
    int max_profit = knapsackBB(W, sorted_items);

    std::cout << "Maximum achievable profit: " << max_profit << std::endl; // Expected result: 45
    std::cout << "-----------------------------------------------" << std::endl;
    
    return 0;
}
