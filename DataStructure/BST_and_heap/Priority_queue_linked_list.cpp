#include <iostream>
#include <stdexcept>

// 1. Define the Node structure
struct Node {
    int priority; 
    Node* next;

    Node(int val) : priority(val), next(nullptr) {}
};

/**
 * Priority Queue implemented using a Linked List sorted by priority.
 * This approach makes insertion O(N) but extraction (pop/top) O(1).
 * NOTE: This is less efficient than the standard Array-based Heap (O(log N) for both).
 */
class PriorityQueueList {
private:
    Node* head; // Pointer to the highest priority item (the largest value)

public:
    // Constructor
    PriorityQueueList() : head(nullptr) {}

    // Destructor (Cleans up all nodes)
    ~PriorityQueueList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // --- Core Priority Queue Operations ---

    // O(N) - Inserts a new node while maintaining sorted order.
    void push(int priorityValue) {
        Node* newNode = new Node(priorityValue);
        
        // Case 1: List is empty or new node is the highest priority (goes to head)
        if (head == nullptr || priorityValue > head->priority) {
            newNode->next = head;
            head = newNode;
            std::cout << "Pushed " << priorityValue << " to head (O(1) insertion)." << std::endl;
            return;
        }

        // Case 2: Traverse the list to find the correct insertion point (O(N) traversal)
        Node* current = head;
        // Stop when the next node is null OR the new value is greater than the next node's value
        while (current->next != nullptr && current->next->priority >= priorityValue) {
            current = current->next;
        }
        
        // Insert the new node between 'current' and 'current->next'
        newNode->next = current->next;
        current->next = newNode;
        std::cout << "Pushed " << priorityValue << " (O(N) insertion after traversing)." << std::endl;
    }

    // O(1) - Returns the highest priority element without removing it.
    int top() const {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty: cannot peek top element.");
        }
        return head->priority; // Highest priority is always the head
    }

    // O(1) - Removes the highest priority element.
    void pop() {
        if (head == nullptr) {
            std::cout << "Error: Cannot pop, queue is empty." << std::endl;
            return;
        }
        
        Node* temp = head;
        head = head->next; // Move head to the next node
        std::cout << "Popped highest priority element: " << temp->priority << std::endl;
        delete temp; // Free the memory
    }

    // O(1) - Check if the queue is empty
    bool empty() const {
        return head == nullptr;
    }
    
    // Helper function to show list structure
    void display() {
        if (head == nullptr) {
            std::cout << "Current List: [Empty]" << std::endl;
            return;
        }
        Node* current = head;
        std::cout << "Current List (Highest Priority First): ";
        while (current != nullptr) {
            std::cout << "[" << current->priority << "]";
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    PriorityQueueList pq;

    std::cout << "=========================================" << std::endl;
    std::cout << "--- Custom Priority Queue (List) Demo ---" << std::endl;
    std::cout << "=========================================" << std::endl;

    // 1. Test Push (O(N) insertion)
    pq.push(50); // Becomes head
    pq.push(10); // Inserted after 50
    pq.push(80); // Becomes the new head (highest priority)
    pq.push(30); // Inserted between 50 and 10
    pq.push(95); // Highest priority item, new head

    pq.display();
    std::cout << "Current Highest Priority (Top): " << pq.top() << "\n" << std::endl;

    // 2. Test Pop (O(1) extraction)
    std::cout << "--- Processing Queue (Pop) ---" << std::endl;
    
    while (!pq.empty()) {
        pq.pop(); 
        if (!pq.empty()) {
             std::cout << "     New Top: " << pq.top() << std::endl;
        }
    }
    
    std::cout << "\nQueue is empty? " << (pq.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
