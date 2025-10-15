#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    cout << "========== COMPREHENSIVE MULTIMAP DEMONSTRATION ==========" << endl << endl;

    // ===== 1. BASIC DIFFERENCE: MAP vs MULTIMAP =====
    cout << "1. MAP vs MULTIMAP: DUPLICATE KEYS" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Regular map (no duplicate keys):" << endl;
    map<string, int> regular_map;
    regular_map["apple"] = 10;
    regular_map["apple"] = 20;  // Overwrites previous value
    regular_map["apple"] = 30;  // Overwrites again
    regular_map["banana"] = 15;
    
    cout << "  After inserting 'apple' three times:" << endl;
    for (auto& p : regular_map) {
        cout << "    " << p.first << " -> " << p.second << endl;
    }
    cout << "  Size: " << regular_map.size() << " (only 2 keys)\n\n";
    
    cout << "Multimap (allows duplicate keys):" << endl;
    multimap<string, int> multi_map;
    multi_map.insert({"apple", 10});
    multi_map.insert({"apple", 20});  // Adds another entry
    multi_map.insert({"apple", 30});  // Adds another entry
    multi_map.insert({"banana", 15});
    
    cout << "  After inserting 'apple' three times:" << endl;
    for (auto& p : multi_map) {
        cout << "    " << p.first << " -> " << p.second << endl;
    }
    cout << "  Size: " << multi_map.size() << " (4 total entries)\n\n";

    // ===== 2. INSERTION METHODS =====
    cout << "2. INSERTION METHODS" << endl;
    cout << string(70, '-') << endl;
    
    multimap<int, string> grades;
    
    cout << "Using insert():" << endl;
    grades.insert({90, "Alice"});
    grades.insert({85, "Bob"});
    grades.insert({90, "Charlie"});  // Duplicate key OK
    grades.insert({78, "Diana"});
    grades.insert({90, "Eve"});      // Another duplicate
    
    cout << "  All insertions succeeded" << endl;
    cout << "  Total entries: " << grades.size() << "\n\n";
    
    cout << "Iterating multimap:" << endl;
    for (auto& p : grades) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";

    // ===== 3. FINDING DUPLICATE KEYS =====
    cout << "3. FINDING AND COUNTING DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multimap<string, int> inventory;
    inventory.insert({"apple", 50});
    inventory.insert({"banana", 30});
    inventory.insert({"apple", 40});
    inventory.insert({"cherry", 25});
    inventory.insert({"apple", 35});
    inventory.insert({"banana", 45});
    
    cout << "Inventory multimap:" << endl;
    for (auto& p : inventory) {
        cout << "  " << p.first << ": " << p.second << endl;
    }
    cout << "\n";
    
    cout << "count() - How many 'apple' entries?" << endl;
    int apple_count = inventory.count("apple");
    cout << "  Count: " << apple_count << "\n\n";
    
    cout << "find() - Find first 'apple':" << endl;
    auto it = inventory.find("apple");
    if (it != inventory.end()) {
        cout << "  First 'apple' value: " << it->second << "\n\n";
    }
    
    cout << "Iterate all 'apple' entries using find() + count():" << endl;
    it = inventory.find("apple");
    for (int i = 0; i < inventory.count("apple"); ++i) {
        cout << "    " << it->first << ": " << it->second << endl;
        ++it;
    }
    cout << "\n";

    // ===== 4. EQUAL_RANGE - THE POWER FEATURE =====
    cout << "4. EQUAL_RANGE - FINDING ALL DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multimap<int, string> scores;
    scores.insert({100, "Perfect"});
    scores.insert({85, "Good"});
    scores.insert({85, "Also Good"});
    scores.insert({85, "Still Good"});
    scores.insert({70, "Okay"});
    
    cout << "All entries:" << endl;
    for (auto& p : scores) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";
    
    cout << "Using equal_range(85) to find all entries with key 85:" << endl;
    auto range = scores.equal_range(85);
    cout << "  Range contains:" << endl;
    for (auto iter = range.first; iter != range.second; ++iter) {
        cout << "    " << iter->first << " -> " << iter->second << endl;
    }
    cout << "  Distance: " << distance(range.first, range.second) << " entries\n\n";

    // ===== 5. LOWER_BOUND AND UPPER_BOUND =====
    cout << "5. LOWER_BOUND vs UPPER_BOUND WITH DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multimap<int, char> data;
    for (char c : {'A', 'B', 'C', 'D'}) {
        data.insert({10, c});
        data.insert({20, c});
        data.insert({30, c});
    }
    
    cout << "All entries:" << endl;
    for (auto& p : data) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";
    
    cout << "lower_bound(20) - first >= 20:" << endl;
    auto lower = data.lower_bound(20);
    for (int i = 0; i < 5 && lower != data.end(); ++i, ++lower) {
        cout << "  " << lower->first << " -> " << lower->second << endl;
    }
    
    cout << "\nupper_bound(20) - first > 20:" << endl;
    auto upper = data.upper_bound(20);
    for (int i = 0; i < 5 && upper != data.end(); ++i, ++upper) {
        cout << "  " << upper->first << " -> " << upper->second << endl;
    }
    cout << "\n";

    // ===== 6. ERASING ENTRIES =====
    cout << "6. ERASING ENTRIES" << endl;
    cout << string(70, '-') << endl;
    
    multimap<string, int> phone_book;
    phone_book.insert({"Alice", 1001});
    phone_book.insert({"Bob", 1002});
    phone_book.insert({"Alice", 1003});  // Alice has 2 numbers
    phone_book.insert({"Charlie", 1004});
    phone_book.insert({"Alice", 1005});  // Alice has 3 numbers
    
    cout << "Original phone book:" << endl;
    for (auto& p : phone_book) {
        cout << "  " << p.first << ": " << p.second << endl;
    }
    cout << "  Size: " << phone_book.size() << "\n\n";
    
    cout << "Erase single entry (first 'Alice'):" << endl;
    phone_book.erase(phone_book.find("Alice"));
    
    cout << "After erasing:" << endl;
    for (auto& p : phone_book) {
        cout << "  " << p.first << ": " << p.second << endl;
    }
    cout << "  Size: " << phone_book.size() << "\n\n";
    
    cout << "Erase all entries with key 'Alice':" << endl;
    size_t erased = phone_book.erase("Alice");
    cout << "  Entries erased: " << erased << "\n";
    
    cout << "After erasing all 'Alice':" << endl;
    for (auto& p : phone_book) {
        cout << "  " << p.first << ": " << p.second << endl;
    }
    cout << "  Size: " << phone_book.size() << "\n\n";

    // ===== 7. REAL-WORLD EXAMPLE: STUDENT GRADES =====
    cout << "7. REAL-WORLD EXAMPLE: STUDENT GRADES BY SCORE" << endl;
    cout << string(70, '-') << endl;
    
    multimap<int, string> students_by_grade;
    students_by_grade.insert({95, "Alice"});
    students_by_grade.insert({87, "Bob"});
    students_by_grade.insert({95, "Charlie"});
    students_by_grade.insert({92, "Diana"});
    students_by_grade.insert({95, "Eve"});
    students_by_grade.insert({87, "Frank"});
    students_by_grade.insert({88, "Grace"});
    
    cout << "Students sorted by grade (multimap keeps duplicates sorted):" << endl;
    for (auto& p : students_by_grade) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";
    
    cout << "Students with grade 95:" << endl;
    auto range95 = students_by_grade.equal_range(95);
    for (auto it = range95.first; it != range95.second; ++it) {
        cout << "  " << it->second << " (score: " << it->first << ")" << endl;
    }
    cout << "\n";
    
    cout << "Students with grade 87:" << endl;
    auto range87 = students_by_grade.equal_range(87);
    for (auto it = range87.first; it != range87.second; ++it) {
        cout << "  " << it->second << " (score: " << it->first << ")" << endl;
    }
    cout << "\n\n";

    // ===== 8. MULTIMAP vs MULTIUNORDERED_MAP =====
    cout << "8. MULTIMAP vs UNORDERED_MULTIMAP" << endl;
    cout << string(70, '-') << endl;
    
    cout << "multimap (sorted by key):" << endl;
    multimap<int, string> mmap;
    mmap.insert({3, "three"});
    mmap.insert({1, "one"});
    mmap.insert({3, "THREE"});
    mmap.insert({2, "two"});
    
    for (auto& p : mmap) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    
    cout << "\nunordered_multimap (arbitrary order):" << endl;
    unordered_multimap<int, string> ummap;
    ummap.insert({3, "three"});
    ummap.insert({1, "one"});
    ummap.insert({3, "THREE"});
    ummap.insert({2, "two"});
    
    for (auto& p : ummap) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";

    // ===== 9. COMPARISON TABLE =====
    cout << "9. QUICK COMPARISON TABLE" << endl;
    cout << string(70, '-') << endl;
    cout << "Feature              | map    | multimap  | unordered_map | unordered_multimap\n";
    cout << string(70, '-') << endl;
    cout << "Duplicate keys       | No     | Yes       | No            | Yes\n";
    cout << "Sorted order         | Yes    | Yes       | No            | No\n";
    cout << "operator[]           | Yes    | No        | Yes           | No\n";
    cout << "Insertion complexity | O(log) | O(log)    | O(1) avg      | O(1) avg\n";
    cout << "Lookup complexity    | O(log) | O(log)    | O(1) avg      | O(1) avg\n";
    cout << "Range queries        | Yes    | Yes       | No            | No\n";
    cout << "equal_range()        | Yes    | Yes       | Yes           | Yes\n\n";

    // ===== 10. USE CASES =====
    cout << "10. WHEN TO USE MULTIMAP" << endl;
    cout << string(70, '-') << endl;
    cout << "Use multimap when:" << endl;
    cout << "  • Need to store multiple values for the same key\n";
    cout << "  • Want keys in sorted order\n";
    cout << "  • Need range queries on duplicate keys\n";
    cout << "  • Examples:\n";
    cout << "    - Phone book (person -> multiple numbers)\n";
    cout << "    - Word index (word -> line numbers)\n";
    cout << "    - Student records (grade -> students)\n";
    cout << "    - Event log (timestamp -> multiple events)\n";
    cout << "    - Dictionary (word -> definitions)\n\n";
    
    cout << "Use unordered_multimap when:" << endl;
    cout << "  • Need fast O(1) lookup with duplicates\n";
    cout << "  • Don't need sorted order\n";
    cout << "  • Working with large datasets\n";
    cout << "  • Examples:\n";
    cout << "    - Hash map with collision handling\n";
    cout << "    - Tag -> items mapping\n";
    cout << "    - ID -> multiple records\n";

    return 0;
}