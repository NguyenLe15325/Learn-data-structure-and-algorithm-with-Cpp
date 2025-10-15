#include <iostream>
#include <memory> // Needed for std::unique_ptr and std::make_unique

// A simple class to show when objects are created and destroyed
class SimpleObject {
public:
    SimpleObject(int value) : value_(value) {
        std::cout << "SimpleObject " << value_ << " created." << std::endl;
    }
    ~SimpleObject() {
        std::cout << "SimpleObject " << value_ << " destroyed." << std::endl;
    }
    void showValue() const {
        std::cout << "My value is: " << value_ << std::endl;
    }
private:
    int value_;
};

void demonstrateUniquePtr() {
    std::cout << "--- Inside demonstrateUniquePtr function ---" << std::endl;

    // 1. Create a unique_ptr
    // `std::make_unique` is the safest and easiest way to create unique_ptr.
    // It creates a SimpleObject(10) on the heap and ptr1 now exclusively owns it.
    std::unique_ptr<SimpleObject> ptr1 = std::make_unique<SimpleObject>(10);
    ptr1->showValue(); // Access the object using the arrow operator (->)

    // 2. Try to copy (this will cause a compile error!)
    // std::unique_ptr<SimpleObject> ptr_copy = ptr1; // ERROR: unique_ptr cannot be copied!

    // 3. Transfer ownership (move)
    // Ownership of SimpleObject(10) is transferred from ptr1 to ptr2.
    // After this line, ptr1 no longer owns the object and becomes empty (nullptr).
    std::unique_ptr<SimpleObject> ptr2 = std::move(ptr1);

    if (ptr1 == nullptr) {
        std::cout << "ptr1 is now empty after moving ownership." << std::endl;
    }

    ptr2->showValue(); // ptr2 now controls the object

    std::cout << "--- Exiting demonstrateUniquePtr function ---" << std::endl;
    // When ptr2 goes out of scope here, SimpleObject(10) is automatically destroyed.
}

int main() {
    std::cout << "--- Main function started ---" << std::endl;

    demonstrateUniquePtr(); // Call the function to see unique_ptr in action

    std::cout << "--- Main function finished ---" << std::endl;
    // No explicit 'delete' needed for SimpleObject(10) because unique_ptr handled it!

    return 0;
}
