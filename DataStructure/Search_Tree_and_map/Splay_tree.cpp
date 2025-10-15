#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits> 

using namespace std;

// --- 1. Node Definition ---
struct SplayNode {
    int key;
    SplayNode *left, *right;

    SplayNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

// --- 2. Splay Tree Class ---
class SplayTree {
private:
    SplayNode* root;

    /**
     * @brief Performs a single right rotation (used by Splay).
     */
    SplayNode* rotateRight(SplayNode* x) {
        SplayNode* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    /**
     * @brief Performs a single left rotation (used by Splay).
     */
    SplayNode* rotateLeft(SplayNode* x) {
        SplayNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    /**
     * @brief The core Splay operation, implemented ITERATIVELY for safety. 
     * Moves the accessed node (or the last node accessed if key is not found) to the root.
     * @return The new root of the (sub)tree.
     */
    SplayNode* splay(SplayNode* current_root, int key) {
        if (current_root == nullptr) return nullptr;

        // Dummy node used to construct the left and right subtrees during splay.
        SplayNode header(0); 
        // left_max: Pointer to the maximum node in the assembled left-tree (nodes < key). 
        SplayNode* left_max = &header;
        // right_min: Pointer to the minimum node in the assembled right-tree (nodes > key).
        SplayNode* right_min = &header;
        SplayNode* current = current_root;

        while (true) {
            if (key < current->key) {
                if (current->left == nullptr) break;

                // Zig-Zig Case (Left-Left): Perform one rotation on the parent.
                if (key < current->left->key) {
                    current = rotateRight(current);
                    if (current->left == nullptr) break;
                }
                
                // Link current node to the right tree
                right_min->left = current;
                right_min = current;
                current = current->left; // Move to the left child
            } 
            else if (key > current->key) {
                if (current->right == nullptr) break;

                // Zig-Zig Case (Right-Right): Perform one rotation on the parent.
                if (key > current->right->key) {
                    current = rotateLeft(current);
                    if (current->right == nullptr) break;
                }

                // Link current node to the left tree
                left_max->right = current;
                left_max = current;
                current = current->right; // Move to the right child
            } 
            else {
                break; // Found the node: key == current->key
            }
        }

        // --- Reassemble the tree ---
        // 1. The root of the assembled left tree is header.right.
        // 2. The root of the assembled right tree is header.left.
        // 3. The current node is the new root.
        left_max->right = current->left;
        right_min->left = current->right;
        current->left = header.right;
        current->right = header.left;

        return current;
    }
    
    /**
     * @brief Helper function for Pre-Order traversal with indentation.
     */
    void printPreOrder(SplayNode* node, int depth) {
        if (node != nullptr) {
            string indent = string(depth * 4, ' ');
            
            cout << indent << "|-- " << node->key << (node == root ? " (ROOT)" : "") << endl;
            
            printPreOrder(node->left, depth + 1);
            printPreOrder(node->right, depth + 1);
        }
    }
    
    /**
     * @brief Recursive helper to safely deallocate the tree nodes (Post-Order).
     */
    void destroyTree(SplayNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    SplayTree() : root(nullptr) {}

    /**
     * @brief Inserts a new key. Always splays the new node to the root.
     */
    void insert(int key) {
        if (root == nullptr) {
            root = new SplayNode(key);
            return;
        }

        root = splay(root, key);

        if (root->key == key) {
            return; // Key already exists
        }

        // Split the tree and insert the new node as the root.
        SplayNode* newNode = new SplayNode(key);

        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else { 
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        root = newNode;
    }

    /**
     * @brief Searches for a key. Always splays the accessed node (or null node) to the root.
     * @return true if found, false otherwise.
     */
    bool search(int key) {
        if (root == nullptr) {
            return false;
        }

        root = splay(root, key);

        return root != nullptr && root->key == key;
    }

    /**
     * @brief Deletes a key by splaying it to the root, splitting the tree, and 
     * then merging the left and right subtrees.
     */
    void remove(int key) {
        SplayNode* temp;

        if (root == nullptr) return;

        // Splay the node to be removed to the root
        root = splay(root, key);

        if (key != root->key) {
            return; // Key not found
        }

        temp = root;
        
        // If the left child is null, the right child becomes the new root.
        if (root->left == nullptr) {
            root = root->right;
        }
        // Otherwise, splay the maximum element in the left subtree to the root 
        // of the left subtree (by searching for INT_MAX) and attach the right child.
        else {
            root = splay(root->left, INT_MAX); 
            // The splayed node (the predecessor) is now the new root.
            // Attach the old root's right child to the new root's right pointer.
            root->right = temp->right;
        }

        delete temp;
    }

    /**
     * @brief Public method to print the tree structure.
     */
    void printTree() {
        cout << "\n--- Splay Tree Structure ---" << endl;
        if (root) {
            printPreOrder(root, 0);
        } else {
            cout << "The tree is empty." << endl;
        }
        cout << "--------------------------\n" << endl;
    }
    
    /**
     * @brief Destructor calls the recursive helper to clean up memory safely.
     */
    ~SplayTree() {
        destroyTree(root);
        root = nullptr;
    }
};

// --- Example Execution ---
int main() {
    SplayTree tree;

    cout << "--- Initial Insertions (Sequential) ---" << endl;
    
    tree.insert(10);
    tree.printTree(); 

    tree.insert(20);
    tree.printTree(); 

    tree.insert(30);
    tree.printTree(); 
    
    tree.insert(40);
    tree.printTree(); 

    cout << "--- Insertions (Scrambled) ---" << endl;
    // These are the operations that were causing the crash previously.
    tree.insert(5);
    tree.insert(25);
    tree.insert(15);
    tree.printTree(); 

    cout << "--- Testing Search and Splaying ---" << endl;
    
    // 1. Search for a node deep in the tree (10)
    cout << "Searching for key 10..." << endl;
    if (tree.search(10)) {
        cout << "Key 10 found." << endl;
    }
    tree.printTree(); 

    // 2. Search for a key that does not exist (99)
    cout << "Searching for key 99 (non-existent)..." << endl;
    if (!tree.search(99)) {
        cout << "Key 99 not found." << endl;
    }
    tree.printTree(); 

    // 3. Delete the root (The non-existent search splayed 40 to the root)
    cout << "Deleting key 40..." << endl;
    tree.remove(40);
    tree.printTree(); 

    // 4. Delete 5
    cout << "Deleting key 5..." << endl;
    tree.remove(5);
    tree.printTree(); 

    return 0; // The successful execution of the destructor should clean up the rest.
}
