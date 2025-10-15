#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

/**
 * @brief Finds the maximum possible sum of a contiguous subarray using the brute force approach.
 * * =========================================================================
 * THE MAXIMUM SUBARRAY SUM PROBLEM DEFINITION
 * =========================================================================
 * Given an array of integers (which can include negative numbers), the goal 
 * is to find the contiguous subarray (a sequence of one or more adjacent 
 * elements) that has the largest sum.
 * * * Brute Force Strategy (O(N^2)):
 * This method iterates through all possible starting indices (i) and, for each 
 * starting index, iterates through all possible ending indices (j). As it moves
 * the ending index 'j', it incrementally calculates the sum of the current 
 * subarray [i...j] and updates the overall maximum sum found so far.
 * * * Time Complexity: O(N^2)
 * The complexity is quadratic because of the two nested loops: the outer loop 
 * runs N times (for the start index), and the inner loop runs up to N times 
 * (for the end index).
 * * @param nums The input array of integers.
 * @return The maximum sum found for any contiguous subarray.
 */
int maxSubArraySum(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    // Initialize maxSoFar with the smallest possible integer value 
    // to correctly handle arrays with large negative numbers.
    int maxSoFar = std::numeric_limits<int>::min();
    int N = nums.size();

    // 1. Outer loop: Selects the starting point 'i' of the subarray.
    for (int i = 0; i < N; ++i) {
        
        // Reset the sum for every new starting position 'i'.
        int currentSubarraySum = 0; 

        // 2. Inner loop: Selects the ending point 'j' and calculates the sum 
        // for all subarrays starting at 'i'.
        for (int j = i; j < N; ++j) {
            
            // Add the next element to the current running sum for the subarray [i...j].
            currentSubarraySum += nums[j];
            
            // 3. Update the global maximum sum found across ALL subarrays checked so far.
            maxSoFar = std::max(maxSoFar, currentSubarraySum);
        }
    }

    return maxSoFar;
}

int main() {
    // Test Case 1: The standard example (Sum is 6: [4, -1, 2, 1])
    std::vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    // Expected: 6
    
    // Test Case 2: Array with all negative numbers (Max sum is -1)
    std::vector<int> nums2 = {-2, -3, -1, -5, -4};
    // Expected: -1 (Since a subarray must contain at least one element)

    // Test Case 3: Simple array (Max sum is 23: [10, 5, 8])
    std::vector<int> nums3 = {1, -2, 10, 5, 8, -100};
    // Expected: 23

    std::cout << "--- Maximum Subarray Sum (Brute Force O(N^2)) ---" << std::endl;

    std::cout << "Test 1: Result: " << maxSubArraySum(nums1) << " (Expected: 6)" << std::endl;
    std::cout << "Test 2: Result: " << maxSubArraySum(nums2) << " (Expected: -1)" << std::endl;
    std::cout << "Test 3: Result: " << maxSubArraySum(nums3) << " (Expected: 23)" << std::endl;

    return 0;
}
