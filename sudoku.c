#include <stdio.h>

#define N 9

// Function prototypes
int isSafe(int grid[N][N], int row, int col, int num);
int solveSudoku(int grid[N][N]);
void printGrid(int grid[N][N]);

int main() {
    // Example Sudoku puzzle (0 represents an empty cell)
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printf("Solved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
}

// Function to check if placing a number is valid
int isSafe(int grid[N][N], int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return 0;

    // Check the column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return 0;

    // Check the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

// Function to solve the Sudoku using backtracking
int solveSudoku(int grid[N][N]) {
    int row, col;
    int empty = 0;

    // Find an empty cell (represented by 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                empty = 1;
                break;
            }
        }
        if (empty) break;
    }

    // If there are no empty cells, the puzzle is solved
    if (!empty)
        return 1;

    // Try placing numbers 1-9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;  // Place the number

            // Recursively attempt to solve the rest of the grid
            if (solveSudoku(grid))
                return 1;

            grid[row][col] = 0;  // Undo if placing the number leads to no solution
        }
    }

    return 0;  // Trigger backtracking
}