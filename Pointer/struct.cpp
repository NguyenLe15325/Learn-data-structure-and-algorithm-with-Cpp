#include <iostream>
#include <string>

// --- 1. Define a simple struct with a member function ---
// A struct can contain both data members and member functions (methods).
// The `printInfo` function is now part of the `Person` struct's definition.
struct Person {
    std::string name;
    int age;

    // A member function (method) to print the person's details.
    // It can directly access the struct's members (`name` and `age`).
    void printInfo() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    // --- 2. Create a struct instance on the stack ---
    Person alice;
    alice.name = "Alice";
    alice.age = 30;
    
    // --- 3. Declare a pointer to a struct ---
    // A pointer to a struct is declared with an asterisk, just like any other pointer.
    // The type is `Person*`.
    Person* ptr_to_alice;

    // Assign the address of the struct instance to the pointer.
    ptr_to_alice = &alice;
    
    // --- 4. Accessing struct members and methods ---
    std::cout << "--- Calling the printInfo() method on 'alice' directly ---" << std::endl;
    alice.printInfo();
    std::cout << std::endl;

    std::cout << "--- Calling the printInfo() method via the pointer 'ptr_to_alice' ---" << std::endl;
    // Method A: Using the dereference operator (*) and the dot operator (.)
    // The parentheses are crucial here: `(*ptr_to_alice)` dereferences the pointer first
    // to get the actual `Person` object, then `.printInfo()` calls the method.
    (*ptr_to_alice).printInfo();
    
    // Method B: Using the arrow operator (->)
    // The arrow operator is syntactic sugar for Method A. It is the preferred and
    // cleaner way to access struct members or methods through a pointer.
    ptr_to_alice->printInfo();
    std::cout << std::endl;

    // --- 5. Example with a dynamically allocated struct ---
    Person* dynamic_person_ptr = new Person;
    
    dynamic_person_ptr->name = "Bob";
    dynamic_person_ptr->age = 25;

    std::cout << "--- Calling the printInfo() method on a dynamically allocated struct ---" << std::endl;
    // Call the method using the arrow operator on the pointer.
    dynamic_person_ptr->printInfo();
    
    // It's essential to deallocate the memory allocated with `new`.
    delete dynamic_person_ptr;
    dynamic_person_ptr = nullptr;

    return 0;
}
