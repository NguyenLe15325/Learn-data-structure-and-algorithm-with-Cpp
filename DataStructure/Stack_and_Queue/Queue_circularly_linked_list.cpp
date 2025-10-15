#include <iostream>
#include <stdexcept> // For std::out_of_range
#include <string>    // Used for the demo data type (std::string) and output
#include <type_traits> // For std::is_same_v

/**
 * Queue Implementation using a Generic CIRCULAR Linked List.
 * * This Queue follows the FIFO (First-In, First-Out) principle.
 * * It uses only ONE pointer (queueRear) for O(1) performance on all core operations.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    // The 'next' pointer is explicitly set during enqueue to maintain circularity
    Node(const T& val) : data(val), next(nullptr) {} 
};

// --- Queue Class ---
template <typename T>
class Queue {
private:
    Node<T>* queueRear;  // Only need a pointer to the REAR/TAIL node
    int queueSize;

public:
    // Constructor
    Queue() : queueRear(nullptr), queueSize(0) {}

    // Destructor: Cleans up all nodes
    ~Queue() {
        clear(); 
    }

    // Check if the queue is empty (O(1))
    bool isEmpty() const {
        // The list is empty if the rear pointer is null
        return queueRear == nullptr;
    }

    // Get the current size of the queue (O(1))
    int size() const {
        return queueSize;
    }

    // 1. ENQUEUE Operation: Add an element to the rear (O(1))
    void enqueue(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        
        if (isEmpty()) {
            // If empty, the new node is the only node. It points to itself.
            queueRear = newNode;
            queueRear->next = queueRear; 
        } else {
            // New node points to the current front (which is queueRear->next)
            newNode->next = queueRear->next; 
            // The old rear now points to the new node
            queueRear->next = newNode;
            // The new node becomes the new rear
            queueRear = newNode;
        }
        queueSize++;
    }

    // 2. DEQUEUE Operation: Remove and return the front element (O(1))
    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot dequeue from an empty queue.");
        }
        
        // The front is always queueRear->next
        Node<T>* oldFront = queueRear->next; 
        T dequeuedValue = oldFront->data;

        if (oldFront == queueRear) {
            // Case 1: Only one element left (front == rear)
            queueRear = nullptr; // List becomes empty
        } else {
            // Case 2: More than one element
            // Rear's next pointer bypasses the old front, linking directly to the new front
            queueRear->next = oldFront->next; 
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
        // Front is always the node after the rear
        return queueRear->next->data;
    }
    
    // Clear the entire queue (Crucial for memory management)
    void clear() {
        if (isEmpty()) return;
        
        Node<T>* current = queueRear->next; // Start at the front
        Node<T>* temp = nullptr;
        
        // Loop through all nodes starting from the front until we return to the front
        for (int i = 0; i < queueSize; ++i) {
            temp = current;
            current = current->next;
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

        Node<T>* current = queueRear->next; // Start at the front
        std::cout << "Queue (Circular FIFO): ";
        
        // Iterate exactly 'queueSize' times to avoid infinite loop
        for (int i = 0; i < queueSize; ++i) {
            // Handle different types for output clarity
            if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, char*>) {
                std::cout << "\"" << current->data << "\"";
            } else {
                std::cout << current->data;
            }
            
            if (i < queueSize - 1) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        
        std::cout << " [FRONT: " << queueRear->next->data 
                  << ", REAR: " << queueRear->data 
                  << ", Size: " << queueSize << "]" << std::endl;
    }
};

int main() {
    // ----------------------------------------------------
    // DEMO 1: Standard String Queue (Customer Processing)
    // ----------------------------------------------------
    Queue<std::string> customerQueue;
    
    std::cout << "========================================" << std::endl;
    std::cout << "--- DEMO 1: Circular String Queue ---" << std::endl;
    std::cout << "========================================" << std::endl;

    // A. Initial state check
    std::cout << "Initial check: Empty? " << (customerQueue.isEmpty() ? "Yes" : "No") 
              << ", Size: " << customerQueue.size() << std::endl;

    // B. ENQUEUE Demo - The first element will point to itself
    std::cout << "\n--- B. ENQUEUE (Add elements) ---" << std::endl;
    customerQueue.enqueue("Alpha"); // Becomes FRONT and REAR
    customerQueue.enqueue("Beta"); 
    customerQueue.enqueue("Gamma"); 
    customerQueue.display(); 

    // C. size() and front() Demo
    std::cout << "\n--- C. size() and front() (Peek) ---" << std::endl;
    std::cout << "Current size: " << customerQueue.size() << std::endl;
    std::cout << "Front element: " << customerQueue.front() << " (Expected: Alpha)" << std::endl;
    customerQueue.display(); 

    // D. DEQUEUE Demo
    std::cout << "\n--- D. DEQUEUE (FIFO Removal) ---" << std::endl;
    std::cout << "Processing (Dequeuing): " << customerQueue.dequeue() << std::endl; // Alpha removed
    std::cout << "Processing (Dequeuing): " << customerQueue.dequeue() << std::endl; // Beta removed
    customerQueue.display(); // Only Gamma remains

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
