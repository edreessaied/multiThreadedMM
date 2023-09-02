/*
    File Name:      matrixMultiply.h
    Description:    Header File For Matrix Multiplication
*/

#include "userInput.h"

/* Struct definition for a matrix */
typedef struct Matrix {
    int** matrix;
    int rows;
    int cols;
} Matrix;

int runMultiThreadMatMul(Matrix* matrixA, Matrix* matrixB, Matrix* matrixC);
void freeMatrix(int** matrix, int rows);