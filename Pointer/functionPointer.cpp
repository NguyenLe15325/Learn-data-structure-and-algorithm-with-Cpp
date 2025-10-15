#include <iostream>

// --- 1. Define some simple functions ---
// These are regular functions that we will point to.
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// --- 2. Function that takes a function pointer as an argument ---
// This function accepts a function pointer `operation` as its first argument.
// The `operation` pointer must point to a function that takes two integers
// and returns an integer.
void performOperation(int (*operation)(int, int), int x, int y) {
    std::cout << "Performing operation..." << std::endl;
    // Call the function through the function pointer
    int result = operation(x, y);
    std::cout << "Result: " << result << std::endl;
}

int main() {
    std::cout << "--- Function Pointer Demonstration ---" << std::endl;

    // --- 3. Declare a function pointer ---
    // Syntax: return_type (*pointer_name)(parameter_list);
    // This declares `mathOperation` as a pointer to a function that
    // takes two `int`s and returns an `int`.
    int (*mathOperation)(int, int);

    // --- 4. Assign a function's address to the function pointer ---
    // You can assign the function name directly. The compiler automatically
    // converts the function name to its address.
    mathOperation = add;

    // --- 5. Call the function through the function pointer ---
    // You can call it just like a regular function.
    std::cout << "Calling 'add' via function pointer:" << std::endl;
    int sum = mathOperation(5, 3);
    std::cout << "Sum: " << sum << std::endl;

    // You can also explicitly dereference it, though it's optional.
    // int sum_explicit = (*mathOperation)(5, 3); // Same as mathOperation(5, 3)

    std::cout << "\n----------------------------------------\n" << std::endl;

    // --- 6. Assign a different function to the same pointer ---
    mathOperation = subtract;

    std::cout << "Calling 'subtract' via function pointer:" << std::endl;
    int difference = mathOperation(10, 4);
    std::cout << "Difference: " << difference << std::endl;

    std::cout << "\n----------------------------------------\n" << std::endl;

    // --- 7. Pass function pointers as arguments ---
    std::cout << "Using 'performOperation' with 'add':" << std::endl;
    performOperation(add, 20, 5); // Pass the 'add' function's address

    std::cout << "\nUsing 'performOperation' with 'subtract':" << std::endl;
    performOperation(subtract, 20, 5); // Pass the 'subtract' function's address

    return 0;
}
