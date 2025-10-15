#include <iostream>
#include <algorithm>  // For std::swap
#include <functional> // Required for std::less (Max Heap default) and std::greater (Min Heap)
#include <stdexcept>  // Required for throw std::out_of_range
#include <vector>     // For cleaner demonstration using a standard array type

/**
 * GENERIC Priority Queue Implementation using a Binary Heap (Array-Based Tree).
 * This class uses templates to support any data type (T) and any comparison logic (Compare).
 * * Max Heap (Default): PriorityQueue<int, std::less<int>> 
 * - The parent (A) is NOT less than the child (B). A >= B. (Largest on top)
 * Min Heap: PriorityQueue<int, std::greater<int>>
 * - The parent (A) is NOT greater than the child (B). A <= B. (Smallest on top)
 * * * * Time Complexity:
 * - push (insert): O(log N)
 * - pop (extract max/min): O(log N)
 * - buildHeap (from array): O(N)
 */

// T is the element type (e.g., int, float, struct).
// Compare defines the priority. Default is std::less<T> which creates a Max Heap.
template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
private:
    T* data;
    int currentSize;
    int currentCapacity;
    
    // The comparator object, which defines priority:
    // If comp(A, B) is true, it means A has LOWER priority than B.
    Compare comp;

    // Helper functions for array-to-tree navigation
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Doubles the capacity of the underlying array and copies elements
    void resizeAndCopy() {
        int newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        // Use a standard vector for temporary storage/copying, then back to T* if needed, 
        // but for a true custom implementation, we stick to T*.
        T* newData = new T[newCapacity];
        
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }

        delete[] data;

        data = newData;
        currentCapacity = newCapacity;
    }
    
    // Restores the heap property by moving the element at 'i' UP towards the root.
    void heapifyUp(int i) {
        // The heap property is violated if the parent (data[parent(i)]) 
        // has LOWER priority than the child (data[i]).
        // Since comp(A, B) means A has lower priority than B, we check:
        // Is the parent ordered before the child? If yes, swap!
        while (i > 0 && comp(data[parent(i)], data[i])) { 
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    // Restores the heap property by moving the element at 'i' DOWN towards the leaves.
    void heapifyDown(int i) {
        int highest_priority_index = i;
        int l = left(i);
        int r = right(i);

        // Check if left child exists and has HIGHER priority than current 'highest_priority_index'.
        // Check: Is 'highest_priority_index' lower priority than 'l'? (i.e., should 'l' be the parent?)
        if (l < currentSize && comp(data[highest_priority_index], data[l])) {
            highest_priority_index = l;
        }

        // Check if right child exists and has HIGHER priority than current 'highest_priority_index'.
        // Note: We compare against the current highest (which might be 'l' from the previous check).
        if (r < currentSize && comp(data[highest_priority_index], data[r])) {
            highest_priority_index = r;
        }

        // If a child had higher priority, swap and continue sinking down
        if (highest_priority_index != i) {
            std::swap(data[i], data[highest_priority_index]);
            heapifyDown(highest_priority_index); 
        }
    }

    // Builds the heap from existing data in O(N) time.
    void buildHeapFromExisting() {
        // Start from the last non-leaf node: (currentSize / 2) - 1
        for (int i = currentSize / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

public:
    // Constructor 1: Initializes an empty queue
    PriorityQueue() : data(nullptr), currentSize(0), currentCapacity(0) {}

    // Constructor 2: Builds a heap from an existing array (O(N) time)
    PriorityQueue(const T* arr, int n) : currentSize(n), currentCapacity(n) {
        if (n <= 0) {
            data = nullptr;
            currentSize = 0;
            currentCapacity = 0;
            return;
        }

        // 1. Allocate memory and copy all elements
        data = new T[n];
        for (int i = 0; i < n; ++i) {
            data[i] = arr[i];
        }

        // 2. Perform the O(N) bottom-up heap building
        buildHeapFromExisting();
    }

    // Destructor (Crucial for manual memory cleanup)
    ~PriorityQueue() { delete[] data; }

    // Add an element to the Priority Queue (O(log N))
    void push(const T& val) {
        if (currentSize == currentCapacity) {
            resizeAndCopy();
        }
        data[currentSize] = val;
        currentSize++;
        heapifyUp(currentSize - 1);
    }

    // Remove the highest priority element (root) (O(log N))
    void pop() {
        if (empty()) {
            std::cerr << "Error: Cannot pop from an empty queue." << std::endl;
            return;
        }
        data[0] = data[currentSize - 1]; // Replace root with last element
        currentSize--;
        heapifyDown(0); // Restore heap property
    }

    // Peek at the highest priority element (O(1))
    T top() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty.");
        }
        return data[0]; 
    }

    bool empty() const { return currentSize == 0; }
    int size() const { return currentSize; }
};

void demo_heap_functionality(const std::string& type_name, std::vector<int> elements, bool is_min_heap) {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "--- DEMO: " << type_name << " ---" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    // Create an instance based on the type requested
    if (is_min_heap) {
        // Min Heap: Smallest element has the highest priority.
        // We use std::greater<int> as the comparator.
        PriorityQueue<int, std::greater<int>> min_pq;
        std::cout << "Priority Rule: Smallest Value = Highest Priority (Min Heap)." << std::endl;
        for (int val : elements) {
            min_pq.push(val);
        }

        std::cout << "Highest Priority (Top): " << min_pq.top() << std::endl; 
        std::cout << "\nExtracting elements:" << std::endl;
        while (!min_pq.empty()) {
            std::cout << "  Popped: " << min_pq.top() << std::endl;
            min_pq.pop(); 
        }

    } else {
        // Max Heap: Largest element has the highest priority.
        // Uses the default std::less<int> comparator.
        PriorityQueue<int> max_pq; 
        std::cout << "Priority Rule: Largest Value = Highest Priority (Max Heap - Default)." << std::endl;
        for (int val : elements) {
            max_pq.push(val);
        }

        std::cout << "Highest Priority (Top): " << max_pq.top() << std::endl; 
        std::cout << "\nExtracting elements:" << std::endl;
        while (!max_pq.empty()) {
            std::cout << "  Popped: " << max_pq.top() << std::endl;
            max_pq.pop(); 
        }
    }
}

int main() {
    std::vector<int> elements = {50, 10, 80, 20, 90, 30};

    // 1. Max Heap Demonstration
    demo_heap_functionality("MAX HEAP (Default)", elements, false);
    
    // 2. Min Heap Demonstration
    demo_heap_functionality("MIN HEAP (Custom Comparator)", elements, true);

    return 0;
}
