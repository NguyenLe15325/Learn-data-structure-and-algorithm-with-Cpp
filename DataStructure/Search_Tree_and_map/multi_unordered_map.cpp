#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

int main() {
    cout << "========== COMPREHENSIVE UNORDERED_MULTIMAP DEMONSTRATION ==========" << endl << endl;

    // ===== 1. BASIC DIFFERENCE: MULTIMAP vs UNORDERED_MULTIMAP =====
    cout << "1. MULTIMAP vs UNORDERED_MULTIMAP: SORTING" << endl;
    cout << string(70, '-') << endl;
    
    cout << "multimap (sorted by key):" << endl;
    multimap<int, string> mmap;
    mmap.insert({50, "fifty"});
    mmap.insert({20, "twenty"});
    mmap.insert({50, "FIFTY"});
    mmap.insert({10, "ten"});
    mmap.insert({30, "thirty"});
    mmap.insert({20, "TWENTY"});
    
    cout << "  Insertion order: 50, 20, 50, 10, 30, 20" << endl;
    cout << "  Stored order:" << endl;
    for (auto& p : mmap) {
        cout << "    " << p.first << " -> " << p.second << endl;
    }
    
    cout << "\nunordered_multimap (arbitrary order):" << endl;
    unordered_multimap<int, string> ummap;
    ummap.insert({50, "fifty"});
    ummap.insert({20, "twenty"});
    ummap.insert({50, "FIFTY"});
    ummap.insert({10, "ten"});
    ummap.insert({30, "thirty"});
    ummap.insert({20, "TWENTY"});
    
    cout << "  Insertion order: 50, 20, 50, 10, 30, 20" << endl;
    cout << "  Stored order (hash-based, arbitrary):" << endl;
    for (auto& p : ummap) {
        cout << "    " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";

    // ===== 2. KEY FEATURES OF UNORDERED_MULTIMAP =====
    cout << "2. NO SORTED ORDER - IMPLICATIONS" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<string, int> tags;
    tags.insert({"cpp", 100});
    tags.insert({"python", 200});
    tags.insert({"cpp", 101});
    tags.insert({"javascript", 150});
    tags.insert({"python", 201});
    tags.insert({"cpp", 102});
    
    cout << "Iteration order is arbitrary (hash table order):" << endl;
    for (auto& p : tags) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\nDespite arbitrary order, duplicates are grouped together internally.\n\n";

    // ===== 3. COUNTING AND FINDING DUPLICATES =====
    cout << "3. COUNTING AND FINDING DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<string, int> product_inventory;
    product_inventory.insert({"laptop", 1500});
    product_inventory.insert({"mouse", 25});
    product_inventory.insert({"laptop", 1600});
    product_inventory.insert({"keyboard", 75});
    product_inventory.insert({"laptop", 1400});
    product_inventory.insert({"mouse", 30});
    
    cout << "Product inventory:" << endl;
    for (auto& p : product_inventory) {
        cout << "  " << p.first << ": $" << p.second << endl;
    }
    cout << "\n";
    
    cout << "Count how many 'laptop' entries: " << product_inventory.count("laptop") << endl;
    cout << "Count how many 'mouse' entries: " << product_inventory.count("mouse") << endl;
    cout << "Count how many 'monitor' entries: " << product_inventory.count("monitor") << "\n\n";

    // ===== 4. EQUAL_RANGE - FINDING ALL DUPLICATES =====
    cout << "4. EQUAL_RANGE - FINDING ALL DUPLICATES" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<int, string> scores;
    scores.insert({100, "Perfect1"});
    scores.insert({85, "Good1"});
    scores.insert({85, "Good2"});
    scores.insert({85, "Good3"});
    scores.insert({70, "Okay"});
    
    cout << "All entries:" << endl;
    for (auto& p : scores) {
        cout << "  " << p.first << " -> " << p.second << endl;
    }
    cout << "\n";
    
    cout << "Using equal_range(85) to find all score 85 entries:" << endl;
    auto range = scores.equal_range(85);
    cout << "  Found entries:" << endl;
    for (auto it = range.first; it != range.second; ++it) {
        cout << "    " << it->first << " -> " << it->second << endl;
    }
    cout << "  Total count: " << distance(range.first, range.second) << "\n\n";

    // ===== 5. FIND METHOD =====
    cout << "5. FIND METHOD" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<string, int> cities;
    cities.insert({"New York", 8000000});
    cities.insert({"Tokyo", 13900000});
    cities.insert({"New York", 8100000});  // Different population estimate
    cities.insert({"Paris", 2161000});
    cities.insert({"Tokyo", 13950000});    // Different population estimate
    
    cout << "Cities with multiple records:" << endl;
    for (auto& p : cities) {
        cout << "  " << p.first << ": " << p.second << " people" << endl;
    }
    cout << "\n";
    
    cout << "find(\"Tokyo\") returns iterator to first entry:" << endl;
    auto it = cities.find("Tokyo");
    if (it != cities.end()) {
        cout << "  " << it->first << ": " << it->second << " people" << endl;
    }
    cout << "\nTo get all Tokyo entries, use equal_range(\"Tokyo\"):\n";
    auto tokyo_range = cities.equal_range("Tokyo");
    for (auto iter = tokyo_range.first; iter != tokyo_range.second; ++iter) {
        cout << "  " << iter->first << ": " << iter->second << " people" << endl;
    }
    cout << "\n";

    // ===== 6. ERASING ENTRIES =====
    cout << "6. ERASING ENTRIES" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<string, int> users;
    users.insert({"alice", 1001});
    users.insert({"bob", 1002});
    users.insert({"alice", 1003});
    users.insert({"charlie", 1004});
    users.insert({"alice", 1005});
    users.insert({"bob", 1006});
    
    cout << "Original users:" << endl;
    for (auto& p : users) {
        cout << "  " << p.first << " -> ID:" << p.second << endl;
    }
    cout << "  Size: " << users.size() << "\n\n";
    
    cout << "Erase single 'alice' entry:" << endl;
    users.erase(users.find("alice"));
    
    for (auto& p : users) {
        cout << "  " << p.first << " -> ID:" << p.second << endl;
    }
    cout << "  Size: " << users.size() << "\n\n";
    
    cout << "Erase all remaining 'alice' entries:" << endl;
    size_t erased = users.erase("alice");
    cout << "  Entries erased: " << erased << "\n";
    
    for (auto& p : users) {
        cout << "  " << p.first << " -> ID:" << p.second << endl;
    }
    cout << "  Size: " << users.size() << "\n\n";

    // ===== 7. PERFORMANCE: MULTIMAP vs UNORDERED_MULTIMAP =====
    cout << "7. PERFORMANCE COMPARISON (500,000 operations)" << endl;
    cout << string(70, '-') << endl;
    
    const int N = 500000;
    
    // multimap insertion
    auto start = chrono::high_resolution_clock::now();
    multimap<int, int> mmap_perf;
    for (int i = 0; i < N; i++) {
        mmap_perf.insert({i % 1000, i});  // Many duplicate keys
    }
    auto end = chrono::high_resolution_clock::now();
    auto mmap_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // unordered_multimap insertion
    start = chrono::high_resolution_clock::now();
    unordered_multimap<int, int> ummap_perf;
    for (int i = 0; i < N; i++) {
        ummap_perf.insert({i % 1000, i});  // Many duplicate keys
    }
    end = chrono::high_resolution_clock::now();
    auto ummap_insert = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "INSERTION (500,000 entries with ~500 per key):" << endl;
    cout << "  multimap:           " << mmap_insert << " μs (O(log n))" << endl;
    cout << "  unordered_multimap: " << ummap_insert << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (ummap_insert < mmap_insert ? "unordered_multimap" : "multimap") << "\n\n";
    
    // multimap find
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        mmap_perf.find(i % 1000);
    }
    end = chrono::high_resolution_clock::now();
    auto mmap_find = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // unordered_multimap find
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        ummap_perf.find(i % 1000);
    }
    end = chrono::high_resolution_clock::now();
    auto ummap_find = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "FIND (10,000 lookups):" << endl;
    cout << "  multimap:           " << mmap_find << " μs (O(log n))" << endl;
    cout << "  unordered_multimap: " << ummap_find << " μs (O(1) avg)" << endl;
    cout << "  Winner: " << (ummap_find < mmap_find ? "unordered_multimap" : "multimap") << "\n\n";

    // ===== 8. BUCKET INFORMATION =====
    cout << "8. HASH TABLE STATISTICS" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<string, int> tags_stats;
    for (int i = 0; i < 50; i++) {
        tags_stats.insert({"tag" + to_string(i % 10), i});
    }
    
    cout << "After inserting 50 elements (with 10 unique keys):" << endl;
    cout << "  Size: " << tags_stats.size() << endl;
    cout << "  Bucket count: " << tags_stats.bucket_count() << endl;
    cout << "  Load factor: " << tags_stats.load_factor() << endl;
    cout << "  Max load factor: " << tags_stats.max_load_factor() << "\n\n";

    // ===== 9. REAL-WORLD EXAMPLE: TAG SYSTEM =====
    cout << "9. REAL-WORLD EXAMPLE: ARTICLE TAGGING SYSTEM" << endl;
    cout << string(70, '-') << endl;
    
    unordered_multimap<string, int> article_tags;
    // tag -> article_id
    article_tags.insert({"cpp", 1001});
    article_tags.insert({"programming", 1001});
    article_tags.insert({"cpp", 1002});
    article_tags.insert({"performance", 1002});
    article_tags.insert({"cpp", 1003});
    article_tags.insert({"memory", 1003});
    article_tags.insert({"programming", 1004});
    article_tags.insert({"python", 1004});
    
    cout << "All tag-article mappings:" << endl;
    for (auto& p : article_tags) {
        cout << "  Tag: " << p.first << " -> Article ID: " << p.second << endl;
    }
    cout << "\n";
    
    cout << "Find all articles tagged with 'cpp':" << endl;
    auto cpp_range = article_tags.equal_range("cpp");
    cout << "  Articles: ";
    for (auto it = cpp_range.first; it != cpp_range.second; ++it) {
        cout << it->second << " ";
    }
    cout << "\n\n";

    // ===== 10. COMPARISON TABLE =====
    cout << "10. ALL FOUR CONTAINERS COMPARISON TABLE" << endl;
    cout << string(70, '-') << endl;
    cout << "Feature           | map    | multimap | unordered_map | unordered_multimap\n";
    cout << string(70, '-') << endl;
    cout << "Unique keys only  | Yes    | No       | Yes           | No\n";
    cout << "Sorted            | Yes    | Yes      | No            | No\n";
    cout << "operator[]        | Yes    | No       | Yes           | No\n";
    cout << "Insert O()        | O(log) | O(log)   | O(1) avg      | O(1) avg\n";
    cout << "Find O()          | O(log) | O(log)   | O(1) avg      | O(1) avg\n";
    cout << "Range queries     | Yes    | Yes      | No            | No\n";
    cout << "Reverse iteration | Yes    | Yes      | No            | No\n";
    cout << "equal_range()     | Yes    | Yes      | Yes           | Yes\n";
    cout << "Space overhead    | Low    | Low      | High          | High\n";
    cout << "Cache friendly    | Yes    | Yes      | No            | No\n\n";

    // ===== 11. WHEN TO USE =====
    cout << "11. WHEN TO USE UNORDERED_MULTIMAP" << endl;
    cout << string(70, '-') << endl;
    cout << "Use unordered_multimap when:" << endl;
    cout << "  • Need fast O(1) average lookup with duplicate keys\n";
    cout << "  • Don't care about sorted order\n";
    cout << "  • Working with very large datasets\n";
    cout << "  • Need to store multiple values per key\n";
    cout << "  • Examples:\n";
    cout << "    - Tag systems (tag -> multiple articles/items)\n";
    cout << "    - Inverted indices (word -> multiple documents)\n";
    cout << "    - Caching with duplicate entries\n";
    cout << "    - Hash collisions (key -> multiple hashes)\n";
    cout << "    - Group by operations on large data\n";
    cout << "    - ID -> multiple records mapping\n\n";
    
    cout << "Use multimap when:" << endl;
    cout << "  • Need sorted order with duplicate keys\n";
    cout << "  • Need range queries on duplicate keys\n";
    cout << "  • Predictable O(log n) performance required\n";
    cout << "  • Examples:\n";
    cout << "    - Phone book (person -> sorted numbers)\n";
    cout << "    - Student grades (grade -> students)\n";
    cout << "    - Log entries (timestamp -> events)\n";
    cout << "    - Word index (word -> line numbers)\n";

    return 0;
}