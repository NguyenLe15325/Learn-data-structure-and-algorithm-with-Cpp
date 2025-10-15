#include <iostream>
#include <stdexcept> // For exceptions like std::out_of_range
#include <algorithm> // For std::min

/**
 * Custom implementation of a Dynamic Array (Vector) using raw C++ arrays (pointers).
 * This demonstrates manual memory management, capacity tracking, and the O(N) resize operation.
 */

template <typename T>
class MyVector {
private:
    T* data;        // Pointer to the start of the dynamically allocated array
    int currentSize;  // Number of elements currently stored (equivalent to vector::size())
    int currentCapacity; // Total number of elements the array can hold (equivalent to vector::capacity())

    // --- Core Logic: Handles dynamic resizing ---
    void resizeAndCopy(int newCapacity) {
        if (newCapacity <= currentCapacity) return;

        // 1. Allocate a new, larger block of memory
        T* newData = new T[newCapacity];
        
        // 2. Copy the existing elements from the old array to the new array
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }

        // 3. Deallocate the old memory block
        delete[] data;

        // 4. Update class members to point to the new data
        data = newData;
        currentCapacity = newCapacity;

        std::cout << "\n[INFO] Resized array to capacity: " << currentCapacity << std::endl;
    }

public:
    // Constructor
    MyVector(int initialCapacity = 2) : currentSize(0) {
        // Ensure minimum capacity
        currentCapacity = initialCapacity > 0 ? initialCapacity : 1; 
        // Allocate initial memory
        data = new T[currentCapacity];
    }

    // Destructor (Crucial for freeing manually allocated memory)
    ~MyVector() {
        delete[] data;
    }

    // --- Core Vector Operations ---

    // Adds an element to the end (O(1) amortized)
    void push_back(const T& value) {
        // Check if the array is full (size == capacity)
        if (currentSize == currentCapacity) {
            // Resize the array to double its current capacity
            resizeAndCopy(currentCapacity * 2);
        }
        // Add the new element
        data[currentSize] = value;
        currentSize++;
    }

    // Removes the last element (O(1))
    void pop_back() {
        if (currentSize == 0) {
            throw std::out_of_range("Vector is empty, cannot pop_back.");
        }
        currentSize--;
        // Optional: Could add logic here to shrink capacity if usage is very low.
    }

    // Access element by index (O(1))
    T& at(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds.");
        }
        return data[index];
    }

    // Read-only access to element by index (O(1))
    const T& operator[](int index) const {
        // Simple access operator, assumes index is valid for performance
        return data[index];
    }

    // Returns a reference to the last element (O(1))
    const T& back() const {
        if (currentSize == 0) {
            throw std::out_of_range("Vector is empty, cannot access back element.");
        }
        return data[currentSize - 1];
    }

    // Returns the number of elements (O(1))
    int size() const {
        return currentSize;
    }

    // Returns the total allocated memory capacity (O(1))
    int capacity() const {
        return currentCapacity;
    }
};

int main() {
    std::cout << "=================================================" << std::endl;
    std::cout << "--- Custom MyVector Demonstration (Dynamic Array) ---" << std::endl;
    std::cout << "=================================================" << std::endl;

    // Create a vector with an initial capacity of 2
    MyVector<int> vec(2); 
    
    std::cout << "Initial size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;

    // A. Testing Push Back (forcing resizes)
    std::cout << "\n--- A. Pushing elements (Watch for Resizing) ---" << std::endl;
    
    vec.push_back(10); // Size 1, Cap 2
    std::cout << "Pushed 10. Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;

    vec.push_back(20); // Size 2, Cap 2 -> FULL!
    std::cout << "Pushed 20. Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;

    vec.push_back(30); // Size 3. Should trigger resize (Cap 2 -> 4)
    std::cout << "Pushed 30. Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;
    
    vec.push_back(40); // Size 4, Cap 4
    std::cout << "Pushed 40. Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;

    vec.push_back(50); // Size 5. Should trigger resize (Cap 4 -> 8)
    std::cout << "Pushed 50. Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;

    // B. Testing Random Access and Pop Back
    std::cout << "\n--- B. Access and Removal ---" << std::endl;
    std::cout << "Element at index 2 (at()): " << vec.at(2) << " (Expected: 30)" << std::endl;
    std::cout << "Element at index 0 ([]): " << vec[0] << " (Expected: 10)" << std::endl;
    
    vec.pop_back(); // Remove 50
    std::cout << "pop_back called. Size: " << vec.size() << ", Last element is now " << vec.back() << std::endl;

    // C. Error Handling
    std::cout << "\n--- C. Error Handling ---" << std::endl;
    try {
        std::cout << "Accessing invalid index 10..." << std::endl;
        vec.at(10);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Error: " << e.what() << std::endl;
    }
    
    // Note: Memory cleanup (delete[] data) happens automatically when vec goes out of scope.

    return 0;
}
