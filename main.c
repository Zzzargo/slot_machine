#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void displayMatrix(int **mat, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


// Spin downwards a column
void spin_col(int **mat, int rows, int columns, int column_to_spin, int times) {
    if (column_to_spin >= columns) {
        printf("Invalid input for column to spin");
    } else {
        for (int i = times; i > 0; i--) {
            int aux = mat[rows - 1][column_to_spin];
            for (int j = rows - 1; j > 0; j--) {
                mat[j][column_to_spin] = mat[j - 1][column_to_spin];
            }
            mat[0][column_to_spin] = aux;
        }
    }
}


// Calculate the number of winning lines and the score
void win(int **mat, int rows, int columns, int* winCount, int* score) {
    bool *distinctValues = calloc(10, sizeof(bool));
    int distinctValuesCount = 0;

    for (int i = 0; i < 3; i++) {
        int currentValue = mat[i][0];
        distinctValues[currentValue] = true;
        int maxLengthStreakValue = 0;
        int streakLengthCurrent = 0;
        int streakLengthMax = 1;

        for (int j = 0; j < columns; j++) {
            // Checking for row sequences
            if (mat[i][j] == currentValue) {
                streakLengthCurrent++;
                // Getting the longest sequence found in a row
                if (streakLengthCurrent >= 3 && streakLengthCurrent >= streakLengthMax) {
                    streakLengthMax = streakLengthCurrent;
                    maxLengthStreakValue = mat[i][j];
                }
            } else {
                currentValue = mat[i][j];
                if (distinctValues[currentValue] == 0) {
                    distinctValues[currentValue] = true;
                }
                streakLengthCurrent = 1;
            }

            // Checking for diagonal sequences
            if (i == 0 && j < columns - 2) {
                int firstDiagonalValue = mat[0][j], secondDiagonalValue = mat[0][j + 2];
                bool firstDiagonalFound = true, secondDiagonalFound = true;

                // Building 3x3 squares for every j to check the diagonals. I chose to do it when i = 0
                for (int k = 0; k < 3; k++) {
                    if (mat[k][j + k] != firstDiagonalValue) {
                        firstDiagonalFound = false;
                    }
                    if (mat[k][j + 2 - k] != secondDiagonalValue) {
                        secondDiagonalFound = false;
                    }
                }

                // An "X" was found
                if (firstDiagonalFound && secondDiagonalFound) {
                    if (firstDiagonalValue == 7) {
                        (*winCount)++;
                        (*score) += 21*2;
                        continue;
                    }
                    (*winCount)++;
                    (*score) += 21;
                    continue;
                }

                // A single diagonal was found
                if (firstDiagonalFound || secondDiagonalFound) {
                    if (firstDiagonalFound && firstDiagonalValue == 7) {
                        (*winCount)++;
                        (*score) += 7*2;
                        continue;
                    }
                    if (secondDiagonalFound && secondDiagonalValue == 7) {
                        (*winCount)++;
                        (*score) += 7*2;
                        continue;
                    }
                    (*winCount)++;
                    (*score) += 7;
                }
            }
        }

        // Checking if the current row had winning sequences
        if (streakLengthMax >= 3) {
            (*winCount)++;
            if (maxLengthStreakValue == 7) {
                (*score) += streakLengthMax*2;
            } else {
                (*score) += streakLengthMax;
            }
        }
    }

    // Checking how many distinct values were found
    for (int i = 0; i < 10; i++) {
        if (distinctValues[i] != 0) {
            distinctValuesCount++;
        }
    }
    if (distinctValuesCount <= 2) {
        (*score) += 100;
    } else {
        if (distinctValuesCount <= 4) {
            (*score) += 15;
        }
    }
    free(distinctValues);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    unsigned char task = 0;
    int rows = 0, columns = 0, i = 0, j = 0;
    scanf("%c", &task);
    scanf("%d %d", &rows, &columns);


    // Allocation of the matrix
    int **matrix = malloc(sizeof(int*) * rows);

    for (i = 0; i < rows; i++) {
        matrix[i] = calloc(columns, sizeof(int));
    }
    // READING
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    switch (task) {
        // Task 1
        case '1': {
            int column_to_spin = 0, spins = 0;
            scanf("%d %d", &column_to_spin, &spins);
            spin_col(matrix, rows, columns, column_to_spin, spins);
            displayMatrix(matrix, rows, columns);
            break;
        }

        // Task 2
        case '2': {
            int winningSequences = 0;
            int score = 0;
            win(matrix, rows, columns, &winningSequences, &score);
            printf("%d\n%d\n", winningSequences, score);
            break;
        }

        // Task 3
        case '3': {
            int timesToCallSpin = 0;
            int winningSequences = 0;
            int score = 0;

            scanf("%d", &timesToCallSpin);
            for (i = 0; i < timesToCallSpin; i++) {
                int column_to_spin = 0, spins = 0;
                scanf("%d %d", &column_to_spin, &spins);
                // if (i == 0) {
                //     win(matrix, rows, columns, &winningSequences, &score);
                // }
                spin_col(matrix, rows, columns, column_to_spin, spins);
                win(matrix, rows, columns, &winningSequences, &score);
            }
            printf("%d\n", score);
            break;
        }

        // Task 4
        case '4': {
            int maxScore = 0;
            for (i = 0; i < 3; i++) {
                for (j = 0; j <= columns; j++) {
                    for (int k = 0; k <= 9; k++) {
                        int testScore = 0;
                        int winningSequences = 0;

                        // Changing a value
                        int aux = matrix[i][j];
                        matrix[i][j] = k;

                        win(matrix, rows, columns, &winningSequences, &testScore);
                        if (testScore > maxScore) {
                            maxScore = testScore;
                        }

                        // Resetting the value
                        matrix[i][j] = aux;
                    }
                }
            }
            printf("%d\n", maxScore);
            break;
        }

        // Task 5
        case '5': {
            int maxScore = 0;
            for (int indexColumn1 = 0; indexColumn1 < columns; indexColumn1++) {
                for (int indexColumn2 = 0; indexColumn2 < columns; indexColumn2++) {
                    for (int timesToSpinColumn1 = 0; timesToSpinColumn1 < rows; timesToSpinColumn1++) {
                        for (int timesToSpinColumn2 = 0; timesToSpinColumn2 < rows; timesToSpinColumn2++) {
                            int winningSequences = 0;
                            int testScore = 0;
                            spin_col(matrix, rows, columns, indexColumn1, timesToSpinColumn1);
                            spin_col(matrix, rows, columns, indexColumn2, timesToSpinColumn2);
                            win(matrix, rows, columns, &winningSequences, &testScore);

                            if (testScore > maxScore) {
                                maxScore = testScore;
                            }
                        }
                    }
                }
            }
            printf("%d\n", maxScore);
            break;
        }

        // Task 6
        case '6': {
            // The values of the following matrix represent the cost of the minimum cost path
            // from the upper-left corner to the value
            int **costMatrix = malloc(sizeof(int *) * 3);
            for (i = 0; i < 3; i++) {
                costMatrix[i] = calloc(columns, sizeof(int));
            }

            for (i = 0; i < 3; i++) {
                for (j = 0; j < columns; j++) {
                    costMatrix[i][j] = __INT_MAX__;  // To get the minimum cost path for each cell
                }
            }

            costMatrix[0][0] = 0;
            // The matrix is being processed by columns, not by rows, so first i will be incremented, then j
            for (j = 0; j < columns; j++) {
                for (i = 0; i < 3; i++) {
                    // Calculating minimum cost paths to each neighbour
                    if (i > 0) {  // Above
                        int absDiff = abs(matrix[i-1][j] - matrix[0][0]);
                        costMatrix[i-1][j] = min(costMatrix[i-1][j], costMatrix[i][j] + absDiff);
                    }
                    if (i < 2) {  // Below
                        int absDiff = abs(matrix[i+1][j] - matrix[0][0]);
                        costMatrix[i+1][j] = min(costMatrix[i+1][j], costMatrix[i][j] + absDiff);
                    }
                    if (j > 0) {  // Left
                        int absDiff = abs(matrix[i][j-1] - matrix[0][0]);
                        costMatrix[i][j-1] = min(costMatrix[i][j-1], costMatrix[i][j] + absDiff);
                    }
                    if (j < columns-1) {  // Right
                        int absDiff = abs(matrix[i][j+1] - matrix[0][0]);
                        costMatrix[i][j+1] = min(costMatrix[i][j+1], costMatrix[i][j] + absDiff);
                    }
                }
            }

            printf("%d\n", costMatrix[2][columns-1]);
            // Free cost matrix
            for (i = 0; i < 3; i++) {
                free(costMatrix[i]);
            }
            free(costMatrix);
            break;
        }
    }
    // Freeing memory
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
