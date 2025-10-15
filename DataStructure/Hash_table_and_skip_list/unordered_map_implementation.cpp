#include <iostream>
#include <vector>
#include <functional> // For std::hash
#include <string>

// --- Configuration Constants ---
// Load factor threshold: If (count / num_buckets) exceeds this, rehash is triggered.
const double MAX_LOAD_FACTOR = 1.0; 
// Initial size of the bucket array. Must be a reasonable prime number for good distribution.
const size_t INITIAL_BUCKET_SIZE = 11; 

// --- 1. Node Structure for Separate Chaining ---
// This represents one element in the linked list chain (the bucket).
template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode<K, V>* next;

    HashNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    // We don't need a destructor here for simplicity, but in a robust system, 
    // it would handle the linked list cleanup.
};

// --- 2. The Unordered Map Class ---
template <typename K, typename V>
class MyUnorderedMap {
private:
    // The bucket array: a vector of pointers to the head of a linked list (the chain).
    std::vector<HashNode<K, V>*> buckets;
    size_t count;         // Current number of elements stored
    size_t num_buckets;   // Size of the bucket array

    /**
     * @brief Determines the bucket index using the key's hash code.
     * This is the heart of the hash table lookup.
     * @param key The key to hash.
     * @return size_t The index in the bucket array.
     */
    size_t getBucketIndex(const K& key) const {
        // Use C++ standard hash function for simplicity (std::hash<K>()).
        std::hash<K> hasher;
        size_t hash_code = hasher(key);
        // Map the large hash code to an index within the bucket array size (num_buckets).
        return hash_code % num_buckets;
    }

    /**
     * @brief Calculates the current load factor.
     * @return double The ratio of elements to buckets (count / num_buckets).
     */
    double calculateLoadFactor() const {
        return static_cast<double>(count) / num_buckets;
    }

    /**
     * @brief Doubles the size of the bucket array and re-inserts all elements.
     * This is crucial to maintain O(1) performance by keeping load factor low.
     */
    void rehash() {
        // Save the old array and its size
        std::vector<HashNode<K, V>*> old_buckets = buckets;
        size_t old_num_buckets = num_buckets;

        // 1. Create a new, larger bucket array
        // A common strategy is to double the size (and often find the next prime).
        // For simplicity, we just double here.
        num_buckets *= 2; 
        buckets.assign(num_buckets, nullptr); // Resize the vector and initialize all to nullptr
        count = 0; // Reset count, as elements will be re-inserted

        std::cout << "\n--- REHASH TRIGGERED: New size is " << num_buckets << " ---" << std::endl;

        // 2. Iterate through the old buckets and re-insert every node
        for (size_t i = 0; i < old_num_buckets; ++i) {
            HashNode<K, V>* current = old_buckets[i];
            while (current) {
                // Save the next node before overwriting the current node's pointer
                HashNode<K, V>* next = current->next; 
                
                // Re-insert the node using the new, larger bucket array size
                size_t new_index = getBucketIndex(current->key);
                
                // Perform the linked list insertion at the head of the new chain
                current->next = buckets[new_index];
                buckets[new_index] = current;
                
                // Increment count for the new structure (only for re-inserted nodes)
                count++; 
                
                current = next;
            }
        }
    }

public:
    MyUnorderedMap() : count(0), num_buckets(INITIAL_BUCKET_SIZE) {
        // Initialize the vector with nullptrs
        buckets.assign(num_buckets, nullptr);
    }

    ~MyUnorderedMap() {
        // Cleanup all dynamically allocated nodes
        for (size_t i = 0; i < num_buckets; ++i) {
            HashNode<K, V>* current = buckets[i];
            while (current) {
                HashNode<K, V>* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    /**
     * @brief Inserts a key-value pair. Handles collisions and triggers rehashing.
     */
    void insert(const K& key, const V& value) {
        size_t index = getBucketIndex(key);
        HashNode<K, V>* current = buckets[index];

        // 1. Check if key already exists (traverse the chain)
        while (current) {
            if (current->key == key) {
                // Key found: update value and return
                current->value = value;
                return;
            }
            current = current->next;
        }

        // 2. Key does not exist: create new node and prepend to the chain
        HashNode<K, V>* new_node = new HashNode<K, V>(key, value);
        new_node->next = buckets[index];
        buckets[index] = new_node;
        count++;

        // 3. Check load factor and rehash if necessary
        if (calculateLoadFactor() > MAX_LOAD_FACTOR) {
            rehash();
        }
    }

    /**
     * @brief Searches for a value associated with a key.
     * @return V The value, or throws exception if not found.
     */
    V search(const K& key) const {
        size_t index = getBucketIndex(key);
        HashNode<K, V>* current = buckets[index];

        // Traverse the chain at the calculated index
        while (current) {
            if (current->key == key) {
                return current->value; // Key found!
            }
            current = current->next;
        }

        throw std::runtime_error("Key not found in map.");
    }

    /**
     * @brief Removes a key-value pair.
     */
    void remove(const K& key) {
        size_t index = getBucketIndex(key);
        HashNode<K, V>* current = buckets[index];
        HashNode<K, V>* prev = nullptr;

        // 1. Traverse the chain to find the node
        while (current) {
            if (current->key == key) {
                break; // Node found
            }
            prev = current;
            current = current->next;
        }

        // 2. If node was not found, return
        if (!current) {
            std::cout << "Key '" << key << "' not found for removal." << std::endl;
            return;
        }

        // 3. Unlink the node from the chain
        if (prev) {
            // Case 1: Node is in the middle or end of the chain
            prev->next = current->next;
        } else {
            // Case 2: Node is the head of the chain
            buckets[index] = current->next;
        }

        // 4. Delete the node and decrement count
        delete current;
        count--;
        std::cout << "Key '" << key << "' removed successfully." << std::endl;
    }

    void displayInfo() const {
        std::cout << "\n--- Map Status ---" << std::endl;
        std::cout << "Total Elements (count): " << count << std::endl;
        std::cout << "Bucket Array Size: " << num_buckets << std::endl;
        std::cout << "Load Factor: " << calculateLoadFactor() << std::endl;
        std::cout << "------------------" << std::endl;
    }
};

int main() {
    MyUnorderedMap<int, std::string> map;
    
    map.displayInfo(); // Initial state

    // --- Insertion and Rehashing Test ---
    std::cout << "\n--- 1. Insertion (Triggering Rehashing) ---" << std::endl;
    // Since INITIAL_BUCKET_SIZE is 11 and MAX_LOAD_FACTOR is 1.0, 
    // insertion 12 will trigger the first rehash.
    for (int i = 1; i <= 15; ++i) {
        map.insert(i * 10, "Value-" + std::to_string(i * 10));
    }

    map.displayInfo(); // State after rehashing

    // --- Search Test (O(1) Average) ---
    std::cout << "\n--- 2. Search Test ---" << std::endl;
    try {
        std::cout << "Search for key 40: " << map.search(40) << std::endl;
        std::cout << "Search for key 150: " << map.search(150) << std::endl;
        
        // Test non-existent key
        // map.search(99); // Uncomment to test exception handling
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught Search Error: " << e.what() << std::endl;
    }
    
    // --- Update Test ---
    map.insert(40, "Value-40-UPDATED");
    std::cout << "Search for key 40 after update: " << map.search(40) << std::endl;

    // --- Removal Test ---
    std::cout << "\n--- 3. Removal Test ---" << std::endl;
    map.remove(150);
    map.remove(10);
    map.remove(999); // Attempt to remove non-existent key

    map.displayInfo();

    return 0;
}
