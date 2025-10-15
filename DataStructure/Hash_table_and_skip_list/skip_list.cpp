#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

// --- Configuration Constants ---
// Maximum number of levels (height) the skip list can reach.
const int MAX_LEVEL = 5; 
// Probability 'P' used for random level generation (0.5 means 50% chance to go up a level).
const double P = 0.5;

// Using template for generic Key and Value types
template <typename K, typename V>
struct SkipListNode {
    K key;
    V value;
    // Array of forward pointers. Size MAX_LEVEL + 1 (for 0-based indexing).
    // forward[i] points to the next node at level 'i'.
    SkipListNode<K, V>* forward[MAX_LEVEL + 1]; 

    SkipListNode(const K& k, const V& v, int level) : key(k), value(v) {
        for (int i = 0; i <= level; ++i) {
            forward[i] = nullptr;
        }
    }
    // Destructor (important for cleanup, though this simple implementation doesn't call it on erase)
    ~SkipListNode() = default; 
};

template <typename K, typename V>
class SkipList {
private:
    // The current maximum level reached by any node in the list
    int current_level; 
    // The header node, which doesn't store data but points to the start of every level
    SkipListNode<K, V>* header; 

    /**
     * @brief Generates a random level for a new node.
     * Starts at level 1 and "flips a coin" (based on P) to decide whether to increment the level.
     * The level is capped by MAX_LEVEL.
     * @return int The randomly determined level for the new node.
     */
    int randomLevel() {
        int level = 0;
        // rand() % 100 ensures a value between 0 and 99. P * 100 is the threshold (e.g., 50).
        while (rand() % 100 < (P * 100) && level < MAX_LEVEL) {
            level++;
        }
        return level;
    }

public:
    SkipList() : current_level(0) {
        // Initialize the header node with a dummy key/value and max level.
        // The header's forward pointers will point to nullptr initially.
        header = new SkipListNode<K, V>(K(), V(), MAX_LEVEL); 
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0))); 
    }

    ~SkipList() {
        // Simple cleanup: delete all nodes starting from level 0, then delete the header.
        SkipListNode<K, V>* current = header->forward[0];
        while (current) {
            SkipListNode<K, V>* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }

    /**
     * @brief Searches for a key and returns the associated value.
     * @param key The key to search for.
     * @return V The value associated with the key.
     */
    V search(const K& key) {
        SkipListNode<K, V>* current = header;
        
        // Start from the highest current level and move down
        for (int i = current_level; i >= 0; i--) {
            // Keep moving forward on the current level as long as the next node exists
            // AND its key is less than the search key.
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        // Drop to the bottom level (0) and check the next node
        current = current->forward[0];

        // If the node exists and the key matches, we found it!
        if (current && current->key == key) {
            return current->value;
        }
        
        // Key not found
        throw std::runtime_error("Key not found in the Skip List.");
    }

    /**
     * @brief Inserts a new key-value pair into the skip list.
     */
    void insert(const K& key, const V& value) {
        // 'update' array stores the rightmost node at each level that precedes the insertion point.
        SkipListNode<K, V>* update[MAX_LEVEL + 1];
        SkipListNode<K, V>* current = header;

        // 1. Find the Insertion Path (Traverse from top down)
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            // Store the node we stopped at for level 'i'
            update[i] = current;
        }

        // 2. Check if the key already exists (must be at level 0)
        current = current->forward[0];
        if (current && current->key == key) {
            std::cout << "Key " << key << " already exists. Updating value." << std::endl;
            current->value = value;
            return;
        }

        // 3. Determine the new node's level
        int new_level = randomLevel();

        // 4. If the new node's level is higher than the current list level, 
        // update the header's pointers for the new levels.
        if (new_level > current_level) {
            for (int i = current_level + 1; i <= new_level; i++) {
                update[i] = header; // New levels start at the header
            }
            current_level = new_level;
        }

        // 5. Create the new node
        SkipListNode<K, V>* new_node = new SkipListNode<K, V>(key, value, new_level);

        // 6. Link the new node into the list at all required levels
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
        std::cout << "Inserted Key " << key << " with Level: " << new_level << std::endl;
    }

    /**
     * @brief Removes a key from the skip list.
     */
    void remove(const K& key) {
        SkipListNode<K, V>* update[MAX_LEVEL + 1];
        SkipListNode<K, V>* current = header;

        // 1. Find the node and record all preceding pointers
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        // 2. Check if the key exists
        if (current && current->key == key) {
            // 3. Unlink the node at every level it appears
            for (int i = 0; i <= current_level; i++) {
                if (update[i]->forward[i] != current) {
                    break; // Node only exists up to a certain level
                }
                update[i]->forward[i] = current->forward[i];
            }
            
            // 4. Delete the node
            delete current;

            // 5. Decrease the current_level if the deleted node was the tallest
            while (current_level > 0 && header->forward[current_level] == nullptr) {
                current_level--;
            }
            std::cout << "Removed Key " << key << ". New Max Level: " << current_level << std::endl;
        } else {
            std::cout << "Key " << key << " not found for removal." << std::endl;
        }
    }

    /**
     * @brief Displays the structure of the skip list for visualization.
     */
    void display() {
        std::cout << "\n--- Skip List Structure (Max Level: " << current_level << ") ---" << std::endl;
        for (int i = current_level; i >= 0; i--) {
            std::cout << "Level " << i << ": ";
            SkipListNode<K, V>* node = header->forward[i];
            while (node) {
                std::cout << node->key << "->";
                node = node->forward[i];
            }
            std::cout << "NULL" << std::endl;
        }
        std::cout << "------------------------------------------" << std::endl;
    }
};

int main() {
    // We will use int keys and string values
    SkipList<int, std::string> sl;
    
    std::cout << "Inserting 10 entries..." << std::endl;
    
    // Insert keys in random order to test sorting/structure
    sl.insert(50, "Fifty");
    sl.insert(10, "Ten");
    sl.insert(70, "Seventy");
    sl.insert(30, "Thirty");
    sl.insert(20, "Twenty");
    sl.insert(60, "Sixty");
    sl.insert(80, "Eighty");
    sl.insert(40, "Forty");
    sl.insert(90, "Ninety");
    sl.insert(55, "Fifty-Five");
    
    sl.display();

    // --- Search Demonstration ---
    std::cout << "\n--- Searching ---" << std::endl;
    try {
        std::cout << "Searching for 40: " << sl.search(40) << std::endl;
        std::cout << "Searching for 10: " << sl.search(10) << std::endl;
        std::cout << "Searching for 90: " << sl.search(90) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Search Error: " << e.what() << std::endl;
    }
    
    // Non-existent key
    try {
        sl.search(99);
    } catch (const std::runtime_error& e) {
        std::cerr << "Search Error: " << e.what() << std::endl;
    }
    
    // --- Removal Demonstration ---
    std::cout << "\n--- Removal ---" << std::endl;
    sl.remove(30); // Should successfully remove
    sl.remove(100); // Should fail

    sl.display();
    
    // Test the update functionality
    sl.insert(50, "Fifty Updated!");
    try {
        std::cout << "\nSearching for 50 after update: " << sl.search(50) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Search Error: " << e.what() << std::endl;
    }

    return 0;
}
