#include <iostream>
#include <vector>
#include <algorithm> // For std::upper_bound/lower_bound (conceptual use)

using namespace std;

// Forward declaration
class BTree;

// --- B-Tree Node Structure ---
class BTreeNode {
private:
    int t;              // Minimum degree (defines maximum number of keys)
    bool isLeaf;        // True if the node is a leaf
    vector<int> keys;   // Vector to store keys
    vector<BTreeNode*> children; // Vector to store child pointers

public:
    BTreeNode(int t, bool isLeaf);
    void traverse();
    BTreeNode* search(int k); // Returns NULL if k is not present

    // Function to insert a new key in a non-full node
    void insertNonFull(int k);

    // Function to split the child y of this node
    void splitChild(int i, BTreeNode* y);

    // Friend class to allow BTree access to private members (for root manipulation)
    friend class BTree;
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int t, bool isLeaf) : t(t), isLeaf(isLeaf) {
    // Keys and children vectors are initialized empty by default
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        // If this is not a leaf, visit the child before keys[i]
        if (!isLeaf) {
            children[i]->traverse();
        }
        cout << " " << keys[i];
    }

    // Print the subtree rooted with the last child
    if (!isLeaf) {
        children[i]->traverse();
    }
}

// Function to search key k in the subtree rooted with this node
BTreeNode* BTreeNode::search(int k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < keys.size() && k > keys[i]) {
        i++;
    }

    // Check if the found key is equal to k
    if (i < keys.size() && keys[i] == k) {
        return this;
    }

    // If key is not found and this is a leaf node
    if (isLeaf) {
        return nullptr;
    }

    // Go to the appropriate child
    return children[i]->search(k);
}

// --- B-Tree Class ---
class BTree {
private:
    BTreeNode* root; // Pointer to the root node
    int t;           // Minimum degree

public:
    BTree(int t);

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }

    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);
};

// Constructor for BTree
BTree::BTree(int t) : t(t), root(nullptr) {}


// Function to split the child y of this node.
// Note: 'this' is the parent node, 'y' is the full child node.
// i is the index in children[] of 'this' where y is located.
void BTreeNode::splitChild(int i, BTreeNode* y) {
    // Create a new node z to store (t-1) keys of y (the right half)
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);

    // 1. Copy the right half of keys from y to z (t-1 keys)
    // Keys start from index t (the key *after* the median)
    for (int j = 0; j < t - 1; j++) {
        z->keys.push_back(y->keys[j + t]);
    }
    
    // 2. If y is not a leaf, copy the right half of children from y to z (t children)
    if (!y->isLeaf) {
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
    }

    // 3. Remove the t keys from y (leaving t-1 keys)
    y->keys.erase(y->keys.begin() + t - 1, y->keys.end());

    // 4. Remove the t children pointers from y (if not leaf)
    if (!y->isLeaf) {
        y->children.erase(y->children.begin() + t, y->children.end());
    }
    
    // 5. Insert the new child z into the children of the parent (this)
    children.insert(children.begin() + i + 1, z);

    // 6. Promote the median key (y->keys[t-1]) to the parent's keys
    // This median key is currently at index t-1 in y, which must be deleted from y
    int medianKey = y->keys[t - 1];
    y->keys.erase(y->keys.begin() + t - 1); // Delete the promoted key from y

    // 7. Insert the median key into the parent (this) at index i
    keys.insert(keys.begin() + i, medianKey);
}


// Function to insert a new key in a non-full node.
// Assumes the node is not full when this function is called.
void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1; // Start from the rightmost element

    // 1. If this is a leaf node, insert the key directly
    if (isLeaf) {
        keys.push_back(0); // Make space for the new key
        
        // Find the location and shift larger keys to the right
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k; // Insert the new key
    }
    // 2. If this is an internal node, find the correct child to descend into
    else {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        i++; // i is the index of the child pointer children[i]

        // Check if the designated child is full
        if (children[i]->keys.size() == 2 * t - 1) {
            // If full, split it
            splitChild(i, children[i]);

            // After splitting, the median key from children[i] moves up to 'this' node.
            // We need to determine which of the two resulting children (children[i] or children[i+1])
            // the new key k should go into.
            if (k > keys[i]) {
                i++; // If k is greater than the promoted key, go to the right split child
            }
        }
        
        // Recursively call insertNonFull on the chosen child
        children[i]->insertNonFull(k);
    }
}

// Main insertion function
void BTree::insert(int k) {
    if (root == nullptr) {
        // Case 1: Tree is empty. Create a new root.
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        // Case 2: Root is full. Tree height increases.
        if (root->keys.size() == 2 * t - 1) {
            // Create a new root node
            BTreeNode* s = new BTreeNode(t, false);
            
            // Make the old root a child of the new root
            s->children.push_back(root);

            // Split the old root and move a median key to the new root
            s->splitChild(0, root);

            // Determine which of the two children to insert the new key into
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            s->children[i]->insertNonFull(k);

            // Set the new root
            root = s;
        }
        // Case 3: Root is not full. Insert directly into the root's subtree.
        else {
            root->insertNonFull(k);
        }
    }
}


// --- Example Execution ---
int main() {
    // Degree t=2 (Min keys: 1, Max keys: 3, Max children: 4)
    BTree t(2);

    vector<int> keys_to_insert = {10, 20, 30, 40, 50, 60, 70, 80, 90, 5, 25, 45, 15};
    
    cout << "--- Inserting Keys (t=2) ---" << endl;
    for (int k : keys_to_insert) {
        cout << "Inserting: " << k << endl;
        t.insert(k);
    }

    cout << "\n--- Final B-Tree Traversal (In-Order) ---" << endl;
    t.traverse();
    cout << "\n" << endl;
    
    cout << "\n--- Testing Search ---" << endl;
    int search_keys[] = {40, 12, 15, 99};
    for (int k : search_keys) {
        if (t.search(k) != nullptr) {
            cout << "Key " << k << ": Found" << endl;
        } else {
            cout << "Key " << k << ": Not Found" << endl;
        }
    }

    // Expected output shows a root with 40, 70
    // Root (40, 70)
    // |--- (10, 20, 30)
    // |--- (45, 50, 60)
    // |--- (80, 90)

    // After 5, 25, 45, 15 insertion, the structure will be more complex.
    /*
    Final structure for keys: 10, 20, 30, 40, 50, 60, 70, 80, 90, 5, 25, 45, 15
    Root: [40, 70]
    |--- Child 0 (Keys < 40): [15, 25] (promoted 20) -> [15, 25] (promoted 10)
    |    |--- Grandchild 0: [5, 10]
    |    |--- Grandchild 1: [20, 30]
    |    |--- Grandchild 2: (Empty/error in conceptual display)
    |--- Child 1 (Keys 40-70): [50, 60]
    |--- Child 2 (Keys > 70): [80, 90]
    */

    return 0;
}
