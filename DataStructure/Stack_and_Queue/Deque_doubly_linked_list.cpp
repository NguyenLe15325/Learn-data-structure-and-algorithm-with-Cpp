#include <iostream>
#include <stdexcept> // For std::out_of_range
#include <string>    // Used for the demo data type (std::string) and output
#include <type_traits> // For std::is_same_v

/**
 * Deque (Double-Ended Queue) Implementation using a Generic DOUBLY Linked List.
 * * This allows insertion and deletion from both the front and the rear.
 * * It uses two pointers (head and tail) for O(1) performance on all core operations.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev; // NEW: Pointer to the previous node

    Node(const T& val) : data(val), next(nullptr), prev(nullptr) {} 
};

// --- Deque Class ---
template <typename T>
class Deque {
private:
    Node<T>* head; // Pointer to the front (first element)
    Node<T>* tail; // Pointer to the rear (last element)
    int dequeSize;

public:
    // Constructor
    Deque() : head(nullptr), tail(nullptr), dequeSize(0) {}

    // Destructor: Cleans up all nodes
    ~Deque() {
        clear(); 
    }

    // Check if the deque is empty (O(1))
    bool isEmpty() const {
        return head == nullptr; // Can check head or tail
    }

    // Get the current size of the deque (O(1))
    int size() const {
        return dequeSize;
    }

    // --- FRONT OPERATIONS ---

    // 1. PUSH FRONT (Add element to the front - O(1))
    void push_front(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        
        if (isEmpty()) {
            // If empty, new node is both head and tail
            head = newNode;
            tail = newNode;
        } else {
            // Current head's prev points to the new node
            head->prev = newNode;
            // New node's next points to the current head
            newNode->next = head;
            // New node becomes the new head
            head = newNode;
        }
        dequeSize++;
    }

    // 2. POP FRONT (Remove and return the front element - O(1))
    T pop_front() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot pop_front from an empty Deque.");
        }
        
        Node<T>* oldHead = head; 
        T poppedValue = oldHead->data;
        
        // Move head pointer to the next node
        head = head->next;

        if (head == nullptr) {
            // If list is now empty, tail must also be null
            tail = nullptr;
        } else {
            // New head's prev must be null
            head->prev = nullptr;
        }
        
        delete oldHead; // Free memory
        dequeSize--;
        
        return poppedValue;
    }

    // 3. FRONT (Get the front element without removing it - O(1))
    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("Deque is empty; cannot view front element.");
        }
        return head->data;
    }
    
    // --- REAR OPERATIONS ---

    // 4. PUSH BACK (Add element to the rear - O(1))
    void push_back(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            // If empty, new node is both head and tail
            head = newNode;
            tail = newNode;
        } else {
            // Current tail's next points to the new node
            tail->next = newNode;
            // New node's prev points to the current tail
            newNode->prev = tail;
            // New node becomes the new tail
            tail = newNode;
        }
        dequeSize++;
    }
    
    // 5. POP BACK (Remove and return the rear element - O(1))
    T pop_back() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot pop_back from an empty Deque.");
        }
        
        Node<T>* oldTail = tail; 
        T poppedValue = oldTail->data;
        
        // Move tail pointer back to the previous node (the new tail)
        tail = tail->prev;

        if (tail == nullptr) {
            // If list is now empty, head must also be null
            head = nullptr;
        } else {
            // New tail's next must be null
            tail->next = nullptr;
        }
        
        delete oldTail; // Free memory
        dequeSize--;
        
        return poppedValue;
    }
    
    // 6. BACK (Get the rear element without removing it - O(1))
    const T& back() const {
        if (isEmpty()) {
            throw std::out_of_range("Deque is empty; cannot view rear element.");
        }
        return tail->data;
    }

    // Clear the entire Deque (Crucial for memory management)
    void clear() {
        // Iterate using the 'next' pointer from the head
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        
        while (current != nullptr) {
            temp = current;
            current = current->next;
            delete temp;
        }
        
        head = nullptr;
        tail = nullptr;
        dequeSize = 0;
    }

    // Display the deque from front to rear
    void display() const {
        if (isEmpty()) {
            std::cout << "Deque: [Empty]" << std::endl;
            return;
        }

        Node<T>* current = head; // Start at the front
        std::cout << "Deque (Front -> Rear): ";
        
        while (current != nullptr) {
            if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, char*>) {
                std::cout << "\"" << current->data << "\"";
            } else {
                std::cout << current->data;
            }
            
            if (current->next != nullptr) {
                std::cout << " <--> ";
            }
            current = current->next;
        }
        
        std::cout << " [FRONT: " << head->data 
                  << ", REAR: " << tail->data 
                  << ", Size: " << dequeSize << "]" << std::endl;
    }
    
    // Display the deque from rear to front (Demonstrates doubly linked nature)
    void display_reverse() const {
        if (isEmpty()) {
            std::cout << "Deque: [Empty]" << std::endl;
            return;
        }

        Node<T>* current = tail; // Start at the rear
        std::cout << "Deque (Rear -> Front): ";
        
        while (current != nullptr) {
            if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, char*>) {
                std::cout << "\"" << current->data << "\"";
            } else {
                std::cout << current->data;
            }
            
            if (current->prev != nullptr) {
                std::cout << " <--> ";
            }
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    // ----------------------------------------------------
    // DEMO 1: String Deque Operations
    // ----------------------------------------------------
    // We use Deque to simulate a line where people can enter/exit both ends.
    Deque<std::string> participantLine;
    
    std::cout << "========================================" << std::endl;
    std::cout << "--- DEMO 1: Doubly Linked List Deque ---" << std::endl;
    std::cout << "========================================" << std::endl;

    // A. Initial state check
    std::cout << "Initial size: " << participantLine.size() << std::endl;

    // B. PUSH FRONT & PUSH BACK
    std::cout << "\n--- B. Additions ---" << std::endl;
    participantLine.push_front("C"); // List: C
    participantLine.push_back("D");  // List: C <--> D
    participantLine.push_front("B"); // List: B <--> C <--> D
    participantLine.push_back("E");  // List: B <--> C <--> D <--> E
    participantLine.push_front("A"); // List: A <--> B <--> C <--> D <--> E
    participantLine.display();

    // C. View Front/Back and Reverse Traversal
    std::cout << "\n--- C. Peek and Reverse Traversal ---" << std::endl;
    std::cout << "Front element (front()): " << participantLine.front() << std::endl; // A
    std::cout << "Rear element (back()): " << participantLine.back() << std::endl;   // E
    participantLine.display_reverse(); // E <--> D <--> C <--> B <--> A

    // D. POP FRONT & POP BACK
    std::cout << "\n--- D. Removals ---" << std::endl;
    std::cout << "Pop Front (A): " << participantLine.pop_front() << std::endl;
    std::cout << "Pop Back (E): " << participantLine.pop_back() << std::endl;
    participantLine.display(); // B <--> C <--> D

    // E. Error Handling (pop_back)
    std::cout << "\n--- E. Final Cleanup & Error ---" << std::endl;
    participantLine.pop_back(); // D
    participantLine.pop_front(); // B
    participantLine.pop_back(); // C (list is now empty)
    
    std::cout << "Size after emptying: " << participantLine.size() << std::endl;
    try {
        std::cout << "Attempting pop_back on empty Deque..." << std::endl;
        participantLine.pop_back(); 
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Error: " << e.what() << std::endl;
    }
    
    // ----------------------------------------------------
    // DEMO 2: Integer Deque (Generic Template Use)
    // ----------------------------------------------------
    Deque<int> intDeque;
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "--- DEMO 2: Integer Deque (Templates) ---" << std::endl;
    std::cout << "========================================" << std::endl;
    
    intDeque.push_back(10);
    intDeque.push_front(5);
    intDeque.push_back(15);
    intDeque.display(); // 5 <--> 10 <--> 15
    
    std::cout << "Popping front: " << intDeque.pop_front() << std::endl; // 5
    std::cout << "Popping back: " << intDeque.pop_back() << std::endl;   // 15
    intDeque.display(); // 10
    intDeque.clear();

    return 0;
}
