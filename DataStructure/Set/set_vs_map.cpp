#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

int main() {
    cout << "========== SET vs MAP COMPREHENSIVE COMPARISON ==========" << endl << endl;

    // ===== 1. BASIC DIFFERENCE: WHAT THEY STORE =====
    cout << "1. BASIC DIFFERENCE: WHAT THEY STORE" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET - Stores only keys (single value):" << endl;
    set<int> numbers;
    numbers.insert(10);
    numbers.insert(20);
    numbers.insert(30);
    
    cout << "  set<int> numbers = {10, 20, 30}" << endl;
    cout << "  Iteration: ";
    for (int n : numbers) cout << n << " ";
    cout << "\n  Memory: Just the key" << endl;
    cout << "  Use: Membership testing, deduplication, unique elements\n\n";
    
    cout << "MAP - Stores key-value pairs:" << endl;
    map<int, string> phone_book;
    phone_book[1] = "Alice";
    phone_book[2] = "Bob";
    phone_book[3] = "Charlie";
    
    cout << "  map<int, string> phone_book" << endl;
    cout << "  phone_book[1] = \"Alice\"" << endl;
    cout << "  Iteration: ";
    for (auto p : phone_book) cout << "(" << p.first << "=" << p.second << ") ";
    cout << "\n  Memory: Key + Value" << endl;
    cout << "  Use: Key-value associations, lookups, data association\n\n";

    // ===== 2. ELEMENT ACCESS =====
    cout << "2. ELEMENT ACCESS" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET - Direct element access:" << endl;
    set<string> fruits = {"apple", "banana", "cherry"};
    
    auto it = fruits.find("banana");
    if (it != fruits.end()) {
        cout << "  find(\"banana\"): " << *it << endl;
    }
    cout << "  No operator[] in set" << endl;
    cout << "  Access: Through iterators or count()/find()\n\n";
    
    cout << "MAP - Access via key:" << endl;
    map<string, int> prices;
    prices["apple"] = 50;
    prices["banana"] = 30;
    prices["cherry"] = 75;
    
    cout << "  prices[\"banana\"] = " << prices["banana"] << endl;
    cout << "  Can use operator[] to access values" << endl;
    cout << "  Also has find() and count() like set\n\n";

    // ===== 3. MODIFICATION BEHAVIOR =====
    cout << "3. MODIFICATION BEHAVIOR" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET - Insert returns pair<iterator, bool>:" << endl;
    set<int> s;
    
    auto result1 = s.insert(100);
    cout << "  insert(100): success=" << result1.second;
    cout << ", value=" << *result1.first << endl;
    
    auto result2 = s.insert(100);
    cout << "  insert(100) again: success=" << result2.second << " (duplicate rejected)" << endl;
    cout << "  Size: " << s.size() << "\n\n";
    
    cout << "MAP - operator[] creates if doesn't exist:" << endl;
    map<int, string> m;
    m[1] = "one";
    m[2] = "two";
    cout << "  m[1] = \"one\", m[2] = \"two\"" << endl;
    cout << "  Size: " << m.size() << endl;
    
    cout << "  Accessing non-existent key m[3]:" << endl;
    string val = m[3];  // Creates default value
    cout << "  m[3] = \"" << val << "\" (empty string created)" << endl;
    cout << "  Size: " << m.size() << " (increased!)" << endl;
    cout << "  To avoid this, use find() or count() instead\n\n";

    // ===== 4. ITERATION =====
    cout << "4. ITERATION" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET - Iterate over single values:" << endl;
    set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    cout << "  for (char v : vowels): ";
    for (char v : vowels) cout << v << " ";
    cout << "\n\n";
    
    cout << "MAP - Iterate over key-value pairs:" << endl;
    map<char, int> letter_count;
    letter_count['a'] = 2;
    letter_count['e'] = 3;
    letter_count['i'] = 1;
    
    cout << "  for (auto p : letter_count):" << endl;
    for (auto p : letter_count) {
        cout << "    " << p.first << " -> " << p.second << endl;
    }
    cout << "  p.first = key, p.second = value\n\n";

    // ===== 5. SEARCHING =====
    cout << "5. SEARCHING" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET - Check if element exists:" << endl;
    set<string> allowed = {"admin", "user", "guest"};
    
    string role = "user";
    cout << "  allowed.count(\"user\"): " << allowed.count(role);
    cout << " (0 or 1)" << endl;
    cout << "  if (allowed.count(role)) { /* allowed */ }" << endl;
    cout << "  Use: Permission checking, membership\n\n";
    
    cout << "MAP - Look up associated value:" << endl;
    map<string, int> age_map;
    age_map["Alice"] = 25;
    age_map["Bob"] = 30;
    age_map["Charlie"] = 28;
    
    if (age_map.find("Bob") != age_map.end()) {
        cout << "  Bob's age: " << age_map["Bob"] << endl;
    }
    cout << "  Use: Dictionary, phonebook, scoring\n\n";

    // ===== 6. MEMORY EFFICIENCY =====
    cout << "6. MEMORY EFFICIENCY" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET - Stores only key:" << endl;
    cout << "  set<int>: ~24 bytes per element (overhead)" << endl;
    cout << "  Each element: 4 bytes (int) + overhead" << endl;
    cout << "  Total for 1000 elements: ~24KB + overhead\n\n";
    
    cout << "MAP - Stores key + value:" << endl;
    cout << "  map<int, string>: More memory" << endl;
    cout << "  Each element: 4 bytes (key) + 24+ bytes (string) + overhead" << endl;
    cout << "  Total for 1000 elements: ~28+KB + overhead" << endl;
    cout << "  Verdict: SET is more memory efficient for just unique values\n\n";

    // ===== 7. PRACTICAL EXAMPLES =====
    cout << "7. PRACTICAL EXAMPLES" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Example 1: SET for visited websites" << endl;
    set<string> visited_urls;
    visited_urls.insert("google.com");
    visited_urls.insert("github.com");
    visited_urls.insert("google.com");  // Duplicate ignored
    
    cout << "  Visited: ";
    for (const auto& url : visited_urls) cout << url << " ";
    cout << "\n  Size: " << visited_urls.size() << " (unique URLs)\n\n";
    
    cout << "Example 2: MAP for browser history" << endl;
    map<string, int> visit_count;
    visit_count["google.com"]++;
    visit_count["github.com"]++;
    visit_count["google.com"]++;
    
    cout << "  Visit counts:" << endl;
    for (auto p : visit_count) {
        cout << "    " << p.first << ": " << p.second << " times" << endl;
    }
    cout << "\n";
    
    cout << "Example 3: SET for student IDs (no duplicates)" << endl;
    set<int> enrolled_students;
    enrolled_students.insert(1001);
    enrolled_students.insert(1002);
    enrolled_students.insert(1001);  // Rejected
    enrolled_students.insert(1003);
    
    cout << "  Total unique: " << enrolled_students.size() << "\n\n";
    
    cout << "Example 4: MAP for student records" << endl;
    map<int, string> student_names;
    student_names[1001] = "Alice";
    student_names[1002] = "Bob";
    student_names[1003] = "Charlie";
    
    cout << "  Find student 1002: " << student_names[1002] << "\n\n";

    // ===== 8. SET OPERATIONS (SET ONLY) =====
    cout << "8. SET-SPECIFIC OPERATIONS" << endl;
    cout << string(70, '-') << endl;
    
    cout << "SET exclusive features:" << endl;
    set<int> set1 = {1, 2, 3, 4, 5};
    set<int> set2 = {3, 4, 5, 6, 7};
    
    cout << "  set1: ";
    for (int x : set1) cout << x << " ";
    cout << "\n  set2: ";
    for (int x : set2) cout << x << " ";
    cout << "\n\n";
    
    cout << "  Union: ";
    set<int> unionSet;
    set_union(set1.begin(), set1.end(),
              set2.begin(), set2.end(),
              inserter(unionSet, unionSet.begin()));
    for (int x : unionSet) cout << x << " ";
    
    cout << "\n  Intersection: ";
    set<int> intersection;
    set_intersection(set1.begin(), set1.end(),
                     set2.begin(), set2.end(),
                     inserter(intersection, intersection.begin()));
    for (int x : intersection) cout << x << " ";
    
    cout << "\n  Difference: ";
    set<int> difference;
    set_difference(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   inserter(difference, difference.begin()));
    for (int x : difference) cout << x << " ";
    cout << "\n\n";

    // ===== 9. PERFORMANCE COMPARISON =====
    cout << "9. PERFORMANCE COMPARISON (1,000,000 operations)" << endl;
    cout << string(70, '-') << endl;
    
    // SET insertion
    auto start = chrono::high_resolution_clock::now();
    set<int> perf_set;
    for (int i = 0; i < 1000000; i++) {
        perf_set.insert(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto set_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // MAP insertion
    start = chrono::high_resolution_clock::now();
    map<int, int> perf_map;
    for (int i = 0; i < 1000000; i++) {
        perf_map[i] = i * 2;
    }
    end = chrono::high_resolution_clock::now();
    auto map_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "SET vs MAP insertion time:" << endl;
    cout << "  set<int> insert 1M:   " << set_insert << " μs" << endl;
    cout << "  map<int,int> insert 1M: " << map_insert << " μs" << endl;
    cout << "  Difference: " << (map_insert > set_insert ? "MAP slower" : "SET slower");
    cout << " (storing extra value takes time)\n\n";

    // ===== 10. WHEN TO USE WHICH =====
    cout << "10. DECISION GUIDE: WHEN TO USE WHICH" << endl;
    cout << string(70, '-') << endl;
    
    cout << "Use SET when:" << endl;
    cout << "  ✓ You only need unique elements" << endl;
    cout << "  ✓ No association with other data" << endl;
    cout << "  ✓ Need membership testing" << endl;
    cout << "  ✓ Need set operations (union, intersection)" << endl;
    cout << "  ✓ Memory efficiency matters" << endl;
    cout << "  Examples: allowed_users, visited_pages, unique_ids\n\n";
    
    cout << "Use MAP when:" << endl;
    cout << "  ✓ Need key-value associations" << endl;
    cout << "  ✓ Look up value from key" << endl;
    cout << "  ✓ Store related data together" << endl;
    cout << "  ✓ Need operator[] convenience" << endl;
    cout << "  Examples: phonebook, config, scoring, translation\n\n";

    // ===== 11. COMPARISON TABLE =====
    cout << "11. QUICK COMPARISON TABLE" << endl;
    cout << string(70, '-') << endl;
    cout << "Feature              | set      | map\n";
    cout << string(70, '-') << endl;
    cout << "Stores               | Keys     | Key-value pairs\n";
    cout << "operator[]           | No       | Yes\n";
    cout << "Insert return        | pair<it,bool> | iterator\n";
    cout << "Memory per element   | Lower    | Higher\n";
    cout << "Iteration           | Values   | Pairs\n";
    cout << "Unique elements     | Yes      | Yes (keys)\n";
    cout << "Set operations      | Yes      | No\n";
    cout << "Use case            | Membership | Lookup/assoc\n";
    cout << "Complexity          | O(log n) | O(log n)\n\n";

    // ===== 12. COMMON MISTAKES =====
    cout << "12. COMMON MISTAKES" << endl;
    cout << string(70, '-') << endl;
    
    cout << "MISTAKE 1: Using map for just unique values" << endl;
    cout << "  Wrong:  map<int, bool> m; m[5] = true;" << endl;
    cout << "  Better: set<int> s; s.insert(5);" << endl;
    cout << "  Why: Wastes memory storing unnecessary booleans\n\n";
    
    cout << "MISTAKE 2: Using set when values needed" << endl;
    cout << "  Wrong:  set<int> scores; // Can't get by ID" << endl;
    cout << "  Better: map<int, int> scores; // ID -> score\n\n";
    
    cout << "MISTAKE 3: Using operator[] on map for checking" << endl;
    set<string> s_bad;
    map<string, int> m_bad;
    
    cout << "  Wrong:  if (m[\"key\"] != 0) // Creates entry if missing!" << endl;
    cout << "  Better: if (m.count(\"key\")) // Doesn't modify" << endl;
    cout << "  or:     if (m.find(\"key\") != m.end())\n\n";

    return 0;
}