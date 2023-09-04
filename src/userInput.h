/*
    File Name:      userInput.h
    Description:    Header File For Collecting User Inputs
    Written By:     Edrees Saied
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 

#ifndef USERINPUT_H 
#define USERINPUT_H

/* Function to collect user requested matrix dimensions */
int extractMatrixDimensions(int* rowsA, int* colsA, int* rowsB, int* colsB);

/* Function to collect a particular user input value */
int extractInputValue(void);

#endif