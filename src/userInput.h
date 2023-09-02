/*
    File Name:      userInput.h
    Description:    Header File For Collecting User Inputs
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 

int extractMatrixDimensions(int* rowsA, int* colsA, int* rowsB, int* colsB);
int extractInputValue(void);