#include <iostream>
#include <stdexcept> // For standard exception classes like std::out_of_range
#include <string>    // Used for the demo data type (std::string) and output (std::cout)

/**
 * Stack Implementation using a MANUAL Dynamic Array (C++ Pointers and new/delete[])
 * * This Stack follows the LIFO (Last-In, First-Out) principle.
 * * It manually implements dynamic resizing when the array runs out of space.
 */

// --- Stack Class (Based on a manually managed array) ---
template <typename T>
class Stack {
private:
    T* data;         // The pointer to the dynamically allocated array
    int capacity;    // Current size of the allocated memory block
    int topIndex;    // Index of the next available slot (also represents the number of elements/size)

    static const int DEFAULT_CAPACITY = 10;

    // Helper function to dynamically resize the array
    void resize(int newCapacity) {
        // 1. Allocate a new array with the new capacity
        T* newData = new T[newCapacity];

        // 2. Copy existing elements to the new array
        // We only copy up to topIndex (the current size)
        for (int i = 0; i < topIndex; ++i) {
            newData[i] = data[i];
        }

        // 3. ESSENTIAL: Deallocate the OLD array memory
        delete[] data;

        // 4. Update the stack's pointers and capacity
        data = newData;
        capacity = newCapacity;

        std::cout << "\n[INFO: Array manually resized to " << capacity << "]" << std::endl;
    }

public:
    // Constructor: Allocates initial memory
    Stack() : data(new T[DEFAULT_CAPACITY]), capacity(DEFAULT_CAPACITY), topIndex(0) {}

    // Destructor: CRUCIAL for freeing the manually allocated memory
    ~Stack() {
        delete[] data;
    }
    
    // Check if the stack is empty (O(1))
    bool isEmpty() const {
        return topIndex == 0;
    }

    // Get the current number of elements (O(1))
    int size() const {
        return topIndex;
    }

    // 1. PUSH Operation: Add an element to the top (O(1) amortized)
    void push(const T& val) {
        if (topIndex == capacity) {
            // Resize if the array is full (e.g., double the capacity)
            resize(capacity * 2);
        }
        data[topIndex] = val; // Add element at the current top index
        topIndex++;           // Increment to point to the next available slot
    }

    // 2. POP Operation: Remove and return the top element (O(1))
    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot pop from an empty stack.");
        }
        
        // Decrement the top index first (since topIndex is one past the last element)
        topIndex--;
        T poppedValue = data[topIndex];
        
        return poppedValue;
    }

    // 3. TOP Operation: Get the top element without removing it (O(1))
    const T& top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty; cannot view top element.");
        }
        // The top element is at index topIndex - 1
        return data[topIndex - 1];
    }
    
    // --- Key Function: Clear the entire stack ---
    void clear() {
        // Resetting topIndex is the minimum for a logical clear. 
        // We reuse the current memory buffer.
        topIndex = 0;
    }

    // Display the stack from top to bottom
    void display() const {
        if (isEmpty()) {
            std::cout << "Stack: [Empty]" << std::endl;
            return;
        }

        std::cout << "Stack (LIFO - Manual Array Based, Capacity: " << capacity << "): " << std::endl;
        
        // Iterate backward from the top (topIndex - 1) to the bottom (index 0)
        for (int i = topIndex - 1; i >= 0; --i) {
            std::cout << "  | " << data[i] << " | <-- " << (i == topIndex - 1 ? "TOP" : " (Popped later)") << std::endl;
            std::cout << "  +-----+" << std::endl;
        }
    }
};

int main() {
    // Demonstrate with strings and manually trigger the resize logic
    Stack<std::string> bookStack;
    
    std::cout << "========================================" << std::endl;
    std::cout << "--- 1. PUSH and Resize Demo (Manual) ---" << std::endl;
    std::cout << "========================================" << std::endl;

    // Use isEmpty() check
    std::cout << "Is stack empty? " << (bookStack.isEmpty() ? "Yes" : "No") << std::endl;
    
    // Push 10 items to fill the initial capacity of 10
    for (int i = 1; i <= 10; ++i) {
        bookStack.push("Item " + std::to_string(i));
    }
    
    // This push (Item 11) will trigger the resize logic from 10 to 20
    std::cout << "\nPushing Item 11, which triggers a resize..." << std::endl;
    bookStack.push("Item 11 (Trigger Resize)"); 
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
    std::cout << "Popping (First Out): " << bookStack.pop() << std::endl;
    std::cout << "New stack size: " << bookStack.size() << std::endl;
    
    // --- 4. clear() Demo ---
    std::cout << "\n========================================" << std::endl;
    std::cout << "--- 4. Clear and isEmpty() Demo ---" << std::endl;
    std::cout << "========================================" << std::endl;
    
    bookStack.clear();
    std::cout << "Stack size after clear: " << bookStack.size() << std::endl;

    // Use isEmpty() check after clear
    std::cout << "Is stack empty now? " << (bookStack.isEmpty() ? "Yes" : "No") << std::endl;

    // Demonstrate error handling on empty stack
    try {
        std::cout << "\nAttempting to Pop empty stack..." << std::endl;
        bookStack.pop(); 
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Error: " << e.what() << std::endl;
    }


    return 0;
}
