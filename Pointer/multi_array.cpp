#include <iostream>

// --- Function to allocate memory for a dynamic 2D array ---
// This function creates a 2D array of size `rows` x `cols` on the heap.
// It returns a pointer to a pointer (`int**`), which serves as a handle to the array.
int** createTwoDArray(int rows, int cols) {
    // 1. Allocate an array of pointers (one pointer for each row).
    int** arr = new int*[rows];

    // 2. For each row pointer, allocate memory for the columns.
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
    }
    return arr;
}

// --- Function to handle user input for the dynamic 2D array ---
// This function populates the dynamically allocated 2D array with user input.
void fillTwoDArray(int** arr, int rows, int cols) {
    std::cout << "Please enter " << rows * cols << " integer values to fill the 2D array." << std::endl;
    std::cout << "The array is a " << rows << "x" << cols << " grid." << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Enter value for element [" << i << "][" << j << "]: ";
            // Using array-like syntax on the `int**` pointer is the cleanest way.
            std::cin >> arr[i][j];
        }
    }
    std::cout << std::endl;
}

// --- Function to print a dynamic 2D array ---
// This function displays the contents of the dynamically allocated 2D array.
void printTwoDArray(int** arr, int rows, int cols) {
    std::cout << "Displaying the 2D array's contents:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// --- Function to deallocate memory ---
// This is a crucial step to prevent memory leaks.
// Memory must be freed in the reverse order it was allocated:
// 1. Delete each row.
// 2. Delete the array of row pointers.
void deleteTwoDArray(int** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i]; // Delete the columns for each row
    }
    delete[] arr; // Delete the array of row pointers
}

int main() {
    int rows, cols;

    // Get the dimensions from the user at runtime.
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;
    std::cout << "\n----------------------------------------\n" << std::endl;

    // Create the dynamic 2D array.
    int** dynamicArray = createTwoDArray(rows, cols);

    // Fill the array with user input.
    fillTwoDArray(dynamicArray, rows, cols);
    
    std::cout << "\n----------------------------------------\n" << std::endl;

    // Print the array.
    printTwoDArray(dynamicArray, rows, cols);

    // Free the memory. This is very important!
    deleteTwoDArray(dynamicArray, rows);

    return 0;
}
