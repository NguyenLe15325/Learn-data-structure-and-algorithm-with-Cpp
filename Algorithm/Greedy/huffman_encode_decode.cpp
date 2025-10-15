#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <memory>
using namespace std;

struct Node {
    char ch;
    int freq;
    shared_ptr<Node> left, right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(shared_ptr<Node> a, shared_ptr<Node> b) {
        return a->freq > b->freq;
    }
};

class HuffmanCoding {
private:
    shared_ptr<Node> root;
    unordered_map<char, string> codes;
    
    void buildCodes(shared_ptr<Node> node, string code) {
        if (!node) return;
        
        if (!node->left && !node->right) {
            codes[node->ch] = code.empty() ? "0" : code;
            return;
        }
        
        buildCodes(node->left, code + "0");
        buildCodes(node->right, code + "1");
    }
    
public:
    void buildTree(const string& text) {
        if (text.empty()) return;
        
        // Count frequencies
        unordered_map<char, int> freq;
        for (char c : text) {
            freq[c]++;
        }
        
        // Create min heap
        priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;
        for (auto& p : freq) {
            pq.push(make_shared<Node>(p.first, p.second));
        }
        
        // Build Huffman tree
        while (pq.size() > 1) {
            auto left = pq.top(); pq.pop();
            auto right = pq.top(); pq.pop();
            
            auto parent = make_shared<Node>('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            pq.push(parent);
        }
        
        root = pq.top();
        
        // Generate codes
        codes.clear();
        buildCodes(root, "");
    }
    
    string encode(const string& text) {
        string encoded;
        for (char c : text) {
            encoded += codes[c];
        }
        return encoded;
    }
    
    string decode(const string& encoded) {
        string decoded;
        auto node = root;
        
        for (char bit : encoded) {
            node = (bit == '0') ? node->left : node->right;
            
            if (!node->left && !node->right) {
                decoded += node->ch;
                node = root;
            }
        }
        
        return decoded;
    }
    
    void printCodes() {
        cout << "\nHuffman Codes:\n";
        for (auto& p : codes) {
            cout << "'" << p.first << "': " << p.second << "\n";
        }
    }
    
    int getOriginalSize(const string& text) {
        return text.length() * 8; // bits
    }
    
    int getEncodedSize(const string& encoded) {
        return encoded.length(); // bits
    }
};

int main() {
    HuffmanCoding hc;
    
    string original = "hello world";
    
    cout << "Original text: " << original << "\n";
    cout << "Original size: " << hc.getOriginalSize(original) << " bits\n\n";
    
    // Build Huffman tree
    hc.buildTree(original);
    hc.printCodes();
    
    // Encode
    string encoded = hc.encode(original);
    cout << "\nEncoded: " << encoded << "\n";
    cout << "Encoded size: " << hc.getEncodedSize(encoded) << " bits\n";
    cout << "Compression ratio: " 
         << (double)hc.getEncodedSize(encoded) / hc.getOriginalSize(original) * 100 
         << "%\n";
    
    // Decode
    string decoded = hc.decode(encoded);
    cout << "\nDecoded: " << decoded << "\n";
    cout << "Decoding successful: " << (decoded == original ? "YES" : "NO") << "\n";
    
    return 0;
}