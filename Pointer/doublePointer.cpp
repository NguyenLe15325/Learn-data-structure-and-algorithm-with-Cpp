#include <iostream>

int main() {
    int value = 10;
    int* ptr = &value;       // ptr stores the address of 'value'
    int** pptr = &ptr;     // pptr stores the address of 'ptr'

    // Accessing the value using different levels of indirection
    
    // 1. Directly
    std::cout << "Value: " << value << std::endl;
    
    // 2. Through the first pointer
    std::cout << "Value via ptr: " << *ptr << std::endl;
    
    // 3. Through the double pointer
    std::cout << "Value via pptr: " << **pptr << std::endl;

    // Outputting the memory addresses
    std::cout << "\nMemory Addresses:" << std::endl;
    std::cout << "Address of value: " << &value << std::endl;
    std::cout << "Value of ptr (address of value): " << ptr << std::endl;
    std::cout << "Address of ptr: " << &ptr << std::endl;
    std::cout << "Value of pptr (address of ptr): " << pptr << std::endl;
    
    // Modifying the original value using the double pointer
    **pptr = 50;

    std::cout << "\nAfter modifying through pptr:" << std::endl;
    std::cout << "New value of 'value': " << value << std::endl;

    return 0;
}