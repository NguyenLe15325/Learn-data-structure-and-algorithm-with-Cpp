#include <iostream>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

// --- 1. Enumeration and Node Structure ---

/**
 * @brief Colors for Red-Black Tree nodes.
 */
enum Color { RED, BLACK };

/**
 * @brief Node structure for the Red-Black Set. Stores only the unique key.
 */
struct RBTNode {
    int key;
    Color color;
    RBTNode* parent;
    RBTNode* left;
    RBTNode* right;

    // Constructor for a new standard node (defaults to RED for insertion)
    RBTNode(int k, Color c = RED)
        : key(k), color(c), parent(nullptr), left(nullptr), right(nullptr) {}
};

/**
 * @brief Forward declaration of the Set class.
 */
class RedBlackSet;

// --- 2. Bidirectional Iterator ---

/**
 * @brief Bidirectional iterator for the RedBlackSet. 
 */
struct RBT_Iterator {
    RBTNode* current;
    RBTNode* NIL; // The sentinel node from the set

    RBT_Iterator(RBTNode* node, RBTNode* nil_sentinel) : current(node), NIL(nil_sentinel) {}

    // Required for comparison
    bool operator==(const RBT_Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const RBT_Iterator& other) const {
        return current != other.current;
    }

    // Access to the key (mimics *it for std::set)
    const int& operator*() const {
        // We must not dereference the NIL sentinel
        if (current == NIL) throw runtime_error("Attempt to dereference end() iterator.");
        return current->key;
    }

    /**
     * @brief Prefix increment: Finds the successor node (next largest key).
     */
    RBT_Iterator& operator++() {
        if (current == NIL) return *this;

        // Case 1: Successor is the minimum node in the right subtree
        if (current->right != NIL) {
            current = current->right;
            while (current->left != NIL) {
                current = current->left;
            }
            return *this;
        }

        // Case 2: No right subtree. Find the lowest ancestor whose left child is also an ancestor.
        RBTNode* y = current->parent;
        while (y != NIL && current == y->right) {
            current = y;
            y = y->parent;
        }
        current = y; // y will either be the successor or NIL (if current was the max node)
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
    
    // Note: operator-- (decrement/predecessor) is omitted for brevity but required for full bidirectional compliance.
};

// --- 3. RedBlackSet Class Definition ---

/**
 * @brief Custom implementation of a unique, sorted set using a Red-Black Tree (RBT).
 * All core operations (insert, erase, find) are O(log N).
 */
class RedBlackSet {
private:
    RBTNode* root;
    RBTNode* NIL; // The sentinel node (always black, acts as external null)
    size_t size_count;

    // Helper: Finds the node with the minimum key in the subtree rooted at node.
    RBTNode* minimum(RBTNode* node) const {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    // --- Core RBT Balancing Operations (Rotations and Fix-ups) ---
    
    // Left Rotation
    void rotateLeft(RBTNode* x) {
        RBTNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == NIL) { root = y; } 
        else if (x == x->parent->left) { x->parent->left = y; } 
        else { x->parent->right = y; }
        
        y->left = x;
        x->parent = y;
    }

    // Right Rotation
    void rotateRight(RBTNode* x) {
        RBTNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;

        if (x->parent == NIL) { root = y; } 
        else if (x == x->parent->right) { x->parent->right = y; } 
        else { x->parent->left = y; }
        
        y->right = x;
        x->parent = y;
    }

    // Fixes the RBT properties after insertion (guarantees O(log N) total time)
    void fixInsert(RBTNode* k) {
        RBTNode* u;
        while (k != root && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right; // Uncle
                
                if (u->color == RED) { // Case 1: Uncle is RED
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent; 
                } 
                else { 
                    if (k == k->parent->right) { // Case 2: Triangle case (Rotation needed)
                        k = k->parent;
                        rotateLeft(k);
                    }
                    // Case 3: Line case (Final rotation)
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            } 
            else { // Mirror cases (parent is right child)
                u = k->parent->parent->left; // Uncle
                
                if (u->color == RED) { // Case 4: Uncle is RED
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } 
                else {
                    if (k == k->parent->left) { // Case 5: Triangle case (Rotation needed)
                        k = k->parent;
                        rotateRight(k);
                    }
                    // Case 6: Line case (Final rotation)
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
        }
        root->color = BLACK; // Root must always be black
    }

    // Replaces one subtree (u) with another subtree (v) at the parent level.
    void rbTransplant(RBTNode* u, RBTNode* v) {
        if (u->parent == NIL) { root = v; } 
        else if (u == u->parent->left) { u->parent->left = v; } 
        else { u->parent->right = v; }
        v->parent = u->parent;
    }

    // The function that fixes the RBT properties after deletion (O(log N) time)
    void fixDelete(RBTNode* x) {
        while (x != root && x->color == BLACK) {
            RBTNode* w; // Sibling node
            if (x == x->parent->left) { // x is a left child
                w = x->parent->right;

                if (w->color == RED) { // Case 1: Sibling w is RED
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right; 
                }
                // Cases 2, 3, 4 follow standard RBT logic based on w's children colors
                if (w->left->color == BLACK && w->right->color == BLACK) { 
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right; 
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root; 
                }
            } else { // Mirror case: x is a right child
                w = x->parent->left;

                if (w->color == RED) { // Case 1 (Mirror)
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                
                if (w->right->color == BLACK && w->left->color == BLACK) { // Case 2 (Mirror)
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) { // Case 3 (Mirror)
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    // Case 4 (Mirror)
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root; 
                }
            }
        }
        x->color = BLACK;
    }

    /**
     * @brief Performs the actual deletion of the node z.
     */
    void deleteNode(RBTNode* z) {
        RBTNode* y = z; 
        RBTNode* x;     
        Color y_original_color = y->color;

        if (z->left == NIL) { // z has at most one child (right)
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == NIL) { // z has only a left child
            x = z->left;
            rbTransplant(z, z->left);
        } else { // z has two children, find successor y
            y = minimum(z->right); 
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) { // Successor is direct child
                x->parent = y;
            } else { // Successor is deeper
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color; // y takes z's color
        }
        delete z; 
        size_count--;

        if (y_original_color == BLACK) {
            fixDelete(x); // Fix the tree if a black node was removed/replaced
        }
    }


    /**
     * @brief Recursively destroys all nodes for cleanup.
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
    RedBlackSet() : root(nullptr), size_count(0) {
        // Initialize the sentinel node (NIL)
        NIL = new RBTNode(0, BLACK); 
        NIL->parent = NIL; 
        root = NIL;
    }

    ~RedBlackSet() {
        clear();
        delete NIL;
    }

    // --- Public Set Interface (STL-like Methods) ---

    using iterator = RBT_Iterator;

    /**
     * @brief Returns an iterator to the first (minimum) element.
     */
    iterator begin() const {
        if (root == NIL) return iterator(NIL, NIL);
        return iterator(minimum(root), NIL);
    }

    /**
     * @brief Returns an iterator past the last element (the sentinel NIL).
     */
    iterator end() const {
        return iterator(NIL, NIL);
    }

    size_t size() const {
        return size_count;
    }
    
    bool empty() const {
        return root == NIL;
    }

    /**
     * @brief Clears all elements from the set.
     */
    void clear() {
        destroyRecursive(root);
        root = NIL;
        size_count = 0;
    }

    /**
     * @brief Search for element with specific key. (O(log N))
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
     * @brief Inserts a new element. (O(log N))
     * @return std::pair<iterator, bool>: iterator points to the element, bool is true if inserted.
     */
    pair<iterator, bool> insert(int key) {
        RBTNode* existing = find(key).current;
        if (existing != NIL) {
            return {iterator(existing, NIL), false}; // Key already exists (Uniqueness enforced)
        }
        
        // 1. Standard BST Insertion setup
        RBTNode* newNode = new RBTNode(key, RED);
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
        if (y == NIL) { this->root = newNode; } 
        else if (newNode->key < y->key) { y->left = newNode; } 
        else { y->right = newNode; } 
        
        newNode->left = NIL;
        newNode->right = NIL;
        size_count++;
        
        // 2. RBT Balancing
        fixInsert(newNode);

        return {iterator(newNode, NIL), true};
    }

    /**
     * @brief Erases the element with the given key. (O(log N))
     * @return size_t: 1 if deleted, 0 otherwise.
     */
    size_t erase(int key) {
        iterator it = find(key);
        if (it == end()) {
            return 0; // Not found
        }
        
        RBTNode* node_to_delete = it.current;
        deleteNode(node_to_delete);
        return 1; // Found and deleted
    }

};

// --- Example Usage ---

int main() {
    cout << "Initializing RedBlackSet (RBT-based set)..." << endl;
    RedBlackSet my_set;
    
    // 1. Insertion Test
    cout << "\n--- Insertion Test (0-10, plus duplicate 5) ---" << endl;
    for (int i = 0; i < 11; ++i) {
        my_set.insert(i * 10);
    }
    auto result_dup = my_set.insert(50);
    cout << "Size: " << my_set.size() << endl;
    cout << "Inserted 50 again? " << (result_dup.second ? "Yes" : "No") << endl;

    // 2. Traversal Test (Should be sorted)
    cout << "\n--- Traversal Test (Sorted Order) ---" << endl;
    cout << "Elements: ";
    for (const int& key : my_set) {
        cout << key << " ";
    }
    cout << endl;

    // 3. Find Test
    cout << "\n--- Find Test ---" << endl;
    int search1 = 60;
    int search2 = 1000;
    cout << "Finding " << search1 << ": " << (my_set.find(search1) != my_set.end() ? "Found" : "Not Found") << endl;
    cout << "Finding " << search2 << ": " << (my_set.find(search2) != my_set.end() ? "Found" : "Not Found") << endl;

    // 4. Deletion Test
    cout << "\n--- Deletion Test ---" << endl;
    cout << "Erasing 30. Result: " << my_set.erase(30) << endl;
    cout << "Erasing 1000. Result: " << my_set.erase(1000) << endl; 
    
    // 5. Final State
    cout << "\n--- Final State ---" << endl;
    cout << "New Size: " << my_set.size() << endl;
    cout << "Elements: ";
    for (auto it = my_set.begin(); it != my_set.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
