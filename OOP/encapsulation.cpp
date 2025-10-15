#include <iostream>  // Includes the standard input/output stream library, which is needed for 'std::cout' to print to the console.
#include <string>    // Includes the string library, which allows us to use the 'std::string' data type for text.

class Student { // Defines a new class named 'Student'. This is a blueprint for creating student objects.
private: // The 'private' access specifier is a core part of encapsulation.
    // It means the following data members can only be accessed by methods within this class.
    // This hides the internal state of the object and protects it from direct, unauthorized modification.
    std::string studentID;      // A private data member to store the student's ID.
    std::string name;           // A private data member for the student's name.
    std::string major;          // A private data member for the student's major.
    double gpa;                 // A private data member for the student's GPA.
    int yearOfStudying;         // A private data member for the student's year.

public: // The 'public' access specifier makes the following methods accessible from outside the class.
    // These methods act as the official interface for interacting with a Student object.

    // This is the constructor. It's a special public method that's called automatically when a new Student object is created.
    // It takes five parameters and uses them to initialize the private data members.
    Student(std::string id, std::string n, std::string m, double gpaVal, int year) {
        studentID = id;          // Initializes the 'studentID' member with the 'id' parameter.
        name = n;                // Initializes the 'name' member.
        major = m;               // Initializes the 'major' member.
        gpa = gpaVal;            // Initializes the 'gpa' member.
        yearOfStudying = year;   // Initializes the 'yearOfStudying' member.
    }

    // A public "setter" method to modify the private 'gpa' data member.
    void setGpa(double newGpa) {
        // This is a key example of encapsulation. Before modifying the data, we validate the input.
        if (newGpa >= 0.0 && newGpa <= 4.0) {
            gpa = newGpa; // If the new GPA is valid, we update the private 'gpa' member.
        } else {
            // If the GPA is invalid, we print an error message and don't change the private data.
            // This prevents the object from ever being in an invalid state.
            std::cout << "Invalid GPA value." << std::endl;
        }
    }

    // Another public "setter" method, this time for the 'yearOfStudying' data member.
    void setYearOfStudying(int newYear) {
        // We validate the input to ensure the year is a positive number.
        if (newYear > 0) {
            yearOfStudying = newYear; // Update the private data if the input is valid.
        } else {
            std::cout << "Invalid year." << std::endl; // Output an error otherwise.
        }
    }

    // A public method to display the student's information.
    void displayInfo() {
        // This method can access all private members directly to print their values to the console.
        std::cout << "ID: " << studentID << ", Name: " << name << ", Major: " << major
                  << ", GPA: " << gpa << ", Year: " << yearOfStudying << std::endl;
    }
};

int main() { // The main function, where program execution begins.
    // Creates an object named 's' of the 'Student' class.
    // The constructor is called with the provided arguments to initialize the object.
    Student s("S12345", "Alice", "Computer Science", 3.85, 2);

    s.displayInfo(); // Calls the public 'displayInfo' method on the 's' object to print its current state.

    s.setGpa(4.1); // Calls the 'setGpa' method with an invalid value. The method's validation logic will catch this.
    
    s.setYearOfStudying(-1); // Calls the 'setYearOfStudying' method with an invalid value. This also gets caught.
    
    s.setGpa(3.95); // Calls 'setGpa' with a valid value. The private 'gpa' member will be successfully updated.
    
    s.setYearOfStudying(3); // Calls 'setYearOfStudying' with a valid value, updating the private member.
    
    s.displayInfo(); // Calls 'displayInfo' again to show the updated state of the 's' object.
    
    return 0; // Indicates successful program execution.
}