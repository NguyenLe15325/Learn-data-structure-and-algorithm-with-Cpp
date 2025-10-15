#include <iostream>

// Function prototype for printing an integer array.
// The `int arr[]` parameter decays to a pointer `int* arr`.
// This is a stylistic choice; the alternative syntax is `void printIntArray(int* arr, int size)`.
// The size is passed separately because the pointer doesn't carry this information.
void printIntArray(int arr[], int size) {
    std::cout << "Values in the integer array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " "; //*(arr + i)
    }
    std::cout << std::endl;
}

// Function prototype for printing a character array.
// This function also accepts the array by a pointer, `char*`.
// The alternative syntax for the parameter is `char* arr`.
// We do not need a separate size parameter for null-terminated strings
// because C-style strings are terminated with a null character `\0`.
void printCharArray(char arr[]) {
    std::cout << "Values in the character array (C-style string):" << std::endl;
    // The `std::cout` object has a special overload for `char*` pointers.
    // It will automatically print characters until it encounters the null terminator `\0`.
    std::cout << arr << std::endl;

    // You could also print it manually, character by character, until the null terminator is found.
    std::cout << "Printing manually:" << std::endl;
    for (int i = 0; arr[i] != '\0'; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Integer array
    int myArray[] = {1, 2, 3, 4, 5};
    int arraySize = sizeof(myArray) / sizeof(myArray[0]);
    printIntArray(myArray, arraySize); 
    
    std::cout << "\n----------------------------------------\n" << std::endl;

    // Character array (C-style string)
    // C++ automatically adds a null-terminator `\0` at the end of string literals.
    char myString[] = "Hello";
    
    // Pass the char array to the new function.
    // `printCharArray` automatically stops printing when it sees the `\0`.
    printCharArray(myString);

    return 0;
}
