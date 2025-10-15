#include <iostream>
#include <string>

// The 'Student' class is the base class with private data and a public interface.
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

    void setGpa(double newGpa) {
        if (newGpa >= 0.0 && newGpa <= 4.0) {
            gpa = newGpa;
        } else {
            std::cout << "Invalid GPA value." << std::endl;
        }
    }

    void setYearOfStudying(int newYear) {
        if (newYear > 0) {
            yearOfStudying = newYear;
        } else {
            std::cout << "Invalid year." << std::endl;
        }
    }

    std::string getStudentID() const { return studentID; }
    std::string getName() const { return name; }
    std::string getMajor() const { return major; }
    double getGpa() const { return gpa; }
    int getYearOfStudying() const { return yearOfStudying; }

    void displayInfo() {
        std::cout << "ID: " << studentID << ", Name: " << name << ", Major: " << major
                  << ", GPA: " << gpa << ", Year: " << yearOfStudying << std::endl;
    }
};

// The 'Undergraduate' class inherits from 'Student' and adds a unique attribute.
class Undergraduate : public Student {
public:
    std::string majorConcentration; // A unique attribute for undergraduates.

    Undergraduate(std::string id, std::string n, std::string m, double gpaVal, int year, std::string concentration)
        : Student(id, n, m, gpaVal, year), majorConcentration(concentration) {}

    void celebrate() {
        std::cout << name << " is celebrating completing their " << getYearOfStudying()
                  << " year of studying with a concentration in " << majorConcentration << "!" << std::endl;
    }
};

// The 'Graduate' class inherits from 'Student' and adds a unique attribute.
class Graduate : public Student {
public:
    std::string researchTopic; // A unique attribute for graduates.

    Graduate(std::string id, std::string n, std::string m, double gpaVal, int year, std::string topic)
        : Student(id, n, m, gpaVal, year), researchTopic(topic) {}

    void presentResearch() {
        std::cout << name << " is presenting their research on " << researchTopic << "." << std::endl;
    }
};

int main() {
    Undergraduate undergrad("U101", "Alice", "Computer Science", 3.85, 3, "Cybersecurity");
    Graduate grad("G202", "Bob", "Physics", 4.0, 1, "Quantum Computing");

    undergrad.displayInfo();
    undergrad.celebrate();

    std::cout << "------------------------------------------" << std::endl;

    grad.displayInfo();
    grad.presentResearch();

    return 0;
}