#include <iostream>
#include <stdexcept> // For standard exception classes like std::out_of_range
#include <string>

/**
 * Stack Implementation using a Linked List (Generic/Templated)
 * * This Stack follows the LIFO (Last-In, First-Out) principle.
 * Operations:
 * 1. Push: Adds an element to the top (O(1)).
 * 2. Pop: Removes and returns the top element (O(1)).
 * 3. Top: Views the top element without removing it (O(1)).
 * * The 'top' of the stack is implemented as the 'head' of the linked list.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    // Constructor
    Node(const T& val) : data(val), next(nullptr) {}
};

// --- Stack Class ---
template <typename T>
class Stack {
private:
    Node<T>* topPtr; // Pointer to the top of the stack (head of the list)
    int stackSize;

public:
    // Constructor
    Stack() : topPtr(nullptr), stackSize(0) {}

    // Destructor: Cleans up all nodes
    ~Stack() {
        clear(); // Use the clear function for cleanup
    }

    // Check if the stack is empty (O(1))
    bool isEmpty() const {
        return topPtr == nullptr;
    }

    // Get the current size of the stack (O(1))
    int size() const {
        return stackSize;
    }

    // 1. PUSH Operation: Add an element to the top (O(1))
    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = topPtr; // New node points to the current top
        topPtr = newNode;        // New node becomes the new top
        stackSize++;
    }

    // 2. POP Operation: Remove and return the top element (O(1))
    T pop() {
        if (isEmpty()) {
            // Throw exception if popping from an empty stack
            throw std::out_of_range("Cannot pop from an empty stack.");
        }
        
        Node<T>* oldTop = topPtr;
        T poppedValue = oldTop->data;
        
        topPtr = topPtr->next; // Move topPtr to the next node
        
        delete oldTop; // Free memory
        stackSize--;
        
        return poppedValue;
    }

    // 3. TOP Operation: Get the top element without removing it (O(1))
    const T& top() const {
        if (isEmpty()) {
            // Throw exception if trying to view an empty stack
            throw std::out_of_range("Stack is empty; cannot view top element.");
        }
        return topPtr->data;
    }
    
    // --- Key Function: Clear the entire stack (Crucial for memory management) ---
    void clear() {
        while (topPtr != nullptr) {
            Node<T>* temp = topPtr;
            topPtr = topPtr->next;
            delete temp;
        }
        stackSize = 0;
    }

    // Display the stack from top to bottom
    void display() const {
        if (isEmpty()) {
            std::cout << "Stack: [Empty]" << std::endl;
            return;
        }

        Node<T>* current = topPtr;
        std::cout << "Stack (LIFO): " << std::endl;
        while (current != nullptr) {
            std::cout << "  | " << current->data << " | <-- TOP" << (current == topPtr ? "" : " (Popped later)") << std::endl;
            std::cout << "  +-----+" << std::endl;
            current = current->next;
        }
    }
};

int main() {
    // Demonstrate with strings (LIFO order: C then B then A)
    Stack<std::string> bookStack;
    
    std::cout << "========================================" << std::endl;
    std::cout << "--- 1. PUSH and Initial Display Demo ---" << std::endl;
    std::cout << "========================================" << std::endl;

    // Use isEmpty() check
    std::cout << "Is stack empty? " << (bookStack.isEmpty() ? "Yes" : "No") << std::endl;

    // PUSH Operations
    bookStack.push("A: Intro to C++"); // Pushed 1st
    bookStack.push("B: Data Structures"); // Pushed 2nd
    bookStack.push("C: Algorithms"); // Pushed 3rd (TOP)
    
    bookStack.display();
    
    // --- 2. size() and top() Demo ---
    std::cout << "\n========================================" << std::endl;
    std::cout << "--- 2. size() and top() Demo (O(1))  ---" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Current stack size: " << bookStack.size() << std::endl;
    std::cout << "Top element is (using top()): " << bookStack.top() << std::endl;

    // --- 3. POP Demo ---
    std::cout << "\n========================================" << std::endl;
    std::cout << "--- 3. POP Demo (LIFO) ---" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Popping (First Out): " << bookStack.pop() << std::endl; // Popped 'C'
    std::cout << "New stack size: " << bookStack.size() << std::endl;
    std::cout << "New top element: " << bookStack.top() << std::endl;

    std::cout << "\nPopping (Next Out): " << bookStack.pop() << std::endl; // Popped 'B'
    bookStack.display(); // Only 'A' remains
    
    // --- 4. isEmpty() and Error Handling Demo ---
    std::cout << "\n========================================" << std::endl;
    std::cout << "--- 4. Final POP and Error Handling ---" << std::endl;
    std::cout << "========================================" << std::endl;
    
    bookStack.pop(); // Pop 'A'
    std::cout << "Popped final item. Stack size: " << bookStack.size() << std::endl;

    // Use isEmpty() check after final pop
    std::cout << "Is stack empty now? " << (bookStack.isEmpty() ? "Yes" : "No") << std::endl;

    // Demonstrate error handling on empty stack
    try {
        std::cout << "Attempting to Pop empty stack..." << std::endl;
        bookStack.pop(); 
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Error: " << e.what() << std::endl;
    }

    // --- 5. clear() Demo (Memory Management) ---
    // Note: Since the stack is already empty, this mainly demonstrates a safe operation.
    // The destructor calls clear() automatically, but we demonstrate it explicitly.
    std::cout << "\n========================================" << std::endl;
    std::cout << "--- 5. clear() Demo ---" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Stack is already empty, but calling clear() ensures memory cleanup." << std::endl;
    bookStack.clear();
    std::cout << "Stack size after clear: " << bookStack.size() << std::endl;


    return 0;
}
