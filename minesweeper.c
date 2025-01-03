#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//gcc minesweeper.c -o minesweeper

void Print_Grid(int rows, int cols, int** gameGrid, int** revealGrid) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (revealGrid[i][j] == 1) {
                if (gameGrid[i][j] == -1) {
                    printf("* ");
                } else {
                    printf("%d ", gameGrid[i][j]);
                }
            } else if (revealGrid[i][j] == -1) {
                printf("! ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("\n");

    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         printf("%d ", gameGrid[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}

int Within_Grid(int newRow, int newCol, int rows, int cols) {
    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
        return 1;
    }
    return 0;
}

void Get_Action(char* action, int* userRow, int* userCol){
    char actionBuffer[10];
    char* token;

    printf("Please input an action, r to reveal, f to flag followed by x and y or just q to quit\n");

    if (fgets(actionBuffer, sizeof(actionBuffer), stdin) != NULL) {
        actionBuffer[strcspn(actionBuffer, "\n")] = '\0';
        token = strtok(actionBuffer, " ");
        *action = token[0];

        token = strtok(NULL, " ");
        *userRow = atoi(token);

        token = strtok(NULL, " ");
        *userCol = atoi(token);
    }
}

int Validate_Action(char action, int userRow, int userCol, int row, int col) {
    if (!(action == 'q' || action == 'r' || action == 'f')) {
        return 0;
    }

    if (!Within_Grid(userRow, userCol, row, col)) {
        return 0;
    }

    return 1;
}

void Start_Game(int rows, int cols, int** gameGrid, int** revealedGrid) {
    int gameActive = 1;
    char action;
    int userRow;
    int userCol;

    while (getchar() != '\n');

    while (gameActive) {
        Print_Grid(rows, cols, gameGrid, revealedGrid);

        Get_Action(&action, &userRow, &userCol);
        if (!Validate_Action(action, userRow, userCol, rows, cols)) {
            printf("Invalid Action\n");
            continue;
        }

        if (action == 'q') {
            printf("Quitting");
            break;
        }

        if (action == 'r') {
            revealedGrid[userRow][userCol] = 1;
            if (gameGrid[userRow][userCol] == 0) {
                
            }
        }

        if (action == 'f') {
            if (revealedGrid[userRow][userCol] == 1) {
                printf("Cannot flag a revealed cell\n");
                continue;
            } else if (revealedGrid[userRow][userCol] == -1) {
                revealedGrid[userRow][userCol] = 0;
            } else {
                revealedGrid[userRow][userCol] = -1;
            }
        }
    }
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

int** Create_Reveal(int rows, int cols) {
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

int Get_Mines(int rows, int cols, int difficulty) {
    int cells;
    int numMines;

    cells = rows * cols;
    numMines = (0.1 + (difficulty * 0.01)) * cells;

    return numMines;
}

int main() {
    int rows;
    int cols;
    int difficulty;
    int numMines;
    int** gameGrid;
    int** revealedGrid;

    srand(time(NULL));

    rows = Get_Input("Input the number of rows[1-15]: \n", 1, 15);
    cols = Get_Input("Input the number of columns[1-15]: \n", 1, 15);
    difficulty = Get_Input("Input the difficulty level[1-9]: \n", 1, 9);

    numMines = Get_Mines(rows, cols, difficulty);

    printf("rows: %d  columns: %d  mines: %d \n", rows, cols, numMines);

    gameGrid = Create_Game(rows, cols, numMines);

    revealedGrid = Create_Reveal(rows, cols);

    Start_Game(rows, cols, gameGrid, revealedGrid);

    return 0;
}