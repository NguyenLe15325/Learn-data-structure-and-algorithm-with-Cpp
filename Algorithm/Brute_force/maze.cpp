#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Constants for the maze dimensions (N x N cells, results in 2N+1 x 2N+1 grid)
const int N_CELLS = 10;
const int SIZE = 2 * N_CELLS + 1; // 21x21 grid including walls

// Characters used for visualization
const char WALL = '#';
const char PASSAGE = ' ';
const char START = 'S';
const char END = 'E';
const char SOLUTION_PATH = '*';

// Global Maze Grid
char maze[SIZE][SIZE];

// --- Utility Functions ---

/**
 * @brief Prints the current state of the maze grid.
 */
void printMaze() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * @brief Checks if a position (r, c) is within the cell bounds of the maze.
 */
bool isCellValid(int r, int c) {
    // Cells must be within 1 and SIZE-2 (excluding outer wall)
    // and must be on an odd index (1, 3, 5, ...)
    return r > 0 && r < SIZE - 1 && c > 0 && c < SIZE - 1 && 
           (r % 2 == 1) && (c % 2 == 1);
}

// --- Maze Generation (Randomized DFS) ---

/**
 * @brief Recursively generates the maze by carving walls using Randomized DFS.
 * * This is the 'brute-force' generation component where every cell is explored.
 * The process starts at a cell and randomly explores unvisited neighbors.
 * When a dead end is reached, the function backtracks (returns) up the call stack.
 *
 * @param r Current row index (must be an odd index, representing a cell center).
 * @param c Current column index (must be an odd index, representing a cell center).
 */
void generateMaze(int r, int c) {
    // Possible directions (dr, dc): N, S, E, W
    std::vector<std::pair<int, int>> directions = {
        {-2, 0}, {2, 0}, {0, 2}, {0, -2}
    };

    // Use a random number generator engine
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

    // Explore neighbors in a random order
    for (const auto& dir : directions) {
        int dr = dir.first;
        int dc = dir.second;
        int next_r = r + dr;
        int next_c = c + dc;

        // Check if the next cell is valid and currently a wall (unvisited)
        if (isCellValid(next_r, next_c) && maze[next_r][next_c] == WALL) {
            
            // 1. Carve the passage (the wall between current and next cell)
            // The wall is at (r + dr/2, c + dc/2)
            maze[r + dr / 2][c + dc / 2] = PASSAGE; 
            
            // 2. Mark the next cell as visited (a passage)
            maze[next_r][next_c] = PASSAGE;

            // 3. Recurse (DFS) from the next cell
            generateMaze(next_r, next_c);
        }
    }
    // Backtracks automatically when the function returns (when all neighbors have been checked or visited)
}

// --- Maze Solving (Standard DFS/Brute Force) ---

/**
 * @brief Solves the maze using standard DFS (Backtracking).
 * * This is the 'brute-force' solving component. It explores a path completely 
 * until it hits a dead end or the exit, recursively trying all possibilities.
 *
 * @param r Current row index.
 * @param c Current column index.
 * @return true if the path leads to the exit, false otherwise (triggers backtrack).
 */
bool solveMaze(int r, int c) {
    // 1. Base Case: If the current cell is the exit (E), we found a solution.
    if (maze[r][c] == END) {
        return true;
    }

    // 2. Base Case: If the current cell is a Wall, outside bounds, or already
    //    part of the solution path, stop exploring this direction.
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || 
        maze[r][c] == WALL || maze[r][c] == SOLUTION_PATH) {
        return false;
    }

    // Ensure we only try to solve the actual passages, not just any cell.
    if (maze[r][c] != PASSAGE && maze[r][c] != START) {
        return false;
    }

    // 3. Recursive Step: Mark current cell as part of the tentative path
    //    (but avoid overwriting the START cell for clean visualization)
    if (maze[r][c] != START) {
        maze[r][c] = SOLUTION_PATH;
    }

    // Possible directions (r, c): N, E, S, W
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    // Try exploring all four adjacent directions (Brute-Force check)
    for (int i = 0; i < 4; ++i) {
        if (solveMaze(r + dr[i], c + dc[i])) {
            return true; // If successful, propagate success up the call stack
        }
    }

    // 4. Backtrack: If none of the directions lead to the exit, unmark the cell.
    //    This means the current path is a dead end.
    if (maze[r][c] == SOLUTION_PATH) {
        maze[r][c] = PASSAGE; // Reset to an open passage
    }
    
    return false; // Return failure to the previous function call
}


// --- Main Execution ---

int main() {
    // 1. Initialize Grid to ALL WALLS
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            maze[i][j] = WALL;
        }
    }

    // 2. Maze Generation using Randomized DFS
    // Start generation at cell (1, 1). Mark it as the starting passage.
    maze[1][1] = PASSAGE;
    std::cout << "--- Step 1: Generating " << N_CELLS << "x" << N_CELLS << " Maze ---\n";
    generateMaze(1, 1);
    
    // Set explicit Start and End points
    maze[1][1] = START;
    maze[SIZE - 2][SIZE - 2] = END;

    std::cout << "Unsolved Maze:\n";
    printMaze();

    // 3. Maze Solving using Standard DFS (Brute Force Backtracking)
    std::cout << "\n--- Step 2: Solving Maze with DFS Brute Force ---\n";
    if (solveMaze(1, 1)) {
        std::cout << "\nMaze Solved! Path marked with '" << SOLUTION_PATH << "'.\n";
    } else {
        std::cout << "\nNo path found.\n";
    }

    // 4. Print the final solved maze
    printMaze();

    return 0;
}
