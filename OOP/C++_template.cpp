#include <iostream>   // Required for standard input/output operations (like std::cout)
#include <string>     // Required for using the std::string class
#include <stdexcept>  // Required for using standard exception classes (like std::out_of_range)
#include <typeinfo>   // Required for the typeid operator (used to find the runtime type name, e.g., in the Pair::display method)

// --- Template Function Definition ---
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ----------------------------------------------------------------
// --- Template Class Definition 1: Single Type (Box) ---
// ----------------------------------------------------------------
// Generic version (works for most types like int, string, float)
template <typename T>
class Box {
private:
    T content; 

public:
    Box(const T& initialContent) : content(initialContent) {}
    T getContent() const { return content; }
    void display() const {
        std::cout << "[Generic Box] Content: '" << content << "'" << std::endl;
    }
};

// ----------------------------------------------------------------
// --- FULL TEMPLATE SPECIALIZATION for 'double' ---
// ----------------------------------------------------------------
// This implementation is used ONLY when T is explicitly 'double'.
// Note the syntax: template <> class Box<double>
template <>
class Box<double> {
private:
    double value;
    const double PI = 3.14159;

public:
    // This constructor is completely different from the generic one.
    Box(double initialValue) : value(initialValue) {}
    
    // The behavior is specialized—it performs a calculation.
    void display() const {
        std::cout << "[SPECIALIZED Box<double>] Area Calculation: " 
                  << value << " * PI = " << (value * PI) << std::endl;
    }
    
    double getCalculatedValue() const { return value * PI; }
};


// ----------------------------------------------------------------
// --- Template Class Definition 2: Multiple Types (Pair) ---
// ----------------------------------------------------------------
template <typename T, typename U>
class Pair {
private:
    T first;  
    U second; 

public:
    Pair(const T& valT, const U& valU) : first(valT), second(valU) {}
    void display() const {
        std::cout << "Pair: {First (" << typeid(T).name() << "): " << first 
                  << ", Second (" << typeid(U).name() << "): " << second << "}" << std::endl;
    }
    T getFirst() const { return first; }
    U getSecond() const { return second; }
};

// ----------------------------------------------------------------
// --- Template Class Definition 3: Non-Type Parameter (FixedSizeArray) ---
// ----------------------------------------------------------------
template <typename T, int N>
class FixedSizeArray {
private:
    T data[N]; 
    
public:
    T& get(int index) {
        if (index < 0 || index >= N) {
            // Throws an exception defined in <stdexcept>
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    int size() const {
        return N;
    }
    
    void fill(const T& value) {
        for (int i = 0; i < N; ++i) {
            data[i] = value;
        }
    }
};


int main() {
    std::cout << "--- Template Function Demonstration ---" << std::endl;
    int num1 = 10;
    int num2 = 20;
    std::cout << "\n[Integer Function Demo]" << std::endl;
    std::cout << "Before swap: num1=" << num1 << ", num2=" << num2 << std::endl;
    swapValues(num1, num2);
    std::cout << "After swap: num1=" << num1 << ", num2=" << num2 << std::endl;

    std::cout << "\n==========================================================" << std::endl;
    std::cout << "--- Template Class Demonstration 1: Single Type (Box) ---" << std::endl;
    std::cout << "==========================================================" << std::endl;

    // 1. Box holding a String (T = std::string) -> USES GENERIC TEMPLATE
    Box<std::string> stringBox("Templates are powerful!");
    stringBox.display();

    // 2. Box holding a Double (T = double) -> USES SPECIALIZED TEMPLATE
    Box<double> doubleBox(10.0);
    doubleBox.display(); // Notice the output is completely different!

    std::cout << "\n==========================================================" << std::endl;
    std::cout << "--- Template Class Demonstration 2: Multiple Types (Pair) ---" << std::endl;
    std::cout << "==========================================================" << std::endl;
    
    // Pair holding an int and a string (T=int, U=std::string)
    Pair<int, std::string> studentGrade(101, "A+");
    studentGrade.display();

    std::cout << "\n==========================================================" << std::endl;
    std::cout << "--- Template Class Demonstration 3: Non-Type Parameter (FixedSizeArray) ---" << std::endl;
    std::cout << "==========================================================" << std::endl;
    
    // Create an array of 5 integers. T=int, N=5
    FixedSizeArray<int, 5> intArray;
    intArray.fill(42);
    intArray.get(2) = 99;
    
    std::cout << "[Integer Array of Size 5]" << std::endl;
    std::cout << "Size: " << intArray.size() << ", Element at index 2: " << intArray.get(2) << std::endl;

    // Create an array of 3 strings. T=std::string, N=3
    FixedSizeArray<std::string, 3> stringArray;
    stringArray.fill("Empty");
    stringArray.get(0) = "Hello";
    
    std::cout << "\n[String Array of Size 3]" << std::endl;
    std::cout << "Size: " << stringArray.size() << ", Element at index 0: " << stringArray.get(0) << std::endl;


    return 0;
}
