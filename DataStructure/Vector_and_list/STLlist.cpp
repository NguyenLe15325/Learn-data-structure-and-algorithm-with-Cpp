#include <iostream>
#include <list>   // The standard library header for std::list
#include <string>
#include <algorithm> // Required for std::find

/**
 * STL std::list Demonstration.
 * std::list implements a Doubly Linked List, offering O(1) insertion/deletion
 * anywhere in the list, but O(N) access time.
 * * Key STL functions:
 * - push_front(), push_back(): Add elements to either end (O(1)).
 * - pop_front(), pop_back(): Remove elements from either end (O(1)).
 * - insert(): Inserts at an iterator position (O(1) after the O(N) search).
 * - remove(): Removes all matching values (O(N) traversal).
 * - splice(): Moves nodes between lists (O(1) operation).
 */

// Helper function to display the list contents
void print_list(const std::list<int>& lst, const std::string& label) {
    std::cout << label << " (Size: " << lst.size() << ") -> [ ";
    for (int val : lst) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    // 1. Creation and Initialization
    std::list<int> inventory;
    
    std::cout << "=========================================" << std::endl;
    std::cout << "--- STL std::list Demonstration ---" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // 2. O(1) Insertion at Ends
    std::cout << "2. Building the list using PUSH FRONT/BACK (O(1)):" << std::endl;
    
    inventory.push_back(40);  // List: [ 40 ]
    inventory.push_front(20); // List: [ 20 40 ]
    inventory.push_back(60);  // List: [ 20 40 60 ]
    inventory.push_front(10); // List: [ 10 20 40 60 ]
    
    print_list(inventory, "Current Inventory");

    // 3. O(N) Search, then O(1) Insertion in the middle
    std::cout << "\n3. Insertion in the Middle (Requires O(N) search, O(1) insert):" << std::endl;
    
    // Find the position of 40 (O(N) search cost)
    auto pos40 = std::find(inventory.begin(), inventory.end(), 40);

    if (pos40 != inventory.end()) {
        // Insert 30 before 40 (O(1) insertion at the found position)
        inventory.insert(pos40, 30);
        std::cout << "   Inserted 30 before 40." << std::endl;
    }
    print_list(inventory, "After Insertion"); // List: [ 10 20 30 40 60 ]
    
    // 4. O(1) Deletion at Ends
    std::cout << "\n4. Removal at Ends (O(1)) and Removing by Value (O(N)):" << std::endl;
    
    inventory.pop_front(); // Remove 10
    inventory.pop_back();  // Remove 60
    print_list(inventory, "After pop_front/back"); // List: [ 20 30 40 ]

    // 5. O(N) Remove by Value
    inventory.push_back(20); // Add a duplicate 20
    print_list(inventory, "With Duplicate"); // List: [ 20 30 40 20 ]

    // The remove operation traverses the entire list (O(N)) to find and delete all matches.
    inventory.remove(20); 
    std::cout << "   Removed all instances of 20." << std::endl;
    print_list(inventory, "After remove(20)"); // List: [ 30 40 ]
    
    // 6. Splice Demonstration (Unique O(1) list operation)
    std::list<int> archive = {5, 15, 25};
    std::cout << "\n6. Splice Operation (O(1) Node Transfer):" << std::endl;
    print_list(archive, "Archive Before Splice");

    // Move all nodes from 'archive' into 'inventory' before the element 40
    auto pos40_2 = std::find(inventory.begin(), inventory.end(), 40); 
    
    // Splice moves the nodes. No data is copied or deleted.
    inventory.splice(pos40_2, archive); 
    
    print_list(inventory, "Inventory After Splice"); // List: [ 30 5 15 25 40 ]
    print_list(archive, "Archive After Splice");     // Archive is now empty (nodes were moved)

    return 0;
}
