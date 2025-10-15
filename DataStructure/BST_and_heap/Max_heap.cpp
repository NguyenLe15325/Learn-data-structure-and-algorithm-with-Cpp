#include <iostream>
#include <stdexcept>
#include <queue>      // For BFS to find insertion/deletion points
#include <algorithm>  // For std::swap
#include <string>

/**
 * COMPLETE LINKED BINARY HEAP IMPLEMENTATION (Max Heap).
 * This implementation provides O(log N) complexity for push and pop, 
 * achieved by using BFS to locate insertion/deletion points in the linked structure.
 * * * Max Heap Rule: Parent data >= Child data.
 */

template <typename T>
struct HeapNode {
    T data;
    HeapNode<T>* left;
    HeapNode<T>* right;
    HeapNode<T>* parent; // Crucial for O(log N) heapifyUp/Down

    HeapNode(const T& val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class LinkedHeap {
private:
    HeapNode<T>* root;
    int size;

    // Helper to find the parent node for insertion (next available slot)
    // Time Complexity: O(N) in the worst case, but practically O(log N) due to structure.
    HeapNode<T>* findInsertionParent() {
        if (!root) return nullptr;
        std::queue<HeapNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            HeapNode<T>* current = q.front();
            q.pop();

            if (current->left == nullptr || current->right == nullptr) {
                return current;
            }
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return nullptr;
    }

    // Helper to find the deepest, rightmost (last) node for deletion swap
    // Time Complexity: O(N) in the worst case (must traverse all nodes).
    HeapNode<T>* findLastNode() {
        if (!root) return nullptr;
        HeapNode<T>* last = nullptr;
        std::queue<HeapNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            last = q.front();
            q.pop();
            if (last->left) q.push(last->left);
            if (last->right) q.push(last->right);
        }
        return last; // Returns the last node visited in level order
    }

    // --- Core Heapify Logic (Max Heap) ---
    // Restores the Max Heap property by bubbling the node UP towards the root.
    // Time Complexity: O(log N)
    void heapifyUp(HeapNode<T>* node) {
        if (!node || !node->parent) return;

        // Max Heap logic: While current node is not the root AND is LARGER (higher priority) than its parent
        while (node->parent != nullptr && node->data > node->parent->data) {
            std::swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    // --- Core Heapify Logic (Max Heap) ---
    // Restores the Max Heap property by bubbling the node DOWN towards the leaves.
    // Time Complexity: O(log N)
    void heapifyDown(HeapNode<T>* node) {
        HeapNode<T>* current = node;
        
        while (true) {
            HeapNode<T>* largest = current; // Now looking for the largest element (highest priority)
            HeapNode<T>* left = current->left;
            HeapNode<T>* right = current->right;

            // Find the largest among current, left, and right (Max Heap logic)
            if (left != nullptr && left->data > largest->data) {
                largest = left;
            }
            if (right != nullptr && right->data > largest->data) {
                largest = right;
            }

            // If the largest is the current node, the heap property is satisfied
            if (largest == current) {
                break;
            }

            // Swap the current data with the largest child's data
            std::swap(current->data, largest->data);
            
            // Continue the process down the tree
            current = largest;
        }
    }

    // --- Destructor Helper ---
    void destroyRecursive(HeapNode<T>* node) {
        if (node) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

    // --- Display Helper (For visualization) ---
    void displayTree(HeapNode<T>* node, int level) const {
        if (node == nullptr) return;

        displayTree(node->right, level + 1);

        for (int i = 0; i < level; ++i) {
            std::cout << "    ";
        }
        std::cout << "|---" << node->data << std::endl;

        displayTree(node->left, level + 1);
    }

public:
    LinkedHeap() : root(nullptr), size(0) {}
    ~LinkedHeap() { destroyRecursive(root); root = nullptr; }

    // Insert a new value (Max Heap) - O(log N) complexity
    void push(const T& val) {
        HeapNode<T>* newNode = new HeapNode<T>(val);
        size++;

        if (!root) {
            root = newNode;
            return;
        }

        HeapNode<T>* parentNode = findInsertionParent(); // Find next available spot
        
        newNode->parent = parentNode;
        if (parentNode->left == nullptr) {
            parentNode->left = newNode;
        } else {
            parentNode->right = newNode;
        }
        
        heapifyUp(newNode); // Restore Max Heap property
    }
    
    // Extract the highest priority element (largest value) - O(log N) complexity
    T pop() {
        if (empty()) {
             throw std::out_of_range("Cannot pop from an empty heap.");
        }
        
        T maxVal = root->data; // Value to return (the largest)
        size--;

        if (root->left == nullptr && root->right == nullptr) {
            // Case 1: Only the root node exists
            delete root;
            root = nullptr;
            return maxVal;
        }

        // 1. Find the last node (deepest, rightmost)
        HeapNode<T>* lastNode = findLastNode();
        
        // 2. Swap data with the root
        root->data = lastNode->data;

        // 3. Detach the last node from its parent
        if (lastNode->parent != nullptr) {
            if (lastNode->parent->left == lastNode) {
                lastNode->parent->left = nullptr;
            } else {
                lastNode->parent->right = nullptr;
            }
        }
        
        // 4. Delete the node object
        delete lastNode;

        // 5. Restore heap property on the new root (O(log N))
        heapifyDown(root);

        return maxVal;
    }

    T top() const {
        if (empty()) {
             throw std::out_of_range("Heap is empty.");
        }
        return root->data; // Returns the largest element
    }

    bool empty() const { return root == nullptr; }
    int get_size() const { return size; }
    
    void display() const {
        std::cout << "\nResulting Linked Max Heap Structure (Size: " << size << ", Root: " << (root ? root->data : T()) << "):" << std::endl;
        displayTree(root, 0);
    }
};

int main() {
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << "--- COMPLETE Linked Binary Heap (Max Heap) Implementation ---" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    LinkedHeap<int> max_heap; 
    
    std::cout << "Phase 1: Insertion (push): 50, 10, 80, 20, 90, 30. (90 should be the root)" << std::endl;
    
    max_heap.push(50);
    max_heap.push(10);  
    max_heap.push(80); // Bubbles up over 50
    max_heap.push(20);  
    max_heap.push(90); // Bubbles up to root (over 80)
    max_heap.push(30); 
    
    max_heap.display(); 
    std::cout << "Expected Top: 90 | Actual Top: " << max_heap.top() << std::endl;

    std::cout << "\nPhase 2: Extraction (pop) Test" << std::endl;
    int pop1 = max_heap.pop(); // Pop 90
    std::cout << "POP 1: Extracted largest element: " << pop1 << std::endl;
    std::cout << "New Expected Top: 80" << std::endl;
    max_heap.display();
    
    int pop2 = max_heap.pop(); // Pop 80
    std::cout << "POP 2: Extracted largest element: " << pop2 << std::endl;
    std::cout << "New Expected Top: 50" << std::endl;
    max_heap.display(); 
    
    std::cout << "\n------------------------------------------------------------------" << std::endl;
    std::cout << "The Max Heap uses '>' comparisons in heapifyUp() and heapifyDown() to" << std::endl;
    std::cout << "ensure the largest element always remains at the root." << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    return 0;
}
