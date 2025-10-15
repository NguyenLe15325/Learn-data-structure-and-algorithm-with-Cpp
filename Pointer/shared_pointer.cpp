#include <iostream>
#include <memory> // Required for shared_ptr

class AnotherClass {
public:
    AnotherClass(int id) : id_(id) {
        std::cout << "AnotherClass " << id_ << " constructed." << std::endl;
    }
    ~AnotherClass() {
        std::cout << "AnotherClass " << id_ << " destructed." << std::endl;
    }
    void display() {
        std::cout << "Value from AnotherClass " << id_ << "." << std::endl;
    }
private:
    int id_;
};

void shareObject(std::shared_ptr<AnotherClass> obj_ptr) {
    std::cout << "Inside shareObject function." << std::endl;
    obj_ptr->display();
    std::cout << "Reference count inside function: " << obj_ptr.use_count() << std::endl;
    std::cout << "Exiting shareObject function." << std::endl;
} // obj_ptr (local shared_ptr) goes out of scope here, decrementing ref count

int main() {
    std::cout << "--- std::shared_ptr Demonstration ---" << std::endl;

    // 1. Creating a shared_ptr
    // `std::make_shared` is the preferred way (more efficient).
    std::shared_ptr<AnotherClass> s_ptr1 = std::make_shared<AnotherClass>(100);
    s_ptr1->display();
    std::cout << "Reference count after s_ptr1 creation: " << s_ptr1.use_count() << std::endl;

    // 2. Copying shared_ptr (increases reference count)
    std::shared_ptr<AnotherClass> s_ptr2 = s_ptr1; // Copy constructor
    std::cout << "Reference count after s_ptr2 copy: " << s_ptr1.use_count() << std::endl;

    // 3. Passing shared_ptr by value (increases reference count temporarily)
    shareObject(s_ptr1);
    std::cout << "Reference count back in main: " << s_ptr1.use_count() << std::endl;

    // 4. Resetting a shared_ptr (decreases reference count)
    s_ptr2.reset(); // s_ptr2 no longer points to the object, ref count decrements
    std::cout << "Reference count after s_ptr2 reset: " << s_ptr1.use_count() << std::endl;

    // When s_ptr1 goes out of scope (end of main), it's the last shared_ptr,
    // so AnotherClass(100) will be destructed.
    std::cout << "Exiting main function." << std::endl;
    return 0;
} // AnotherClass(100) is destructed here
