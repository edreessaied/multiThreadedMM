/*
    File Name:      matrixMultiply.h
    Description:    Header File For Matrix Multiplication
*/

#ifndef  MATRIXMULTIPLY_H 
#define MATRIXMULTIPLY_H

/* Struct definition for a matrix */
typedef struct Matrix {
    int** matrix;
    int rows;
    int cols;
} Matrix;

int runMultiThreadMatMul();
void freeMatrix(int** matrix, int rows);

#endif