#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Required for functions like std::sort

// The std::string class is highly optimized and provides a safer, more intuitive
// way to handle variable-length character sequences (text) compared to
// C-style char arrays.

using namespace std;

void print_separator(const string& title) {
    cout << "\n--------------------------------------------" << endl;
    cout << " " << title << " " << endl;
    cout << "--------------------------------------------" << endl;
}

int main() {
    // --- 1. Initialization and Declaration ---
    print_separator("1. Initialization and Declaration");

    // Default initialization (empty string)
    string s1;
    cout << "s1 (empty): '" << s1 << "'" << endl;

    // Direct initialization
    string s2 = "Hello, C++ STL!";
    cout << "s2 (direct): '" << s2 << "'" << endl;

    // Initialization from another string
    string s3(s2);
    cout << "s3 (copy of s2): '" << s3 << "'" << endl;

    // Initialization with a specific number of characters
    string s4(5, 'X'); // Creates "XXXXX"
    cout << "s4 (5 'X' chars): '" << s4 << "'" << endl;


    // --- 2. Input/Output (I/O) ---
    print_separator("2. Input/Output (I/O)");
    
    // Note: To make this example runnable without interactive input, we will
    // demonstrate the methods, but use hardcoded values for the rest.
    
    // a. Standard input (stops at first whitespace)
    // string word;
    // cout << "Enter a word: ";
    // cin >> word;
    // cout << "You entered (std::cin): " << word << endl;
    
    // b. Reading a full line (including spaces)
    // string full_line;
    // cout << "Enter a full sentence: ";
    // // Clears the input buffer before reading the line
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // getline(cin, full_line);
    // cout << "You entered (getline): " << full_line << endl;
    
    // Using hardcoded string for further demos
    string main_text = "The quick brown fox jumps over the lazy dog.";
    cout << "Working with: '" << main_text << "'" << endl;


    // --- 3. Size, Capacity, and Element Access ---
    print_separator("3. Size, Capacity, and Element Access");

    // .length() and .size() are synonyms and return the number of characters.
    cout << "Length/Size: " << main_text.length() << " chars" << endl;
    
    // .capacity() is the storage currently allocated (often >= size)
    cout << "Capacity (allocated memory): " << main_text.capacity() << " bytes" << endl;

    // Accessing characters (like an array)
    cout << "First character: " << main_text[0] << endl;
    cout << "Last character (using .at()): " << main_text.at(main_text.size() - 1) << endl;


    // --- 4. Concatenation and Appending ---
    print_separator("4. Concatenation and Appending");

    string part1 = "Data";
    string part2 = "Structure";
    
    // a. Using the '+' operator (returns a new string)
    string combined = part1 + " " + part2;
    cout << "Combined (+ operator): '" << combined << "'" << endl;
    
    // b. Using .append() (modifies the current string)
    string message = "C++";
    message.append(" Programming");
    cout << "Appended (.append()): '" << message << "'" << endl;

    // c. Using the '+=' operator (modifies the current string)
    message += " is fun!";
    cout << "Appended (+= operator): '" << message << "'" << endl;


    // --- 5. String Manipulation ---
    print_separator("5. String Manipulation");
    
    string target = "I like apples and bananas. I really like all fruits.";
    cout << "Target: '" << target << "'" << endl;
    
    // a. find(): Locates the first occurrence of a substring
    size_t pos = target.find("like");
    if (pos != string::npos) {
        cout << "Substring 'like' found at index: " << pos << endl;
    }
    
    // b. substr(): Extracts a part of the string
    // substr(start_index, length)
    string sub = target.substr(pos, 11); // "like apples"
    cout << "Substring extracted: '" << sub << "'" << endl;
    
    // c. replace(): Replaces a portion of the string
    // replace(start_index, length, replacement_string)
    // Replacing "apples and bananas" (18 chars starting after "I like ")
    target.replace(pos + 5, 18, "oranges and grapes");
    cout << "After replace: '" << target << "'" << endl;
    
    // d. erase(): Removes a portion of the string
    // erase(start_index, length)
    target.erase(target.find("I really"), 10);
    cout << "After erase: '" << target << "'" << endl;
    

    // --- 6. Iteration (Looping) ---
    print_separator("6. Iteration (Looping)");

    string iterate_string = "ITERATE";
    cout << "Original: " << iterate_string << endl;

    // a. Range-based for loop (most modern and cleanest)
    cout << "Range-based loop: ";
    for (char c : iterate_string) {
        cout << c << " ";
    }
    cout << endl;

    // b. Iterators (useful for algorithms)
    cout << "Iterator loop (reverse): ";
    for (auto it = iterate_string.rbegin(); it != iterate_string.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // c. Using STL Algorithms (Example: sorting the characters)
    string sortable = "edcba";
    cout << "Before sort: " << sortable << endl;
    sort(sortable.begin(), sortable.end());
    cout << "After sort (STL algorithm): " << sortable << endl;
    
    return 0;
}
