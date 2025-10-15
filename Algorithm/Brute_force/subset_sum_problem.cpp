#include <iostream>
#include <vector>
#include <numeric>

/**
 * @brief Solves the Subset Sum Problem using a recursive brute force approach.
 * * =========================================================================
 * THE SUBSET SUM PROBLEM DEFINITION
 * =========================================================================
 * Given a set of non-negative integers (stored in the vector 'set') and a 
 * target sum (targetSum), determine if there exists a subset of the given 
 * set whose elements sum up to the targetSum.
 * * * Brute Force Strategy (via Recursion):
 * This function explores every possible combination of elements by considering 
 * two choices for each item:
 * 1. Exclude the current element (set[n-1]) from the subset.
 * 2. Include the current element (set[n-1]) in the subset.
 * * The algorithm continues until the target sum is reached or all elements 
 * have been processed.
 * * * Time Complexity: O(2^N)
 * The complexity is exponential because the function makes up to two 
 * recursive calls for every element, leading to a decision tree with 2^N leaves.
 * * @param set The input vector of non-negative integers.
 * @param n The current size of the set (or number of remaining elements to check).
 * @param targetSum The target sum we are trying to achieve.
 * @return true if a subset with the targetSum is found, false otherwise.
 */
bool isSubsetSum(const std::vector<int>& set, int n, int targetSum) {
    // --- Base Cases ---

    // 1. If the target sum is 0, we have found a valid subset (an empty one 
    //    if the recursion is at the start, or a combination of included elements 
    //    if targetSum has been reduced to 0).
    if (targetSum == 0) {
        return true;
    }

    // 2. If all elements have been processed (n == 0) and the target sum is 
    //    still greater than 0, no valid subset exists.
    if (n == 0) {
        return false;
    }

    // --- Recursive Step ---

    // If the last element (set[n-1]) is greater than the targetSum, it 
    // cannot be included in the subset. We only recurse on the remaining elements.
    if (set[n - 1] > targetSum) {
        return isSubsetSum(set, n - 1, targetSum);
    }

    // Otherwise, the element set[n-1] is a candidate. We explore two possibilities:
    
    // Possibility 1: EXCLUDE the current element.
    // The targetSum remains the same, and we move to the next element (n-1).
    bool excluded = isSubsetSum(set, n - 1, targetSum);

    // Possibility 2: INCLUDE the current element.
    // The targetSum is reduced by the element's value, and we move to the next element (n-1).
    bool included = isSubsetSum(set, n - 1, targetSum - set[n - 1]);

    // Return true if EITHER including or excluding the current element leads to a solution.
    return excluded || included;
}

/**
 * @brief Main function to test the Subset Sum function.
 */
int main() {
    // Test Case 1: Solution exists (11 + 6 = 17)
    std::vector<int> set1 = {3, 34, 4, 12, 5, 2};
    int target1 = 17;
    
    // Test Case 2: Solution exists (5 + 10 = 15)
    std::vector<int> set2 = {1, 2, 5, 8, 10};
    int target2 = 15;

    // Test Case 3: No solution exists
    std::vector<int> set3 = {1, 3, 5, 8};
    int target3 = 7;

    std::cout << "--- Subset Sum Problem (Brute Force Recursive) ---" << std::endl;

    // Run Test 1
    std::cout << "Set 1: {3, 34, 4, 12, 5, 2}, Target: " << target1 << std::endl;
    if (isSubsetSum(set1, set1.size(), target1)) {
        std::cout << "Result: Found a subset with sum " << target1 << "." << std::endl;
    } else {
        std::cout << "Result: No subset found with sum " << target1 << "." << std::endl;
    }
    std::cout << "---------------------------------------------------" << std::endl;

    // Run Test 2
    std::cout << "Set 2: {1, 2, 5, 8, 10}, Target: " << target2 << std::endl;
    if (isSubsetSum(set2, set2.size(), target2)) {
        std::cout << "Result: Found a subset with sum " << target2 << "." << std::endl;
    } else {
        std::cout << "Result: No subset found with sum " << target2 << "." << std::endl;
    }
    std::cout << "---------------------------------------------------" << std::endl;
    
    // Run Test 3
    std::cout << "Set 3: {1, 3, 5, 8}, Target: " << target3 << std::endl;
    if (isSubsetSum(set3, set3.size(), target3)) {
        std::cout << "Result: Found a subset with sum " << target3 << "." << std::endl;
    } else {
        std::cout << "Result: No subset found with sum " << target3 << "." << std::endl;
    }
    std::cout << "---------------------------------------------------" << std::endl;


    return 0;
}
