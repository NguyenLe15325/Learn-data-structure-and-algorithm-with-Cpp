#include <iostream>
#include <vector>   // The standard library header for std::vector
#include <string>

/**
 * STL std::vector Demonstration.
 * This container automatically handles memory, allocation, and resizing.
 * It provides O(1) access by index due to contiguous memory storage.
 * * * Key STL functions:
 * - push_back(): Adds an element to the end (O(1) amortized).
 * - pop_back(): Removes the last element (O(1)).
 * - at(), []: Accesses elements by index (O(1)).
 * - size(), capacity(): Get current usage and allocated size.
 * - insert(), erase(): Operations that are O(N) due to element shifting.
 */

// Helper function to display vector status
void print_vector_status(const std::vector<int>& vec, const std::string& label) {
    std::cout << label << " -> Size: " << vec.size() 
              << ", Capacity: " << vec.capacity() 
              << ", Elements: { ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "}" << std::endl;
}

int main() {
    // 1. Creation and Initialization
    std::vector<int> numbers;
    
    std::cout << "==========================================" << std::endl;
    std::cout << "--- STL std::vector Demonstration ---" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    print_vector_status(numbers, "Initial State");
    
    // 2. push_back (Forcing Resizes)
    std::cout << "\n2. Pushing Back (Vector Handles Resizing Automatically):" << std::endl;
    
    // Note: The doubling capacity behavior is implementation-dependent but common.
    numbers.push_back(100); 
    print_vector_status(numbers, "Pushed 100");
    
    numbers.push_back(200); 
    print_vector_status(numbers, "Pushed 200");
    
    // This push will likely trigger a resize (e.g., capacity 2 -> 4)
    numbers.push_back(300); 
    print_vector_status(numbers, "Pushed 300");
    
    numbers.push_back(400); 
    numbers.push_back(500); // This push will likely trigger a resize (e.g., capacity 4 -> 8)
    print_vector_status(numbers, "Pushed 500");

    // 3. Access and Peek
    std::cout << "\n3. Accessing Elements (O(1) Random Access):" << std::endl;
    std::cout << "   Element at index 1 (operator[]): " << numbers[1] << std::endl; // 200
    std::cout << "   Last element (back()): " << numbers.back() << std::endl;     // 500

    // 4. Insertion in the middle (O(N) operation)
    // Insertion at the beginning requires shifting all 5 elements
    std::cout << "\n4. Insertion (O(N)): Inserting '50' at the front." << std::endl;
    numbers.insert(numbers.begin(), 50); 
    print_vector_status(numbers, "After insert");

    // 5. Deletion in the middle (O(N) operation)
    // Erasing the element at index 2 (which is now 200) requires shifting subsequent elements
    std::cout << "\n5. Deletion (O(N)): Erasing element at index 2." << std::endl;
    numbers.erase(numbers.begin() + 2); // Erase the 200
    print_vector_status(numbers, "After erase");

    // 6. pop_back (O(1) constant time)
    std::cout << "\n6. Pop Back (O(1)): Removing last element." << std::endl;
    numbers.pop_back();
    print_vector_status(numbers, "After pop_back");

    return 0;
}
