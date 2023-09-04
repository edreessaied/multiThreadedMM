/*
    File Name:      matrixMultiply.h
    Description:    Header File For Matrix Multiplication Operations
    Written By:     Edrees Saied
*/

#ifndef  MATRIXMULTIPLY_H 
#define MATRIXMULTIPLY_H

/* Struct definition designed to store vital information about a particular matrix */
typedef struct Matrix {
    int** matrix; // Matrix location in memory
    int rows; // Number of rows
    int cols; // Number of columns
} Matrix;


/* Function that initiates matrix multiplication and creates/join threads */
int runMultiThreadMatMul();

/* Frees the matrix allocation in memory */
void freeMatrix(int** matrix, int rows);

#endif