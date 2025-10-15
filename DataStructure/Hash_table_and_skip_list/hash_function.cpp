#include <iostream>
#include <functional> // Contains std::hash
#include <string>

// --- 1. Custom Struct Definition ---

struct Point {
    int x;
    int y;

    // We still need the equality operator (operator==) to confirm if two Points
    // are considered the same, which is essential after hashing potentially collides.
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// --- 2. SPECIALIZATION of std::hash for the custom Point struct ---

/* This block tells the C++ standard library how to generate a hash code 
 * for any 'Point' object. We must put this definition inside the 'std' namespace.
 */
namespace std {
    template <>
    struct hash<Point> {
        // This is the function call operator that performs the hash calculation.
        std::size_t operator()(const Point& p) const {
            
            // Step 1: Get the hash of the individual members (x and y).
            std::size_t hx = std::hash<int>{}(p.x);
            std::size_t hy = std::hash<int>{}(p.y);
            
            // Step 2: Combine the hashes. 
            // The combination uses XOR (^) and a bit shift (<< 1) to mix the two values.
            // This is a standard way to combine hash codes to avoid simple collisions.
            return hx ^ (hy << 1);
        }
    };
}
// End of std namespace specialization

int main() {
    // ------------------------------------------------
    // DEMO A: Using std::hash with a built-in type (std::string)
    // ------------------------------------------------
    std::cout << "--- Demo A: Built-in Type (std::string) ---" << std::endl;

    std::string key1 = "Saturn";
    std::string key2 = "Jupiter";

    // You create a std::hash object instance for the type you want to hash.
    std::hash<std::string> stringHasher; 

    // The calculated hash code is a large unsigned integer (std::size_t).
    std::size_t hash1 = stringHasher(key1);
    std::size_t hash2 = stringHasher(key2);

    std::cout << "Key: \"" << key1 << "\" -> Raw Hash Code: " << hash1 << std::endl;
    std::cout << "Key: \"" << key2 << "\" -> Raw Hash Code: " << hash2 << std::endl;
    std::cout << "\nNotice the wildly different hash codes, even for similar strings." << std::endl;
    std::cout << "------------------------------------------------\n" << std::endl;


    // ------------------------------------------------
    // DEMO B: Using the specialized std::hash with the custom Point type
    // ------------------------------------------------
    std::cout << "--- Demo B: Custom Type (Point) using our custom specialization ---" << std::endl;
    
    Point p1 = {10, 20};
    Point p2 = {5, 15};
    Point p3 = {10, 20}; // Identical to p1

    // 1. Calculate hashes for the custom type
    // The compiler automatically uses the specialization we wrote above.
    std::hash<Point> pointHasher;
    std::size_t hash_p1 = pointHasher(p1);
    std::size_t hash_p2 = pointHasher(p2);
    std::size_t hash_p3 = pointHasher(p3);

    std::cout << "Point (10, 20) -> Hash Code: " << hash_p1 << std::endl;
    std::cout << "Point (5, 15)  -> Hash Code: " << hash_p2 << std::endl;
    std::cout << "Point (10, 20) -> Hash Code: " << hash_p3 << " (Must be same as P1)" << std::endl;

    // 2. Check for equality after hashing (what the hash table does)
    if (hash_p1 == hash_p3) {
        std::cout << "\n*Success*: Hash codes for identical points match!" << std::endl;
    }

    if (p1 == p3) {
        std::cout << "*Success*: The equality operator confirms P1 and P3 are equal." << std::endl;
    } else {
        std::cout << "*Failure*: Equality check failed." << std::endl;
    }

    return 0;
}
