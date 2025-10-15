#include <iostream>
#include <array>
#include <numeric> // For std::accumulate

void demonstrate_arrays() {
    // --- 1. Basic C-style Array (Fixed Size) ---
    std::cout << "--- 1. C-style Array Demonstration ---" << std::endl;

    // Declaration and Initialization
    int numbers[5] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    std::cout << "Initial array elements: ";
    for (int i = 0; i < size; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";

    // Accessing elements (O(1) time complexity)
    std::cout << "Accessing element at index 2: " << numbers[2] << " (which is 30)" << std::endl;

    // Modifying an element
    numbers[0] = 100;
    std::cout << "Element at index 0 after modification: " << numbers[0] << std::endl;

    std::cout << "\n";

    // --- 2. Using std::array (Modern C++) ---
    std::cout << "--- 2. std::array Demonstration (Fixed Size Container) ---" << std::endl;

    // Declaration and Initialization (size is part of the type)
    std::array<double, 4> decimals = {1.5, 2.5, 3.5, 4.5};

    // Accessing elements
    std::cout << "Element at index 3 using .at(): " << decimals.at(3) << " (with bounds checking)" << std::endl;

    // Traversal (using a C++ range-based for loop - highly recommended)
    std::cout << "Traversing std::array: ";
    for (const auto& element : decimals) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    // Getting size
    std::cout << "Size of std::array: " << decimals.size() << std::endl;

    // Using an STL algorithm (e.g., calculating the sum)
    double sum = std::accumulate(decimals.begin(), decimals.end(), 0.0);
    std::cout << "Sum of elements using std::accumulate: " << sum << std::endl;
}

int main() {
    demonstrate_arrays();
    return 0;
}