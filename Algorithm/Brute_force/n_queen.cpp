#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Global counter for the number of solutions found
int solution_count = 0;

/**
 * @brief Prints a single valid configuration of the chessboard.
 *
 * @param N The size of the board (N x N).
 * @param columns A vector where columns[i] is the column index of the queen in row i.
 */
void printSolution(int N, const vector<int>& columns) {
    cout << "\n--- Solution " << ++solution_count << " ---\n";

    // Print column headers
    cout << "  ";
    for (int c = 0; c < N; ++c) {
        cout << c << " ";
    }
    cout << "\n";

    // Print the board row by row
    for (int r = 0; r < N; ++r) {
        cout << r << " "; // Print row header
        for (int c = 0; c < N; ++c) {
            if (columns[r] == c) {
                // Found the queen at this position
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << "\n";
    }
}

/**
 * @brief Checks if a queen can be safely placed at (row, col)
 * with respect to all previously placed queens (in rows 0 to row-1).
 *
 * @param row The current row where we are attempting to place a queen.
 * @param col The current column where we are attempting to place a queen.
 * @param columns A vector containing the column positions of queens in preceding rows.
 * @return true if the placement is safe, false otherwise.
 */
bool isSafe(int row, int col, const vector<int>& columns) {
    // Check all previous rows (0 up to row - 1)
    for (int prev_row = 0; prev_row < row; ++prev_row) {
        
        int prev_col = columns[prev_row];

        // 1. Check for same column (vertical attack)
        if (prev_col == col) {
            return false;
        }

        // 2. Check diagonals
        // The difference in rows must equal the difference in columns for a diagonal attack.
        if (abs(prev_col - col) == abs(prev_row - row)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief The recursive backtracking function to solve the N-Queens problem.
 * This function systematically tries to place a queen in the current row
 * and recursively calls itself for the next row.
 *
 * @param N The total size of the board.
 * @param row The current row we are trying to fill.
 * @param columns A vector where columns[r] stores the column index of the queen in row r.
 */
void solveNQueens(int N, int row, vector<int>& columns) {
    
    // 1. Base Case: All queens have been placed successfully (We reached the row after the last one).
    if (row == N) {
        printSolution(N, columns);
        return;
    }

    // 2. Recursive Step: Try placing a queen in every column of the current row.
    // This is the BRUTE FORCE element: check all N columns.
    for (int col = 0; col < N; ++col) {
        
        // Check if the current placement is safe from previous queens.
        if (isSafe(row, col, columns)) {
            
            // a) Tentatively place the queen (MAKE CHOICE)
            columns[row] = col;

            // b) Recurse to the next row (EXPLORE)
            solveNQueens(N, row + 1, columns);

            // c) Backtrack (UNDO CHOICE)
            // The choice is automatically undone when the current function call returns
            // and the 'col' loop moves to the next iteration. We don't need to explicitly
            // reset columns[row] because it will be overwritten in the next iteration 
            // of the 'col' loop or when backtracking to a previous row.
            // For clarity, we can skip explicit undo here, as the loop handles it.
        }
        // If isSafe is false, we implicitly skip this column and try the next one.
    }
}

// --- Driver Code ---

int main() {
    // Set the board size. 8 is the standard N-Queens problem.
    const int N = 8; 

    // This vector stores the column index of the queen for each row.
    // Example: columns[0] = 3 means the queen in row 0 is in column 3.
    vector<int> columns(N);

    cout << "Starting N-Queens Solver (Backtracking Brute Force) for N=" << N << "...\n";

    // Start solving from the first row (row 0)
    solveNQueens(N, 0, columns);

    cout << "\n-------------------------------------\n";
    cout << "Total solutions found for N=" << N << ": " << solution_count << "\n";
    cout << "-------------------------------------\n";

    return 0;
}
