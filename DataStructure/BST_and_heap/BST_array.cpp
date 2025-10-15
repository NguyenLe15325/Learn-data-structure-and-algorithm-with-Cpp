#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

/**
 * COMPLETE BINARY SEARCH TREE (BST) IMPLEMENTATION.
 * A BST maintains a strict ordering:
 * - All nodes in its left subtree have values LESS than the parent node.
 * - All nodes in its right subtree have values GREATER than the parent node.
 * This property allows for O(log N) search, insertion, and deletion in the average case.
 */

template <typename T>
struct BSTNode {
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
private:
    BSTNode<T>* root;

    // --- Private Recursive Helper Functions ---

    /**
     * @brief Recursively inserts a new value, maintaining the BST property.
     * Time Complexity: O(log N) average, O(N) worst case (skewed tree).
     */
    BSTNode<T>* insertRecursive(BSTNode<T>* node, const T& val) {
        // Base case: If the current node is null, we've found the insertion point.
        if (node == nullptr) {
            return new BSTNode<T>(val);
        }

        // Recursive Step: Decide whether to go left or right.
        if (val < node->data) {
            node->left = insertRecursive(node->left, val);
        } else if (val > node->data) {
            node->right = insertRecursive(node->right, val);
        }
        // If val == node->data, we typically do nothing (no duplicate insertion).

        return node;
    }

    /**
     * @brief Displays the tree elements in-order (Left -> Root -> Right).
     * Time Complexity: O(N) in both average and worst cases (must visit every node).
     */
    void inOrderRecursive(BSTNode<T>* node) const {
        if (node != nullptr) {
            inOrderRecursive(node->left); // 1. Recurse Left
            std::cout << node->data << " "; // 2. Visit Root
            inOrderRecursive(node->right); // 3. Recurse Right
        }
    }
    
    /**
     * @brief Finds a value recursively.
     * Time Complexity: O(log N) average, O(N) worst case.
     */
    bool searchRecursive(BSTNode<T>* node, const T& val) const {
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
     * @brief Helper function used in the two-child deletion case to find the inorder successor.
     * Time Complexity: O(log N) average, O(N) worst case (proportional to the height of the subtree).
     */
    BSTNode<T>* findMinRecursive(BSTNode<T>* node) const {
        // Keep going left until the left pointer is null
        if (node == nullptr || node->left == nullptr) {
            return node;
        }
        return findMinRecursive(node->left);
    }

    /**
     * @brief Recursively removes a node with the given value while maintaining BST properties.
     * Time Complexity: O(log N) average, O(N) worst case.
     */
    BSTNode<T>* removeRecursive(BSTNode<T>* node, const T& val) {
        if (node == nullptr) {
            return nullptr; // Value not found
        }

        // 1. Traverse to find the node
        if (val < node->data) {
            node->left = removeRecursive(node->left, val);
        } else if (val > node->data) {
            node->right = removeRecursive(node->right, val);
        } else {
            // 2. Node found: handle the three deletion cases

            // Case A: Node has zero or one child (including leaf)
            if (node->left == nullptr) {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Case B: Node has two children (most complex case)
            // Find the Inorder Successor (the minimum node in the right subtree)
            BSTNode<T>* temp = findMinRecursive(node->right);
            
            // Copy the successor's data to this node (logically replacing it)
            node->data = temp->data;

            // Delete the original successor node from the right subtree.
            node->right = removeRecursive(node->right, temp->data);
        }

        return node;
    }

    // Helper for destructor
    void destroyRecursive(BSTNode<T>* node) {
        if (node) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    // Constructor and Destructor
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { destroyRecursive(root); root = nullptr; }

    // --- Public Interface ---

    /**
     * @brief Inserts a single value into the BST.
     * Time Complexity: O(log N) average, O(N) worst case.
     */
    void insert(const T& val) {
        root = insertRecursive(root, val);
    }
    
    /**
     * @brief Builds the BST from an unordered list of data.
     * Time Complexity: O(N log N) average, O(N^2) worst case (where N is the size of the vector).
     * This is due to N calls to the insert function.
     */
    void buildFromVector(const std::vector<T>& data) {
        std::cout << "\nBuilding BST from " << data.size() << " elements: [";
        // Display the input data for clarity
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << (i < data.size() - 1 ? ", " : "");
        }
        std::cout << "]" << std::endl;

        // Iterate through the vector and insert each element sequentially
        for (const T& val : data) {
            this->insert(val); // Utilizes the O(log N) / O(N) insert function
        }
        std::cout << "Building complete. Tree structure established." << std::endl;
    }

    /**
     * @brief Removes a value from the BST.
     * Time Complexity: O(log N) average, O(N) worst case.
     */
    void remove(const T& val) {
        bool wasPresent = this->search(val);
        root = removeRecursive(root, val);
        
        if (wasPresent && !this->search(val)) {
            std::cout << "Successfully removed: " << val << "!" << std::endl;
        } else if (wasPresent && this->search(val)) {
            std::cout << "Warning: Attempted removal of " << val << ", but it might still exist." << std::endl;
        } else {
            std::cout << "Could not remove: " << val << " (Not found)." << std::endl;
        }
    }

    /**
     * @brief Displays the elements in sorted order.
     * Time Complexity: O(N) in both average and worst cases.
     */
    void inOrderDisplay() const {
        std::cout << "\nIn-Order Traversal (Sorted): [";
        inOrderRecursive(root);
        std::cout << "]" << std::endl;
    }
    
    /**
     * @brief Searches for a value.
     * Time Complexity: O(log N) average, O(N) worst case.
     */
    bool search(const T& val) const {
        return searchRecursive(root, val);
    }
};

int main() {
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << "--- Binary Search Tree (BST) Build, Search, and Delete Demo ---" << std::endl;
    std::cout << "--- All operations are O(log N) average, O(N) worst case. ---" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    BinarySearchTree<int> bst;
    
    // Initial unordered input data
    std::vector<int> unorderedData = { 50, 30, 70, 20, 40, 60, 80, 15, 35, 75 };
    
    // O(N log N) average case construction
    bst.buildFromVector(unorderedData);
    bst.inOrderDisplay(); 
    
    std::cout << "\n==========================================================" << std::endl;
    std::cout << "--- Deletion Demonstration (O(log N) average case) ---" << std::endl;
    std::cout << "==========================================================" << std::endl;
    
    // Case 1: Delete a Leaf Node (15) - O(log N)
    std::cout << "\n-- Deleting a LEAF NODE (15) --" << std::endl;
    bst.remove(15);
    bst.inOrderDisplay();

    // Case 2: Delete a Node with ONE CHILD (20) - O(log N)
    std::cout << "\n-- Deleting a ONE-CHILD NODE (20) --" << std::endl;
    bst.remove(20);
    bst.inOrderDisplay();

    // Case 3: Delete a Node with TWO CHILDREN (70) - O(log N)
    std::cout << "\n-- Deleting a TWO-CHILD NODE (70) --" << std::endl;
    bst.remove(70);
    bst.inOrderDisplay();
    
    // Case 4: Delete the Root (50) - O(log N)
    std::cout << "\n-- Deleting the ROOT NODE (50) --" << std::endl;
    bst.remove(50);
    bst.inOrderDisplay();

    std::cout << "\n------------------------------------------------------------------" << std::endl;
    std::cout << "--- Worst Case Scenario Demo (O(N^2) Construction) ---" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    BinarySearchTree<int> skewedBst;
    // This input leads to a skewed tree where subsequent operations will be O(N)
    std::vector<int> sortedData = { 10, 20, 30, 40, 50 }; 
    skewedBst.buildFromVector(sortedData); // O(N^2) construction
    
    skewedBst.inOrderDisplay(); // O(N) traversal
    std::cout << "This tree is skewed. Deleting '50' would take O(N) time." << std::endl;

    return 0;
}
