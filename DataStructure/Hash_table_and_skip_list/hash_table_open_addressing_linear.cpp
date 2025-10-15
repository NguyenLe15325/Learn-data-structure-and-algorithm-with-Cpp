#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <functional> // Required for std::hash

/**
 * Hash Table Implementation using Open Addressing with Linear Probing.
 * This method uses a single array and no external linked lists.
 * * * Performance Summary:
 * - Insert, Lookup, Delete: O(1) on average.
 * - Worst Case (High Clustering): O(N).
 * - Performance degrades significantly if the table (Load Factor) gets too full.
 */

// Define the size of the internal array (number of "buckets")
const int TABLE_SIZE = 10; 

// Status enum required for Open Addressing to handle deleted slots correctly.
enum SlotStatus { EMPTY, OCCUPIED, DELETED };

// Entry structure for each slot in the array.
template <typename K, typename V>
struct Entry {
    K key;
    V value;
    SlotStatus status;

    // Constructor to create an empty slot
    Entry() : status(EMPTY) {}
};

template <typename K, typename V>
class HashTableOpenAddressing {
private:
    // The main data structure: a fixed-size array of Entry structs.
    std::vector<Entry<K, V>> dataArray;
    int elementCount;

    /**
     * @brief Computes the initial hash index for a given key.
     * Time Complexity: O(1).
     */
    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

    /**
     * @brief Performs the search (probing) sequence for a key.
     * Time Complexity: O(1) average. O(N) worst case (if massive clustering occurs).
     * @return The index where the key is found, or the index where it should be inserted (the first EMPTY slot found).
     */
    int probe(const K& key) const {
        int index = hashFunction(key);
        int startIndex = index;

        // Loop through the array until an EMPTY slot is found, or the key is found.
        while (dataArray[index].status != EMPTY) {
            
            // Check if the current slot holds the key we are looking for
            if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
                return index; // Key found!
            }

            // Linear Probing: Move to the next slot (i + 1)
            index = (index + 1) % TABLE_SIZE;

            // If we've circled back to the starting point, the table is full (or lookup failed)
            if (index == startIndex) {
                // Return -1 or throw exception indicating failure to find space
                return -1; 
            }
        }
        
        // Return the first EMPTY slot found (where insertion should occur)
        return index;
    }

public:
    // Constructor: Initializes the vector to TABLE_SIZE empty entries.
    HashTableOpenAddressing() : dataArray(TABLE_SIZE), elementCount(0) {}

    /**
     * @brief Inserts or updates a key-value pair.
     * Time Complexity: O(1) average. O(N) worst case.
     */
    void insert(const K& key, const V& value) {
        int index = probe(key);

        if (index == -1) {
            throw std::out_of_range("Hash Table is full.");
        }

        // Case 1: Key already exists (found by probe) -> Update the value
        if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
            dataArray[index].value = value;
            std::cout << "Updated key '" << key << "' at index " << index << std::endl;
        } 
        // Case 2: New key found an empty/deleted slot -> Insert new entry
        else {
            dataArray[index].key = key;
            dataArray[index].value = value;
            dataArray[index].status = OCCUPIED;
            elementCount++;
            std::cout << "Inserted key '" << key << "' at index " << index << std::endl;
        }
    }

    /**
     * @brief Retrieves the value associated with a key (Lookup).
     * Time Complexity: O(1) average. O(N) worst case.
     */
    V lookup(const K& key) const {
        int index = hashFunction(key);
        int startIndex = index;

        while (dataArray[index].status != EMPTY) {
            // Found the occupied slot with the matching key
            if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
                return dataArray[index].value;
            }
            
            // Linear Probing: move to the next slot
            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                // Full circle, key not found
                break;
            }
        }
        
        // Key not found
        throw std::out_of_range("Key not found in Hash Table.");
    }
    
    /**
     * @brief Removes a key-value pair. Critical to mark as DELETED, not EMPTY.
     * Time Complexity: O(1) average. O(N) worst case.
     */
    void remove(const K& key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (dataArray[index].status != EMPTY) {
            if (dataArray[index].status == OCCUPIED && dataArray[index].key == key) {
                // Key found, mark as DELETED (not EMPTY!)
                dataArray[index].status = DELETED;
                elementCount--;
                std::cout << "Successfully removed (marked DELETED) key '" << key << "' at index " << index << "." << std::endl;
                return;
            }

            // Linear Probing: move to the next slot
            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) break;
        }
        
        std::cout << "Removal failed: Key '" << key << "' not found." << std::endl;
    }

    /**
     * @brief Displays the internal structure.
     */
    void displayStructure() const {
        std::cout << "\n--- Hash Table Structure (Open Addressing) ---" << std::endl;
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
    HashTableOpenAddressing<std::string, int> scores;

    std::cout << "=========================================================" << std::endl;
    std::cout << "--- Open Addressing (Linear Probing) Demonstration ---" << std::endl;
    std::cout << "=========================================================" << std::endl;

    // We rely on collisions to show probing and clustering.
    // Hash results are often based on the length/order of the string.
    std::cout << "\n[1] Insertion (Demonstrating Probing)" << std::endl;
    
    // Assume these keys hash to the same or nearby initial index for demonstration:
    scores.insert("Cat", 100); 
    scores.insert("Dog", 200);
    scores.insert("Tap", 300); // This should collide with one of the above, triggering a probe
    scores.insert("Pat", 400); // Further collision and probe

    scores.displayStructure(); 

    // [2] Lookup Demonstration (O(1) average)
    std::cout << "\n[2] Lookup Operations" << std::endl;
    try {
        std::cout << "Score for Dog: " << scores.lookup("Dog") << std::endl;
        std::cout << "Score for Tap: " << scores.lookup("Tap") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error during lookup: " << e.what() << std::endl;
    }

    // [3] Removal Demonstration (Crucial step for DELETED status)
    std::cout << "\n[3] Removal and DELETED Status" << std::endl;
    scores.remove("Dog");
    
    // Now, let's look up 'Tap'. If 'Dog' slot was marked EMPTY, the lookup for 'Tap' would fail,
    // because the probe sequence would stop early at the 'Dog' slot.
    std::cout << "Score for Tap (after Dog removed): " << scores.lookup("Tap") << std::endl; 

    scores.displayStructure();

    return 0;
}
