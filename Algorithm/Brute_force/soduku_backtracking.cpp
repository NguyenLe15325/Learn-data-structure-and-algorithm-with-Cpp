#include <iostream>
#include <vector>

// Define the size of the Sudoku grid (9x9)
const int N = 9;

// --- Helper Functions ---

/**
 * @brief Checks if the given number is safe to place in the current row.
 */
bool usedInRow(const int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the given number is safe to place in the current column.
 */
bool usedInCol(const int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the given number is safe to place in the current 3x3 box.
 */
bool usedInBox(const int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + boxStartRow][col + boxStartCol] == num) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks if the number is valid to place at grid[row][col].
 */
bool isSafe(const int grid[N][N], int row, int col, int num) {
    // Check row, column, and the corresponding 3x3 box
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

/**
 * @brief Finds the first unassigned location (a cell with value 0).
 * @return True if an unassigned cell is found, false otherwise.
 */
bool findUnassignedLocation(const int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cell found (grid is full)
}

/**
 * @brief Prints the Sudoku grid with dividers for better visualization.
 */
void printGrid(const int grid[N][N]) {
    std::cout << "  -------------------------\n";
    for (int row = 0; row < N; row++) {
        std::cout << " | ";
        for (int col = 0; col < N; col++) {
            std::cout << grid[row][col] << (col % 3 == 2 ? " | " : " ");
        }
        std::cout << "\n";
        if (row % 3 == 2) {
            std::cout << "  -------------------------\n";
        }
    }
}

// --- Main Backtracking Function ---

/**
 * @brief The recursive function that solves the Sudoku using backtracking.
 * @return True if a solution exists and is found, false otherwise.
 */
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // 1. Base Case: If no unassigned location is found, the puzzle is solved.
    if (!findUnassignedLocation(grid, row, col)) {
        return true; 
    }

    // 2. Recursive Step: Try numbers 1 through 9.
    for (int num = 1; num <= 9; num++) {
        
        // Check if placing 'num' at (row, col) is valid
        if (isSafe(grid, row, col, num)) {
            
            // a) Tentatively place the number
            grid[row][col] = num;

            // b) Recursively try to solve the rest of the puzzle
            if (solveSudoku(grid)) {
                return true; // Success! Solution found.
            }

            // c) FAILURE (Backtrack): If the number leads to an invalid state, 
            //    reset the cell to 0 and try the next number (num + 1).
            grid[row][col] = 0;
        }
    }

    // 3. Complete Failure: If no number from 1-9 works in this cell, 
    //    return false, triggering backtracking to the previous cell.
    return false;
}


// --- Driver Code ---

int main() {
    // Example difficult Sudoku puzzle (0 represents an empty cell)
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    std::cout << "--- Unsolved Sudoku Grid ---\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        std::cout << "\n--- Solved Sudoku Grid ---\n";
        printGrid(grid);
    } else {
        std::cout << "\nNo solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}
