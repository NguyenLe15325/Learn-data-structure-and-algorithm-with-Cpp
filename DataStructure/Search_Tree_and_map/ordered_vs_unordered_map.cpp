#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>
#include <string>
#include <algorithm>
using namespace std;

// Custom class for demonstrating custom key types
struct Person {
    string name;
    int age;
    
    Person() = default;
    Person(string n, int a) : name(n), age(a) {}
    
    // Required for map (operator<)
    bool operator<(const Person& other) const {
        return name < other.name;
    }
    
    // Required for unordered_map (hash and equality)
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// Hash function for Person
struct PersonHash {
    size_t operator()(const Person& p) const {
        return hash<string>()(p.name) ^ (hash<int>()(p.age) << 1);
    }
};

int main() {
    cout << "========== COMPREHENSIVE MAP vs UNORDERED_MAP DEMONSTRATION ==========" << endl << endl;

    // ===== 1. ORDERING DEMONSTRATION =====
    cout << "1. INSERTION ORDER vs SORTED ORDER" << endl;
    cout << string(60, '-') << endl;
    
    int keys[] = {15, 3, 9, 1, 12, 5, 20, 7};
    
    cout << "Insertion order: ";
    for (int k : keys) cout << k << " ";
    cout << "\n\n--- map (Red-Black Tree - SORTED) ---" << endl;
    
    map<int, string> m;
    for (int k : keys) {
        m[k] = "value_" + to_string(k);
    }
    
    for (auto& p : m) {
        cout << p.first << " ";
    }
    cout << "\n\n--- unordered_map (Hash Table - ARBITRARY) ---" << endl;
    
    unordered_map<int, string> um;
    for (int k : keys) {
        um[k] = "value_" + to_string(k);
    }
    
    for (auto& p : um) {
        cout << p.first << " ";
    }
    cout << "\n\n";

    // ===== 2. ITERATOR CHARACTERISTICS =====
    cout << "2. ITERATOR PROPERTIES" << endl;
    cout << string(60, '-') << endl;
    cout << "map: Bidirectional iterators (can go forward AND backward)" << endl;
    
    map<int, int> m_iter;
    for (int i = 1; i <= 5; i++) m_iter[i] = i * 10;
    
    cout << "Forward:  ";
    for (auto it = m_iter.begin(); it != m_iter.end(); ++it) {
        cout << it->first << " ";
    }
    
    cout << "\nBackward: ";
    for (auto it = m_iter.rbegin(); it != m_iter.rend(); ++it) {
        cout << it->first << " ";
    }
    
    cout << "\n\nunordered_map: Forward iterators only (can only go forward)" << endl;
    unordered_map<int, int> um_iter;
    for (int i = 1; i <= 5; i++) um_iter[i] = i * 10;
    
    cout << "Forward:  ";
    for (auto it = um_iter.begin(); it != um_iter.end(); ++it) {
        cout << it->first << " ";
    }
    cout << "(reverse iteration not available)\n\n";

    // ===== 3. RANGE QUERIES =====
    cout << "3. RANGE QUERIES (map only feature)" << endl;
    cout << string(60, '-') << endl;
    
    map<int, string> m_range;
    for (int i : {10, 20, 30, 40, 50, 60, 70, 80, 90}) {
        m_range[i] = "val_" + to_string(i);
    }
    
    cout << "All elements: ";
    for (auto& p : m_range) cout << p.first << " ";
    cout << "\n\n";
    
    cout << "lower_bound(35) - first >= 35:" << endl;
    auto it_lower = m_range.lower_bound(35);
    for (auto it = it_lower; it != m_range.end() && it->first <= 75; ++it) {
        cout << it->first << " ";
    }
    
    cout << "\n\nupper_bound(50) - first > 50:" << endl;
    auto it_upper = m_range.upper_bound(50);
    for (auto it = it_upper; it != m_range.end() && it->first <= 85; ++it) {
        cout << it->first << " ";
    }
    
    cout << "\n\nequal_range(40) - all elements == 40:" << endl;
    auto range = m_range.equal_range(40);
    if (range.first != range.second) {
        cout << "Found: " << range.first->first << endl;
    }
    cout << "\n";

    // ===== 4. PERFORMANCE COMPARISON =====
    cout << "4. PERFORMANCE COMPARISON (1,000,000 operations)" << endl;
    cout << string(60, '-') << endl;
    
    const int N = 1000000;
    
    // MAP - INSERT
    auto start = chrono::high_resolution_clock::now();
    map<int, int> m_perf;
    for (int i = 0; i < N; i++) {
        m_perf[i] = i * 2;
    }
    auto end = chrono::high_resolution_clock::now();
    auto map_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // UNORDERED_MAP - INSERT
    start = chrono::high_resolution_clock::now();
    unordered_map<int, int> um_perf;
    for (int i = 0; i < N; i++) {
        um_perf[i] = i * 2;
    }
    end = chrono::high_resolution_clock::now();
    auto umap_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "INSERTION:" << endl;
    cout << "  map:            " << map_insert << " μs (O(log n))" << endl;
    cout << "  unordered_map:  " << umap_insert << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (umap_insert < map_insert ? "unordered_map" : "map") << endl;
    
    // MAP - LOOKUP
    start = chrono::high_resolution_clock::now();
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += m_perf[i];
    }
    end = chrono::high_resolution_clock::now();
    auto map_lookup = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // UNORDERED_MAP - LOOKUP
    start = chrono::high_resolution_clock::now();
    sum = 0;
    for (int i = 0; i < N; i++) {
        sum += um_perf[i];
    }
    end = chrono::high_resolution_clock::now();
    auto umap_lookup = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "\nLOOKUP:" << endl;
    cout << "  map:            " << map_lookup << " μs (O(log n))" << endl;
    cout << "  unordered_map:  " << umap_lookup << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (umap_lookup < map_lookup ? "unordered_map" : "map") << endl;
    
    // MAP - ERASE
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N / 10; i++) {
        m_perf.erase(i);
    }
    end = chrono::high_resolution_clock::now();
    auto map_erase = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // UNORDERED_MAP - ERASE
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N / 10; i++) {
        um_perf.erase(i);
    }
    end = chrono::high_resolution_clock::now();
    auto umap_erase = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "\nERASE (100,000 deletions):" << endl;
    cout << "  map:            " << map_erase << " μs (O(log n))" << endl;
    cout << "  unordered_map:  " << umap_erase << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (umap_erase < map_erase ? "unordered_map" : "map") << endl << "\n";

    // ===== 5. MEMORY AND INTERNAL SIZE =====
    cout << "5. INTERNAL STATISTICS" << endl;
    cout << string(60, '-') << endl;
    
    map<int, int> m_stats;
    for (int i = 0; i < 100; i++) m_stats[i] = i;
    
    unordered_map<int, int> um_stats;
    for (int i = 0; i < 100; i++) um_stats[i] = i;
    
    cout << "After inserting 100 elements:" << endl;
    cout << "map size:             " << m_stats.size() << endl;
    cout << "unordered_map size:   " << um_stats.size() << endl;
    cout << "unordered_map buckets: " << um_stats.bucket_count() << endl;
    cout << "unordered_map load factor: " << um_stats.load_factor() << endl << "\n";

    // ===== 6. CUSTOM KEY TYPES =====
    cout << "6. CUSTOM KEY TYPES" << endl;
    cout << string(60, '-') << endl;
    
    cout << "map<Person, int> (requires operator<):" << endl;
    map<Person, int> person_map;
    person_map[Person("Alice", 30)] = 1001;
    person_map[Person("Bob", 25)] = 1002;
    person_map[Person("Charlie", 35)] = 1003;
    
    for (auto& p : person_map) {
        cout << "  " << p.first.name << " (age " << p.first.age << "): " << p.second << endl;
    }
    
    cout << "\nunordered_map<Person, int> (requires hash and operator==):" << endl;
    unordered_map<Person, int, PersonHash> person_umap;
    person_umap[Person("Alice", 30)] = 1001;
    person_umap[Person("Bob", 25)] = 1002;
    person_umap[Person("Charlie", 35)] = 1003;
    
    for (auto& p : person_umap) {
        cout << "  " << p.first.name << " (age " << p.first.age << "): " << p.second << endl;
    }
    cout << "\n";

    // ===== 7. FIND AND COUNT =====
    cout << "7. SEARCH METHODS" << endl;
    cout << string(60, '-') << endl;
    
    map<string, int> m_find;
    m_find["apple"] = 10;
    m_find["banana"] = 20;
    m_find["cherry"] = 30;
    
    cout << "map.find(\"banana\"):" << endl;
    auto it = m_find.find("banana");
    if (it != m_find.end()) {
        cout << "  Found: " << it->first << " = " << it->second << endl;
    }
    
    cout << "\nmap.count(\"banana\"):" << endl;
    cout << "  Count: " << m_find.count("banana") << " (always 0 or 1)" << endl;
    
    unordered_map<string, int> um_find;
    um_find["apple"] = 10;
    um_find["banana"] = 20;
    um_find["cherry"] = 30;
    
    cout << "\nunordered_map.find(\"banana\"):" << endl;
    auto um_it = um_find.find("banana");
    if (um_it != um_find.end()) {
        cout << "  Found: " << um_it->first << " = " << um_it->second << endl;
    }
    
    cout << "\nunordered_map.count(\"banana\"):" << endl;
    cout << "  Count: " << um_find.count("banana") << " (always 0 or 1)" << endl << "\n";

    // ===== 8. SUMMARY TABLE =====
    cout << "8. QUICK COMPARISON TABLE" << endl;
    cout << string(60, '-') << endl;
    cout << "Feature                | map        | unordered_map\n";
    cout << string(60, '-') << endl;
    cout << "Ordering               | Sorted     | Arbitrary\n";
    cout << "Insertion              | O(log n)   | O(1) avg\n";
    cout << "Lookup                 | O(log n)   | O(1) avg\n";
    cout << "Deletion               | O(log n)   | O(1) avg\n";
    cout << "Range queries          | Yes        | No\n";
    cout << "Iteration              | Sorted     | Unordered\n";
    cout << "Reverse iteration      | Yes        | No\n";
    cout << "Key requirement        | operator<  | hash func\n";
    cout << "Space overhead         | Lower      | Higher\n";
    cout << "Cache friendliness     | Better     | Worse\n" << endl;

    // ===== 9. USE CASE EXAMPLES =====
    cout << "9. PRACTICAL USE CASES" << endl;
    cout << string(60, '-') << endl;
    cout << "Use map when:" << endl;
    cout << "  • Need elements in sorted order\n";
    cout << "  • Range queries (e.g., ages 18-65)\n";
    cout << "  • Need reverse iteration\n";
    cout << "  • Predictable O(log n) performance\n";
    cout << "  • Using custom types that only have operator<\n";
    cout << "  • Examples: Caching with time windows, lexicographic sorting\n\n";
    
    cout << "Use unordered_map when:" << endl;
    cout << "  • Need fast average O(1) lookup\n";
    cout << "  • Don't care about order\n";
    cout << "  • Working with huge datasets\n";
    cout << "  • Simple key types (int, string)\n";
    cout << "  • Examples: Counting word frequency, caching, memoization\n";

    return 0;
}