#include <iostream>
#include <string>

// 1. Generic Node Structure
// The Node now holds data of type T, determined when the list is instantiated.
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    // Constructor
    Node(const T& val) : data(val), next(nullptr) {}
};

// 2. Generic LinkedList Class
// The entire class is templated to work with type T.
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor: Must correctly handle deleting generic nodes
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // --- Core Operations ---

    // Insert a new node at the beginning (Head)
    void insertAtHead(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
        std::cout << "Inserted '" << val << "' at head." << std::endl;
    }

    // Insert a new node at the end (Tail)
    void insertAtTail(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        if (head == nullptr) {
            head = newNode;
            std::cout << "Inserted '" << val << "' at tail (list was empty)." << std::endl;
            return;
        }

        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        std::cout << "Inserted '" << val << "' at tail." << std::endl;
    }

    // Delete the head node
    void deleteHead() {
        if (head == nullptr) {
            std::cout << "Error: Cannot delete head, list is empty." << std::endl;
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        std::cout << "Deleted head node with data: '" << temp->data << "'" << std::endl;
        delete temp;
    }

    // Search for a specific value
    bool search(const T& val) {
        Node<T>* current = head;
        int position = 0;
        while (current != nullptr) {
            if (current->data == val) {
                std::cout << "Found value '" << val << "' at position " << position << "." << std::endl;
                return true;
            }
            current = current->next;
            position++;
        }
        std::cout << "Value '" << val << "' not found." << std::endl;
        return false;
    }

    // Display the linked list
    void display() {
        if (head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        Node<T>* current = head;
        std::cout << "Current List (" << typeid(T).name() << "): ";
        while (current != nullptr) {
            std::cout << "['" << current->data << "']";
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// Main function to demonstrate the Generic LinkedList
int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "Demonstration 1: Integer Linked List (T=int)" << std::endl;
    std::cout << "=========================================" << std::endl;

    // Instantiate LinkedList with integer type
    LinkedList<int> intList;
    intList.insertAtTail(100);
    intList.insertAtHead(50);
    intList.insertAtTail(150);
    intList.display();

    intList.search(100);
    intList.deleteHead();
    intList.display();
    intList.search(50); // Should now be missing

    std::cout << "\n=========================================" << std::endl;
    std::cout << "Demonstration 2: String Linked List (T=std::string)" << std::endl;
    std::cout << "=========================================" << std::endl;

    // Instantiate LinkedList with string type
    LinkedList<std::string> stringList;
    stringList.insertAtHead("Charlie");
    stringList.insertAtTail("Alpha");
    stringList.insertAtHead("Delta");
    stringList.display();

    stringList.search("Alpha");
    stringList.deleteHead();
    stringList.display();
    stringList.search("Beta"); // Search for non-existent string

    std::cout << "\n--- Program Finished ---" << std::endl;
    return 0;
}
