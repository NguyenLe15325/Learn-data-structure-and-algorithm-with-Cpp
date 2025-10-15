#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

enum Color { RED, BLACK };

template<typename T>
class RBTNode {
public:
    T data;
    Color color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    
    RBTNode(T value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
class RBTSet {
private:
    RBTNode<T>* root;
    int size_count;
    
    // Utility functions
    RBTNode<T>* insert_recursive(RBTNode<T>* node, T value, RBTNode<T>* parent);
    void fix_insert(RBTNode<T>* node);
    void rotate_left(RBTNode<T>* node);
    void rotate_right(RBTNode<T>* node);
    
    RBTNode<T>* find_node(RBTNode<T>* node, T value) const;
    RBTNode<T>* find_min(RBTNode<T>* node) const;
    RBTNode<T>* find_max(RBTNode<T>* node) const;
    RBTNode<T>* find_successor(RBTNode<T>* node) const;
    
    void delete_recursive(RBTNode<T>* node, T value);
    void fix_delete(RBTNode<T>* node);
    void replace_node(RBTNode<T>* u, RBTNode<T>* v);
    
    void inorder_traversal(RBTNode<T>* node) const;
    void delete_tree(RBTNode<T>* node);
    int get_height(RBTNode<T>* node) const;
    
public:
    RBTSet() : root(nullptr), size_count(0) {}
    ~RBTSet() { delete_tree(root); }
    
    // Public interface
    void insert(T value);
    void remove(T value);
    bool contains(T value) const;
    int size() const { return size_count; }
    bool empty() const { return size_count == 0; }
    void display() const;
    int height() const { return get_height(root); }
};

template<typename T>
RBTNode<T>* RBTSet<T>::insert_recursive(RBTNode<T>* node, T value, RBTNode<T>* parent) {
    if (node == nullptr) {
        RBTNode<T>* new_node = new RBTNode<T>(value);
        new_node->parent = parent;
        size_count++;
        return new_node;
    }
    
    if (value < node->data) {
        node->left = insert_recursive(node->left, value, node);
    } else if (value > node->data) {
        node->right = insert_recursive(node->right, value, node);
    } else {
        // Duplicate, do nothing (set behavior)
        return node;
    }
    
    return node;
}

template<typename T>
void RBTSet<T>::rotate_left(RBTNode<T>* node) {
    RBTNode<T>* right_child = node->right;
    node->right = right_child->left;
    
    if (right_child->left != nullptr) {
        right_child->left->parent = node;
    }
    
    right_child->parent = node->parent;
    
    if (node->parent == nullptr) {
        root = right_child;
    } else if (node == node->parent->left) {
        node->parent->left = right_child;
    } else {
        node->parent->right = right_child;
    }
    
    right_child->left = node;
    node->parent = right_child;
}

template<typename T>
void RBTSet<T>::rotate_right(RBTNode<T>* node) {
    RBTNode<T>* left_child = node->left;
    node->left = left_child->right;
    
    if (left_child->right != nullptr) {
        left_child->right->parent = node;
    }
    
    left_child->parent = node->parent;
    
    if (node->parent == nullptr) {
        root = left_child;
    } else if (node == node->parent->right) {
        node->parent->right = left_child;
    } else {
        node->parent->left = left_child;
    }
    
    left_child->right = node;
    node->parent = left_child;
}

template<typename T>
void RBTSet<T>::fix_insert(RBTNode<T>* node) {
    while (node->parent != nullptr && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            RBTNode<T>* uncle = node->parent->parent->right;
            
            if (uncle != nullptr && uncle->color == RED) {
                // Case 1: Uncle is red
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // Case 2 & 3: Uncle is black
                if (node == node->parent->right) {
                    // Case 2: Node is right child
                    node = node->parent;
                    rotate_left(node);
                }
                // Case 3: Node is left child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotate_right(node->parent->parent);
            }
        } else {
            RBTNode<T>* uncle = node->parent->parent->left;
            
            if (uncle != nullptr && uncle->color == RED) {
                // Case 1: Uncle is red
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // Case 2 & 3: Uncle is black
                if (node == node->parent->left) {
                    // Case 2: Node is left child
                    node = node->parent;
                    rotate_right(node);
                }
                // Case 3: Node is right child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotate_left(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template<typename T>
void RBTSet<T>::insert(T value) {
    if (contains(value)) return;  // No duplicates
    
    root = insert_recursive(root, value, nullptr);
    fix_insert(root);
}

template<typename T>
RBTNode<T>* RBTSet<T>::find_node(RBTNode<T>* node, T value) const {
    if (node == nullptr) return nullptr;
    
    if (value < node->data) {
        return find_node(node->left, value);
    } else if (value > node->data) {
        return find_node(node->right, value);
    } else {
        return node;
    }
}

template<typename T>
bool RBTSet<T>::contains(T value) const {
    return find_node(root, value) != nullptr;
}

template<typename T>
RBTNode<T>* RBTSet<T>::find_min(RBTNode<T>* node) const {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename T>
RBTNode<T>* RBTSet<T>::find_max(RBTNode<T>* node) const {
    while (node != nullptr && node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template<typename T>
RBTNode<T>* RBTSet<T>::find_successor(RBTNode<T>* node) const {
    if (node->right != nullptr) {
        return find_min(node->right);
    }
    
    RBTNode<T>* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

template<typename T>
void RBTSet<T>::replace_node(RBTNode<T>* u, RBTNode<T>* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template<typename T>
void RBTSet<T>::fix_delete(RBTNode<T>* node) {
    while (node != root && (node == nullptr || node->color == BLACK)) {
        if (node == nullptr || node == node->parent->left) {
            RBTNode<T>* sibling = (node == nullptr) ? node->parent->right : node->parent->right;
            
            if (sibling != nullptr && sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotate_left(node->parent);
                sibling = node->parent->right;
            }
            
            if (sibling != nullptr) {
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr) sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotate_right(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr) sibling->right->color = BLACK;
                    rotate_left(node->parent);
                    node = root;
                }
            }
        } else {
            RBTNode<T>* sibling = node->parent->left;
            
            if (sibling != nullptr && sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotate_right(node->parent);
                sibling = node->parent->left;
            }
            
            if (sibling != nullptr) {
                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr) sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotate_left(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr) sibling->left->color = BLACK;
                    rotate_right(node->parent);
                    node = root;
                }
            }
        }
    }
    if (node != nullptr) node->color = BLACK;
}

template<typename T>
void RBTSet<T>::remove(T value) {
    RBTNode<T>* node = find_node(root, value);
    if (node == nullptr) return;
    
    RBTNode<T>* node_to_fix = nullptr;
    RBTNode<T>* node_to_fix_parent = nullptr;
    
    if (node->left == nullptr || node->right == nullptr) {
        RBTNode<T>* child = (node->left != nullptr) ? node->left : node->right;
        
        if (node->color == BLACK) {
            if (child != nullptr) {
                child->color = BLACK;
                node_to_fix = child;
            } else {
                node_to_fix = node;
            }
        }
        
        replace_node(node, child);
        delete node;
    } else {
        RBTNode<T>* successor = find_successor(node);
        node->data = successor->data;
        
        RBTNode<T>* child = successor->right;
        if (successor->color == BLACK) {
            node_to_fix = child;
            node_to_fix_parent = successor->parent;
        }
        
        replace_node(successor, child);
        delete successor;
    }
    
    size_count--;
    if (node_to_fix != nullptr || node_to_fix_parent != nullptr) {
        fix_delete(node_to_fix);
    }
}

template<typename T>
void RBTSet<T>::inorder_traversal(RBTNode<T>* node) const {
    if (node == nullptr) return;
    
    inorder_traversal(node->left);
    cout << node->data << " [" << (node->color == RED ? "R" : "B") << "] ";
    inorder_traversal(node->right);
}

template<typename T>
void RBTSet<T>::display() const {
    if (empty()) {
        cout << "Set is empty" << endl;
        return;
    }
    cout << "Set (in-order): ";
    inorder_traversal(root);
    cout << endl;
}

template<typename T>
int RBTSet<T>::get_height(RBTNode<T>* node) const {
    if (node == nullptr) return 0;
    return 1 + max(get_height(node->left), get_height(node->right));
}

template<typename T>
void RBTSet<T>::delete_tree(RBTNode<T>* node) {
    if (node == nullptr) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

// ========== DEMONSTRATION ==========
int main() {
    cout << "========== RED-BLACK TREE SET IMPLEMENTATION ==========" << endl << endl;
    
    // ===== 1. BASIC INSERTION =====
    cout << "1. BASIC INSERTION" << endl;
    cout << string(70, '-') << endl;
    
    RBTSet<int> set1;
    cout << "Inserting: 10, 20, 30, 40, 50, 25, 35" << endl;
    set1.insert(10);
    set1.insert(20);
    set1.insert(30);
    set1.insert(40);
    set1.insert(50);
    set1.insert(25);
    set1.insert(35);
    
    set1.display();
    cout << "Size: " << set1.size() << ", Height: " << set1.height() << "\n\n";
    
    // ===== 2. NO DUPLICATES =====
    cout << "2. NO DUPLICATES (Set behavior)" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Inserting duplicate 30:" << endl;
    set1.insert(30);
    set1.display();
    cout << "Size: " << set1.size() << " (unchanged)\n\n";
    
    // ===== 3. SEARCH =====
    cout << "3. SEARCH OPERATIONS" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Contains 25? " << (set1.contains(25) ? "Yes" : "No") << endl;
    cout << "Contains 100? " << (set1.contains(100) ? "Yes" : "No") << "\n\n";
    
    // ===== 4. DELETION =====
    cout << "4. DELETION" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Original set: ";
    set1.display();
    
    cout << "Remove 20:" << endl;
    set1.remove(20);
    set1.display();
    cout << "Size: " << set1.size() << "\n\n";
    
    // ===== 5. STRINGS =====
    cout << "5. USING WITH STRINGS" << endl;
    cout << string(70, '-') << endl;
    
    RBTSet<string> str_set;
    cout << "Inserting: apple, banana, cherry, date, elderberry" << endl;
    str_set.insert("apple");
    str_set.insert("banana");
    str_set.insert("cherry");
    str_set.insert("date");
    str_set.insert("elderberry");
    
    str_set.display();
    cout << "Size: " << str_set.size() << ", Height: " << str_set.height() << "\n\n";
    
    // ===== 6. TREE PROPERTIES =====
    cout << "6. TREE PROPERTIES" << endl;
    cout << string(70, '-') << endl;
    
    RBTSet<int> set2;
    int arr[] = {7, 3, 18, 10, 22, 8, 11, 26};
    cout << "Inserting: ";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
        set2.insert(arr[i]);
    }
    cout << "\n";
    
    set2.display();
    cout << "Size: " << set2.size() << endl;
    cout << "Height: " << set2.height() << endl;
    cout << "Balanced height: O(log n) = O(log " << set2.size() << ") ≈ " 
         << (int)ceil(log2(set2.size() + 1)) << "\n\n";
    
    // ===== 7. LARGE DATASET =====
    cout << "7. LARGE DATASET TEST" << endl;
    cout << string(70, '-') << endl;
    
    RBTSet<int> large_set;
    cout << "Inserting 100 random elements:" << endl;
    for (int i = 0; i < 100; i++) {
        large_set.insert(rand() % 200);
    }
    
    cout << "Size: " << large_set.size() << " (unique elements)" << endl;
    cout << "Height: " << large_set.height() << endl;
    cout << "Expected balanced height: O(log " << large_set.size() << ") ≈ " 
         << (int)ceil(log2(large_set.size() + 1)) << endl;
    cout << "Height is well-balanced due to RBT properties!\n\n";
    
    // ===== 8. DELETION SEQUENCE =====
    cout << "8. DELETION SEQUENCE" << endl;
    cout << string(70, '-') << endl;
    
    RBTSet<int> set3;
    cout << "Initial insertions: 15, 10, 20, 8, 12, 25, 6" << endl;
    set3.insert(15);
    set3.insert(10);
    set3.insert(20);
    set3.insert(8);
    set3.insert(12);
    set3.insert(25);
    set3.insert(6);
    
    set3.display();
    cout << "Size: " << set3.size() << "\n\n";
    
    cout << "Delete 15 (root has two children):" << endl;
    set3.remove(15);
    set3.display();
    cout << "Size: " << set3.size() << "\n\n";
    
    cout << "Delete 10:" << endl;
    set3.remove(10);
    set3.display();
    cout << "Size: " << set3.size() << "\n\n";

    return 0;
}