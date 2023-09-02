/*
    File Name:      readWriteMatrices.h
    Description:    Header File For File I/O Functions
*/

#include <time.h>
#include "userInput.h"

int writeMatrixToFile(const char* path, int rows, int cols);
int** readMatrixFromFile(const char* path, int rows, int cols);