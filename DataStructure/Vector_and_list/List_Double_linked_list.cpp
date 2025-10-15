#include <iostream>
#include <stdexcept>
#include <string>

/**
 * Custom implementation of a Doubly Linked List (similar to std::list).
 * Key Feature: O(1) insertion/deletion anywhere if the position is known.
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev; // Pointer to the previous node

    Node(const T& val) : data(val), next(nullptr), prev(nullptr) {} 
};

// --- List Class ---
template <typename T>
class MyList {
private:
    Node<T>* head; // Pointer to the start of the list
    Node<T>* tail; // Pointer to the end of the list
    int listSize;

public:
    // Constructor
    MyList() : head(nullptr), tail(nullptr), listSize(0) {}

    // Destructor: Cleans up all nodes
    ~MyList() {
        clear(); 
    }

    // Check if the list is empty (O(1))
    bool isEmpty() const {
        return head == nullptr;
    }

    // Get the current size of the list (O(1))
    int size() const {
        return listSize;
    }

    // Clears the list and frees memory
    void clear() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        
        while (current != nullptr) {
            temp = current;
            current = current->next;
            delete temp;
        }
        
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    // --- Core Insertion Operations (O(1)) ---

    // 1. PUSH FRONT (Add element to the beginning)
    void push_front(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }

    // 2. PUSH BACK (Add element to the end)
    void push_back(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }

    // 3. INSERT AFTER (Inserts a new value *after* the given node - O(1))
    // NOTE: This assumes 'targetNode' is a valid pointer within the list.
    void insert_after(Node<T>* targetNode, const T& val) {
        if (!targetNode) {
            throw std::invalid_argument("Target node cannot be null for insertion.");
        }
        
        // If inserting after the tail, use push_back logic
        if (targetNode == tail) {
            push_back(val);
            return;
        }

        Node<T>* newNode = new Node<T>(val);
        Node<T>* nextNode = targetNode->next;

        // Link NewNode into the list between TargetNode and NextNode
        newNode->next = nextNode;
        newNode->prev = targetNode;

        targetNode->next = newNode;
        nextNode->prev = newNode;

        listSize++;
    }

    // --- Traversal and Display ---

    void display() const {
        if (isEmpty()) {
            std::cout << "List: [Empty]" << std::endl;
            return;
        }

        Node<T>* current = head;
        std::cout << "List (Front -> Back): ";
        
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " <--> ";
            }
            current = current->next;
        }
        std::cout << " (Size: " << listSize << ")" << std::endl;
    }

    // Expose head pointer for demonstration purposes (simulating an iterator)
    Node<T>* get_head() const {
        return head;
    }
    
    // Simple traversal to find a node by value (O(N) search)
    Node<T>* find_node(const T& val) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    MyList<std::string> shoppingList;
    
    std::cout << "===============================================" << std::endl;
    std::cout << "--- Custom MyList Demonstration (Doubly Linked List) ---" << std::endl;
    std::cout << "===============================================" << std::endl;

    // A. PUSH FRONT and PUSH BACK (O(1) operations)
    std::cout << "A. Building the list:" << std::endl;
    shoppingList.push_back("Milk");
    shoppingList.push_front("Eggs");
    shoppingList.push_back("Bread");
    shoppingList.push_front("Cheese");
    shoppingList.display(); // Expected: Cheese <--> Eggs <--> Milk <--> Bread

    // B. O(1) Insertion in the middle
    std::cout << "\nB. O(1) Insertion in the middle (requires finding the node first):" << std::endl;
    
    // We must first perform an O(N) search to find the target node, 
    // but the actual insert operation is O(1).
    Node<std::string>* milkNode = shoppingList.find_node("Milk");

    if (milkNode) {
        // Insert "Yogurt" AFTER "Milk"
        shoppingList.insert_after(milkNode, "Yogurt"); 
        std::cout << "   Inserted 'Yogurt' after 'Milk'." << std::endl;
    }
    shoppingList.display(); // Expected: Cheese <--> Eggs <--> Milk <--> Yogurt <--> Bread

    // C. Size and Cleanup
    std::cout << "\nC. Size and Cleanup:" << std::endl;
    std::cout << "   Final Size: " << shoppingList.size() << std::endl;
    
    shoppingList.clear();
    shoppingList.display();

    return 0;
}
