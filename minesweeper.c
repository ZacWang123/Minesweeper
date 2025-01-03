#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//gcc minesweeper.c -o minesweeper

void Print_Grid(int rows, int cols, int** grid) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void Start_Game(int rows, int cols, int** grid) {
    Print_Grid(rows, cols, grid);
}

int Within_Grid(int newRow, int newCol, int rows, int cols) {
    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
        return 1;
    }
    return 0;
}

int** Calculate_Neighbors(int rows, int cols, int** grid) {
    int newRow;
    int newCol;
    int mineCounter = 0;
    int neighbors[8][2] = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mineCounter = 0;
            if (grid[i][j] != -1) {
                for (int k = 0; k < 8; k++) {
                    newRow = i + neighbors[k][0];
                    newCol = j + neighbors[k][1];
                    if (Within_Grid(newRow, newCol, rows, cols)) {
                        if (grid[newRow][newCol] == -1) {
                            mineCounter += 1;
                        }
                    }
                }
                grid[i][j] = mineCounter;
            }
        }
    }

    return grid;
}

int** Place_Mines(int rows, int cols, int numMines, int** grid) {
    int mineCounter = 0;
    int randrow;
    int randcol;
    randrow = rand() % rows;
    randcol = rand() % cols;

    while (mineCounter < numMines) {
        while (grid[randrow][randcol] != 0) {
            randrow = rand() % rows;
            randcol = rand() % cols;
        }
        grid[randrow][randcol] = -1;
        mineCounter += 1;
    }

    return grid;
}

int** Create_Game(int rows, int cols, int numMines) {
    int **grid = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        grid[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }

    grid = Place_Mines(rows, cols, numMines, grid);

    grid = Calculate_Neighbors(rows, cols, grid);

    return grid;
}

int Get_Input(char* text, int minValue, int maxValue) {
    int value;

    printf("%s", text);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue) {
        printf("Invalid input, please input a number between %d and %d\n", minValue, maxValue);
        while (getchar() != '\n');
    }

    return value;
}

int Get_Mines(int rows, int cols, int difficulty) {
    int cells;
    int numMines;

    cells = rows * cols;
    numMines = difficulty * 0.1 * cells;

    return numMines;
}

int main() {
    int rows;
    int cols;
    int difficulty;
    int numMines;
    int** gameGrid;

    srand(time(NULL));

    rows = Get_Input("Input the number of rows[1-10]: \n", 1, 15);
    cols = Get_Input("Input the number of columns[1-10]: \n", 1, 15);
    difficulty = Get_Input("Input the difficulty level[1-9]: \n", 1, 9);

    numMines = Get_Mines(rows, cols, difficulty);

    printf("rows: %d  columns: %d  mines: %d\n", rows, cols, numMines);

    gameGrid = Create_Game(rows, cols, numMines);

    Start_Game(rows, cols, gameGrid);

    return 0;
}