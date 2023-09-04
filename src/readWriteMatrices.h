/*
    File Name:      readWriteMatrices.h
    Description:    Header File For File I/O Functions
    Written By:     Edrees Saied
*/

#include <time.h>
#include "threads.h"
#include "matrixMultiply.h"

#ifndef  READWRITEMATRICES_H 
#define READWRITEMATRICES_H

/* Function that reads matrix of size rows x cols from file location at path */
int** readMatrixFromFile(const char* path, int rows, int cols);

/* Function that writes matrix of size rows x cols to file location at path */
int writeMatrixToFile(const char* path, int rows, int cols);

/* Function that writes matrix specified by matrixCInfo to file location at path */
int writeProductMatrixToFile(char* path, Matrix* matrixCInfo);

#endif