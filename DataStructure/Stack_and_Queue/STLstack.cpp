#include <iostream>
#include <stack>   // The standard library header for std::stack
#include <string>

/**
 * Stack Implementation using the C++ Standard Template Library (STL).
 * The std::stack container adapter automatically provides LIFO behavior
 * and handles all memory management internally.
 * * Key STL functions:
 * - push(): Adds an element to the top.
 * - pop(): Removes the element from the top.
 * - top(): Returns a reference to the top element without removing it.
 * - empty(): Checks if the stack is empty.
 * - size(): Returns the number of elements.
 */

int main() {
    // 1. Creation and PUSH (Adding elements)
    // Create a stack of strings
    std::stack<std::string> taskStack;

    std::cout << "==========================================" << std::endl;
    std::cout << "--- STL std::stack Demonstration (LIFO) ---" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    std::cout << "1. Pushing elements onto the stack (LIFO):" << std::endl;
    
    // Add elements. "Task 3" is the last one in.
    taskStack.push("Task 1: Initialize system");
    taskStack.push("Task 2: Process user data");
    taskStack.push("Task 3: Generate report (Last In)");
    
    std::cout << "   Current Size: " << taskStack.size() << std::endl;
    std::cout << "   Is Empty? " << (taskStack.empty() ? "Yes" : "No") << std::endl;

    // 2. TOP and POP (Accessing and Removing elements)
    std::cout << "\n2. Processing stack (First Out is Last In):" << std::endl;

    // We loop until the stack is empty
    while (!taskStack.empty()) {
        // TOP: View the element at the top ("Task 3" first)
        std::cout << "   - Next task (TOP): " << taskStack.top() << std::endl;
        
        // POP: Remove the element from the top
        taskStack.pop();
        
        std::cout << "     Task finished. Remaining size: " << taskStack.size() << std::endl;
    }
    
    // 3. Final Check
    std::cout << "\n3. Final state check:" << std::endl;
    std::cout << "   Current Size: " << taskStack.size() << std::endl;
    std::cout << "   Is Empty? " << (taskStack.empty() ? "Yes" : "No") << std::endl;

    // Note: Always check for empty() before calling top() or pop() on STL stacks,
    // as doing so on an empty stack results in undefined behavior (a crash).
    
    return 0;
}
