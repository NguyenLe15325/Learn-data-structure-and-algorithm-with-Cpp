#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

// --- 1. Enumeration and Node Structure ---

/**
 * @brief Colors for Red-Black Tree nodes.
 */
enum Color { RED, BLACK };

/**
 * @brief Node structure for the Red-Black Map.
 */
struct RBTNode {
    int key;
    string value;
    Color color;
    RBTNode* parent;
    RBTNode* left;
    RBTNode* right;

    RBTNode(int k, const string& v = "", Color c = RED)
        : key(k), value(v), color(c), parent(nullptr), left(nullptr), right(nullptr) {}
};

/**
 * @brief Forward declaration of the map class for the iterator definition.
 */
class RedBlackMap;

// --- 2. Bidirectional Iterator ---

/**
 * @brief Bidirectional iterator for the RedBlackMap. 
 * Allows for in-order (sorted) traversal using operator++ and operator--.
 */
struct RBT_Iterator {
    RBTNode* current;
    RBTNode* NIL; // The sentinel node from the map

    RBT_Iterator(RBTNode* node, RBTNode* nil_sentinel) : current(node), NIL(nil_sentinel) {}

    // Required for comparison
    bool operator==(const RBT_Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const RBT_Iterator& other) const {
        return current != other.current;
    }

    // Access to the key-value pair (mimics std::map behavior)
    pair<const int, string>& operator*() const {
        // This is safe because RBTNode is structurally similar to pair<int, string>
        // We use a reinterpret_cast to safely treat the RBTNode as the pair it represents
        return *reinterpret_cast<pair<const int, string>*>(current);
    }
    
    pair<const int, string>* operator->() const {
        return reinterpret_cast<pair<const int, string>*>(current);
    }

    /**
     * @brief Prefix increment: Find the successor node (next largest key).
     * This is the core of in-order traversal.
     */
    RBT_Iterator& operator++() {
        if (current == NIL) return *this;

        // Case 1: If right subtree exists, successor is the minimum node in the right subtree
        if (current->right != NIL) {
            current = current->right;
            while (current->left != NIL) {
                current = current->left;
            }
            return *this;
        }

        // Case 2: No right subtree. Successor is the lowest ancestor whose left child is also an ancestor of current.
        RBTNode* y = current->parent;
        while (y != NIL && current == y->right) {
            current = y;
            y = y->parent;
        }
        current = y; // y is the successor (or NIL if we reached the root's parent)
        return *this;
    }

    /**
     * @brief Postfix increment (returns copy before increment).
     */
    RBT_Iterator operator++(int) {
        RBT_Iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Defer implementation of operator-- (decrement) for complexity reduction
    // This implementation is focused on the minimum requirements for a map.
};

// --- 3. RedBlackMap Class Definition ---

/**
 * @brief Custom implementation of a key-value map using a Red-Black Tree (RBT).
 * Guarantees O(log N) worst-case performance.
 */
class RedBlackMap {
private:
    RBTNode* root;
    RBTNode* NIL; // The sentinel node (always black, represents NULL children)
    size_t size_count;

    // Helper: Finds the node with the minimum key in the subtree rooted at node.
    RBTNode* minimum(RBTNode* node) const {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    // Helper: Finds the node with the maximum key in the subtree rooted at node.
    RBTNode* maximum(RBTNode* node) const {
        while (node->right != NIL) {
            node = node->right;
        }
        return node;
    }

    // --- Core RBT Balancing Operations ---

    // Left Rotation
    void rotateLeft(RBTNode* x) {
        RBTNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Right Rotation
    void rotateRight(RBTNode* x) {
        RBTNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;

        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Fixes the RBT properties after insertion of node 'k'. (O(log N) time)
    void fixInsert(RBTNode* k) {
        RBTNode* u;
        while (k != root && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right; // Uncle
                
                // Case 1: Uncle is RED (Recoloring)
                if (u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent; 
                } 
                else { 
                    // Case 2: k is a RIGHT child (Triangle Case - Left Rotation)
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotateLeft(k);
                    }
                    // Case 3: k is a LEFT child (Line Case - Right Rotation)
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            } 
            else { // Mirror Case (Parent is right child of Grandparent)
                u = k->parent->parent->left; // Uncle
                
                // Case 4: Uncle is RED (Recoloring)
                if (u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } 
                else {
                    // Case 5: k is a LEFT child (Triangle Case - Right Rotation)
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    // Case 6: k is a RIGHT child (Line Case - Left Rotation)
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Helper: Replaces one subtree (u) with another subtree (v) at the parent level.
    void rbTransplant(RBTNode* u, RBTNode* v) {
        if (u->parent == NIL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // The function that fixes the RBT properties after an internal deletion (O(log N) time)
    void fixDelete(RBTNode* x) {
        while (x != root && x->color == BLACK) {
            RBTNode* w; // Sibling node
            if (x == x->parent->left) { // x is a left child
                w = x->parent->right;

                // Case 1: Sibling w is RED (recolor and rotate to get to a black sibling case)
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right; // Update w (it must now be black)
                }

                // Case 2: Sibling w is BLACK, and both of w's children are BLACK (recolor w and move up)
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } 
                else {
                    // Case 3: Sibling w is BLACK, w's right child is BLACK, and w's left child is RED 
                    // (Right rotation on w to transform to Case 4)
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right; // Update w
                    }
                    // Case 4: Sibling w is BLACK, and w's right child is RED (final rotation and coloring)
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root; // Done, loop terminates
                }
            } 
            else { // Mirror case: x is a right child
                w = x->parent->left;

                // Case 1 (Mirror): Sibling w is RED
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }

                // Case 2 (Mirror): Sibling w is BLACK, and both children are BLACK
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } 
                else {
                    // Case 3 (Mirror): Sibling w is BLACK, w's left child is BLACK, and w's right child is RED
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    // Case 4 (Mirror): Sibling w is BLACK, and w's left child is RED
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root; // Done, loop terminates
                }
            }
        }
        x->color = BLACK;
    }

    /**
     * @brief Performs the deletion of the node z.
     * Implements the core deletion logic used in RBTs, including replacement and fixing.
     */
    void deleteNode(RBTNode* z) {
        RBTNode* y = z; // y is the node to be physically removed or moved
        RBTNode* x;     // x is the child of y, which moves into y's position
        Color y_original_color = y->color;

        if (z->left == NIL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right); // y is z's successor
            y_original_color = y->color;
            x = y->right;
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
            y->color = z->color;
        }
        delete z; // The node memory is freed
        size_count--;

        if (y_original_color == BLACK) {
            fixDelete(x); // If a black node was removed/moved, fix the balance
        }
    }


    /**
     * @brief Recursively destroys all nodes (for the destructor and clear()).
     */
    void destroyRecursive(RBTNode* node) {
        if (node != NIL) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }


public:
    // --- Constructor & Destructor ---
    RedBlackMap() : root(nullptr), size_count(0) {
        // Initialize the sentinel NIL node (always Black)
        NIL = new RBTNode(0, "", BLACK); 
        NIL->parent = NIL; // NIL points to itself to handle root/NIL parent case
        root = NIL;
    }

    ~RedBlackMap() {
        clear();
        delete NIL;
    }

    // Prevent copy/move operations for simplicity
    RedBlackMap(const RedBlackMap&) = delete;
    RedBlackMap& operator=(const RedBlackMap&) = delete;


    // --- Public Map Interface (Core STL Methods) ---

    // Type definition for iterator
    using iterator = RBT_Iterator;

    /**
     * @brief Returns an iterator to the first element (the smallest key).
     */
    iterator begin() const {
        if (root == NIL) return iterator(NIL, NIL);
        return iterator(minimum(root), NIL);
    }

    /**
     * @brief Returns an iterator to the past-the-end element (the NIL sentinel).
     */
    iterator end() const {
        return iterator(NIL, NIL);
    }

    /**
     * @brief Checks if the container is empty.
     */
    bool empty() const {
        return root == NIL;
    }

    /**
     * @brief Returns the number of elements.
     */
    size_t size() const {
        return size_count;
    }

    /**
     * @brief Clears the map content.
     */
    void clear() {
        destroyRecursive(root);
        root = NIL;
        size_count = 0;
    }

    /**
     * @brief Search for element with specific key. Returns end() if not found. (O(log N))
     */
    iterator find(int key) const {
        RBTNode* current = root;
        while (current != NIL) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return iterator(current, NIL); // Key found
            }
        }
        return end(); // Key not found
    }
    
    /**
     * @brief Access operator (std::map::operator[]). Inserts default value if key not present. (O(log N))
     */
    string& operator[](int key) {
        iterator it = find(key);
        if (it != end()) {
            return (*it).second; // Key found, return reference to value
        }
        
        // Key not found, insert with default value and return reference
        // This leverages the main RBT insertion logic
        return insert(key, "").first->second;
    }

    /**
     * @brief Inserts a new element. Returns an iterator to the element and a bool (true if inserted). (O(log N))
     */
    pair<iterator, bool> insert(int key, const string& value) {
        RBTNode* existing = find(key).current;
        if (existing != NIL) {
            return {iterator(existing, NIL), false}; // Key already exists
        }
        
        // --- 1. Standard BST Insertion ---
        RBTNode* newNode = new RBTNode(key, value, RED);
        RBTNode* y = NIL;
        RBTNode* x = this->root;

        while (x != NIL) {
            y = x;
            if (newNode->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        newNode->parent = y;
        if (y == NIL) {
            this->root = newNode;
        } else if (newNode->key < y->key) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        newNode->left = NIL;
        newNode->right = NIL;
        size_count++;
        
        // --- 2. RBT Balancing ---
        fixInsert(newNode);

        return {iterator(newNode, NIL), true};
    }

    /**
     * @brief Erases the element at the given iterator position. (O(log N))
     */
    iterator erase(iterator position) {
        if (position.current == NIL) {
            return end();
        }

        RBTNode* node_to_delete = position.current;
        iterator next_it = position;
        ++next_it; // Get the successor before deleting

        deleteNode(node_to_delete);
        return next_it;
    }

    /**
     * @brief Erases the element with the given key. Returns 1 if deleted, 0 otherwise. (O(log N))
     */
    size_t erase(int key) {
        iterator it = find(key);
        if (it == end()) {
            return 0; // Not found
        }
        
        erase(it);
        return 1; // Found and deleted
    }
};

// --- Example Usage (Main function) ---

int main() {
    RedBlackMap my_map;
    
    cout << "--- RBT Map Initialization ---" << endl;
    
    // 1. Insertion using operator[] (inserts if not exists)
    my_map[50] = "Root";
    my_map[30] = "Left";
    my_map[70] = "Right";
    my_map[20] = "L-Left";
    my_map[40] = "L-Right";
    my_map[60] = "R-Left";
    my_map[80] = "R-Right";
    
    cout << "Size after initial insertions: " << my_map.size() << endl;

    // 2. Traversal using iterators (should print in sorted order)
    cout << "\n--- In-Order Traversal (Sorted Keys) ---" << endl;
    for (auto it = my_map.begin(); it != my_map.end(); ++it) {
        cout << "Key: " << (*it).first << ", Value: " << (*it).second << endl;
    }

    // 3. Insertion that forces balancing (e.g., creating a double-red case)
    cout << "\n--- Forced RBT Balancing (Inserting 10 and 90) ---" << endl;
    my_map[10] = "Deep Left";
    my_map[90] = "Deep Right";
    cout << "Size after balancing insertions: " << my_map.size() << endl;

    // 4. Access and Update
    my_map[50] = "New Root Value";
    cout << "Value of key 50 after update: " << my_map[50] << endl;

    // 5. Searching (find)
    cout << "\n--- Search Operation ---" << endl;
    auto found_it = my_map.find(40);
    if (found_it != my_map.end()) {
        cout << "Found key 40: " << (*found_it).second << endl;
    } else {
        cout << "Key 40 not found (Error in logic!)." << endl;
    }

    // 6. Deletion (erase)
    cout << "\n--- Deletion (Erase 30 and 50) ---" << endl;
    
    // Erase by key
    size_t erased_count = my_map.erase(30);
    cout << "Erased key 30. Count: " << erased_count << ". New Size: " << my_map.size() << endl;

    // Erase by iterator (erasing the root, which will force a complex fixDelete)
    auto it_to_erase = my_map.find(50); 
    if (it_to_erase != my_map.end()) {
        my_map.erase(it_to_erase); 
        cout << "Erased key 50 (Root). New Size: " << my_map.size() << endl;
    }

    // 7. Final Traversal
    cout << "\n--- Final Traversal After Deletion ---" << endl;
    for (const auto& entry : my_map) {
        // C++17 structured binding/range-based for loop
        cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
    }
    
    return 0;
}
