#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int** Create_Grid(int rows, int cols, int difficulty) {
    int **grid = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        grid[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }

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

int main() {
    int rows;
    int cols;
    int difficulty;
    int** grid;

    rows = Get_Input("Input the number of rows[1-10]: \n", 1, 10);
    cols = Get_Input("Input the number of columns[1-10]: \n", 1, 10);
    difficulty = Get_Input("Input the difficulty level[1-10]: \n", 1, 10);

    printf("rows: %d  columns: %d  difficulty: %d\n", rows, cols, difficulty);

    grid = Create_Grid(rows, cols, difficulty);

    Start_Game(rows, cols, grid);

    return 0;
}