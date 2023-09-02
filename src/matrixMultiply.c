/*
    File Name:      matrixMultiply.c
    Description:    Implementation File For Matrix Multiplication
*/

#include "matrixMultiply.h"

int runMultiThreadMatMul(Matrix* matrixA, Matrix* matrixB, Matrix* matrixC) {
    if (!matrixA || !matrixB || !matrixC) {
        return 1;
    }

    /* Validate */
    return 0;
}

void freeMatrix(int** matrix, int rows) {
    if (!matrix || rows <= 0) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
