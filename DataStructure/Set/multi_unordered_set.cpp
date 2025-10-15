#include <iostream>
#include <unordered_set> // This header is used for all unordered containers
#include <string>
#include <algorithm>
#include <utility> // For pair

using namespace std;

/**
 * @brief Helper function to print the contents of the multiset.
 * The order is UNORDERED and based on the internal hash function.
 */
void printMultiset(const unordered_multiset<string>& umset, const string& title) {
    cout << "\n--- " << title << " (Total Elements: " << umset.size() << ") ---" << endl;
    cout << "Elements:" << endl;
    
    // Iterate and print elements
    for (const string& element : umset) {
        cout << "[" << element << "] ";
    }
    cout << "\n------------------------------------------------\n" << endl;
}

int main() {
    // 1. Initialization and Insertion (Allows Duplicates)
    unordered_multiset<string> inventory;

    cout << "1. Inserting elements, including duplicates..." << endl;
    
    inventory.insert("Sword");      // Instance 1
    inventory.insert("Health Potion");
    inventory.insert("Sword");      // Instance 2 (Duplicate is allowed)
    inventory.insert("Gold Coin");
    inventory.insert("Sword");      // Instance 3
    inventory.insert("Health Potion");

    printMultiset(inventory, "Inventory After Initial Insertions");

    // 2. Counting Occurrences
    string item_to_count = "Sword";
    size_t sword_count = inventory.count(item_to_count); // O(1) average
    cout << "2. Counting occurrences of '" << item_to_count << "':" << endl;
    cout << "   The count is: " << sword_count << endl; 

    // 3. Targeted Deletion (All instances)
    string item_to_erase_all = "Health Potion";
    cout << "\n3. Erasing ALL instances of '" << item_to_erase_all << "'..." << endl;
    
    // The erase method removes ALL matching elements in a multiset and returns the count. (O(count) average)
    size_t erased_count = inventory.erase(item_to_erase_all);
    cout << "   Successfully erased " << erased_count << " elements." << endl;

    printMultiset(inventory, "Inventory After Erasing Health Potions");

    // 4. Targeted Deletion (Single Instance)
    cout << "4. Erasing a SINGLE instance of 'Sword'..." << endl;
    
    // To erase just one instance, we must find it first and use the iterator-based erase.
    // The find() method returns an iterator to the first matching element. (O(1) average)
    auto it = inventory.find("Sword");
    
    if (it != inventory.end()) {
        inventory.erase(it); // Erases only the element pointed to by the iterator. (O(1) average)
        cout << "   One 'Sword' instance removed." << endl;
    }

    printMultiset(inventory, "Inventory After Erasing One Sword");
    
    // 5. Finding All Instances using equal_range
    item_to_count = "Sword";
    cout << "\n5. Finding ALL remaining '" << item_to_count << "' items using equal_range:" << endl;
    
    // equal_range returns a pair of iterators: [first, last), marking the range of matching elements.
    pair<unordered_multiset<string>::iterator, unordered_multiset<string>::iterator> range;
    range = inventory.equal_range(item_to_count);
    
    int found_count = 0;
    cout << "   Found instances: ";
    for (auto current_it = range.first; current_it != range.second; ++current_it) {
        cout << *current_it << " ";
        found_count++;
    }
    cout << "\n   Total found via equal_range: " << found_count << endl;
    
    return 0;
}
/* 
 * @brief Key Takeaways from the Code
 * 
 * * **Header:** You only need `<unordered_set>` to use it.
 * * **Unordered Nature:** Notice that when the elements are printed, they are not necessarily in the order that they were inserted. The order is determined by the hash function and the internal state of the buckets.
 * * **Complexity:** All primary operations (`insert`, `count`, `erase`, `find`) execute in **$O(1)$ average time**, which is a massive performance advantage over `std::multiset` ($O(\log N)$) when ordering is not needed.
 * * **Duplicates Allowed:** Unlike `std::unordered_set`, this container allows multiple identical elements, making it suitable for scenarios like inventories where duplicates are common.
 * * **Targeted Deletion:** You can erase all instances of an element or just a single instance by using an iterator obtained from `find()`.
 * * **Finding All Instances:** The `equal_range()` method is a powerful way to retrieve all occurrences of a specific element efficiently.
 * 
 * Did you notice how the order of elements changed after the manual load factor manipulation? That's the **rehashing** in action! Would you like to see the equivalent demonstration for **`std::unordered_map`**?*/