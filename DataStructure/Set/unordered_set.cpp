#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief Demonstrates the core functionality of std::unordered_set.
 * std::unordered_set uses a Hash Table for O(1) average time complexity.
 */
void printSet(const unordered_set<string>& uset, const string& title) {
    cout << "\n--- " << title << " (Size: " << uset.size() << ") ---" << endl;
    cout << "Elements (Note: Order is NOT guaranteed and may change):" << endl;
    
    // Iterate and print elements to demonstrate the lack of guaranteed order
    for (const string& element : uset) {
        cout << "[" << element << "] ";
    }
    cout << "\n------------------------------------------------\n" << endl;
}

int main() {
    // 1. Initialization and Insertion
    unordered_set<string> grocery_items;

    cout << "1. Inserting elements..." << endl;
    grocery_items.insert("Apple"); // O(1) average
    grocery_items.insert("Banana");
    grocery_items.insert("Milk");
    grocery_items.insert("Bread");
    grocery_items.insert("Yogurt");

    printSet(grocery_items, "Set After Initial Insertions");

    // 2. Uniqueness Constraint
    cout << "2. Attempting to insert a duplicate (Apple)..." << endl;
    
    // insert() returns a pair: {iterator, bool}. 'second' is true if inserted, false if duplicate.
    auto [it, inserted] = grocery_items.insert("Apple");
    
    if (!inserted) {
        cout << "   'Apple' was NOT inserted because it already exists (Uniqueness enforced)." << endl;
    }

    // 3. Lookup / Membership Test (The core use case)
    string check_item = "Milk";
    cout << "\n3. Checking for membership (count function)..." << endl;
    
    // The count method returns 1 if the element is present, 0 otherwise. (O(1) average)
    if (grocery_items.count(check_item) > 0) {
        cout << "   SUCCESS: '" << check_item << "' is present in the set." << endl;
    } else {
        cout << "   MISSING: '" << check_item << "' is NOT present in the set." << endl;
    }
    
    // Checking for a non-existent item
    string missing_item = "Cheese";
    if (grocery_items.count(missing_item) == 0) {
        cout << "   SUCCESS: '" << missing_item << "' is correctly reported as missing." << endl;
    }

    // 4. Deletion
    string item_to_remove = "Banana";
    cout << "\n4. Erasing '" << item_to_remove << "'..." << endl;
    
    // erase() returns the number of elements removed (1 or 0). (O(1) average)
    size_t erased_count = grocery_items.erase(item_to_remove);
    cout << "   Elements erased: " << erased_count << endl;

    printSet(grocery_items, "Set After Deletion");
    
    // 5. Hash Table Specific Information (Optional but useful for understanding)
    cout << "5. Hash Table Metrics:" << endl;
    cout << "   Current Bucket Count (Capacity): " << grocery_items.bucket_count() << endl;
    cout << "   Load Factor (Elements / Buckets): " << grocery_items.load_factor() << endl;
    
    // Manually setting maximum load factor (e.g., to force rehashing)
    grocery_items.max_load_factor(0.5f);
    cout << "   Max Load Factor set to 0.5" << endl;

    // The set will automatically rehash when the load factor exceeds 0.5 on the next insertion.
    cout << "\n   Inserting 'Oranges' (May trigger rehash and change element order)..." << endl;
    grocery_items.insert("Oranges");
    grocery_items.insert("Applesauce"); // Ensure enough elements to show bucket change

    cout << "   New Bucket Count (Capacity): " << grocery_items.bucket_count() << endl;

    printSet(grocery_items, "Set After Rehashing");

    return 0;
}
