#include <iostream>
#include <stdexcept>

// --- 1. Node Structure ---
// Represents one element in the tree.
struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// --- 2. BST Class ---
class BST {
private:
    Node *root;

    // --- Private Helper Functions for Recursion ---

    /**
     * @brief Recursively inserts a new key into the correct position.
     * @param node The current node being examined.
     * @param key The value to insert.
     * @return Node* The updated node pointer (used to link children).
     */
    Node* insertRecursive(Node* node, int key) {
        // Base case: If the current node is null, we found the insertion point.
        if (node == nullptr) {
            return new Node(key);
        }

        // Standard BST rule: keys smaller than current node go left.
        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } 
        // keys larger than current node go right.
        else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }
        // Duplicate keys are typically ignored in a basic BST.
        // else { key is equal, do nothing }

        return node;
    }

    /**
     * @brief Recursively searches for a key.
     * @param node The current node being examined.
     * @param key The value to find.
     * @return bool True if the key is found, false otherwise.
     */
    bool searchRecursive(Node* node, int key) const {
        // Base case 1: Key not found (reached a leaf's null pointer).
        if (node == nullptr) {
            return false;
        }

        // Base case 2: Key found.
        if (key == node->key) {
            return true;
        }

        // Recursive step: Go left or right.
        if (key < node->key) {
            return searchRecursive(node->left, key);
        } else {
            return searchRecursive(node->right, key);
        }
    }
    
    /**
     * @brief Traverses the tree: Left -> Node -> Right.
     * This always prints keys in ascending (sorted) order.
     * @param node The current node.
     */
    void inorderTraversal(Node* node) const {
        if (node != nullptr) {
            inorderTraversal(node->left);  // 1. Visit Left
            std::cout << node->key << " "; // 2. Visit Node (Print)
            inorderTraversal(node->right); // 3. Visit Right
        }
    }

    /**
     * @brief Traverses the tree: Node -> Left -> Right.
     * This is useful for copying the tree structure.
     * @param node The current node.
     */
    void preorderTraversal(Node* node) const {
        if (node != nullptr) {
            std::cout << node->key << " "; // 1. Visit Node (Print)
            preorderTraversal(node->left);  // 2. Visit Left
            preorderTraversal(node->right); // 3. Visit Right
        }
    }

    /**
     * @brief Helper function to delete all nodes (used in the destructor).
     * @param node The current node to delete.
     */
    void destroyRecursive(Node* node) {
        if (node != nullptr) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    // Destructor to clean up all dynamically allocated memory.
    ~BST() {
        destroyRecursive(root);
    }

    // --- Public Interface Functions ---

    /**
     * @brief Public entry point for insertion.
     */
    void insert(int key) {
        root = insertRecursive(root, key);
        std::cout << "Inserted key: " << key << std::endl;
    }

    /**
     * @brief Public entry point for searching.
     */
    bool search(int key) const {
        return searchRecursive(root, key);
    }

    /**
     * @brief Prints all keys in sorted (in-order) sequence.
     */
    void printInOrder() const {
        std::cout << "In-Order (Sorted): ";
        inorderTraversal(root);
        std::cout << std::endl;
    }

    /**
     * @brief Prints keys in Pre-Order sequence.
     */
    void printPreOrder() const {
        std::cout << "Pre-Order:       ";
        preorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "--- Binary Search Tree Demonstration ---" << std::endl;

    BST tree;
    
    // Inserting keys in a specific order: 50 -> 30 -> 70 -> 20 -> 40 -> 60 -> 80
    // This insertion order creates a relatively balanced tree:
    //         50
    //       /    \
    //      30     70
    //     / \    / \
    //    20 40  60 80
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    std::cout << "\n--- Traversal ---" << std::endl;
    tree.printInOrder();
    tree.printPreOrder();

    std::cout << "\n--- Search Test ---" << std::endl;
    int key_found = 40;
    int key_missing = 99;

    std::cout << "Searching for " << key_found << ": " 
              << (tree.search(key_found) ? "Found" : "Not Found") << std::endl;
              
    std::cout << "Searching for " << key_missing << ": " 
              << (tree.search(key_missing) ? "Found" : "Not Found") << std::endl;

    // Note: A full implementation would also require a complex 'remove' function, 
    // which involves finding the in-order successor to maintain the BST properties 
    // when deleting a node with two children.

    return 0;
}
