#include <iostream>
#include <string>

// This is the original abstract base class.
class Student {
private:
    std::string studentID;
    std::string major;
    double gpa;
    int yearOfStudying;

protected:
    std::string name;

public:
    Student(std::string id, std::string n, std::string m, double gpaVal, int year) {
        studentID = id;
        name = n;
        major = m;
        gpa = gpaVal;
        yearOfStudying = year;
    }
    
    // A pure virtual function, making the class abstract.
    virtual void study() = 0;
    
    // Getters for accessing private data.
    std::string getName() const { return name; }
    std::string getMajor() const { return major; }
};

// Undergraduate is a derived class that provides a specific implementation of study().
class Undergraduate : public Student {
private:
    std::string majorConcentration; // Unique attribute for undergraduates.
public:
    Undergraduate(std::string id, std::string n, std::string m, double gpaVal, int year, std::string concentration)
        : Student(id, n, m, gpaVal, year), majorConcentration(concentration) {}
        
    // Provides the unique implementation for study().
    void study() override {
        std::cout << name << " is attending lectures for their " << getMajor() << " degree with a concentration in " << majorConcentration << "." << std::endl;
    }
};

// Graduate is another derived class with its own implementation of study().
class Graduate : public Student {
private:
    std::string researchTopic; // Unique attribute for graduates.
public:
    Graduate(std::string id, std::string n, std::string m, double gpaVal, int year, std::string topic)
        : Student(id, n, m, gpaVal, year), researchTopic(topic) {}
        
    // Provides its unique implementation for study().
    void study() override {
        std::cout << name << " is conducting research on " << researchTopic << " for their thesis." << std::endl;
    }
};

int main() {
    // Create base class pointers for polymorphism.
    Student* student1;
    Student* student2; 
    
    // Assign a derived class object to each base class pointer.
    student1 = new Undergraduate("U101", "Alice", "Computer Science", 3.85, 3, "Cybersecurity");
    student2 = new Graduate("G202", "Bob", "Physics", 4.0, 1, "Quantum Computing");
    
    // Call the same function on each pointer.
    // At runtime, the program determines the actual object type and calls the correct
    // study() method—either Undergraduate's or Graduate's.
    student1->study();
    student2->study();
    
    // Clean up dynamically allocated memory.
    delete student1;
    delete student2;
    
    return 0;
}