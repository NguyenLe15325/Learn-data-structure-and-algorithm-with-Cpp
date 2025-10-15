#include <iostream>

int main() {
    // --- 1. Dynamic allocation of a single variable ---
    
    // `new` allocates memory for a single integer on the heap and returns a pointer
    // to that memory. The pointer `int_ptr` stores the address of the allocated memory.
    int* int_ptr = new int;

    // Check if the allocation was successful. In modern C++, `new` throws
    // a `std::bad_alloc` exception on failure, but a check is still good practice.
    if (int_ptr == nullptr) {
        std::cerr << "Memory allocation failed for int_ptr!" << std::endl;
        return 1; // Exit with an error code
    }

    // Dereference the pointer to assign a value to the allocated memory.
    *int_ptr = 10;

    // Print the value and the memory address to demonstrate it's on the heap.
    std::cout << "Dynamically allocated integer:" << std::endl;
    std::cout << "Value: " << *int_ptr << std::endl;
    std::cout << "Address: " << int_ptr << std::endl;
    
    // `delete` frees the memory pointed to by `int_ptr`.
    // It is crucial to deallocate memory to prevent memory leaks.
    delete int_ptr;
    // Set the pointer to `nullptr` to avoid "dangling pointers" after deletion.
    int_ptr = nullptr;


    std::cout << "\n----------------------------------------\n" << std::endl;


    // --- 2. Dynamic allocation of an array ---

    // `new[]` allocates memory for an array of 5 integers.
    // `new[]` returns a pointer to the first element of the array.
    int size = 5;
    int* array_ptr = new int[size];

    if (array_ptr == nullptr) {
        std::cerr << "Memory allocation failed for array_ptr!" << std::endl;
        return 1;
    }

    // Populate the dynamic array using array-like syntax.
    // This is equivalent to `*(array_ptr + i) = ...`.
    for (int i = 0; i < size; ++i) {
        array_ptr[i] = i * 10;
    }

    // Print the contents of the dynamic array.
    std::cout << "Dynamically allocated array of 5 integers:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "Element " << i << ": " << array_ptr[i] << " (Address: " << &array_ptr[i] << ")" << std::endl;
    }

    // `delete[]` frees the memory for the entire array.
    // It is important to use `delete[]` for arrays and not `delete`.
    delete[] array_ptr;
    array_ptr = nullptr;

    return 0;
}
