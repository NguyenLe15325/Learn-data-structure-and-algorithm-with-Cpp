#include <iostream>
#include <queue>   // The standard library header for std::queue
#include <string>

/**
 * Queue Implementation using the C++ Standard Template Library (STL).
 * The std::queue container adapter automatically provides FIFO behavior
 * (First-In, First-Out) and handles all memory management internally.
 * * * Key STL functions:
 * - push(): Adds an element to the back (rear).
 * - pop(): Removes the element from the front.
 * - front(): Returns a reference to the front element (peek).
 * - back(): Returns a reference to the back element (peek).
 * - empty(): Checks if the queue is empty.
 * - size(): Returns the number of elements.
 */

int main() {
    // 1. Creation and PUSH (Adding elements to the rear)
    // Create a queue of strings
    std::queue<std::string> customerQueue;

    std::cout << "=========================================" << std::endl;
    std::cout << "--- STL std::queue Demonstration (FIFO) ---" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "1. Pushing elements into the queue (FIFO Order):" << std::endl;
    
    // Add elements. "Customer A" is the first one in.
    customerQueue.push("Customer A (First In)");
    customerQueue.push("Customer B");
    customerQueue.push("Customer C (Last In)");
    
    std::cout << "   Current Size: " << customerQueue.size() << std::endl;
    std::cout << "   Front element (peek): " << customerQueue.front() << std::endl;
    std::cout << "   Back element (peek): " << customerQueue.back() << std::endl;

    // 2. FRONT and POP (Accessing and Removing elements)
    std::cout << "\n2. Processing queue (First Out is First In):" << std::endl;

    while (!customerQueue.empty()) {
        // FRONT: View the element at the front ("Customer A" first)
        std::cout << "   - Serving (FRONT): " << customerQueue.front() << std::endl;
        
        // POP: Remove the element from the front
        customerQueue.pop();
        
        std::cout << "     Customer served. Remaining size: " << customerQueue.size() << std::endl;
    }
    
    // 3. Final Check
    std::cout << "\n3. Final state check:" << std::endl;
    std::cout << "   Current Size: " << customerQueue.size() << std::endl;
    std::cout << "   Is Empty? " << (customerQueue.empty() ? "Yes" : "No") << std::endl;

    // Note: Always check for empty() before calling front(), back(), or pop() 
    // on STL queues, as it leads to undefined behavior if the queue is empty.
    
    return 0;
}
