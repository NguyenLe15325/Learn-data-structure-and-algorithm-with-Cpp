#include <iostream>
#include <stdexcept>
#include <algorithm>

/**
 * COMPLETE BINARY SEARCH TREE (BST) IMPLEMENTATION.
 * Time Complexity is based on tree height (h). 
 * Average Case (Balanced Tree): h = O(log N).
 * Worst Case (Skewed Tree): h = O(N).
 */

// --- Node Structure ---
template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& val) : data(val), left(nullptr), right(nullptr) {} 
};

// --- Binary Search Tree Class ---
template <typename T>
class BinarySearchTree {
private:
    Node<T>* root;

    // --- Private Recursive Helper Functions ---

    /**
     * @brief Recursively inserts a new value.
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    Node<T>* insertRecursive(Node<T>* node, const T& val) {
        if (node == nullptr) {
            return new Node<T>(val);
        }

        if (val < node->data) {
            node->left = insertRecursive(node->left, val);
        } else if (val > node->data) {
            node->right = insertRecursive(node->right, val);
        }
        return node;
    }
    
    /**
     * @brief Finds the smallest node in a subtree (left-most node). Used for deletion.
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    Node<T>* findMinRecursive(Node<T>* node) const {
        if (node == nullptr || node->left == nullptr) {
            return node;
        }
        return findMinRecursive(node->left);
    }
    
    /**
     * @brief Recursively removes a node with the given value.
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    Node<T>* removeRecursive(Node<T>* node, const T& val) {
        if (node == nullptr) {
            return nullptr; // Value not found
        }

        // 1. Traverse to find the node
        if (val < node->data) {
            node->left = removeRecursive(node->left, val);
        } else if (val > node->data) {
            node->right = removeRecursive(node->right, val);
        } else {
            // 2. Node found: handle the three deletion cases (0, 1, or 2 children)

            // Case A: Node with 0 or 1 child
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                return temp; 
            } else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Case B: Node with 2 children
            // Find the Inorder Successor (min in the right subtree)
            Node<T>* successor = findMinRecursive(node->right);
            
            // Copy the successor's data to this node
            node->data = successor->data;

            // Delete the original successor from the right subtree
            node->right = removeRecursive(node->right, successor->data);
        }

        return node;
    }

    /**
     * @brief Searches for a value recursively.
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    bool searchRecursive(Node<T>* node, const T& val) const {
        if (node == nullptr) {
            return false;
        }
        if (val == node->data) {
            return true;
        } else if (val < node->data) {
            return searchRecursive(node->left, val);
        } else {
            return searchRecursive(node->right, val);
        }
    }

    /**
     * @brief Inorder Traversal (Left -> Root -> Right). Prints sorted elements.
     * Time Complexity: O(N) (must visit every node).
     */
    void inorderRecursive(Node<T>* node) const {
        if (node != nullptr) {
            inorderRecursive(node->left);
            std::cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }

    /**
     * @brief Preorder Traversal (Root -> Left -> Right).
     * Time Complexity: O(N).
     */
    void preorderRecursive(Node<T>* node) const {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }
    
    /**
     * @brief Postorder Traversal (Left -> Right -> Root).
     * Time Complexity: O(N).
     */
    void postorderRecursive(Node<T>* node) const {
        if (node != nullptr) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            std::cout << node->data << " ";
        }
    }

    // Helper for memory cleanup
    void destroyRecursive(Node<T>* node) {
        if (node != nullptr) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    // Constructor and Destructor
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { destroyRecursive(root); }

    // --- Core Operations ---

    /**
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    void insert(const T& val) {
        root = insertRecursive(root, val);
    }

    /**
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    void remove(const T& val) {
        root = removeRecursive(root, val);
    }

    /**
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    bool search(const T& val) const {
        return searchRecursive(root, val);
    }

    // --- Traversal Methods (Always O(N)) ---

    void inorderTraversal() const {
        std::cout << "Inorder (Sorted): ";
        inorderRecursive(root);
        std::cout << std::endl;
    }
    
    void preorderTraversal() const {
        std::cout << "Preorder: ";
        preorderRecursive(root);
        std::cout << std::endl;
    }
    
    void postorderTraversal() const {
        std::cout << "Postorder: ";
        postorderRecursive(root);
        std::cout << std::endl;
    }

    // --- Min/Max Finding ---

    /**
     * @brief Finds the minimum element (left-most node).
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    T findMin() const {
        if (root == nullptr) {
            throw std::out_of_range("Tree is empty, cannot find minimum.");
        }
        Node<T>* current = root;
        // Iteratively traverse the left child pointers
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    /**
     * @brief Finds the maximum element (right-most node).
     * Time Complexity: O(h). O(log N) average, O(N) worst case.
     */
    T findMax() const {
        if (root == nullptr) {
            throw std::out_of_range("Tree is empty, cannot find maximum.");
        }
        Node<T>* current = root;
        // Iteratively traverse the right child pointers
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }
};

int main() {
    BinarySearchTree<int> tree;

    std::cout << "=========================================================" << std::endl;
    std::cout << "--- Complete Binary Search Tree (BST) Demonstration ---" << std::endl;
    std::cout << "--- Average Time Complexity for Core Ops: O(log N) ---" << std::endl;
    std::cout << "=========================================================" << std::endl;

    // Insertion (O(log N) average)
    std::cout << "\n[1] Insertion (50, 30, 70, 20, 40, 60, 80, 55)" << std::endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(55);

    // Traversal Demonstrations (O(N) complexity)
    std::cout << "\n[2] Traversal Methods (O(N) Complexity)" << std::endl;
    tree.inorderTraversal();  
    tree.preorderTraversal(); 
    tree.postorderTraversal();

    // Search Demonstration (O(log N) average)
    std::cout << "\n[3] Search Operations (O(log N) average)" << std::endl;
    std::cout << "Searching for 40: " << (tree.search(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 10: " << (tree.search(10) ? "Found" : "Not Found") << std::endl;

    // Min/Max Demonstration (O(log N) average)
    std::cout << "\n[4] Min/Max Operations (O(log N) average)" << std::endl;
    try {
        std::cout << "Minimum value: " << tree.findMin() << std::endl; 
        std::cout << "Maximum value: " << tree.findMax() << std::endl; 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Deletion Demonstration (O(log N) average)
    std::cout << "\n[5] Deletion Operations (O(log N) average)" << std::endl;
    
    // Delete 1-Child Node (70)
    std::cout << "-- Removing 70 (1 Child) --" << std::endl;
    tree.remove(70);
    tree.inorderTraversal(); 

    // Delete 2-Child Node (30, replaced by 55 - its inorder successor)
    std::cout << "-- Removing 50 (Root/2 Children) --" << std::endl;
    tree.remove(50);
    tree.inorderTraversal(); 

    return 0;
}
