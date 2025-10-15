#include <iostream>

// 1. Define the Node structure
// Each Node holds the data and a pointer to the next Node in the list.
struct Node {
    int data;     // Data value stored in the node
    Node* next;   // Pointer to the next node in the list

    // Constructor to initialize a new node easily
    Node(int val) : data(val), next(nullptr) {}
};

// 2. Define the LinkedList class
// This class manages the sequence of Nodes via the 'head' pointer.
class LinkedList {
private:
    Node* head; // Pointer to the first node (the entry point of the list)

public:
    // Constructor: Initialize an empty list
    LinkedList() : head(nullptr) {}

    // Destructor: Essential for C++ to prevent memory leaks.
    // It iterates through the entire list and deletes every node.
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next; // Save the next node's address
            delete current;             // Delete the current node
            current = next;             // Move to the next node
        }
        head = nullptr; // Ensure head is null after cleanup
    }

    // --- Core Operations ---

    // Insert a new node at the beginning of the list.
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        // New node points to the old head
        newNode->next = head;
        // Head now points to the new node
        head = newNode;
        std::cout << "Inserted " << val << " at head." << std::endl;
    }

    // Insert a new node at the end of the list.
    void insertAtTail(int val) {
        Node* newNode = new Node(val);

        // Case 1: List is empty
        if (head == nullptr) {
            head = newNode;
            std::cout << "Inserted " << val << " at tail (list was empty)." << std::endl;
            return;
        }

        // Case 2: List is not empty, traverse to the last node
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // Link the last node to the new node
        current->next = newNode;
        std::cout << "Inserted " << val << " at tail." << std::endl;
    }

    // Delete the node at the beginning of the list.
    void deleteHead() {
        if (head == nullptr) {
            std::cout << "Error: Cannot delete head, list is empty." << std::endl;
            return; // List is empty
        }
        Node* temp = head;          // Temporary pointer to the node to be deleted
        head = head->next;          // Move the head pointer to the next node
        std::cout << "Deleted head node with data: " << temp->data << std::endl;
        delete temp;                // Free the memory of the old head
    }

    // Search for a specific value in the list.
    bool search(int val) {
        Node* current = head;
        int position = 0;
        while (current != nullptr) {
            if (current->data == val) {
                std::cout << "Found value " << val << " at position " << position << " (0-indexed)." << std::endl;
                return true;
            }
            current = current->next;
            position++;
        }
        std::cout << "Value " << val << " not found in the list." << std::endl;
        return false;
    }

    // Display all elements in the linked list sequentially.
    void display() {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        Node* current = head;
        std::cout << "Current List: ";
        while (current != nullptr) {
            std::cout << "[" << current->data << "]";
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Main function to demonstrate the LinkedList
int main() {
    // Create an instance of the linked list
    LinkedList list;

    std::cout << "--- Initializing List ---" << std::endl;

    // 1. Insert at the tail
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.display(); // List: [10] -> [20] -> [30]

    std::cout << "\n--- Modifying List ---" << std::endl;

    // 2. Insert at the head
    list.insertAtHead(5);
    list.insertAtHead(1);
    list.display(); // List: [1] -> [5] -> [10] -> [20] -> [30]

    // 3. Delete the head node twice
    list.deleteHead(); // Deletes 1
    list.deleteHead(); // Deletes 5
    list.display(); // List: [10] -> [20] -> [30]

    std::cout << "\n--- Searching List ---" << std::endl;
    // 4. Demonstrate search functionality
    list.search(20); // Should be found
    list.search(42); // Should not be found


    std::cout << "\n--- Final State ---" << std::endl;
    list.display();

    // The destructor will automatically clean up nodes 10, 20, and 30 when 'list' goes out of scope.
    std::cout << "Linked List demonstration complete. Memory will be freed by the destructor." << std::endl;

    return 0;
}
