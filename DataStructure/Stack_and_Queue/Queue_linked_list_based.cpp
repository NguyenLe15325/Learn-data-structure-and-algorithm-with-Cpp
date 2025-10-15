#include <iostream>
#include <stdexcept> // For std::out_of_range
#include <string>    // Used for the demo data type (std::string) and output

/**
 * Queue Implementation using a Generic Linked List.
 * * This Queue follows the FIFO (First-In, First-Out) principle.
 * * It uses two pointers (front and rear) for O(1) performance on all core operations.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& val) : data(val), next(nullptr) {}
};

// --- Queue Class ---
template <typename T>
class Queue {
private:
    Node<T>* queueFront; // Pointer to the front of the queue (element to be dequeued)
    Node<T>* queueRear;  // Pointer to the rear of the queue (where new elements are added)
    int queueSize;

public:
    // Constructor
    Queue() : queueFront(nullptr), queueRear(nullptr), queueSize(0) {}

    // Destructor: Cleans up all nodes
    ~Queue() {
        clear(); // Use the clear function for cleanup
    }

    // Check if the queue is empty (O(1))
    bool isEmpty() const {
        return queueFront == nullptr; // Can also check queueSize == 0
    }

    // Get the current size of the queue (O(1))
    int size() const {
        return queueSize;
    }

    // 1. ENQUEUE Operation: Add an element to the rear (O(1))
    void enqueue(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        
        if (isEmpty()) {
            // If the queue is empty, the new node is both the front and the rear
            queueFront = newNode;
            queueRear = newNode;
        } else {
            // The current rear node's 'next' pointer points to the new node
            queueRear->next = newNode;
            // The new node becomes the new rear
            queueRear = newNode;
        }
        queueSize++;
    }

    // 2. DEQUEUE Operation: Remove and return the front element (O(1))
    T dequeue() {
        if (isEmpty()) {
            // Throw exception if dequeuing from an empty queue
            throw std::out_of_range("Cannot dequeue from an empty queue.");
        }
        
        Node<T>* oldFront = queueFront;
        T dequeuedValue = oldFront->data;
        
        // Move front pointer to the next node
        queueFront = queueFront->next;
        
        // Check if the list became empty after removal
        if (queueFront == nullptr) {
            queueRear = nullptr; // Crucial: if front is null, rear must also be null
        }
        
        delete oldFront; // Free memory
        queueSize--;
        
        return dequeuedValue;
    }

    // 3. FRONT Operation: Get the front element without removing it (O(1))
    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty; cannot view front element.");
        }
        return queueFront->data;
    }
    
    // Clear the entire queue (Crucial for memory management)
    void clear() {
        // Repeatedly dequeue and delete all nodes until the queue is empty
        while (queueFront != nullptr) {
            Node<T>* temp = queueFront;
            queueFront = queueFront->next;
            delete temp;
        }
        queueRear = nullptr;
        queueSize = 0;
    }

    // Display the queue from front to rear
    void display() const {
        if (isEmpty()) {
            std::cout << "Queue: [Empty]" << std::endl;
            return;
        }

        Node<T>* current = queueFront;
        std::cout << "Queue (FIFO): ";
        while (current != nullptr) {
            // Handle different types for output clarity
            if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, char*>) {
                std::cout << "\"" << current->data << "\"";
            } else {
                std::cout << current->data;
            }
            
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << " [FRONT, REAR, Size: " << queueSize << "]" << std::endl;
    }
};

int main() {
    // ----------------------------------------------------
    // DEMO 1: Standard String Queue (Customer Processing)
    // ----------------------------------------------------
    Queue<std::string> customerQueue;
    
    std::cout << "========================================" << std::endl;
    std::cout << "--- DEMO 1: String Queue Operations ---" << std::endl;
    std::cout << "========================================" << std::endl;

    // A. Initial state check
    std::cout << "Initial check: Empty? " << (customerQueue.isEmpty() ? "Yes" : "No") 
              << ", Size: " << customerQueue.size() << std::endl;

    // B. ENQUEUE Demo
    std::cout << "\n--- B. ENQUEUE (Add elements) ---" << std::endl;
    customerQueue.enqueue("Alice"); 
    customerQueue.enqueue("Bob"); 
    customerQueue.enqueue("Charlie"); 
    customerQueue.display(); 

    // C. size() and front() Demo
    std::cout << "\n--- C. size() and front() (Peek) ---" << std::endl;
    std::cout << "Current size: " << customerQueue.size() << std::endl;
    std::cout << "Front element: " << customerQueue.front() << " (Expected: Alice)" << std::endl;
    customerQueue.display(); // List remains unchanged

    // D. DEQUEUE Demo
    std::cout << "\n--- D. DEQUEUE (FIFO Removal) ---" << std::endl;
    std::cout << "Processing (Dequeuing): " << customerQueue.dequeue() << std::endl; // Alice removed
    std::cout << "Processing (Dequeuing): " << customerQueue.dequeue() << std::endl; // Bob removed
    customerQueue.display(); // Only Charlie remains

    // E. clear() Demo
    std::cout << "\n--- E. clear() (Memory Cleanup) ---" << std::endl;
    customerQueue.enqueue("Final Customer");
    std::cout << "Size before clear: " << customerQueue.size() << std::endl;
    customerQueue.clear();
    std::cout << "Size after clear: " << customerQueue.size() << std::endl;
    customerQueue.display();
    
    // F. Error Handling Demo
    std::cout << "\n--- F. Error Handling (Empty Queue) ---" << std::endl;
    try {
        std::cout << "Attempting to Dequeue empty queue..." << std::endl;
        customerQueue.dequeue(); 
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Error: " << e.what() << std::endl;
    }
    
    // ----------------------------------------------------
    // DEMO 2: Integer Queue (Generic Template Use)
    // ----------------------------------------------------
    Queue<int> intQueue;
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "--- DEMO 2: Integer Queue (Templates) ---" << std::endl;
    std::cout << "========================================" << std::endl;
    
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);
    intQueue.display();
    
    std::cout << "Front item: " << intQueue.front() << std::endl;
    std::cout << "Dequeued item: " << intQueue.dequeue() << std::endl;
    intQueue.display();
    intQueue.clear();
    std::cout << "Int queue size after clear: " << intQueue.size() << std::endl;

    return 0;
}
