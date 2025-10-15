#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Forward declaration
class BPlusTree;

// --- B+ Tree Node Structure ---
class BTreeNode {
private:
    int t;              // Minimum degree (t=3 means Max keys = 5, Min keys = 2)
    bool isLeaf;        // True if the node is a leaf
    vector<int> keys;   // Vector to store keys (The data)
    vector<BTreeNode*> children; // Vector to store child pointers (internal nodes only)
    BTreeNode* next;    // Pointer to the next leaf node (leaf nodes only)

public:
    BTreeNode(int t, bool isLeaf);
    
    // Public getter to safely expose the first key (used for printing)
    int getFirstKey() const { 
        return keys.empty() ? -1 : keys.front(); 
    }
    
    // Public getter to safely expose the entire key vector (used for printing and searching in main)
    const vector<int>& getKeys() const { 
        return keys; 
    }

    void printTree(int depth);
    BTreeNode* search(int k); 
    BTreeNode* findLeftmostLeaf(); 

    // Core B+ Tree Operations
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);

    friend class BPlusTree;
};

// Constructor
BTreeNode::BTreeNode(int t, bool isLeaf) : t(t), isLeaf(isLeaf), next(nullptr) {}

// Print the tree structure with indentation
void BTreeNode::printTree(int depth) {
    // Use 4 spaces per level for clear indentation
    cout << string(depth * 4, ' '); 

    // 1. Build the key display with separators
    cout << "Level " << depth << ": [ ";
    for (size_t i = 0; i < keys.size(); i++) {
        cout << keys[i] << (i < keys.size() - 1 ? " | " : ""); // Use | as a visual separator
    }
    
    // Display node type
    cout << " ]" << (isLeaf ? " (LEAF: Data)" : " (INTERNAL: Index)");
    
    // Display next pointer if it's a leaf. We use the public getter here.
    if (isLeaf && next != nullptr) {
        cout << " -> Next Leaf Starts with: " << next->getFirstKey();
    }

    cout << endl;

    // 2. Recursively print children
    if (!isLeaf) {
        for (BTreeNode* child : children) {
            child->printTree(depth + 1);
        }
    }
}

// Search utility: B+ Tree search always ends at a leaf node
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    // Find the first key greater than or equal to k
    while (i < keys.size() && k >= keys[i]) {
        i++;
    }

    if (isLeaf) {
        // Return the leaf node where the key *should* reside
        return this;
    }

    // Go to the appropriate child 
    return children[i]->search(k);
}

// Utility to find the leftmost leaf
BTreeNode* BTreeNode::findLeftmostLeaf() {
    if (isLeaf) {
        return this;
    }
    return children.front()->findLeftmostLeaf();
}

// Split Child Function (B+ Tree Logic)
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    int t = y->t;
    int promotedKey;

    if (y->isLeaf) {
        // --- LEAF SPLIT: Key is COPIED UP (Duplicate in index and leaf) ---
        
        // z gets keys from index t-1 to 2t-2 (t keys, including the median key)
        for (int j = 0; j < t; j++) { 
            z->keys.push_back(y->keys[j + t - 1]);
        }

        // y keeps keys from 0 to t-2 (t-1 keys)
        y->keys.erase(y->keys.begin() + t - 1, y->keys.end()); 
        
        // Link leaves (y -> z)
        z->next = y->next;
        y->next = z;
        
        // The key promoted to the parent is the smallest key of the new node z
        promotedKey = z->keys[0]; 

    } else {
        // --- INTERNAL SPLIT: Key is MOVED UP (Standard B-Tree Split) ---

        // z gets keys from index t to 2t-2 (t-1 keys)
        for (int j = 0; j < t - 1; j++) {
            z->keys.push_back(y->keys[j + t]);
        }
        
        // z gets children from index t to 2t-1 (t children)
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
        
        // The key promoted to the parent is the median key
        promotedKey = y->keys[t - 1]; 
        
        // Remove keys and children from y (including the promoted key)
        y->keys.erase(y->keys.begin() + t - 1, y->keys.end());
        y->children.erase(y->children.begin() + t, y->children.end());
    }
    
    // Insert new child z into the parent (this)
    children.insert(children.begin() + i + 1, z);

    // Insert promoted key into parent's keys
    keys.insert(keys.begin() + i, promotedKey);
}

// Function to insert a new key in a non-full node.
void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1; 

    // 1. If this is a leaf node, insert the key directly
    if (isLeaf) {
        keys.push_back(0); // Make space
        
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

        // Check if the designated child is full (2*t - 1 keys)
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);

            // Determine which of the two resulting children to insert into
            if (k > keys[i]) {
                i++;
            }
        }
        
        // Recursively call insertNonFull on the chosen child
        children[i]->insertNonFull(k);
    }
}


// --- B+ Tree Class ---
class BPlusTree {
private:
    BTreeNode* root; 
    int t;           

public:
    BPlusTree(int t);

    void printStructure() {
        if (root != nullptr) {
            cout << "\n--- B+ Tree Structure (Degree t=" << t << ", Max Keys=" << 2 * t - 1 << ") ---" << endl;
            root->printTree(0);
            cout << "---------------------------------------------------" << endl;
        } else {
            cout << "The tree is empty." << endl;
        }
    }
    
    void printLeafChain();

    // Public wrapper for insertion
    void insert(int k);
    
    // Public wrapper for search
    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }
};

// Constructor
BPlusTree::BPlusTree(int t) : t(t), root(nullptr) {}

// Prints the linked list of leaf nodes
void BPlusTree::printLeafChain() {
    if (root == nullptr) {
        return;
    }
    
    BTreeNode* current = root->findLeftmostLeaf();
    
    cout << "\n--- Leaf Node Chain (Range Query View) ---" << endl;
    while (current != nullptr) {
        cout << "[";
        // Use the public getter to access keys for printing
        const auto& currentKeys = current->getKeys();
        for (size_t i = 0; i < currentKeys.size(); i++) {
            cout << currentKeys[i] << (i < currentKeys.size() - 1 ? " | " : "");
        }
        cout << "]";
        
        if (current->next != nullptr) {
            cout << " --> ";
        }
        current = current->next;
    }
    cout << "\n------------------------------------------" << endl;
}

// Main insertion function
void BPlusTree::insert(int k) {
    if (root == nullptr) {
        // Case 1: Tree is empty. Create a new root which must be a leaf.
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        // Case 2: Root is full. Tree height increases.
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);

            int i = 0;
            if (k > s->keys[0]) {
                i++;
            }
            s->children[i]->insertNonFull(k);
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
    // Degree t=3 (Min keys: 2, Max keys: 5)
    BPlusTree tree(3);

    // Insert keys that will force several splits and create multiple levels
    vector<int> keys_to_insert = {10, 20, 30, 40, 50, 60, 70, 80, 90, 5, 25, 45, 15, 35, 55, 65, 75, 85, 95, 2, 7, 12, 17};
    
    cout << "--- B+ Tree Insertion Log (t=3) ---" << endl;
    for (int k : keys_to_insert) {
        cout << "Inserting: " << k << endl;
        tree.insert(k);
    }
    cout << "Insertion complete." << endl;

    // Display the final structure
    tree.printStructure();
    
    // Display the linked list of leaf nodes
    tree.printLeafChain();
    
    cout << "\n--- Testing Search ---" << endl;
    int search_keys[] = {40, 12, 15, 99};
    for (int k : search_keys) {
        BTreeNode* leaf = tree.search(k);
        if (leaf != nullptr) {
            // FIX: Access the first key using the public getter method
            cout << "Search for " << k << ": Found in leaf starting with " << leaf->getFirstKey() << endl;
        } else {
            cout << "Search for " << k << ": Not Found (Error in structure)" << endl;
        }
    }

    return 0;
}
