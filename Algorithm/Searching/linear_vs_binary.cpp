/**
 * @file search_benchmark.cpp
 * @brief Performs a real-world time comparison between Linear Search (O(N)) and 
 * Binary Search (O(log N)) using a large dataset and high-resolution timing.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>

// --- Search Algorithm Implementations (from previous response) ---

/**
 * @brief Linear (Sequential) Search. Worst Case: O(N)
 */
int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; 
        }
    }
    return -1; 
}

/**
 * @brief Binary Search on a SORTED array. Worst Case: O(log N)
 */
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; 
        } 
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; 
}

// --- Main Benchmark Function ---

int main() {
    // Define the size of the dataset
    const int DATA_SIZE = 1000000; // 1 million elements
    std::vector<int> data(DATA_SIZE);
    
    // 1. Generate large, sorted dataset: [0, 1, 2, ..., 999999]
    for (int i = 0; i < DATA_SIZE; ++i) {
        data[i] = i;
    }

    // 2. Define the worst-case target (the very last element)
    int worst_case_target = DATA_SIZE - 1;

    std::cout << "--- Search Algorithm Benchmark ---" << std::endl;
    std::cout << "Dataset Size (N): " << DATA_SIZE << std::endl;
    std::cout << "Target (Worst Case): " << worst_case_target << " (last element)" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    // ===========================================
    // 3. BENCHMARK: LINEAR SEARCH (O(N))
    // ===========================================
    std::cout << "\n[1] Linear Search (O(N))" << std::endl;

    auto start_linear = std::chrono::high_resolution_clock::now();
    
    // Execute the search
    int linear_result = linearSearch(data, worst_case_target);
    
    auto end_linear = std::chrono::high_resolution_clock::now();
    
    // Calculate duration in microseconds (1/1,000,000 of a second)
    auto duration_linear = std::chrono::duration_cast<std::chrono::microseconds>(end_linear - start_linear).count();

    std::cout << "-> Result Index: " << linear_result << std::endl;
    std::cout << "-> Time Taken:   " << (double)duration_linear / 1000.0 << " milliseconds" << std::endl;

    // ===========================================
    // 4. BENCHMARK: BINARY SEARCH (O(log N))
    // ===========================================
    std::cout << "\n[2] Binary Search (O(log N))" << std::endl;

    auto start_binary = std::chrono::high_resolution_clock::now();

    // Execute the search
    int binary_result = binarySearch(data, worst_case_target);

    auto end_binary = std::chrono::high_resolution_clock::now();

    // Calculate duration in microseconds
    auto duration_binary = std::chrono::duration_cast<std::chrono::microseconds>(end_binary - start_binary).count();

    std::cout << "-> Result Index: " << binary_result << std::endl;
    std::cout << "-> Time Taken:   " << duration_binary << " microseconds" << std::endl;

    std::cout << "\n--------------------------------------------------" << std::endl;
    
    // 5. Comparison
    if (duration_linear > 0) {
        double ratio = (double)duration_linear / duration_binary;
        std::cout << "Binary Search was approximately " << ratio << "x faster!" << std::endl;
    }

    return 0;
}
