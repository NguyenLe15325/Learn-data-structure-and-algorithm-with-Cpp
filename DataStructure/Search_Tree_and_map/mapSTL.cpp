#include <iostream>
#include <map>
#include <string>

using namespace std;

// Function to print the contents of the map
void print_map(const map<int, string>& m, const string& title) {
    cout << "\n--- " << title << " (Size: " << m.size() << ") ---" << endl;
    if (m.empty()) {
        cout << "(Map is empty)" << endl;
        return;
    }
    // Iterate over the map. Keys are guaranteed to be printed in sorted order.
    for (const auto& pair : m) {
        cout << "  Key: " << pair.first << ", Value: \"" << pair.second << "\"" << endl;
    }
}

int main() {
    // 1. Initialization: Creates a map where Key is int and Value is string.
    map<int, string> student_grades;
    
    cout << "--- 1. Insertion ---" << endl;
    
    // Method A: Using the [] operator (preferred for insertion/update)
    // If the key (101) exists, it updates the value. If not, it inserts.
    student_grades[101] = "Alice";
    student_grades[105] = "Charlie";
    
    // Method B: Using the insert function
    // insert returns a pair: {iterator to element, bool was_inserted}
    auto result = student_grades.insert({103, "Bob"});
    if (result.second) {
        cout << "Inserted Bob successfully." << endl;
    }

    // Attempting to insert a duplicate key does nothing (map keys must be unique)
    student_grades.insert({105, "Charles (Duplicate attempt)"});
    
    // Method C: Using the emplace function (often more efficient for complex objects)
    student_grades.emplace(107, "Eve");
    
    print_map(student_grades, "Map After Initial Insertions (Sorted by Key)");

    // ---
    
    cout << "\n--- 2. Access and Update ---" << endl;

    // Update an existing value using the [] operator
    student_grades[105] = "Charity (Updated)";
    cout << "Value for key 105 is now: " << student_grades[105] << endl;

    // Access using .at(). Throws std::out_of_range exception if key not found.
    try {
        cout << "Value for key 101 is: " << student_grades.at(101) << endl;
        // This will throw an exception:
        // cout << "Value for key 999 is: " << student_grades.at(999) << endl; 
    } catch (const out_of_range& e) {
        cerr << "Error: Attempted to access non-existent key using .at()" << endl;
    }

    // ---

    cout << "\n--- 3. Search and Check Existence ---" << endl;

    int search_key = 103;
    // .find() returns an iterator to the element if found, or .end() if not found.
    auto it_found = student_grades.find(search_key);

    if (it_found != student_grades.end()) {
        cout << "Key " << search_key << " found! Value: " << it_found->second << endl;
    } else {
        cout << "Key " << search_key << " not found." << endl;
    }
    
    // ---

    cout << "\n--- 4. Deletion ---" << endl;

    // Method A: Erase by key (returns the number of elements erased: 1 or 0)
    size_t count = student_grades.erase(107);
    cout << "Erased key 107. Elements removed: " << count << endl;

    // Method B: Erase by iterator (using the iterator returned by find)
    auto it_to_erase = student_grades.find(101);
    if (it_to_erase != student_grades.end()) {
        // Erase and get an iterator to the element following the one erased.
        it_to_erase = student_grades.erase(it_to_erase); 
        cout << "Erased key 101. Iterator now points to key: " << it_to_erase->first << endl;
    }
    
    print_map(student_grades, "Map After Deletion");
    
    // ---
    
    cout << "\n--- 5. Final Operations ---" << endl;

    // Check if empty
    cout << "Is map empty? " << (student_grades.empty() ? "Yes" : "No") << endl;

    // Clear the map
    student_grades.clear();
    cout << "Map cleared." << endl;
    cout << "Final size: " << student_grades.size() << endl;

    return 0;
}
