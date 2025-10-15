#include <iostream>
#include <string>

/**
 * Doubly Linked List Implementation (Generic/Templated)
 * * This structure allows for bidirectional traversal (forward and backward)
 * because each Node maintains a pointer to both the previous and the next node.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* prev; // Pointer to the previous node
    Node<T>* next; // Pointer to the next node

    // Constructor
    Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};

// --- Doubly Linked List Class ---
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Constructor: Initializes an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor: Cleans up all nodes to prevent memory leaks
    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    // 1. Insertion at the beginning (Head)
    void insertAtHead(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // 2. Insertion at the end (Tail)
    void insertAtTail(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 3. Deletion by Value (Showcasing the 'prev' pointer advantage)
    bool deleteByValue(const T& val) {
        if (head == nullptr) return false;

        Node<T>* current = head;
        
        while (current != nullptr && current->data != val) {
            current = current->next;
        }

        if (current == nullptr) return false; // Value not found

        // Case 1: Deleting the Head
        if (current == head) {
            head = current->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr; // List became empty
            }
        } 
        // Case 2: Deleting the Tail
        else if (current == tail) {
            tail = current->prev;
            tail->next = nullptr;
        } 
        // Case 3: Deleting a Middle Node
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        return true;
    }

    // 4. Traversal and Display (Forward)
    void displayForward() const {
        Node<T>* current = head;
        std::cout << "List (Forward): ";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " <-> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }

    // 5. Traversal and Display (Backward - Advantage of Doubly Linked List)
    void displayBackward() const {
        Node<T>* current = tail;
        std::cout << "List (Backward): ";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->prev != nullptr) {
                std::cout << " <-> ";
            }
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Demonstrate with integers
    DoublyLinkedList<int> intList;
    
    std::cout << "--- Integer Doubly Linked List Demo ---" << std::endl;
    intList.insertAtTail(10);
    intList.insertAtTail(20);
    intList.insertAtHead(5);
    intList.insertAtTail(30);

    intList.displayForward();  // Expected: 5 <-> 10 <-> 20 <-> 30
    intList.displayBackward(); // Expected: 30 <-> 20 <-> 10 <-> 5

    std::cout << "\nAttempting to delete '20' (middle node)..." << std::endl;
    intList.deleteByValue(20);
    intList.displayForward(); // Expected: 5 <-> 10 <-> 30

    std::cout << "Attempting to delete '5' (head node)..." << std::endl;
    intList.deleteByValue(5);
    intList.displayForward(); // Expected: 10 <-> 30

    std::cout << "Attempting to delete '30' (tail node)..." << std::endl;
    intList.deleteByValue(30);
    intList.displayForward(); // Expected: 10

    std::cout << "\n--- String Doubly Linked List Demo ---" << std::endl;
    DoublyLinkedList<std::string> stringList;
    stringList.insertAtHead("World");
    stringList.insertAtHead("Hello");
    stringList.insertAtTail("!");
    stringList.displayForward();
    stringList.displayBackward();
    
    stringList.deleteByValue("Hello");
    std::cout << "\nAfter deleting 'Hello':" << std::endl;
    stringList.displayForward(); // Expected: World <-> !

    // The destructors automatically clean up the remaining nodes.

    return 0;
}
