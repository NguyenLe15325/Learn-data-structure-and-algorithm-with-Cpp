#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <functional> // Required for std::hash

/**
 * Hash Table Implementation using Open Addressing with Quadratic Probing.
 * * CORE CONCEPT: If a collision occurs at index h(k), the subsequent probe locations are:
 * (h(k) + 1^2) % M, (h(k) + 2^2) % M, (h(k) + 3^2) % M, and so on.
 * M (the table size) should ideally be a prime number for best performance.
 */

// Define the size of the internal array. A prime number is crucial 
// for Quadratic Probing to ensure a large number of slots are checked.
const int TABLE_SIZE = 11; 

// Status enum required for Open Addressing to handle deleted slots correctly.
enum SlotStatus { EMPTY, OCCUPIED, DELETED };

// Entry structure for each slot in the array.
template <typename K, typename V>
struct Entry {
    K key;
    V value;
    SlotStatus status;

    Entry() : status(EMPTY) {}
};

template <typename K, typename V>
class HashTableQuadraticProbing {
private:
    std::vector<Entry<K, V>> dataArray;
    int elementCount;

    /**
     * @brief Computes the initial hash index for a given key.
     */
    int hashFunction(const K& key) const {
        // Use the standard library hash function for demonstration
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

    /**
     * @brief Searches for a key, or finds the best slot for insertion (first DELETED or EMPTY).
     * @return The index of the found key, the best insertion index, or -1 if the table is full.
     */
    int findSlot(const K& key) const {
        int startIndex = hashFunction(key);
        int step = 0;
        int firstDeletedIndex = -1; // We prefer to reuse a DELETED slot over an EMPTY one.

        // Probe up to TABLE_SIZE times to prevent infinite loop.
        while (step < TABLE_SIZE) {
            
            // Quadratic Probing Formula: index = (start + step^2) % size
            int index = (startIndex + step * step) % TABLE_SIZE;

            if (dataArray[index].status == EMPTY) {
                // Found an EMPTY slot. Return the first DELETED index if we found one, 
                // otherwise return this EMPTY index for insertion.
                return (firstDeletedIndex != -1) ? firstDeletedIndex : index;
            }

            if (dataArray[index].status == OCCUPIED) {
                if (dataArray[index].key == key) {
                    return index; // Key found!
                }
            } else if (dataArray[index].status == DELETED) {
                // Found a DELETED slot. Record its location for reuse, but continue probing
                // in case the key we're looking for is further along the probe path.
                if (firstDeletedIndex == -1) {
                    firstDeletedIndex = index; 
                }
            }
            
            step++;
        }
        
        // Table is full or key not found after checking all possible slots
        return (firstDeletedIndex != -1) ? firstDeletedIndex : -1;
    }

public:
    // Constructor: Initializes the vector to TABLE_SIZE empty entries.
    HashTableQuadraticProbing() : dataArray(TABLE_SIZE), elementCount(0) {}

    /**
     * @brief Inserts or updates a key-value pair.
     */
    void insert(const K& key, const V& value) {
        int index = findSlot(key);

        if (index == -1) {
            throw std::out_of_range("Hash Table is full.");
        }
        
        // Flag to check if we are reusing a DELETED slot or inserting into a new one.
        bool wasDeletedSlot = dataArray[index].status == DELETED;

        // Case 1: Key already exists (found by findSlot) -> Update the value
        if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
            dataArray[index].value = value;
            std::cout << "Updated key '" << key << "' at index " << index << std::endl;
        } 
        // Case 2: New key found an empty/deleted slot -> Insert new entry
        else {
            dataArray[index].key = key;
            dataArray[index].value = value;
            dataArray[index].status = OCCUPIED;
            
            // Only increment elementCount if we insert into an EMPTY slot, 
            // or if we reuse a DELETED slot that wasn't already counted.
            if (!wasDeletedSlot) {
                elementCount++;
            }
            std::cout << "Inserted key '" << key << "' at index " << index << " (Step: " << (index - hashFunction(key)) % TABLE_SIZE << ")" << std::endl;
        }
    }

    /**
     * @brief Retrieves the value associated with a key (Lookup).
     * NOTE: The lookup must continue probing past DELETED slots, stopping only at EMPTY slots.
     */
    V lookup(const K& key) const {
        int startIndex = hashFunction(key);
        int step = 0;

        while (step < TABLE_SIZE) {
            int index = (startIndex + step * step) % TABLE_SIZE;

            if (dataArray[index].status == EMPTY) {
                // Hit an EMPTY slot, so the key cannot be further down the probe sequence.
                break;
            }
            
            if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
                return dataArray[index].value; // Key found!
            }
            
            step++;
        }
        
        throw std::out_of_range("Key not found in Hash Table.");
    }
    
    /**
     * @brief Removes a key-value pair. Marks the slot as DELETED.
     */
    void remove(const K& key) {
        int startIndex = hashFunction(key);
        int step = 0;

        while (step < TABLE_SIZE) {
            int index = (startIndex + step * step) % TABLE_SIZE;

            if (dataArray[index].status == EMPTY) {
                break; // Key not found
            }

            if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
                // Key found, mark as DELETED 
                dataArray[index].status = DELETED;
                elementCount--;
                std::cout << "Successfully removed (marked DELETED) key '" << key << "' at index " << index << "." << std::endl;
                return;
            }

            step++;
        }
        
        std::cout << "Removal failed: Key '" << key << "' not found." << std::endl;
    }

    /**
     * @brief Displays the internal structure.
     */
    void displayStructure() const {
        std::cout << "\n--- Hash Table Structure (Quadratic Probing, M=" << TABLE_SIZE << ") ---" << std::endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Slot " << i << ": ";
            switch (dataArray[i].status) {
                case EMPTY:
                    std::cout << "EMPTY";
                    break;
                case DELETED:
                    std::cout << "DELETED (Placeholder)";
                    break;
                case OCCUPIED:
                    std::cout << "OCCUPIED [Key: " << dataArray[i].key << ", Value: " << dataArray[i].value << "]";
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << "Total elements: " << elementCount << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;
    }
};

int main() {
    HashTableQuadraticProbing<std::string, int> scores;

    std::cout << "=========================================================" << std::endl;
    std::cout << "--- Open Addressing (Quadratic Probing) Demonstration ---" << std::endl;
    std::cout << "=========================================================" << std::endl;

    // Keys that might hash to the same or nearby initial index (for M=11)
    std::cout << "\n[1] Insertion (Quadratic Steps)" << std::endl;
    scores.insert("A", 10); 
    scores.insert("B", 20); // Initial index B=1, A=0 (hypothetical)
    scores.insert("C", 30); // Initial index C=2
    scores.insert("D", 40); // Initial index D=3
    
    // Let's insert a key that forces a collision and requires a jump (e.g., to index + 4)
    scores.insert("Key1", 100); 
    scores.insert("Key2", 200); 
    scores.insert("Key3", 300); // This key is likely to collide, forcing a quadratic probe (1, 4, 9...)

    scores.displayStructure(); 

    // [2] Removal and Lookup
    std::cout << "\n[2] Removal and Lookup Operations" << std::endl;
    scores.remove("Key2"); // Marks the slot as DELETED
    
    // Lookup for Key3 must now jump over the DELETED slot
    try {
        std::cout << "Score for Key1: " << scores.lookup("Key1") << std::endl;
        std::cout << "Score for Key3 (found after skipping DELETED slot): " << scores.lookup("Key3") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error during lookup: " << e.what() << std::endl;
    }

    scores.displayStructure();

    return 0;
}
