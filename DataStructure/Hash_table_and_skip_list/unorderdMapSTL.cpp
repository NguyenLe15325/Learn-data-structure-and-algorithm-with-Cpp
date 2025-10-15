#include <iostream>
#include <unordered_map>
#include <string>

/**
 * @brief Demonstrates the use of the C++ STL std::unordered_map container.
 * * std::unordered_map stores key-value pairs using a Hash Table.
 * * Access time is O(1) average.
 * * Key iteration order is unpredictable (based on hash function).
 */
int main() {
    // A map where the Key is a string (fruit name) and the Value is an integer (count).
    std::unordered_map<std::string, int> fruit_counts;

    std::cout << "--- 1. Insertion (O(1) Average) ---" << std::endl;

    // Insertion is fast and uses the key's hash to find the bucket index.
    fruit_counts["apple"] = 5;
    fruit_counts["banana"] = 10;
    fruit_counts["grape"] = 15;
    fruit_counts["orange"] = 7;
    
    // Insertion overwrites the existing value if the key is already present.
    fruit_counts["apple"] = 12; 
    std::cout << "The count for 'apple' was updated to 12." << std::endl;


    std::cout << "\n--- 2. Iteration (Unsorted Order) ---" << std::endl;
    std::cout << "Key\tValue" << std::endl;
    std::cout << "----------------------" << std::endl;
    
    // Note: The output order will NOT be alphabetical (apple, banana, etc.).
    // It will be the order the keys are found in the internal hash table's buckets.
    for (const auto& pair : fruit_counts) {
        // pair.first is the key (string) and pair.second is the value (int)
        std::cout << pair.first << "\t" << pair.second << std::endl;
    }


    std::cout << "\n--- 3. Accessing Elements (O(1) Average) ---" << std::endl;
    
    // Access Method 1: The 'at()' function (safe access, throws exception if key not found)
    try {
        std::cout << "Count for banana: " << fruit_counts.at("banana") << std::endl;
        
        // Accessing a key that doesn't exist will throw std::out_of_range
        // std::cout << fruit_counts.at("kiwi") << std::endl; // Throws exception

    } catch (const std::out_of_range& e) {
        std::cout << "Error: Key not found when using .at() functionality." << std::endl;
    }
    
    // Access Method 2: Subscript operator [] 
    // This is less safe for lookups but creates the key/value pair if it doesn't exist!
    std::cout << "Count for orange (using []): " << fruit_counts["orange"] << std::endl;
    
    // Access Method 3: count()
    if (fruit_counts.count("grape")) {
        std::cout << "Grape is present in the map." << std::endl;
    }


    std::cout << "\n--- 4. Deletion (O(1) Average) ---" << std::endl;
    std::string delete_key = "orange";
    
    // erase() returns the number of elements removed (0 or 1, since keys are unique)
    size_t removed = fruit_counts.erase(delete_key);
    
    std::cout << "Removed " << removed << " element(s) for key '" << delete_key << "'." << std::endl;
    std::cout << "Current size: " << fruit_counts.size() << std::endl;
    
    // Final check
    std::cout << "Final Keys: ";
    for (const auto& pair : fruit_counts) {
        std::cout << pair.first << " ";
    }
    std::cout << std::endl;

    return 0;
}
