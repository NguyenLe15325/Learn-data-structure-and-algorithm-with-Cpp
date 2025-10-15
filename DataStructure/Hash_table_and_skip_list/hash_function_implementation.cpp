#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Global constant defining the size of the hash table.
 * Using a prime number helps with index distribution.
 */
const int TABLE_SIZE = 13; 

/**
 * @brief Custom implementation of a hash function for strings using the Polynomial Rolling Hash technique.
 * It transforms the string into a large integer value.
 * * @param key The string to be hashed.
 * @return unsigned int The resulting raw hash value.
 */
unsigned int custom_string_hash(const std::string& key) {
    // P: A prime number multiplier, often chosen around 31.
    const unsigned int P = 31; 
    unsigned int hashValue = 0;

    // Formula: hashValue = hashValue * P + character_value
    for (char c : key) {
        // The unsigned int overflow acts as a large modulus to keep the number manageable.
        hashValue = (hashValue * P) + (unsigned int)c;
    }
    
    return hashValue;
}

// --- Simplified Hash Table Implementation ---
template <typename V>
class SimpleHashTable {
private:
    std::vector<std::pair<std::string, V>> data;
    std::vector<bool> occupied;

    /**
     * @brief Maps the large hash value to a valid table index (0 to TABLE_SIZE - 1).
     * @param hashValue The large integer result from the custom hash function.
     * @return int The index in the array.
     */
    int get_index(unsigned int hashValue) const {
        return hashValue % TABLE_SIZE;
    }

public:
    SimpleHashTable() : data(TABLE_SIZE), occupied(TABLE_SIZE, false) {}

    /**
     * @brief Inserts a key-value pair using the custom hash function and linear probing.
     */
    void insert(const std::string& key, const V& value) {
        unsigned int hash = custom_string_hash(key);
        int startIndex = get_index(hash);
        int index = startIndex;
        int probeCount = 0;

        // Linear Probing: Look for the next available slot
        do {
            if (!occupied[index]) {
                data[index] = {key, value};
                occupied[index] = true;
                std::cout << "  -> Inserted '" << key << "' at index: " << index 
                          << " (Probes: " << probeCount << ")" << std::endl;
                return;
            }
            
            // Collision occurred! Use linear probing (step size of 1).
            index = (index + 1) % TABLE_SIZE;
            probeCount++;

        } while (probeCount < TABLE_SIZE);

        std::cerr << "Table is full! Cannot insert '" << key << "'." << std::endl;
    }
};

int main() {
    std::cout << "--- Custom String Hash Function Demonstration (Polynomial Rolling Hash) ---" << std::endl;
    std::cout << "--- Hash Table Size (TABLE_SIZE): " << TABLE_SIZE << " ---" << std::endl;
    
    // 1. Calculate raw hash values
    std::string key1 = "apple";
    std::string key2 = "banana";
    std::string key3 = "pleas"; 
    std::string key4 = "elppa"; 

    unsigned int hash1 = custom_string_hash(key1);
    unsigned int hash2 = custom_string_hash(key2);
    unsigned int hash3 = custom_string_hash(key3);
    unsigned int hash4 = custom_string_hash(key4);

    // This now works because TABLE_SIZE is global.
    std::cout << "Key: " << key1 << " | Raw Hash: " << hash1 << " | Initial Index: " << hash1 % TABLE_SIZE << std::endl;
    std::cout << "Key: " << key2 << " | Raw Hash: " << hash2 << " | Initial Index: " << hash2 % TABLE_SIZE << std::endl;
    std::cout << "Key: " << key3 << " | Raw Hash: " << hash3 << " | Initial Index: " << hash3 % TABLE_SIZE << std::endl;
    std::cout << "Key: " << key4 << " | Raw Hash: " << hash4 << " | Initial Index: " << hash4 % TABLE_SIZE << std::endl;

    std::cout << "\n--- Simple Hash Table Insertion (Linear Probing) ---" << std::endl;
    SimpleHashTable<std::string> table;
    
    // Example Initial Indices: 
    // "banana" (0), "elppa" (1), "apple" (2), "grape" (2), "zebra" (0)
    
    // Insertion 1: No collision (Index 0)
    table.insert("banana", "Yellow Fruit"); 
    
    // Insertion 2: No collision (Index 1)
    table.insert("elppa", "Reverse Apple"); 

    // Insertion 3: Collision with "banana" at index 0. Probes 1 to 1. Inserted at Index 2.
    table.insert("zebra", "Striped Animal"); 
    
    // Insertion 4: Collision with "zebra" at index 2. Probes 1 to 3. Inserted at Index 3.
    table.insert("apple", "Red Fruit"); 
    
    // Insertion 5: Collision with "apple" at index 2. Probes 1 to 4. Inserted at Index 4.
    table.insert("grape", "Small Fruit"); 
    
    return 0;
}
