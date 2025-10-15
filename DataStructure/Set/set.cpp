#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

int main() {
    cout << "========== COMPREHENSIVE SET DEMONSTRATION ==========" << endl << endl;

    // ===== 1. BASIC SET - UNIQUE ELEMENTS =====
    cout << "1. SET BASICS - UNIQUE ELEMENTS ONLY" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Vector (allows duplicates):" << endl;
    vector<int> vec = {5, 2, 8, 2, 9, 5, 1, 8};
    cout << "  Original: ";
    for (int v : vec) cout << v << " ";
    cout << "\n  Size: " << vec.size() << "\n\n";
    
    cout << "Set (automatically removes duplicates):" << endl;
    set<int> s(vec.begin(), vec.end());
    cout << "  From vector: ";
    for (int v : s) cout << v << " ";
    cout << "\n  Size: " << s.size() << "\n";
    cout << "  Notice: Duplicates removed AND sorted!\n\n";

    // ===== 2. INSERTION AND DUPLICATES =====
    cout << "2. INSERTION BEHAVIOR WITH DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    set<int> numbers;
    cout << "Inserting: 10, 20, 15, 20, 5, 15, 10" << endl;
    
    auto result1 = numbers.insert(10);
    cout << "  insert(10): Success=" << result1.second << ", Value=" << *result1.first << endl;
    
    auto result2 = numbers.insert(20);
    cout << "  insert(20): Success=" << result2.second << ", Value=" << *result2.first << endl;
    
    numbers.insert(15);
    
    auto result3 = numbers.insert(20);  // Duplicate
    cout << "  insert(20) again: Success=" << result3.second << " (duplicate rejected!)" << endl;
    
    numbers.insert(5);
    numbers.insert(15);  // Duplicate
    numbers.insert(10);  // Duplicate
    
    cout << "\nFinal set:" << endl;
    for (int n : numbers) cout << "  " << n << endl;
    cout << "  Size: " << numbers.size() << " (only 4 unique values)\n\n";

    // ===== 3. SORTED ORDER =====
    cout << "3. SORTED ORDER (Red-Black Tree)" << endl;
    cout << string(70, '-') << endl;
    
    set<string> colors;
    colors.insert("red");
    colors.insert("blue");
    colors.insert("green");
    colors.insert("yellow");
    colors.insert("purple");
    colors.insert("orange");
    
    cout << "Insertion order: red, blue, green, yellow, purple, orange" << endl;
    cout << "Set storage order (sorted):" << endl;
    for (const auto& c : colors) {
        cout << "  " << c << endl;
    }
    cout << "\n";

    // ===== 4. ITERATOR PROPERTIES =====
    cout << "4. ITERATOR TYPES" << endl;
    cout << string(70, '-') << endl;
    
    set<int> nums = {10, 20, 30, 40, 50};
    
    cout << "Forward iteration:" << endl;
    cout << "  ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << " ";
    }
    
    cout << "\nReverse iteration:" << endl;
    cout << "  ";
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        cout << *it << " ";
    }
    
    cout << "\n\nBidirectional iteration:" << endl;
    auto it = nums.find(30);
    cout << "  Start at 30: ";
    for (int i = 0; i < 2 && it != nums.end(); ++i, ++it) {
        cout << *it << " ";
    }
    cout << "\n  Back one: ";
    --it;
    cout << *it << "\n\n";

    // ===== 5. FIND, COUNT, LOWER_BOUND =====
    cout << "5. SEARCH OPERATIONS" << endl;
    cout << string(70, '-') << endl;
    
    set<int> data = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    
    cout << "Set: ";
    for (int d : data) cout << d << " ";
    cout << "\n\n";
    
    cout << "find(40):" << endl;
    auto found = data.find(40);
    if (found != data.end()) {
        cout << "  Found: " << *found << "\n\n";
    }
    
    cout << "find(45) (doesn't exist):" << endl;
    auto not_found = data.find(45);
    cout << "  Result: " << (not_found == data.end() ? "not found" : "found") << "\n\n";
    
    cout << "count(40):" << endl;
    cout << "  Count: " << data.count(40) << " (always 0 or 1)\n\n";
    
    cout << "lower_bound(35) - first >= 35:" << endl;
    auto lower = data.lower_bound(35);
    cout << "  Element: " << *lower << "\n\n";
    
    cout << "upper_bound(50) - first > 50:" << endl;
    auto upper = data.upper_bound(50);
    cout << "  Element: " << *upper << "\n\n";
    
    cout << "equal_range(40):" << endl;
    auto range = data.equal_range(40);
    cout << "  Range contains: " << *range.first << endl;
    cout << "  Next element after range: " << *range.second << "\n\n";

    // ===== 6. SET OPERATIONS =====
    cout << "6. SET OPERATIONS (union, intersection, difference)" << endl;
    cout << string(70, '-') << endl;
    
    set<int> setA = {1, 2, 3, 4, 5};
    set<int> setB = {3, 4, 5, 6, 7};
    
    cout << "Set A: ";
    for (int a : setA) cout << a << " ";
    cout << "\nSet B: ";
    for (int b : setB) cout << b << " ";
    cout << "\n\n";
    
    // Union
    set<int> unionSet;
    set_union(setA.begin(), setA.end(),
              setB.begin(), setB.end(),
              inserter(unionSet, unionSet.begin()));
    
    cout << "Union (A ∪ B): ";
    for (int u : unionSet) cout << u << " ";
    cout << "\n\n";
    
    // Intersection
    set<int> intersectionSet;
    set_intersection(setA.begin(), setA.end(),
                     setB.begin(), setB.end(),
                     inserter(intersectionSet, intersectionSet.begin()));
    
    cout << "Intersection (A ∩ B): ";
    for (int i : intersectionSet) cout << i << " ";
    cout << "\n\n";
    
    // Difference
    set<int> diffSet;
    set_difference(setA.begin(), setA.end(),
                   setB.begin(), setB.end(),
                   inserter(diffSet, diffSet.begin()));
    
    cout << "Difference (A - B): ";
    for (int d : diffSet) cout << d << " ";
    cout << "\n\n";

    // ===== 7. ERASE OPERATIONS =====
    cout << "7. ERASING ELEMENTS" << endl;
    cout << string(70, '-') << endl;
    
    set<string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    cout << "Original set:" << endl;
    for (const auto& w : words) cout << "  " << w << endl;
    cout << "  Size: " << words.size() << "\n\n";
    
    cout << "Erase by value (cherry):" << endl;
    words.erase("cherry");
    for (const auto& w : words) cout << "  " << w << endl;
    cout << "  Size: " << words.size() << "\n\n";
    
    cout << "Erase by iterator (first element):" << endl;
    words.erase(words.begin());
    for (const auto& w : words) cout << "  " << w << endl;
    cout << "  Size: " << words.size() << "\n\n";
    
    cout << "Erase range (remove 2 elements from position 1):" << endl;
    auto start_it = words.begin();
    ++start_it;
    words.erase(start_it, words.end());
    for (const auto& w : words) cout << "  " << w << endl;
    cout << "  Size: " << words.size() << "\n\n";

    // ===== 8. SET vs UNORDERED_SET =====
    cout << "8. SET vs UNORDERED_SET" << endl;
    cout << string(70, '-') << endl;
    
    cout << "set (sorted):" << endl;
    set<int> sorted_set = {50, 20, 80, 10, 40};
    cout << "  Insertion: 50, 20, 80, 10, 40" << endl;
    cout << "  Storage: ";
    for (int s : sorted_set) cout << s << " ";
    cout << "\n\n";
    
    cout << "unordered_set (arbitrary):" << endl;
    unordered_set<int> unsorted_set = {50, 20, 80, 10, 40};
    cout << "  Insertion: 50, 20, 80, 10, 40" << endl;
    cout << "  Storage: ";
    for (int u : unsorted_set) cout << u << " ";
    cout << "\n\n";

    // ===== 9. PERFORMANCE COMPARISON =====
    cout << "9. PERFORMANCE COMPARISON (1,000,000 operations)" << endl;
    cout << string(70, '-') << endl;
    
    const int N = 1000000;
    
    // set insertion
    auto start = chrono::high_resolution_clock::now();
    set<int> set_perf;
    for (int i = 0; i < N; i++) {
        set_perf.insert(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto set_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // unordered_set insertion
    start = chrono::high_resolution_clock::now();
    unordered_set<int> uset_perf;
    for (int i = 0; i < N; i++) {
        uset_perf.insert(i);
    }
    end = chrono::high_resolution_clock::now();
    auto uset_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "INSERTION:" << endl;
    cout << "  set:            " << set_insert << " μs (O(log n))" << endl;
    cout << "  unordered_set:  " << uset_insert << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (uset_insert < set_insert ? "unordered_set" : "set") << "\n\n";
    
    // set find
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        set_perf.find(i);
    }
    end = chrono::high_resolution_clock::now();
    auto set_find = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // unordered_set find
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        uset_perf.find(i);
    }
    end = chrono::high_resolution_clock::now();
    auto uset_find = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "FIND (100,000 lookups):" << endl;
    cout << "  set:            " << set_find << " μs (O(log n))" << endl;
    cout << "  unordered_set:  " << uset_find << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (uset_find < set_find ? "unordered_set" : "set") << "\n\n";

    // ===== 10. CUSTOM DATA TYPES =====
    cout << "10. CUSTOM DATA TYPES IN SET" << endl;
    cout << string(70, '-') << endl;
    
    struct Person {
        string name;
        int age;
        
        bool operator<(const Person& other) const {
            return name < other.name;  // Sort by name
        }
    };
    
    set<Person> people;
    people.insert({"Charlie", 30});
    people.insert({"Alice", 25});
    people.insert({"Bob", 28});
    people.insert({"Alice", 26});  // Duplicate name, different age
    
    cout << "Person set (sorted by name):" << endl;
    for (const auto& p : people) {
        cout << "  " << p.name << " (age " << p.age << ")" << endl;
    }
    cout << "  Size: " << people.size() << " (Alice appears once)\n\n";

    // ===== 11. REAL-WORLD EXAMPLES =====
    cout << "11. REAL-WORLD EXAMPLES" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Example 1: Remove duplicates from list" << endl;
    vector<int> nums_with_dups = {5, 2, 8, 2, 9, 5, 1, 8, 3};
    set<int> unique_nums(nums_with_dups.begin(), nums_with_dups.end());
    cout << "  Original: ";
    for (int n : nums_with_dups) cout << n << " ";
    cout << "\n  Unique: ";
    for (int n : unique_nums) cout << n << " ";
    cout << "\n\n";
    
    cout << "Example 2: Check if element exists" << endl;
    set<string> allowed_colors = {"red", "blue", "green"};
    string user_color = "blue";
    if (allowed_colors.count(user_color)) {
        cout << "  '" << user_color << "' is allowed" << endl;
    } else {
        cout << "  '" << user_color << "' is NOT allowed" << endl;
    }
    cout << "\n";
    
    cout << "Example 3: Finding unique elements in range" << endl;
    set<int> range_set;
    for (int i = 1; i <= 10; i++) {
        range_set.insert(i % 4);  // Values 0, 1, 2, 3
    }
    cout << "  Unique values from modulo operation: ";
    for (int r : range_set) cout << r << " ";
    cout << "\n\n";

    // ===== 12. COMPARISON TABLE =====
    cout << "12. SET CONTAINERS COMPARISON TABLE" << endl;
    cout << string(70, '-') << endl;
    cout << "Feature              | set    | unordered_set | multiset   | unordered_multiset\n";
    cout << string(70, '-') << endl;
    cout << "Unique elements      | Yes    | Yes           | No         | No\n";
    cout << "Sorted               | Yes    | No            | Yes        | No\n";
    cout << "Insert complexity    | O(log) | O(1) avg      | O(log)     | O(1) avg\n";
    cout << "Find complexity      | O(log) | O(1) avg      | O(log)     | O(1) avg\n";
    cout << "Range queries        | Yes    | No            | Yes        | No\n";
    cout << "Reverse iteration    | Yes    | No            | Yes        | No\n";
    cout << "Lower/upper bound    | Yes    | No            | Yes        | No\n";
    cout << "Space overhead       | Low    | High          | Low        | High\n";
    cout << "Cache friendly       | Yes    | No            | Yes        | No\n\n";

    // ===== 13. WHEN TO USE SET =====
    cout << "13. WHEN TO USE SET" << endl;
    cout << string(70, '-') << endl;
    cout << "Use set when:" << endl;
    cout << "  • Need unique elements only\n";
    cout << "  • Want elements automatically sorted\n";
    cout << "  • Need range queries or lower/upper bounds\n";
    cout << "  • Predictable O(log n) performance required\n";
    cout << "  • Examples:\n";
    cout << "    - Removing duplicates while maintaining order\n";
    cout << "    - Student IDs (unique, sorted)\n";
    cout << "    - Allowed/forbidden items\n";
    cout << "    - Lexicographically sorted list\n";
    cout << "    - Finding closest values\n\n";
    
    cout << "Use unordered_set when:" << endl;
    cout << "  • Need O(1) average lookup for unique elements\n";
    cout << "  • Don't care about order\n";
    cout << "  • Working with large datasets\n";
    cout << "  • Examples:\n";
    cout << "    - Membership testing (visited nodes)\n";
    cout << "    - Deduplication on large data\n";
    cout << "    - Cache of seen items\n";
    cout << "    - Fast lookup without sorting\n";
    cout << "    - Skip list implementations\n";

    return 0;
}