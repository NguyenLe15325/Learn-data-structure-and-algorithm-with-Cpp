#include <iostream>
#include <algorithm> // For std::swap
#include <cmath>     // Required for floor() or simple integer division

/**
 * Custom Priority Queue Implementation using a Max Heap (Array-Based Tree).
 * This class prioritizes the LARGEST number (Max Heap).
 * It uses a dynamically allocated array and manual memory management.
 * * * Time Complexity:
 * - push (insert): O(log N)
 * - pop (extract max): O(log N)
 * - top (peek max): O(1)
 */
class PriorityQueue {
private:
    int* data;
    int currentSize;
    int currentCapacity;

    // Helper function to get the index of the parent node
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Helper function to get the index of the left child
    int left(int i) {
        return 2 * i + 1;
    }

    // Helper function to get the index of the right child
    int right(int i) {
        return 2 * i + 2;
    }

    // Doubles the capacity of the underlying array and copies elements
    void resizeAndCopy() {
        int newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        int* newData = new int[newCapacity];
        
        // Copy existing elements to the new, larger array
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }

        // Delete the old array memory
        delete[] data;

        // Update the pointer and capacity
        data = newData;
        currentCapacity = newCapacity;
    }
    
    // Restores the Max Heap property after an element is added.
    // The new element (at index i) bubbles UP towards the root.
    void heapifyUp(int i) {
        // While current node is not the root (i > 0) AND is larger than its parent
        while (i > 0 && data[i] > data[parent(i)]) {
            // Swap the node with its parent
            std::swap(data[i], data[parent(i)]);
            // Move up to the parent's index
            i = parent(i);
        }
    }

    // Restores the Max Heap property after the root (max) element is removed.
    // The new root (last element) sinks DOWN towards the leaves.
    void heapifyDown(int i) {
        int largest = i; // Start by assuming the current node is the largest
        int l = left(i);
        int r = right(i);

        // Check if the left child exists and is larger than the current largest
        if (l < currentSize && data[l] > data[largest]) {
            largest = l;
        }

        // Check if the right child exists and is larger than the current largest
        if (r < currentSize && data[r] > data[largest]) {
            largest = r;
        }

        // If the largest is not the current node, swap and continue sinking down
        if (largest != i) {
            std::swap(data[i], data[largest]);
            heapifyDown(largest); // Recursive call to continue checking the subtree
        }
    }

public:
    // Constructor
    PriorityQueue() : data(nullptr), currentSize(0), currentCapacity(0) {}

    // Destructor (Crucial for manual memory cleanup)
    ~PriorityQueue() {
        delete[] data;
    }

    // Add an element to the Priority Queue (O(log N))
    void push(int val) {
        if (currentSize == currentCapacity) {
            resizeAndCopy();
        }

        // 1. Insert the new element at the end (next available spot)
        data[currentSize] = val;
        currentSize++;

        // 2. Restore heap property by letting the new element bubble up
        heapifyUp(currentSize - 1);
    }

    // Remove the highest priority element (root) (O(log N))
    void pop() {
        if (empty()) {
            std::cerr << "Error: Cannot pop from an empty queue." << std::endl;
            return;
        }

        // 1. Replace the root (the element to be removed) with the last element
        data[0] = data[currentSize - 1];
        currentSize--;

        // 2. Restore heap property by letting the new root sink down
        heapifyDown(0);
    }

    // Peek at the highest priority element (O(1))
    int top() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty.");
        }
        return data[0]; // The max element is always at the root (index 0)
    }

    bool empty() const {
        return currentSize == 0;
    }

    int size() const {
        return currentSize;
    }
};

int main() {
    PriorityQueue pq;

    std::cout << "========================================" << std::endl;
    std::cout << "--- Custom Priority Queue (Max Heap) ---" << std::endl;
    std::cout << "========================================" << std::endl;

    // 1. Insert elements
    std::cout << "1. Pushing elements: 10, 50, 20, 100, 5, 70" << std::endl;
    pq.push(10); 
    pq.push(50); // 50 bubbles up
    pq.push(20);
    pq.push(100); // 100 bubbles all the way to the root
    pq.push(5);
    pq.push(70); // 70 bubbles up below 100

    std::cout << "   Current size: " << pq.size() << std::endl;
    std::cout << "   Highest Priority (Top): " << pq.top() << std::endl; // Should be 100

    // 2. Extract elements in priority order
    std::cout << "\n2. Extracting elements (Highest value first):" << std::endl;
    int count = 1;
    while (!pq.empty()) {
        int highest = pq.top();
        pq.pop(); 
        std::cout << "   " << count++ << ". Popped: " << highest;
        if (!pq.empty()) {
            std::cout << " | Next Top: " << pq.top();
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n3. Final state check:" << std::endl;
    std::cout << "   Is Empty? " << (pq.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
