#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Define colors using an enum for type safety
enum Color { RED, BLACK };

// --- 1. Node Structure ---
struct RBNode {
    int key;
    Color color;
    RBNode *parent;
    RBNode *left;
    RBNode *right;

    // Constructor for a standard node (defaults to RED for new insertions)
    RBNode(int val, Color c = RED) : 
        key(val), color(c), parent(nullptr), left(nullptr), right(nullptr) {}
};

// --- 2. Red-Black Tree Class ---
class RedBlackTree {
private:
    // The single sentinel node (NIL) for all external leaves.
    // It must always be BLACK.
    RBNode* NIL; 
    RBNode* root;

    // Helper for printing color names
    string colorToString(Color c) const {
        return (c == RED) ? "RED" : "BLACK";
    }

    /**
     * @brief Performs a Left Rotation around node x.
     * x's right child (y) moves up to x's position.
     */
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        
        // 1. Turn y's left subtree (T2) into x's right subtree
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }

        // 2. Link x's parent to y
        y->parent = x->parent;
        if (x->parent == NIL) {
            this->root = y; // y becomes the new root
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        // 3. Put x on y's left
        y->left = x;
        x->parent = y;
    }

    /**
     * @brief Performs a Right Rotation around node y.
     * y's left child (x) moves up to y's position.
     */
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;

        // 1. Turn x's right subtree (T2) into y's left subtree
        y->left = x->right;
        if (x->right != NIL) {
            x->right->parent = y;
        }

        // 2. Link y's parent to x
        x->parent = y->parent;
        if (y->parent == NIL) {
            this->root = x; // x becomes the new root
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }

        // 3. Put y on x's right
        x->right = y;
        y->parent = x;
    }

    /**
     * @brief Restores Red-Black properties after insertion.
     * @param z The newly inserted RED node.
     */
    void insertFixup(RBNode* z) {
        while (z->parent->color == RED) {
            // Case 1: z's parent is the left child of its grandparent
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right; // Uncle of z
                
                // Case 1a: Uncle y is RED (Recoloring)
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent; 
                } 
                // Case 1b & 1c: Uncle y is BLACK (Rotation)
                else {
                    // Case 1b: z is a right child (LR Case)
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z); 
                    }
                    // Case 1c: z is a left child (LL Case)
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } 
            // Case 2: z's parent is the right child of its grandparent (Symmetric)
            else { 
                RBNode* y = z->parent->parent->left; // Uncle of z

                // Case 2a: Uncle y is RED (Recoloring)
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent; 
                } 
                // Case 2b & 2c: Uncle y is BLACK (Rotation)
                else {
                    // Case 2b: z is a left child (RL Case)
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z); 
                    }
                    // Case 2c: z is a right child (RR Case)
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        this->root->color = BLACK; // Rule 2: Root must be Black
    }

    /**
     * @brief Helper to move subtree v to position of subtree u.
     */
    void rbTransplant(RBNode* u, RBNode* v) {
        if (u->parent == NIL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    /**
     * @brief Finds the node with the minimum key in a subtree.
     */
    RBNode* treeMinimum(RBNode* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    /**
     * @brief Restores Red-Black properties after deletion of a BLACK node.
     * @param x The node that replaces the deleted node (can be NIL).
     */
    void deleteFixup(RBNode* x) {
        // x is the double-black node (or NIL replacing a black node)
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right; // w is sibling

                // Case 1: Sibling w is RED (Recolor and Left Rotate to Case 2/3/4)
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right; // New sibling (now BLACK)
                }

                // Case 2: Sibling w is BLACK and both children are BLACK (Move Double-Black up)
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    // Case 3: Sibling w is BLACK, w's right child is BLACK, w's left child is RED (Inner Rotation)
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right; // New sibling
                    }
                    
                    // Case 4: Sibling w is BLACK, and w's right child is RED (Outer Rotation)
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root; // Terminate loop
                }
            } 
            // Symmetric cases (x is a right child)
            else { 
                RBNode* w = x->parent->left; 

                // Case 1: Sibling w is RED
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                // Case 2: Sibling w is BLACK and both children are BLACK
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    // Case 3: Inner Rotation (LR)
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    // Case 4: Outer Rotation (LL)
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root; // Terminate loop
                }
            }
        }
        x->color = BLACK; // Resolve any remaining double-black node (now single black)
    }

    /**
     * @brief Search utility.
     */
    RBNode* searchRecursive(RBNode* node, int key) const {
        if (node == NIL || key == node->key) {
            return node;
        }
        if (key < node->key) {
            return searchRecursive(node->left, key);
        }
        return searchRecursive(node->right, key);
    }

    /**
     * @brief Clean up memory.
     */
    void destroyRecursive(RBNode* node) {
        if (node != NIL) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }
    
    /**
     * @brief In-Order Traversal for printing.
     */
    void inOrder(RBNode* node) const {
        if (node != NIL) {
            inOrder(node->left);
            cout << node->key << " (" << colorToString(node->color) << ") ";
            inOrder(node->right);
        }
    }


public:
    RedBlackTree() {
        // Initialize the sentinel NIL node (always BLACK)
        NIL = new RBNode(0, BLACK);
        NIL->parent = NIL;
        NIL->left = NIL;
        NIL->right = NIL;
        root = NIL;
    }

    ~RedBlackTree() {
        destroyRecursive(root);
        delete NIL; // Delete the sentinel node
    }

    void insert(int key) {
        // Standard BST insertion
        RBNode* z = new RBNode(key);
        RBNode* y = NIL;
        RBNode* x = this->root;

        while (x != NIL) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else if (z->key > x->key) {
                x = x->right;
            } else {
                 // Handle duplicate keys
                 delete z;
                 return;
            }
        }

        z->parent = y;
        if (y == NIL) {
            this->root = z; // Tree was empty
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }

        // Initialize links to NIL and color to RED
        z->left = NIL;
        z->right = NIL;
        z->color = RED; 

        // Fix the Red-Black violations
        insertFixup(z);
    }
    
    void deleteNode(int key) {
        RBNode* z = searchRecursive(root, key);
        if (z == NIL) {
            cout << "  Key " << key << " not found for deletion." << endl;
            return;
        }
        
        // y is the node that gets spliced out (either z or z's successor)
        RBNode* y = z; 
        RBNode* x;
        Color y_original_color = y->color;

        if (z->left == NIL) {
            x = z->right; 
            rbTransplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left; 
            rbTransplant(z, z->left);
        } 
        else {
            y = treeMinimum(z->right); // y is z's successor
            y_original_color = y->color;
            x = y->right; // x is y's (possible NIL) child

            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right); 
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y); 
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color; // y inherits z's color
        }
        
        delete z; // Free memory of the node spliced out
        
        // Only fixup if a BLACK node was removed (or if its color was BLACK)
        if (y_original_color == BLACK) {
            deleteFixup(x);
        }
    }

    bool search(int key) const {
        return searchRecursive(root, key) != NIL;
    }

    void printTree() const {
        if (root == NIL) {
            cout << "Tree is empty." << endl;
            return;
        }
        cout << "\n--- In-Order Traversal (Key, Color) ---" << endl;
        inOrder(root);
        cout << "\n----------------------------------------" << endl;
        cout << "Root: " << root->key << " (" << colorToString(root->color) << ")" << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "    Red-Black Tree Demonstration" << endl;
    cout << "========================================" << endl;

    RedBlackTree rbt;

    // --- Part 1: Insertion Test ---
    cout << "\n### PHASE 1: Insertion (Testing Fixup/Rotations) ###" << endl;
    
    // Insert sequence that forces various rotations and recolorings (e.g., 10, 20, 30 forces RR and recoloring)
    vector<int> keys = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    for (int key : keys) {
        cout << "Inserting " << key << endl;
        rbt.insert(key);
    }

    rbt.printTree();

    // --- Part 2: Search Test ---
    cout << "\n### PHASE 2: Search Test ###" << endl;
    cout << "Searching for 40: " << (rbt.search(40) ? "Found" : "Not Found") << endl;
    cout << "Searching for 15: " << (rbt.search(15) ? "Found" : "Not Found") << endl;
    cout << "Searching for 90: " << (rbt.search(90) ? "Found" : "Not Found") << endl;

    // --- Part 3: Deletion Test ---
    cout << "\n### PHASE 3: Deletion (Testing Fixup) ###" << endl;
    
    cout << "Deleting 10 (RED leaf, easy)..." << endl;
    rbt.deleteNode(10); 
    rbt.printTree();
    
    cout << "Deleting 60 (Requires finding successor and transplanting)..." << endl;
    rbt.deleteNode(60); 
    rbt.printTree();

    cout << "Deleting 30 (This will likely trigger a full BLACK deletion fixup)..." << endl;
    rbt.deleteNode(30); 
    rbt.printTree();
    
    cout << "Deleting 50 (Root changes and rebalance may occur)..." << endl;
    rbt.deleteNode(50); 
    rbt.printTree();
    
    cout << "\nFinal Search Test after deletions:" << endl;
    cout << "Searching for 60: " << (rbt.search(60) ? "Found" : "Not Found") << endl; 

    return 0;
}
