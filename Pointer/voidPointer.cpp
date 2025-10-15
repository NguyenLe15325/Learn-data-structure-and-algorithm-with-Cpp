#include <iostream>

// Use an enum to represent the data types we want to handle.
enum class DataType {
    INT,
    DOUBLE,
    CHAR
};

// This function accepts a void pointer and a DataType enum.
void printData(void* data_pointer, DataType type) {
    // A switch statement is used to handle each data type.
    // This allows us to perform the correct cast and dereference.
    switch (type) {
        case DataType::INT:
            // Cast the void pointer to an int pointer and then dereference.
            std::cout << "Data is an integer: " << *(static_cast<int*>(data_pointer)) << std::endl;
            break;
        case DataType::DOUBLE:
            // Cast the void pointer to a double pointer and then dereference.
            std::cout << "Data is a double: " << *(static_cast<double*>(data_pointer)) << std::endl;
            break;
        case DataType::CHAR:
            // Cast the void pointer to a char pointer and then dereference.
            std::cout << "Data is a character: " << *(static_cast<char*>(data_pointer)) << std::endl;
            break;
        default:
            std::cout << "Unknown data type." << std::endl;
            break;
    }
}

// Main function to demonstrate the use of printData
int main() {
    int my_int = 100;
    double my_double = 3.14159;
    char my_char = 'A';

    // Call the function with a void pointer to an int
    printData(&my_int, DataType::INT);

    // Call the function with a void pointer to a double
    printData(&my_double, DataType::DOUBLE);

    // Call the function with a void pointer to a char
    printData(&my_char, DataType::CHAR);

    return 0;
}