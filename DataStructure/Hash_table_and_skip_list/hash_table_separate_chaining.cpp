#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <string>
#include <functional> // Required for std::hash

/**
 * Hash Table Implementation using Separate Chaining.
 * This structure implements the Map (or Dictionary) concept, mapping Keys to Values.
 * * Performance Summary:
 * - Insert, Lookup, Delete: O(1) on average.
 * - Worst Case (High Collisions): O(N), where N is the number of elements.
 * The efficiency relies on the hash function distributing keys evenly.
 */

// Define the size of the internal array (number of "buckets")
const int TABLE_SIZE = 10; 

template <typename K, typename V>
class HashTable {
private:
    // The main data structure: a vector of linked lists (buckets).
    // Each bucket holds a list of key-value pairs (the chain).
    std::vector<std::list<std::pair<K, V>>> table;
    int elementCount;

    /**
     * @brief Computes a hash index for a given key.
     * Time Complexity: O(1) - Constant time.
     */
    int hashFunction(const K& key) const {
        // Use C++'s built-in hash, then modulo by TABLE_SIZE to get the bucket index.
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

public:
    // Constructor: Initializes the vector with TABLE_SIZE empty lists.
    HashTable() : table(TABLE_SIZE), elementCount(0) {}

    /**
     * @brief Inserts a key-value pair into the hash table. Updates the value if the key already exists.
     * Time Complexity: O(1) average. O(N) worst case.
     */
    void insert(const K& key, const V& value) {
        int index = hashFunction(key);
        
        // O(1) average lookup for duplicates within the chain
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                // Key found, update the value
                pair.second = value;
                std::cout << "Updated key '" << key << "' to value '" << value << "'" << std::endl;
                return;
            }
        }

        // Add the new pair to the list (O(1) insertion at the end of the list)
        table[index].emplace_back(key, value);
        elementCount++;
        std::cout << "Inserted key '" << key << "' with value '" << value << "'" << std::endl;
    }

    /**
     * @brief Retrieves the value associated with a key (Lookup).
     * Time Complexity: O(1) average. O(N) worst case.
     */
    V lookup(const K& key) const {
        int index = hashFunction(key);
        
        // O(1) average search within the chain
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        
        // Key not found
        throw std::out_of_range("Key not found in Hash Table.");
    }
    
    /**
     * @brief Removes a key-value pair from the hash table.
     * Time Complexity: O(1) average. O(N) worst case.
     */
    void remove(const K& key) {
        int index = hashFunction(key);
        
        // O(1) average search and removal using an iterator
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it); // Safe removal
                elementCount--;
                std::cout << "Successfully removed key '" << key << "'." << std::endl;
                return;
            }
        }
        
        // Key not found
        std::cout << "Removal failed: Key '" << key << "' not found." << std::endl;
    }

    /**
     * @brief Displays the internal structure of the hash table (for visualizing collisions).
     * Time Complexity: O(N) because it must visit every stored element.
     */
    void displayStructure() const {
        std::cout << "\n--- Hash Table Structure (Buckets: " << TABLE_SIZE << ") ---" << std::endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Bucket " << i << ": ";
            if (table[i].empty()) {
                std::cout << "Empty";
            } else {
                for (const auto& pair : table[i]) {
                    // Display key -> value
                    std::cout << "[" << pair.first << " -> " << pair.second << "] -> ";
                }
                std::cout << "NULL";
            }
            std::cout << std::endl;
        }
        std::cout << "Total elements: " << elementCount << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;
    }
};

int main() {
    // Using string keys and integer values
    HashTable<std::string, int> employeeScores;

    std::cout << "=========================================================" << std::endl;
    std::cout << "--- Hash Table (Map) Demonstration ---" << std::endl;
    std::cout << "--- Core Ops are O(1) Average Case ---" << std::endl;
    std::cout << "=========================================================" << std::endl;

    // [1] Insertion Demonstration (O(1) average)
    std::cout << "\n[1] Inserting Employees:" << std::endl;
    employeeScores.insert("Alice", 95);
    employeeScores.insert("Bob", 88);
    employeeScores.insert("Charlie", 72);
    employeeScores.insert("Diana", 99);
    employeeScores.insert("Earl", 65); // Might cause a collision

    // Demonstrate update (same key)
    employeeScores.insert("Charlie", 78);

    employeeScores.displayStructure(); 

    // [2] Lookup Demonstration (O(1) average)
    std::cout << "\n[2] Lookup Employee Scores:" << std::endl;
    try {
        std::cout << "Alice's score: " << employeeScores.lookup("Alice") << std::endl;
        std::cout << "Diana's score: " << employeeScores.lookup("Diana") << std::endl;
        // This will cause an exception
        std::cout << "Frank's score: " << employeeScores.lookup("Frank") << std::endl; 
    } catch (const std::out_of_range& e) {
        std::cerr << "Error during lookup: " << e.what() << std::endl;
    }

    // [3] Removal Demonstration (O(1) average)
    std::cout << "\n[3] Removal Operations:" << std::endl;
    employeeScores.remove("Bob");
    employeeScores.remove("Frank"); // Key not found

    employeeScores.displayStructure();

    return 0;
}
