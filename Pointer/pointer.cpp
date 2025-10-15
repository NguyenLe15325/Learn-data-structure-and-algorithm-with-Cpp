#include <iostream>

int main() {
    // Declare an integer variable
    int age = 25;
    
    // Declare a pointer to an integer
    // The asterisk (*) indicates that 'pAge' is a pointer
    int* pAge; 

    // Assign the memory address of 'age' to 'pAge'
    // The ampersand (&) is the address-of operator
    pAge = &age;

    // Output the value of the variable 'age'
    std::cout << "The value of age is: " << age << std::endl;

    // Output the memory address of 'age'
    // This is the value stored inside the pointer 'pAge'
    std::cout << "The memory address of age is: " << pAge << std::endl;

    // Use the dereference operator (*) to get the value stored at the address in 'pAge'
    // This is how you access the original variable's data through the pointer
    std::cout << "The value at the address stored in pAge is: " << *pAge << std::endl;

    // Change the value of the variable 'age' using the pointer
    *pAge = 30;

    // Now, let's see the new value of 'age'
    std::cout << "The new value of age is: " << age << std::endl;

    return 0;
}