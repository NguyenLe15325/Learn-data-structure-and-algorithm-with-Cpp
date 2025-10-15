#include <iostream>
#include <string>

/**
 * Circularly Linked List Implementation (Generic/Templated)
 * In this list, the 'next' pointer of the last node points back to the first node (the head).
 * The list is managed using a single 'tail' pointer, as 'tail->next' always points to the head.
 * This structure allows for O(1) insertion at both the head and the tail.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* next; // Pointer to the next node (which may be the head)

    // Constructor
    Node(const T& val) : data(val), next(nullptr) {}
};

// --- Circularly Linked List Class ---
template <typename T>
class CircularLinkedList {
private:
    // We only need one pointer: 'tail'. The head is always 'tail->next'.
    Node<T>* tail; 

public:
    // Constructor: Initializes an empty list
    CircularLinkedList() : tail(nullptr) {}

    // Destructor: Cleans up all nodes to prevent memory leaks
    ~CircularLinkedList() {
        if (tail == nullptr) return;

        Node<T>* current = tail->next; // Start at the head
        while (current != tail) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        delete tail; // Delete the last node
        tail = nullptr;
    }

    // Check if the list is empty
    bool isEmpty() const {
        return tail == nullptr;
    }

    // 1. Insertion at the beginning (Head) - O(1)
    void insertAtHead(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            tail = newNode;
            tail->next = tail; // Point to itself to complete the circle
        } else {
            newNode->next = tail->next; // New node points to the current head
            tail->next = newNode;       // Tail points to the new node (making it the new head)
        }
    }

    // 2. Insertion at the end (Tail) - O(1)
    // This is achieved by inserting at the head, then advancing the tail pointer.
    void insertAtTail(const T& val) {
        insertAtHead(val);
        tail = tail->next; // Move tail to the newly inserted node
    }
    
    // 3. Deletion by Value
    bool deleteByValue(const T& val) {
        if (isEmpty()) return false;

        Node<T>* current = tail->next; // Start at head
        Node<T>* previous = tail;
        
        // Traverse the list until we come back to the head
        do {
            if (current->data == val) {
                // Found the node to delete

                // Case 1: Single node list
                if (current == tail && current->next == tail) {
                    delete tail;
                    tail = nullptr;
                    return true;
                }
                
                // Case 2: Deleting the Tail
                if (current == tail) {
                    previous->next = tail->next;
                    tail = previous;
                }
                // Case 3: Deleting the Head or a Middle Node
                else {
                    previous->next = current->next;
                }

                delete current;
                return true;
            }
            
            previous = current;
            current = current->next;

        } while (current != tail->next); // Loop ends when we complete the circle

        return false; // Value not found
    }

    // 4. Traversal and Display
    void display() const {
        if (isEmpty()) {
            std::cout << "List: (Empty)" << std::endl;
            return;
        }

        Node<T>* current = tail->next; // Start at the Head

        std::cout << "List (Circular): ";
        // Traverse until we return to the starting node (Head)
        do {
            std::cout << current->data;
            if (current != tail) {
                std::cout << " -> ";
            }
            current = current->next;
        } while (current != tail->next);

        std::cout << " -> (Back to Head)" << std::endl;
    }
};

int main() {
    // Demonstrate with integers
    CircularLinkedList<int> intList;
    
    std::cout << "--- Integer Circularly Linked List Demo ---" << std::endl;
    intList.insertAtHead(10); 
    intList.insertAtHead(5);  
    intList.insertAtTail(20); 
    intList.insertAtTail(30); 

    intList.display();  // Expected: 5 -> 10 -> 20 -> 30 -> (Back to Head)

    std::cout << "\nAttempting to delete '20' (middle node)..." << std::endl;
    intList.deleteByValue(20);
    intList.display(); 

    std::cout << "Attempting to delete '5' (head node)..." << std::endl;
    intList.deleteByValue(5);
    intList.display(); 
    
    std::cout << "Attempting to delete '30' (tail node)..." << std::endl;
    intList.deleteByValue(30);
    intList.display(); 

    std::cout << "Attempting to delete '10' (last remaining node)..." << std::endl;
    intList.deleteByValue(10);
    intList.display(); 

    std::cout << "\n--- String Circularly Linked List Demo ---" << std::endl;
    CircularLinkedList<std::string> stringList;
    stringList.insertAtHead("is");
    stringList.insertAtTail("fun");
    stringList.insertAtHead("Coding");
    stringList.display();
    
    stringList.deleteByValue("is");
    std::cout << "\nAfter deleting 'is':" << std::endl;
    stringList.display(); 

    return 0;
}
