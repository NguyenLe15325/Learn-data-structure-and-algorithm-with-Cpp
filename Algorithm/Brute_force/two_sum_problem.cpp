#include <iostream>
#include <vector>
#include <stdexcept>

/**
 * @brief Solves the Two Sum problem using the brute force (O(N^2)) approach.
 * * =========================================================================
 * THE TWO SUM PROBLEM DEFINITION
 * =========================================================================
 * Given an array of integers (nums) and a specific integer target (target),
 * the goal is to find the *indices* of the two numbers in the array that add 
 * up exactly to the target.
 * * We assume:
 * 1. Exactly one solution exists.
 * 2. We cannot use the same element twice (e.g., nums[i] must be used with 
 * nums[j], where i != j).
 * * Brute Force Strategy:
 * This method checks every single unique pair of elements (nums[i], nums[j])
 * in the array using nested loops until the required sum is found.
 * * Time Complexity: O(N^2)
 * The complexity is O(N^2) because for an array of size N, the outer loop runs 
 * N times, and the inner loop runs up to N times for each outer iteration.
 * * @param nums The input array of integers.
 * @param target The target sum.
 * @return A vector of two integers representing the indices [i, j].
 * @throws std::runtime_error if no solution is found.
 */
std::vector<int> twoSumBruteForce(const std::vector<int>& nums, int target) {
    int N = nums.size();

    // 1. Outer loop: Fixes the first number of the pair at index 'i'.
    for (int i = 0; i < N; ++i) {

        // 2. Inner loop: Fixes the second number of the pair at index 'j'.
        // Starting j at i + 1 ensures i != j and avoids redundant checks.
        for (int j = i + 1; j < N; ++j) {
            
            // 3. Check the condition.
            if (nums[i] + nums[j] == target) {
                
                // 4. Solution found! Return the indices.
                return {i, j};
            }
        }
    }

    // In competitive programming, we typically trust the input guarantees, 
    // but this ensures the function handles impossible cases gracefully.
    throw std::runtime_error("No two sum solution exists in the input array.");
}

/**
 * @brief Utility function to print the result vector.
 */
void printResult(const std::vector<int>& nums, int target, const std::vector<int>& result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    std::cout << "], Target: " << target << " -> Output Indices: [";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Test Case 1: Simple case (2 + 7 = 9)
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    
    // Test Case 2: Solution not at the beginning (2 + 4 = 6)
    std::vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    
    // Test Case 3: Duplicates are the solution (3 + 3 = 6)
    std::vector<int> nums3 = {3, 3};
    int target3 = 6;

    try {
        std::vector<int> result1 = twoSumBruteForce(nums1, target1);
        printResult(nums1, target1, result1);

        std::vector<int> result2 = twoSumBruteForce(nums2, target2);
        printResult(nums2, target2, result2);

        std::vector<int> result3 = twoSumBruteForce(nums3, target3);
        printResult(nums3, target3, result3);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
