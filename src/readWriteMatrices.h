/*
    File Name:      readWriteMatrices.h
    Description:    Header File For File I/O Functions
*/


#include <time.h>
#include "threads.h"
#include "matrixMultiply.h"

#ifndef  READWRITEMATRICES_H 
#define READWRITEMATRICES_H

int writeMatrixToFile(const char* path, int rows, int cols);
int** readMatrixFromFile(const char* path, int rows, int cols);
int writeProductMatrixToFile(char* path, Matrix* matrixCInfo);

#endif