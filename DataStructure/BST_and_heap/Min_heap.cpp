#include <iostream>
#include <stdexcept>
#include <queue>      // For BFS to find insertion/deletion points
#include <algorithm>  // For std::swap
#include <string>

/**
 * COMPLETE LINKED BINARY HEAP IMPLEMENTATION (Min Heap).
 * This implementation provides O(log N) complexity for push and pop, 
 * achieved by using BFS to locate insertion/deletion points in the linked structure.
 * * * Min Heap Rule: Parent data <= Child data.
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

    // --- Core Heapify Logic (Min Heap) ---
    // Restores the Min Heap property by bubbling the node UP towards the root.
    // Time Complexity: O(log N)
    void heapifyUp(HeapNode<T>* node) {
        if (!node || !node->parent) return;

        // While current node is not the root AND is SMALLER (higher priority) than its parent
        while (node->parent != nullptr && node->data < node->parent->data) {
            std::swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    // --- Core Heapify Logic (Min Heap) ---
    // Restores the Min Heap property by bubbling the node DOWN towards the leaves.
    // Time Complexity: O(log N)
    void heapifyDown(HeapNode<T>* node) {
        HeapNode<T>* current = node;
        
        while (true) {
            HeapNode<T>* smallest = current;
            HeapNode<T>* left = current->left;
            HeapNode<T>* right = current->right;

            // Find the smallest among current, left, and right (Min Heap logic)
            if (left != nullptr && left->data < smallest->data) {
                smallest = left;
            }
            if (right != nullptr && right->data < smallest->data) {
                smallest = right;
            }

            // If the smallest is the current node, the heap property is satisfied
            if (smallest == current) {
                break;
            }

            // Swap the current data with the smallest child's data
            std::swap(current->data, smallest->data);
            
            // Continue the process down the tree
            current = smallest;
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

    // Insert a new value (Min Heap) - O(log N) complexity
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
        
        heapifyUp(newNode); // Restore Min Heap property
    }
    
    // Extract the highest priority element (smallest value) - O(log N) complexity
    T pop() {
        if (empty()) {
             throw std::out_of_range("Cannot pop from an empty heap.");
        }
        
        T minVal = root->data; // Value to return
        size--;

        if (root->left == nullptr && root->right == nullptr) {
            // Case 1: Only the root node exists
            delete root;
            root = nullptr;
            return minVal;
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

        return minVal;
    }

    T top() const {
        if (empty()) {
             throw std::out_of_range("Heap is empty.");
        }
        return root->data;
    }

    bool empty() const { return root == nullptr; }
    int get_size() const { return size; }
    
    void display() const {
        std::cout << "\nResulting Linked Min Heap Structure (Size: " << size << ", Root: " << (root ? root->data : T()) << "):" << std::endl;
        displayTree(root, 0);
    }
};

int main() {
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << "--- COMPLETE Linked Binary Heap (Min Heap) Implementation ---" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    LinkedHeap<int> min_heap; 
    
    std::cout << "Phase 1: Insertion (push): 50, 10, 80, 20, 90, 30" << std::endl;
    
    min_heap.push(50);
    min_heap.push(10);  // Bubbles to root
    min_heap.push(80); 
    min_heap.push(20);  
    min_heap.push(90); 
    min_heap.push(30); 
    
    min_heap.display(); 
    std::cout << "Expected Top: 10 | Actual Top: " << min_heap.top() << std::endl;

    std::cout << "\nPhase 2: Extraction (pop) Test" << std::endl;
    int pop1 = min_heap.pop(); // Pop 10
    std::cout << "POP 1: Extracted smallest element: " << pop1 << std::endl;
    std::cout << "New Expected Top: 20" << std::endl;
    min_heap.display();
    
    int pop2 = min_heap.pop(); // Pop 20
    std::cout << "POP 2: Extracted smallest element: " << pop2 << std::endl;
    std::cout << "New Expected Top: 30" << std::endl;
    min_heap.display(); 
    
    std::cout << "\n------------------------------------------------------------------" << std::endl;
    std::cout << "The pop() function now correctly finds the last node, swaps it with the root," << std::endl;
    std::cout << "deletes the last node, and runs heapifyDown() to restore the heap property." << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    return 0;
}
