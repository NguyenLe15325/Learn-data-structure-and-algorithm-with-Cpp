#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;

int main() {
    cout << "========== COMPREHENSIVE MULTISET DEMONSTRATION ==========" << endl << endl;

    // ===== 1. BASIC DIFFERENCE: SET vs MULTISET =====
    cout << "1. SET vs MULTISET: DUPLICATE ELEMENTS" << endl;
    cout << string(70, '-') << endl;
    
    cout << "set (no duplicates):" << endl;
    set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(10);  // Rejected
    s.insert(30);
    s.insert(20);  // Rejected
    
    cout << "  Inserted: 10, 20, 10, 30, 20" << endl;
    cout << "  Stored: ";
    for (int val : s) cout << val << " ";
    cout << "\n  Size: " << s.size() << "\n\n";
    
    cout << "multiset (allows duplicates):" << endl;
    multiset<int> ms;
    ms.insert(10);
    ms.insert(20);
    ms.insert(10);  // Accepted
    ms.insert(30);
    ms.insert(20);  // Accepted
    
    cout << "  Inserted: 10, 20, 10, 30, 20" << endl;
    cout << "  Stored: ";
    for (int val : ms) cout << val << " ";
    cout << "\n  Size: " << ms.size() << " (all elements kept, sorted)\n\n";

    // ===== 2. SORTED STORAGE WITH DUPLICATES =====
    cout << "2. SORTED ORDER WITH DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multiset<string> grades;
    grades.insert("A");
    grades.insert("C");
    grades.insert("A");
    grades.insert("B");
    grades.insert("A");
    grades.insert("B");
    grades.insert("D");
    
    cout << "Insertion order: A, C, A, B, A, B, D" << endl;
    cout << "Multiset storage (sorted with duplicates):" << endl;
    for (const auto& g : grades) {
        cout << "  " << g << endl;
    }
    cout << "\n";

    // ===== 3. INSERTION AND RETURN VALUES =====
    cout << "3. INSERTION BEHAVIOR" << endl;
    cout << string(70, '-') << endl;
    
    multiset<int> numbers;
    
    cout << "Multiset insert() returns iterator (not pair):" << endl;
    
    auto result1 = numbers.insert(100);
    cout << "  insert(100): value=" << *result1 << endl;
    
    auto result2 = numbers.insert(100);  // Duplicate
    cout << "  insert(100) again: value=" << *result2 << endl;
    
    numbers.insert(150);
    numbers.insert(50);
    
    cout << "  insert(150): value=" << *numbers.insert(150) << endl;
    cout << "  insert(50): value=" << *numbers.insert(50) << endl;
    
    cout << "\n  Note: Unlike set, multiset.insert() ALWAYS succeeds\n";
    cout << "  It always returns an iterator (never false)\n";
    cout << "  All elements in multiset: ";
    for (int n : numbers) cout << n << " ";
    cout << "\n\n";

    // ===== 4. COUNT AND FIND =====
    cout << "4. COUNTING AND FINDING DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multiset<int> scores;
    scores.insert(85);
    scores.insert(90);
    scores.insert(85);
    scores.insert(85);
    scores.insert(95);
    scores.insert(90);
    
    cout << "Multiset: ";
    for (int s : scores) cout << s << " ";
    cout << "\n\n";
    
    cout << "count(85): " << scores.count(85) << " occurrences" << endl;
    cout << "count(90): " << scores.count(90) << " occurrences" << endl;
    cout << "count(100): " << scores.count(100) << " occurrences\n\n";
    
    cout << "find(85) returns iterator to first 85:" << endl;
    auto it = scores.find(85);
    cout << "  First 85 found: " << *it << "\n\n";

    // ===== 5. EQUAL_RANGE - POWER FEATURE =====
    cout << "5. EQUAL_RANGE - FINDING ALL DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multiset<string> inventory;
    inventory.insert("apple");
    inventory.insert("banana");
    inventory.insert("apple");
    inventory.insert("cherry");
    inventory.insert("apple");
    inventory.insert("banana");
    
    cout << "Inventory: ";
    for (const auto& item : inventory) cout << item << " ";
    cout << "\n\n";
    
    cout << "equal_range(\"apple\"):" << endl;
    auto range = inventory.equal_range("apple");
    cout << "  All 'apple' entries:" << endl;
    for (auto iter = range.first; iter != range.second; ++iter) {
        cout << "    " << *iter << endl;
    }
    cout << "  Count: " << distance(range.first, range.second) << "\n\n";

    // ===== 6. LOWER_BOUND AND UPPER_BOUND =====
    cout << "6. LOWER_BOUND vs UPPER_BOUND WITH DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    multiset<int> values;
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < 3; j++) {
            values.insert(i * 10);
        }
    }
    
    cout << "Multiset: ";
    for (int v : values) cout << v << " ";
    cout << "\n\n";
    
    cout << "lower_bound(30) - first >= 30:" << endl;
    auto lower = values.lower_bound(30);
    cout << "  Element: " << *lower << "\n\n";
    
    cout << "upper_bound(30) - first > 30:" << endl;
    auto upper = values.upper_bound(30);
    cout << "  Element: " << *upper << "\n\n";
    
    cout << "All elements in range [30, 30] (equal_range):" << endl;
    auto erange = values.equal_range(30);
    cout << "  Elements: ";
    for (auto iter = erange.first; iter != erange.second; ++iter) {
        cout << *iter << " ";
    }
    cout << "\n\n";

    // ===== 7. ERASING ENTRIES =====
    cout << "7. ERASING ENTRIES" << endl;
    cout << string(70, '-') << endl;
    
    multiset<char> letters;
    for (char c : {'a', 'b', 'c', 'a', 'b', 'a'}) {
        letters.insert(c);
    }
    
    cout << "Original multiset: ";
    for (char l : letters) cout << l << " ";
    cout << "\n  Size: " << letters.size() << "\n\n";
    
    cout << "Erase one 'a' (by iterator):" << endl;
    letters.erase(letters.find('a'));
    cout << "  Result: ";
    for (char l : letters) cout << l << " ";
    cout << "\n  Size: " << letters.size() << "\n\n";
    
    cout << "Erase all 'a' entries:" << endl;
    size_t erased = letters.erase('a');
    cout << "  Entries erased: " << erased << endl;
    cout << "  Result: ";
    for (char l : letters) cout << l << " ";
    cout << "\n  Size: " << letters.size() << "\n\n";

    // ===== 8. ITERATOR PROPERTIES =====
    cout << "8. ITERATOR TYPES" << endl;
    cout << string(70, '-') << endl;
    
    multiset<int> nums = {10, 20, 20, 30, 30, 30};
    
    cout << "Forward iteration:" << endl;
    cout << "  ";
    for (auto val : nums) cout << val << " ";
    
    cout << "\n\nReverse iteration:" << endl;
    cout << "  ";
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        cout << *it << " ";
    }
    
    cout << "\n\nBidirectional (forward then back):" << endl;
    auto it_bi = nums.begin();
    advance(it_bi, 3);
    cout << "  At position 3: " << *it_bi << endl;
    --it_bi;
    cout << "  Step back: " << *it_bi << "\n\n";

    // ===== 9. MULTISET vs UNORDERED_MULTISET =====
    cout << "9. MULTISET vs UNORDERED_MULTISET" << endl;
    cout << string(70, '-') << endl;
    
    cout << "multiset (sorted):" << endl;
    multiset<int> mset;
    mset.insert(50);
    mset.insert(20);
    mset.insert(50);
    mset.insert(10);
    mset.insert(30);
    mset.insert(20);
    
    cout << "  Insertion: 50, 20, 50, 10, 30, 20" << endl;
    cout << "  Storage: ";
    for (int m : mset) cout << m << " ";
    cout << "\n\n";
    
    cout << "unordered_multiset (arbitrary):" << endl;
    unordered_multiset<int> umset;
    umset.insert(50);
    umset.insert(20);
    umset.insert(50);
    umset.insert(10);
    umset.insert(30);
    umset.insert(20);
    
    cout << "  Insertion: 50, 20, 50, 10, 30, 20" << endl;
    cout << "  Storage: ";
    for (int u : umset) cout << u << " ";
    cout << "\n\n";

    // ===== 10. PERFORMANCE COMPARISON =====
    cout << "10. PERFORMANCE COMPARISON (500,000 operations)" << endl;
    cout << string(70, '-') << endl;
    
    const int N = 500000;
    
    // multiset insertion
    auto start = chrono::high_resolution_clock::now();
    multiset<int> mset_perf;
    for (int i = 0; i < N; i++) {
        mset_perf.insert(i % 1000);  // Many duplicates
    }
    auto end = chrono::high_resolution_clock::now();
    auto mset_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // unordered_multiset insertion
    start = chrono::high_resolution_clock::now();
    unordered_multiset<int> umset_perf;
    for (int i = 0; i < N; i++) {
        umset_perf.insert(i % 1000);  // Many duplicates
    }
    end = chrono::high_resolution_clock::now();
    auto umset_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "INSERTION (500,000 entries with duplicates):" << endl;
    cout << "  multiset:             " << mset_insert << " μs (O(log n))" << endl;
    cout << "  unordered_multiset:   " << umset_insert << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (umset_insert < mset_insert ? "unordered_multiset" : "multiset") << "\n\n";
    
    // multiset find
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        mset_perf.find(i % 1000);
    }
    end = chrono::high_resolution_clock::now();
    auto mset_find = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // unordered_multiset find
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        umset_perf.find(i % 1000);
    }
    end = chrono::high_resolution_clock::now();
    auto umset_find = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "FIND (10,000 lookups):" << endl;
    cout << "  multiset:             " << mset_find << " μs (O(log n))" << endl;
    cout << "  unordered_multiset:   " << umset_find << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (umset_find < mset_find ? "unordered_multiset" : "multiset") << "\n\n";

    // ===== 11. REAL-WORLD EXAMPLE: FREQUENCY COUNTER =====
    cout << "11. REAL-WORLD EXAMPLE: WORD FREQUENCY COUNTER" << endl;
    cout << string(70, '-') << endl;
    
    string words_array[] = {"apple", "banana", "apple", "cherry", "banana", 
                            "apple", "date", "banana", "apple"};
    multiset<string> word_freq(words_array, words_array + 9);
    
    cout << "Words: ";
    for (const auto& w : word_freq) cout << w << " ";
    cout << "\n\n";
    
    cout << "Word frequencies (using multiset):" << endl;
    set<string> unique_words(word_freq.begin(), word_freq.end());
    for (const auto& word : unique_words) {
        cout << "  '" << word << "': " << word_freq.count(word) << " times" << endl;
    }
    cout << "\n";

    // ===== 12. REAL-WORLD EXAMPLE: TOP-K ELEMENTS =====
    cout << "12. REAL-WORLD EXAMPLE: TOP-K ELEMENTS" << endl;
    cout << string(70, '-') << endl;
    
    multiset<int> scores_list = {95, 87, 92, 88, 95, 85, 90, 95, 88, 92};
    
    cout << "All scores: ";
    for (int sc : scores_list) cout << sc << " ";
    cout << "\n\n";
    
    cout << "Top 5 highest scores (reverse iteration):" << endl;
    int count = 0;
    for (auto it = scores_list.rbegin(); it != scores_list.rend() && count < 5; ++it, ++count) {
        cout << "  " << *it << endl;
    }
    cout << "\n";
    
    cout << "Scores >= 90:" << endl;
    auto range90 = scores_list.lower_bound(90);
    for (auto it = range90; it != scores_list.end(); ++it) {
        cout << "  " << *it << endl;
    }
    cout << "\n";

    // ===== 13. CUSTOM DATA TYPES =====
    cout << "13. CUSTOM DATA TYPES IN MULTISET" << endl;
    cout << string(70, '-') << endl;
    
    struct Student {
        string name;
        int score;
        
        bool operator<(const Student& other) const {
            if (score != other.score) {
                return score > other.score;  // Higher score first (descending)
            }
            return name < other.name;  // Then alphabetically
        }
    };
    
    multiset<Student> students;
    students.insert({"Alice", 95});
    students.insert({"Bob", 88});
    students.insert({"Alice", 95});  // Duplicate
    students.insert({"Charlie", 92});
    students.insert({"Bob", 88});    // Duplicate
    
    cout << "Students (sorted by score desc, then name asc):" << endl;
    for (const auto& st : students) {
        cout << "  " << st.name << ": " << st.score << endl;
    }
    cout << "\n";

    // ===== 14. COMPARISON TABLE =====
    cout << "14. ALL SET CONTAINERS COMPARISON TABLE" << endl;
    cout << string(70, '-') << endl;
    cout << "Feature              | set    | multiset  | unordered_set | unordered_multiset\n";
    cout << string(70, '-') << endl;
    cout << "Unique elements      | Yes    | No        | Yes           | No\n";
    cout << "Sorted               | Yes    | Yes       | No            | No\n";
    cout << "Insert complexity    | O(log) | O(log)    | O(1) avg      | O(1) avg\n";
    cout << "Find complexity      | O(log) | O(log)    | O(1) avg      | O(1) avg\n";
    cout << "Range queries        | Yes    | Yes       | No            | No\n";
    cout << "Reverse iteration    | Yes    | Yes       | No            | No\n";
    cout << "Lower/upper bound    | Yes    | Yes       | No            | No\n";
    cout << "Space overhead       | Low    | Low       | High          | High\n";
    cout << "Cache friendly       | Yes    | Yes       | No            | No\n\n";

    // ===== 15. WHEN TO USE MULTISET =====
    cout << "15. WHEN TO USE MULTISET" << endl;
    cout << string(70, '-') << endl;
    cout << "Use multiset when:" << endl;
    cout << "  • Need to store duplicate elements\n";
    cout << "  • Want elements automatically sorted\n";
    cout << "  • Need range queries or bounds\n";
    cout << "  • Predictable O(log n) performance required\n";
    cout << "  • Examples:\n";
    cout << "    - Frequency counting (word/score frequency)\n";
    cout << "    - Sorted list with allowed duplicates\n";
    cout << "    - Top-K elements\n";
    cout << "    - Priority queue (sorted elements)\n";
    cout << "    - Test scores with duplicates\n";
    cout << "    - Event timestamps\n";
    cout << "    - Grading system (multiple students per grade)\n\n";
    
    cout << "Use unordered_multiset when:" << endl;
    cout << "  • Need O(1) average lookup with duplicates\n";
    cout << "  • Don't care about order\n";
    cout << "  • Working with very large datasets\n";
    cout << "  • Examples:\n";
    cout << "    - Fast deduplication with counts\n";
    cout << "    - Element frequency analysis on huge data\n";
    cout << "    - Duplicate detection\n";
    cout << "    - Collision handling in hash tables\n";
    cout << "    - Group by on large unordered data\n";

    return 0;
}
