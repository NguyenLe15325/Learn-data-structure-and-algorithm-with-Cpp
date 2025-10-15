#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Performs a brute force Linear Search to find a target value in an unsorted array.
 * * =========================================================================
 * LINEAR SEARCH ALGORITHM (BRUTE FORCE)
 * =========================================================================
 * This is the most straightforward search method. It sequentially checks 
 * every element of the array until a match for the target value is found.
 * * * * Brute Force Strategy:
 * The algorithm starts at the first element (index 0) and moves through the 
 * array one step at a time, comparing the current element to the search key.
 * * * * Time Complexity: O(N)
 * In the worst-case scenario (the target is the last element or not present), 
 * the algorithm must check all N elements.
 * * @param arr The input array (vector) of integers.
 * @param target The integer value to search for.
 * @return The index of the first occurrence of the target, or -1 if not found.
 */
int linearSearch(const std::vector<int>& arr, int target) {
    int N = arr.size();

    // Loop through every single element in the array from start to end (0 to N-1).
    for (int i = 0; i < N; ++i) {
        // Brute force comparison: check if the current element matches the target.
        if (arr[i] == target) {
            // Match found! Return the index immediately.
            return i;
        }
    }

    // If the loop completes without finding the target, it means the element is not present.
    return -1;
}

int main() {
    // Unsorted test array
    std::vector<int> data = {45, 12, 89, 3, 55, 7, 20};
    int target1 = 55; // Expected: Index 4
    int target2 = 12; // Expected: Index 1
    int target3 = 100; // Expected: Index -1 (Not Found)

    std::cout << "--- Unsorted Search (Linear Search O(N)) ---" << std::endl;
    std::cout << "Array: {45, 12, 89, 3, 55, 7, 20}" << std::endl;
    
    // Search for target1
    int result1 = linearSearch(data, target1);
    std::cout << "Searching for " << target1 << ": ";
    if (result1 != -1) {
        std::cout << "Found at index " << result1 << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    // Search for target2
    int result2 = linearSearch(data, target2);
    std::cout << "Searching for " << target2 << ": ";
    if (result2 != -1) {
        std::cout << "Found at index " << result2 << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    // Search for target3
    int result3 = linearSearch(data, target3);
    std::cout << "Searching for " << target3 << ": ";
    if (result3 != -1) {
        std::cout << "Found at index " << result3 << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    return 0;
}
