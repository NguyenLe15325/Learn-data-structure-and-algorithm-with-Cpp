/**
 * @file huffman_coding.cpp
 * @brief Implementation of Huffman Coding, a classic greedy algorithm for lossless data compression.
 * * --- THE PROBLEM: OPTIMAL PREFIX-FREE CODING ---
 * The core problem addressed by Huffman Coding is to find the most efficient way 
 * to encode a stream of data (like text) using variable-length binary codes.
 * * Goal: Minimize the total number of bits required to encode the entire data set.
 * * Constraint: The codes MUST be **prefix-free**, meaning the code for one character 
 * cannot be the starting sequence (prefix) of the code for any other character. 
 * This ensures unambiguous decoding.
 * * The Solution (Greedy Choice):
 * The algorithm solves this optimally by applying a **greedy strategy**:
 * 1. Identify the two characters/subtrees with the SMALLEST frequencies.
 * 2. Merge them into a new parent node.
 * 3. Repeat until only one node remains (the root).
 * * This method ensures that the most frequent characters receive the shortest codes, 
 * which is the mathematically optimal path to minimize the total encoded file size.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

/**
 * @brief Structure for a node in the Huffman Tree.
 * Each node can represent a character or an intermediate merge point.
 */
struct HuffmanNode {
    char data;          // Character stored in the node ('$' for internal nodes)
    int freq;           // Frequency (weight) of the character or subtree
    HuffmanNode *left, *right; // Pointers to the left and right children

    // Constructor for a leaf node
    HuffmanNode(char data, int freq) : 
        data(data), 
        freq(freq), 
        left(nullptr), 
        right(nullptr) {}

    // Constructor for an internal node (merge point)
    HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right) :
        data('$'), // Using '$' to mark internal nodes
        freq(freq),
        left(left),
        right(right) {}
};

/**
 * @brief Custom Comparator for the Min-Priority Queue.
 * The priority queue needs to be structured so that the node with the 
 * SMALLEST frequency is at the top (highest priority).
 */
struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        // Return true if node 'a' has a GREATER frequency than 'b',
        // which makes 'a' lower priority in a min-heap structure.
        return a->freq > b->freq; 
    }
};

/**
 * @brief Recursively traverses the Huffman Tree to generate codes.
 * Left branch is assigned '0', Right branch is assigned '1'.
 * * @param root The current node in the traversal.
 * @param code The binary string built up from the root to the current node.
 * @param huffmanCodes A map to store the final character codes.
 */
void printCodes(HuffmanNode* root, std::string code, std::map<char, std::string>& huffmanCodes) {
    // Base case: If the node is null
    if (!root) return;

    // Check if the node is a leaf (it holds a character)
    if (root->data != '$') {
        std::cout << root->data << ": " << code << std::endl;
        huffmanCodes[root->data] = code;
        return;
    }

    // Recursive step: Traverse left, appending '0'
    printCodes(root->left, code + "0", huffmanCodes);
    
    // Recursive step: Traverse right, appending '1'
    printCodes(root->right, code + "1", huffmanCodes);
}

/**
 * @brief Deallocates the memory used by the Huffman Tree.
 */
void deleteTree(HuffmanNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


/**
 * @brief Main function to implement the Huffman Coding algorithm.
 * * @param char_freq A map containing character and its corresponding frequency.
 */
void huffmanCoding(const std::map<char, int>& char_freq) {
    
    // Check for empty input
    if (char_freq.empty()) {
        std::cout << "No characters provided to encode." << std::endl;
        return;
    }

    // Min-Priority Queue declaration: Stores HuffmanNode pointers, ordered by frequency
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> minHeap;

    // 1. Initial Greedy Step: Create a leaf node for every character and push it onto the Min-Heap.
    for (const auto& pair : char_freq) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // 2. Main Greedy Loop: Build the tree
    // Continue until only one node (the root) remains in the heap.
    while (minHeap.size() > 1) {
        
        // a. GREEDY CHOICE: Extract the two nodes with the smallest frequency.
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();
        
        // b. MERGE: Create a new internal node (parent) with a frequency 
        // equal to the sum of the two children.
        HuffmanNode* top = new HuffmanNode(left->freq + right->freq, left, right);
        
        // c. Insert the new internal node back into the heap.
        minHeap.push(top);
    }
    
    // 3. The remaining node is the Root of the Huffman Tree.
    HuffmanNode* root = minHeap.top();
    std::map<char, std::string> huffmanCodes;

    std::cout << "\n--- Generated Huffman Codes ---" << std::endl;
    printCodes(root, "", huffmanCodes);
    std::cout << "-------------------------------" << std::endl;
    
    // Calculate and display the total bits saved
    long long original_bits = 0;
    long long compressed_bits = 0;

    // Assuming 8 bits per character for the original data (standard ASCII)
    for (const auto& pair : char_freq) {
        char character = pair.first;
        int freq = pair.second;
        
        original_bits += (long long)freq * 8; // Original: frequency * 8 bits
        
        // Compressed: frequency * (length of new code)
        if (huffmanCodes.count(character)) {
            compressed_bits += (long long)freq * huffmanCodes.at(character).length();
        }
    }
    
    std::cout << "Original size (8 bits/char): " << original_bits << " bits" << std::endl;
    std::cout << "Compressed size (Huffman):   " << compressed_bits << " bits" << std::endl;
    std::cout << "Bits Saved:                  " << original_bits - compressed_bits << " bits" << std::endl;


    // Clean up memory
    deleteTree(root);
}

int main() {
    // Example text: "this is a test string for huffman coding"
    // Frequencies:
    std::map<char, int> frequencies = {
        {'a', 2}, {'e', 1}, {'f', 2}, {'g', 1}, {'h', 2}, {'i', 4}, 
        {'n', 2}, {'o', 2}, {'r', 2}, {'s', 4}, {'t', 4}, {'d', 1}, 
        {'c', 1}, {' ', 6} // Space is often the most frequent character
    };
    
    std::cout << "Input Characters and Frequencies:" << std::endl;
    for (const auto& pair : frequencies) {
        std::cout << "'" << pair.first << "': " << pair.second << " | ";
    }
    std::cout << "\n";

    huffmanCoding(frequencies);

    return 0;
}
