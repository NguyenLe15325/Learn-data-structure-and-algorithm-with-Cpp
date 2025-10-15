#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// --- 1. Hash Node Structure (Separate Chaining) ---

/**
 * @brief Node stored in the hash table. Stores only the key and a pointer
 * to the next node in case of a collision.
 */
struct HashNode {
    int key;
    HashNode* next;

    HashNode(int k) : key(k), next(nullptr) {}
};

// --- 2. UnorderedSet Class Definition (Hash Table) ---

/**
 * @brief Custom implementation of an Unordered Set using a Hash Table with Separate Chaining.
 * Guarantees O(1) average time complexity.
 */
class UnorderedSet {
private:
    vector<HashNode*> table;
    int capacity;
    size_t size_count;

    // Simple hash function using the modulo operator.
    size_t hashFunction(int key) const {
        return abs(key) % capacity;
    }

    // Helper function to destroy all nodes in a given linked list chain
    void deleteChain(HashNode* head) {
        HashNode* current = head;
        while (current) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }

public:
    UnorderedSet(int initialCapacity = 10) 
        : capacity(initialCapacity), size_count(0) {
        // Initialize the bucket array with null pointers
        table.resize(capacity, nullptr);
    }

    ~UnorderedSet() {
        for (HashNode* head : table) {
            deleteChain(head);
        }
    }
    
    size_t size() const { return size_count; }

    /**
     * @brief Inserts a key into the set. (O(1) average)
     * Enforces uniqueness by checking the chain before insertion.
     */
    bool insert(int key) {
        size_t index = hashFunction(key);
        
        // 1. Check for uniqueness (traverses the linked list at the bucket)
        HashNode* current = table[index];
        while (current) {
            if (current->key == key) {
                return false; // Key already exists
            }
            current = current->next;
        }

        // 2. Insert new node at the head of the linked list (O(1) operation)
        HashNode* newNode = new HashNode(key);
        newNode->next = table[index];
        table[index] = newNode;
        size_count++;
        
        // Note: Real implementations rehash and resize the table when load factor is too high.
        return true;
    }

    /**
     * @brief Finds a key in the set. (O(1) average)
     * @return true if the key is found, false otherwise.
     */
    bool find(int key) const {
        size_t index = hashFunction(key);
        HashNode* current = table[index];
        
        while (current) {
            if (current->key == key) {
                return true; // Key found
            }
            current = current->next;
        }
        return false;
    }

    /**
     * @brief Erases a key from the set. (O(1) average)
     * @return true if the key was found and erased, false otherwise.
     */
    bool erase(int key) {
        size_t index = hashFunction(key);
        HashNode* current = table[index];
        HashNode* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next; // Bypass the node
                } else {
                    table[index] = current->next; // Node is the head of the chain
                }
                delete current;
                size_count--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    /**
     * @brief Prints the contents of the hash table bucket by bucket.
     * This visually demonstrates the UNORDERED nature.
     */
    void printBuckets() const {
        cout << "\n--- Hash Table Bucket View (Unordered Output) ---" << endl;
        cout << "Capacity: " << capacity << ", Total Elements: " << size_count << endl;
        
        for (int i = 0; i < capacity; ++i) {
            cout << "Bucket [" << i << "]: ";
            HashNode* current = table[i];
            
            if (!current) {
                cout << "EMPTY" << endl;
                continue;
            }
            
            // Print the linked list for this bucket
            while (current) {
                cout << current->key << (current->next ? " -> " : "");
                current = current->next;
            }
            cout << endl;
        }
        cout << "------------------------------------------------" << endl;
    }
};

// --- Example Usage ---

int main() {
    // Initial capacity set to 7 to ensure some collisions occur for demonstration
    UnorderedSet my_set(7); 
    
    cout << "--- UnorderedSet Operations Demonstration ---" << endl;

    // 1. Insertion (O(1) average)
    my_set.insert(15); // Hash: 15 % 7 = 1
    my_set.insert(23); // Hash: 23 % 7 = 2
    my_set.insert(8);  // Hash: 8 % 7 = 1 (Collision at bucket 1)
    my_set.insert(4);  // Hash: 4 % 7 = 4
    my_set.insert(30); // Hash: 30 % 7 = 2 (Collision at bucket 2)
    my_set.insert(10); // Hash: 10 % 7 = 3

    // Attempt to insert duplicate (should fail)
    bool success = my_set.insert(15);
    cout << "Attempted to insert 15 again. Success: " << (success ? "Yes" : "No") << endl;
    cout << "Total elements: " << my_set.size() << endl;

    // 2. View the Buckets (Demonstrates Unordered nature)
    // The keys are grouped by their hash value, not their numerical value.
    my_set.printBuckets();

    // 3. Find Operation (O(1) average)
    int key_to_find = 30;
    cout << "\n--- Find Operation ---" << endl;
    cout << "Is " << key_to_find << " present? " << (my_set.find(key_to_find) ? "Yes" : "No") << endl;
    cout << "Is 99 present? " << (my_set.find(99) ? "Yes" : "No") << endl;

    // 4. Erase Operation (O(1) average)
    int key_to_erase = 8; // This key is in a chain (collision)
    cout << "\n--- Erase Operation ---" << endl;
    cout << "Erasing " << key_to_erase << ". Success: " << (my_set.erase(key_to_erase) ? "Yes" : "No") << endl;
    
    my_set.printBuckets();
    
    return 0;
}
