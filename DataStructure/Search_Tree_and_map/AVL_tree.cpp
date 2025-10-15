#include <iostream>
#include <algorithm> // For std::max

// --- 1. Node Structure ---
// AVLNode tracks its key and its height for balancing.
struct AVLNode {
    int key;
    AVLNode *left;
    AVLNode *right;
    int height; 

    AVLNode(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

// --- 2. AVL Tree Class ---
class AVLTree {
private:
    AVLNode *root;

    // --- Helper Functions ---

    /**
     * @brief Gets the height of a node. Returns 0 if the node is nullptr.
     */
    int getHeight(AVLNode* node) const {
        return (node == nullptr) ? 0 : node->height;
    }

    /**
     * @brief Calculates the Balance Factor (Height of Left - Height of Right).
     */
    int getBalanceFactor(AVLNode* node) const {
        return (node == nullptr) ? 0 : (getHeight(node->left) - getHeight(node->right));
    }

    /**
     * @brief Updates the height of a node based on its children's heights.
     */
    void updateHeight(AVLNode* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    /**
     * @brief Finds the node with the minimum key in a subtree (used for deletion).
     */
    AVLNode* findMinNode(AVLNode* node) const {
        AVLNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // --- 3. Rotation Operations ---
    
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        // Heights MUST be updated from bottom up (y first, then x)
        updateHeight(y);
        updateHeight(x);

        return x; // New root
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        // Heights MUST be updated from bottom up (x first, then y)
        updateHeight(x);
        updateHeight(y);

        return y; // New root
    }
    
    // --- 4. Rebalancing Logic ---

    /**
     * @brief Performs the necessary rotation(s) to restore balance.
     * @param node The root of the unbalanced subtree.
     * @param balance The balance factor of the node.
     * @param key (Optional for insertion, but general logic requires knowing where the imbalance came from)
     * @return AVLNode* The new root of the balanced subtree.
     */
    AVLNode* rebalance(AVLNode* node) {
        // 1. Update height before checking balance
        updateHeight(node); 
        int balance = getBalanceFactor(node);

        // Case 1: Left Left (LL)
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        // Case 2: Right Right (RR)
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Case 3: Left Right (LR)
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Case 4: Right Left (RL)
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // Already balanced
    }

    // --- 5. Insertion ---

    /**
     * @brief Recursively inserts a key and rebalances.
     */
    AVLNode* insertRecursive(AVLNode* node, int key) {
        // 1. Standard BST Insertion (Base Case)
        if (node == nullptr) {
            return new AVLNode(key);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        } else {
            return node; // Duplicate keys ignored
        }
        
        // 2. Rebalance and return the new root of this subtree
        return rebalance(node);
    }
    
    // --- 6. Deletion ---

    /**
     * @brief Recursively deletes a key and rebalances the tree.
     */
    AVLNode* deleteRecursive(AVLNode* node, int key) {
        // 1. Standard BST Deletion (Base Case)
        if (node == nullptr) return nullptr;

        // Find the node
        if (key < node->key) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = deleteRecursive(node->right, key);
        } else {
            // Node with key found
            
            // Case 1: 0 or 1 child
            if ((node->left == nullptr) || (node->right == nullptr)) {
                AVLNode* temp = node->left ? node->left : node->right;

                if (temp == nullptr) { // 0 children
                    temp = node;
                    node = nullptr;
                } else { // 1 child
                    *node = *temp; // Copy contents of the single child
                }
                delete temp;
            } 
            // Case 2: 2 children
            else {
                // Get the in-order successor (smallest in the right subtree)
                AVLNode* temp = findMinNode(node->right);

                // Copy the successor's data to this node
                node->key = temp->key;

                // Delete the in-order successor (which now has 0 or 1 child)
                node->right = deleteRecursive(node->right, temp->key);
            }
        }

        // If the tree had only one node, then return
        if (node == nullptr) return nullptr;

        // 2. Rebalance and return the new root of this subtree
        return rebalance(node);
    }
    
    // --- 7. Search ---
    
    /**
     * @brief Standard BST Search.
     */
    bool searchRecursive(AVLNode* node, int key) const {
        if (node == nullptr) return false;
        if (key == node->key) return true;
        if (key < node->key) return searchRecursive(node->left, key);
        return searchRecursive(node->right, key);
    }

    // --- 8. Traversal and Destruction ---

    void inOrder(AVLNode* node) const {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->key << "(h:" << node->height << ", bf:" << getBalanceFactor(node) << ") ";
            inOrder(node->right);
        }
    }
    
    void destroyRecursive(AVLNode* node) {
        if (node != nullptr) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }


public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyRecursive(root); }

    void insert(int key) {
        std::cout << "-> Inserting " << key << std::endl;
        root = insertRecursive(root, key);
    }

    void deleteNode(int key) {
        std::cout << "-> Deleting " << key << std::endl;
        root = deleteRecursive(root, key);
    }

    bool search(int key) const {
        return searchRecursive(root, key);
    }

    void printTreeState() const {
        std::cout << "\n--- Current Tree State (In-Order: Key, Height, Balance Factor) ---" << std::endl;
        inOrder(root);
        std::cout << "\n-------------------------------------------------------------------" << std::endl;
        if (root) {
            std::cout << "Root Key: " << root->key << " | Height: " << root->height << std::endl;
        } else {
            std::cout << "Tree is empty." << std::endl;
        }
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "    AVL Tree Demonstration (Insert, Delete, Search)" << std::endl;
    std::cout << "========================================" << std::endl;

    AVLTree tree;

    // --- Part 1: Insertion and Rebalancing ---
    std::cout << "\n### PHASE 1: Insertion (Testing Rotations) ###" << std::endl;
    
    // Insert 10, 20, 30 (Triggers RR Rotation at 10, 20 becomes new root)
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); 
    tree.printTreeState(); // Expected: 10(h:1, bf:0) 20(h:2, bf:-1) 30(h:1, bf:0)

    // Insert 40, 50, 60
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.printTreeState(); 
    // Tree should now look like: 30 is root (balance -1)
    
    // Insert 25 (Triggers LR Rotation at 40 (inside 30's right subtree))
    tree.insert(25);
    tree.printTreeState(); 

    // --- Part 2: Search ---
    std::cout << "\n### PHASE 2: Search Test ###" << std::endl;
    int search_key_1 = 40;
    int search_key_2 = 99;
    std::cout << "Search for " << search_key_1 << ": " 
              << (tree.search(search_key_1) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for " << search_key_2 << ": " 
              << (tree.search(search_key_2) ? "Found" : "Not Found") << std::endl;


    // --- Part 3: Deletion and Rebalancing ---
    std::cout << "\n### PHASE 3: Deletion (Testing Rebalancing) ###" << std::endl;
    
    // Delete a leaf (10) - Simple deletion
    tree.deleteNode(10);
    tree.printTreeState();
    
    // Delete 50 (Node with 2 children - uses successor)
    tree.deleteNode(50);
    tree.printTreeState();
    
    // Delete 20 - This delete will cause the tree to become unbalanced 
    // and trigger a rebalance (usually a single rotation) on the path up.
    std::cout << "\n--- Deleting 20 (Triggers Rebalance on ancestor) ---" << std::endl;
    tree.deleteNode(20);
    tree.printTreeState();
    
    // Final state of the tree after multiple balanced operations.
    std::cout << "\nFinal Search Test after deletions:" << std::endl;
    std::cout << "Search for 20: " << (tree.search(20) ? "Found" : "Not Found") << std::endl; // Should be Not Found

    return 0;
}
