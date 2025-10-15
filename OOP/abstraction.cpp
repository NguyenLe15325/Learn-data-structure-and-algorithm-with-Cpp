#include <iostream>  // Includes the standard input/output stream library for printing to the console.
#include <string>    // Includes the string library to use the std::string data type.

/*
 * This is an abstract base class. It serves as a blueprint for other classes.
 * It enforces abstraction by including a pure virtual function, 'study()', which
 * any derived class MUST implement.
 * The data members are private, which enforces encapsulation. The public methods
 * act as the secure interface for interacting with a Student object.
 */
class Student {
private: // The 'private' access specifier enforces encapsulation.
    // These data members are hidden from external code AND from derived classes.
    std::string studentID;
    std::string name;
    std::string major;
    double gpa;
    int yearOfStudying;

public: // The 'public' section contains the interface for the class.
    // This is the constructor. It's a special public method that's called automatically
    // when a new Student object is created, ensuring the object is in a valid state
    // from the start.
    Student(std::string id, std::string n, std::string m, double gpaVal, int year) {
        studentID = id;
        name = n;
        major = m;
        gpa = gpaVal;
        yearOfStudying = year;
    }
    
    // A public "setter" method for GPA. This is part of the class's public interface
    // and enforces encapsulation by validating the data before it's assigned.
    void setGpa(double newGpa) {
        if (newGpa >= 0.0 && newGpa <= 4.0) {
            gpa = newGpa; // Validated data is assigned to the private member.
        } else {
            std::cout << "Invalid GPA value." << std::endl;
        }
    }
    
    // A public "setter" method for the year of studying, also with validation.
    void setYearOfStudying(int newYear) {
        if (newYear > 0) {
            yearOfStudying = newYear;
        } else {
            std::cout << "Invalid year." << std::endl;
        }
    }
    
    // Pure virtual function. The '= 0' syntax makes this an abstract function.
    // Any class inheriting from 'Student' MUST provide its own implementation of 'study()'.
    // This is the core of abstraction: hiding the "how" and only showing the "what."
    virtual void study() = 0;
    
    // Public getter methods to allow derived classes and external code to access the private data.
    // These are safe because they are "read-only" and don't allow direct modification.
    // The 'const' keyword guarantees that these methods will not change the object's state.
    std::string getStudentID() const { return studentID; }
    std::string getName() const { return name; }
    std::string getMajor() const { return major; }
    double getGpa() const { return gpa; }
    int getYearOfStudying() const { return yearOfStudying; }
    
    // A concrete public method that all derived classes can use to display information.
    void displayInfo() {
        std::cout << "ID: " << studentID << ", Name: " << name << ", Major: " << major
                  << ", GPA: " << gpa << ", Year: " << yearOfStudying << std::endl;
    }
};

/*
 * The 'Undergraduate' class inherits publicly from the 'Student' class.
 * This establishes an "is-a" relationship (an Undergraduate is a Student).
 * Public inheritance means that public members of 'Student' remain public in 'Undergraduate'.
 * The private members of 'Student' remain inaccessible.
 * The derived class must implement the pure virtual function 'study()', which is the
 * key to abstraction and polymorphism.
 */
class Undergraduate : public Student {
public:
    // The constructor for Undergraduate. It calls the base class constructor to initialize
    // the inherited members using an initializer list, a standard C++ practice.
    Undergraduate(std::string id, std::string n, std::string m, double gpaVal, int year)
        : Student(id, n, m, gpaVal, year) {}
        
    // This function provides the specific implementation for the 'study' pure virtual function.
    // It's a form of abstraction and polymorphism, as this method's behavior is unique
    // to an undergraduate student. The 'override' keyword is a good practice.
    void study() override {
        // We use the public getter methods to safely access the private data from the base class.
        std::cout << getName() << " is attending lectures and completing assignments for their undergraduate degree." << std::endl;
    }
};

/*
 * The 'Graduate' class also inherits publicly from 'Student'.
 * This also establishes an "is-a" relationship.
 * The derived class must also implement the 'study()' method, but with its own
 * specific behavior.
 */
class Graduate : public Student {
public:
    std::string researchTopic;

    // The constructor for Graduate. It calls the base class constructor and initializes its own member.
    Graduate(std::string id, std::string n, std::string m, double gpaVal, int year, std::string topic)
        : Student(id, n, m, gpaVal, year), researchTopic(topic) {}
        
    // This is the Graduate's specific implementation of the 'study' function.
    // Polymorphism allows the program to call the correct version of this function
    // based on the object's type at runtime.
    void study() override {
        std::cout << getName() << " is conducting research on " << researchTopic << " for their thesis." << std::endl;
    }
};

int main() {
    // Creating an Undergraduate object and a Graduate object.
    Undergraduate undergrad("U101", "Alice", "Computer Science", 3.85, 3);
    Graduate grad("G202", "Bob", "Physics", 4.0, 1, "Quantum Computing");

    // We can call the 'displayInfo' function on both objects.
    // This method is inherited from the Student base class.
    undergrad.displayInfo();
    grad.displayInfo();
    
    // This demonstrates polymorphism. We can call the same function 'study()'
    // on different object types, and the correct behavior is executed at runtime.
    undergrad.study();
    grad.study();

    // The following would cause a compile-time error because you cannot instantiate
    // an abstract class directly.
    // Student s("S100", "Invalid", "N/A", 0.0, 0);

    return 0; // Standard return value indicating successful program execution.
}