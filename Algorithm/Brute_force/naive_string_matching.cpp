#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Implements the Naive String Matching algorithm (Brute Force).
 * * =========================================================================
 * THE NAIVE STRING MATCHING ALGORITHM
 * =========================================================================
 * This function searches for all occurrences of a given pattern 'pat' 
 * within a larger text 'txt'.
 * * * Brute Force Strategy (O(M * N)):
 * 1. The outer loop iterates through all possible starting shifts 'i' 
 * in the text (from 0 up to N-M).
 * 2. The inner loop compares the 'M' characters of the pattern against 
 * the corresponding 'M' characters of the text starting at index 'i'.
 * 3. If all characters match, an occurrence is found at that shift 'i'.
 * * * Time Complexity: O(N * M)
 * In the worst case (e.g., Text: "AAAAA", Pattern: "AAA"), the inner loop 
 * runs M times for almost every shift N, leading to N * M comparisons.
 * * @param txt The main text string (Length N).
 * @param pat The pattern string to search for (Length M).
 * @return A vector of starting indices where the pattern is found in the text.
 */
std::vector<int> naiveSearch(const std::string& txt, const std::string& pat) {
    int N = txt.length(); // Length of the text
    int M = pat.length(); // Length of the pattern
    std::vector<int> found_indices;

    if (M == 0) {
        // Edge case: empty pattern
        std::cout << "Pattern cannot be empty." << std::endl;
        return found_indices;
    }

    // Outer loop: Iterate through all possible starting positions in the text.
    // We only need to check up to N - M, because the pattern won't fit after that.
    for (int i = 0; i <= N - M; ++i) {
        int j;

        // Inner loop: Compare pattern characters with text characters starting at 'i'.
        for (j = 0; j < M; ++j) {
            // Check if the current character in the pattern matches the corresponding 
            // character in the text at position (i + j).
            if (txt[i + j] != pat[j]) {
                // Mismatch found, break the inner loop and move to the next shift (i+1).
                break;
            }
        }

        // If the inner loop completed without a 'break', it means all M characters matched.
        if (j == M) {
            // Pattern found at shift i
            found_indices.push_back(i);
        }
    }

    return found_indices;
}

int main() {
    // Test Case 1: Multiple matches
    std::string text1 = "AABAACAADAABAABA";
    std::string pattern1 = "AABA";
    
    // Test Case 2: No match
    std::string text2 = "GEEKSFORGEEKS";
    std::string pattern2 = "PQR";

    // Test Case 3: Overlapping matches (Worst case for naive search)
    std::string text3 = "AAAAAB";
    std::string pattern3 = "AAA";
    
    std::cout << "--- Naive String Matching (Brute Force) ---" << std::endl;

    // Run Test 1
    std::vector<int> result1 = naiveSearch(text1, pattern1);
    std::cout << "Text: \"" << text1 << "\", Pattern: \"" << pattern1 << "\"" << std::endl;
    if (!result1.empty()) {
        std::cout << "Pattern found at indices: ";
        for (int index : result1) {
            std::cout << index << " ";
        }
        std::cout << std::endl; // Expected: 0 9 12
    } else {
        std::cout << "Pattern not found." << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;


    // Run Test 2
    std::vector<int> result2 = naiveSearch(text2, pattern2);
    std::cout << "Text: \"" << text2 << "\", Pattern: \"" << pattern2 << "\"" << std::endl;
    if (!result2.empty()) {
        std::cout << "Pattern found at indices: ";
        for (int index : result2) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Pattern not found." << std::endl; // Expected: Not found
    }
    std::cout << "------------------------------------------" << std::endl;


    // Run Test 3
    std::vector<int> result3 = naiveSearch(text3, pattern3);
    std::cout << "Text: \"" << text3 << "\", Pattern: \"" << pattern3 << "\"" << std::endl;
    if (!result3.empty()) {
        std::cout << "Pattern found at indices: ";
        for (int index : result3) {
            std::cout << index << " ";
        }
        std::cout << std::endl; // Expected: 0 1 2
    } else {
        std::cout << "Pattern not found." << std::endl;
    }
    
    return 0;
}
