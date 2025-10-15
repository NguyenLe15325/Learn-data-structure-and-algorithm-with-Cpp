#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <functional> // Required for std::hash

/**
 * Hash Table Implementation using Open Addressing with Double Hashing.
 * This method uses a unique step size for each key to eliminate clustering.
 */

// M: Table size (must be prime for best performance).
const int TABLE_SIZE = 11; 

// R: Secondary prime, slightly less than M (used in h2).
const int SECONDARY_PRIME = 7; 

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
class HashTableDoubleHashing {
private:
    std::vector<Entry<K, V>> dataArray;
    int elementCount;

    /**
     * @brief h1(k): Primary hash function - determines the starting index.
     * Time Complexity: O(1).
     */
    int hashFunction1(const K& key) const {
        // Use the standard library hash function for demonstration
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

    /**
     * @brief h2(k): Secondary hash function - determines the step size.
     * Formula: R - (raw_hash(k) % R). Ensures step size is never 0 and depends on the key.
     * Time Complexity: O(1).
     */
    int hashFunction2(const K& key) const {
        size_t rawHash = std::hash<K>{}(key);
        // Ensure result is > 0 and < R.
        return SECONDARY_PRIME - (rawHash % SECONDARY_PRIME);
    }

    /**
     * @brief Searches for a key, or finds the best slot for insertion (first DELETED or EMPTY).
     * Probe Sequence: (h1(k) + j * h2(k)) % M
     * @return The index of the found key, the best insertion index, or -1 if the table is full.
     */
    int findSlot(const K& key) const {
        int h1 = hashFunction1(key);
        int h2 = hashFunction2(key);
        int step = 0;
        int firstDeletedIndex = -1; 

        // We probe up to TABLE_SIZE times.
        while (step < TABLE_SIZE) {
            
            // Double Hashing Formula: index = (h1 + step * h2) % M
            int index = (h1 + step * h2) % TABLE_SIZE;

            if (dataArray[index].status == EMPTY) {
                // Found an EMPTY slot. 
                return (firstDeletedIndex != -1) ? firstDeletedIndex : index;
            }

            if (dataArray[index].status == OCCUPIED) {
                if (dataArray[index].key == key) {
                    return index; // Key found!
                }
            } else if (dataArray[index].status == DELETED) {
                // Found a DELETED slot. Record it but keep searching in case the key is ahead.
                if (firstDeletedIndex == -1) {
                    firstDeletedIndex = index; 
                }
            }
            
            step++;
        }
        
        // Return the DELETED slot if found, otherwise -1 (full/failed search)
        return (firstDeletedIndex != -1) ? firstDeletedIndex : -1;
    }

public:
    // Constructor: Initializes the vector to M empty entries.
    HashTableDoubleHashing() : dataArray(TABLE_SIZE), elementCount(0) {}

    /**
     * @brief Inserts or updates a key-value pair.
     */
    void insert(const K& key, const V& value) {
        int index = findSlot(key);

        if (index == -1) {
            throw std::out_of_range("Hash Table is full.");
        }
        
        // Track if we are reusing a DELETED slot.
        bool wasDeletedSlot = dataArray[index].status == DELETED;

        // Case 1: Key already exists -> Update the value
        if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
            dataArray[index].value = value;
            std::cout << "Updated key '" << key << "' at index " << index << std::endl;
        } 
        // Case 2: New key found an empty/deleted slot -> Insert new entry
        else {
            dataArray[index].key = key;
            dataArray[index].value = value;
            dataArray[index].status = OCCUPIED;
            
            if (!wasDeletedSlot) {
                elementCount++;
            }
            
            int h1 = hashFunction1(key);
            int h2 = hashFunction2(key);
            // Calculate step for output display
            int actualStep = 0;
            if (h2 != 0) {
                 actualStep = (index - h1 + TABLE_SIZE) % TABLE_SIZE / h2; 
            }
            std::cout << "Inserted key '" << key << "' at index " << index 
                      << " (H1=" << h1 << ", H2=" << h2 << ", Step=" << actualStep << ")" << std::endl;
        }
    }

    /**
     * @brief Retrieves the value associated with a key (Lookup).
     */
    V lookup(const K& key) const {
        int h1 = hashFunction1(key);
        int h2 = hashFunction2(key);
        int step = 0;

        while (step < TABLE_SIZE) {
            int index = (h1 + step * h2) % TABLE_SIZE;

            if (dataArray[index].status == EMPTY) {
                // Hit an empty slot, key cannot be found further.
                break;
            }
            
            if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
                return dataArray[index].value;
            }
            
            step++;
        }
        
        throw std::out_of_range("Key not found in Hash Table.");
    }
    
    /**
     * @brief Removes a key-value pair. Marks the slot as DELETED.
     */
    void remove(const K& key) {
        int h1 = hashFunction1(key);
        int h2 = hashFunction2(key);
        int step = 0;

        while (step < TABLE_SIZE) {
            int index = (h1 + step * h2) % TABLE_SIZE;

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
        std::cout << "\n--- Hash Table Structure (Double Hashing, M=" << TABLE_SIZE << ", R=" << SECONDARY_PRIME << ") ---" << std::endl;
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
    HashTableDoubleHashing<std::string, double> records;

    std::cout << "=========================================================" << std::endl;
    std::cout << "--- Open Addressing (Double Hashing) Demonstration ---" << std::endl;
    std::cout << "=========================================================" << std::endl;

    std::cout << "\n[1] Insertion (Demonstrating Unique Steps)" << std::endl;
    
    records.insert("Apple", 1.0); 
    records.insert("Banana", 2.0); 
    records.insert("Cherry", 3.0); 
    
    records.insert("Date", 4.0);
    records.insert("Elderberry", 5.0); 
    records.insert("Fig", 6.0); 

    records.displayStructure(); 

    std::cout << "\n[2] Lookup and Removal Operations" << std::endl;
    
    records.remove("Banana");
    
    try {
        std::cout << "Value for Date: " << records.lookup("Date") << std::endl;
        std::cout << "Value for Cherry (successfully found): " << records.lookup("Cherry") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error during lookup: " << e.what() << std::endl;
    }

    records.displayStructure();

    return 0;
}
