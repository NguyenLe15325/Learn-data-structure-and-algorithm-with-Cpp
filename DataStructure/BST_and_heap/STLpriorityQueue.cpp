#include <iostream>
#include <queue>    // Required for std::priority_queue
#include <vector>   // The underlying container (default is std::vector)
#include <functional> // REQUIRED for std::greater to define the Min Heap comparator

/**
 * STL std::priority_queue Demonstration.
 * This container adapter implements a Binary Heap, providing O(log N) operations.
 * * Priority Order:
 * - Max Heap (Default): Uses std::less<T>. Largest value = Highest Priority.
 * - Min Heap (Custom): Uses std::greater<T>. Smallest value = Highest Priority.
 * * * Core Operations Time Complexity:
 * - push (insert element): O(log N)
 * - pop (extract max element): O(log N)
 * - top (peek max element): O(1)
 */
void demo_max_heap() {
    // Default implementation: Max Heap. 
    // Equivalent to: std::priority_queue<int, std::vector<int>, std::less<int>>
    std::priority_queue<int> max_pq; 

    std::cout << "\n--- MAX HEAP (Largest Value is Highest Priority) ---" << std::endl;
    
    // 1. Insertion (O(log N))
    max_pq.push(10); 
    max_pq.push(50); 
    max_pq.push(20); 
    max_pq.push(100); 

    std::cout << "Pushing 10, 50, 20, 100." << std::endl;
    std::cout << "Highest Priority (Top): " << max_pq.top() << " (Expected: 100)" << std::endl;

    // 2. Extraction (O(log N))
    std::cout << "\nExtracting elements (Should be largest first):" << std::endl;
    while (!max_pq.empty()) {
        int highest = max_pq.top(); // Peek (O(1))
        max_pq.pop();               // Remove (O(log N))
        std::cout << "  Popped: " << highest;
        if (!max_pq.empty()) {
            std::cout << " | Next Top: " << max_pq.top();
        }
        std::cout << std::endl;
    }
}

void demo_min_heap() {
    // Standard Min Heap implementation.
    // The three template parameters are required:
    // 1. int: The element type.
    // 2. std::vector<int>: The underlying container.
    // 3. std::greater<int>: The comparator, which prioritizes the SMALLER value.
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

    std::cout << "\n--- MIN HEAP (Smallest Value is Highest Priority) ---" << std::endl;
    
    // 1. Insertion (O(log N)) - Push the original positive values
    min_pq.push(10); 
    min_pq.push(50); 
    min_pq.push(20); 
    min_pq.push(100); 

    std::cout << "Pushing 10, 50, 20, 100." << std::endl;
    std::cout << "Highest Priority (Top): " << min_pq.top() << " (Expected: 10)" << std::endl;

    // 2. Extraction (O(log N))
    std::cout << "\nExtracting elements (Should be smallest first):" << std::endl;
    while (!min_pq.empty()) {
        int highest = min_pq.top(); 
        min_pq.pop();               
        std::cout << "  Popped: " << highest;
        if (!min_pq.empty()) {
            std::cout << " | Next Top: " << min_pq.top();
        }
        std::cout << std::endl;
    }
}


int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "--- STL std::priority_queue Demonstration ---" << std::endl;
    std::cout << "=========================================" << std::endl;

    demo_max_heap();
    
    std::cout << "\n-----------------------------------------" << std::endl;

    demo_min_heap();

    return 0;
}
