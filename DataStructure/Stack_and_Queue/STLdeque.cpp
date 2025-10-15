#include <iostream>
#include <deque>   // The standard library header for std::deque
#include <string>

/**
 * Deque (Double-Ended Queue) Implementation using the C++ Standard Template Library (STL).
 * std::deque is a sequence container that allows fast insertion and deletion at
 * both the beginning and the end, making it versatile for both Stack and Queue roles.
 * * Key STL functions:
 * - push_front(): Adds an element to the front (O(1)).
 * - push_back(): Adds an element to the back (O(1)).
 * - pop_front(): Removes the element from the front (O(1)).
 * - pop_back(): Removes the element from the back (O(1)).
 * - front(): Views the front element.
 * - back(): Views the back element.
 */

void print_deque(const std::deque<std::string>& dq) {
    if (dq.empty()) {
        std::cout << "   Deque: [Empty]" << std::endl;
        return;
    }
    std::cout << "   Deque (Front -> Back): ";
    for (const auto& item : dq) {
        std::cout << item << " | ";
    }
    std::cout << "(Size: " << dq.size() << ")" << std::endl;
}

int main() {
    // 1. Creation
    // Create a deque of strings
    std::deque<std::string> transactionLog;

    std::cout << "=========================================" << std::endl;
    std::cout << "--- STL std::deque Demonstration ---" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // 2. PUSH FRONT & PUSH BACK
    std::cout << "2. Adding elements (Front and Back):" << std::endl;
    
    // Push Back (Queue-like behavior)
    transactionLog.push_back("Transaction B"); // Front: | B |
    transactionLog.push_back("Transaction C"); // Front: | B | C |
    
    // Push Front (Stack-like behavior)
    transactionLog.push_front("Transaction A"); // Front: | A | B | C |
    
    print_deque(transactionLog);
    
    // 3. FRONT and BACK (Peek)
    std::cout << "\n3. Peeking at ends:" << std::endl;
    std::cout << "   Front element: " << transactionLog.front() << std::endl;
    std::cout << "   Back element: " << transactionLog.back() << std::endl;

    // 4. POP FRONT & POP BACK
    std::cout << "\n4. Removing elements (Bidirectional Pop):" << std::endl;

    // POP BACK: Remove C (Last In)
    std::cout << "   Pop Back: Removing " << transactionLog.back() << std::endl;
    transactionLog.pop_back(); 
    print_deque(transactionLog); // Front: | A | B |
    
    // POP FRONT: Remove A (First In)
    std::cout << "   Pop Front: Removing " << transactionLog.front() << std::endl;
    transactionLog.pop_front(); 
    print_deque(transactionLog); // Front: | B |
    
    // 5. Final Cleanup
    std::cout << "\n5. Final cleanup:" << std::endl;
    if (!transactionLog.empty()) {
        std::cout << "   Popping final element: " << transactionLog.front() << std::endl;
        transactionLog.pop_front();
    }
    
    // 6. Final state check
    std::cout << "   Is Empty? " << (transactionLog.empty() ? "Yes" : "No") << std::endl;
    
    return 0;
}

