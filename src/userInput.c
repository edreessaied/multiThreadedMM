/*
    File Name:      userInput.c
    Description:    Implementation File For Collecting User Inputs
    Written By:     Edrees Saied
*/

#include "userInput.h"

/* Function to collect user requested matrix dimensions */
int extractMatrixDimensions(int* rowsA, int* colsA, int* rowsB, int* colsB) {
    int errorCheck = 0;

    /* Program Startup Screen */
    printf("\n*  MultiThreaded Matrix Multiplication  *\n"
           "\n I will ask you for the dimensions of "
           "\n of your two desired matrices and     "
           "\n then fill them in with random values "
           "\n to execute the multi-threaded matrix "
           "\n multiplication.                      \n");

    /* Extract Number of Desired Rows For Matrix A*/
    printf("\n* Enter the desired number of rows for your left matrix *\n");
    *rowsA = extractInputValue();
    if (!(*rowsA)) {
        return 1;
    }

    /* Extract Number of Desired Columns For Matrix A */
    printf("\n* Enter the desired number of columns for your left matrix *\n");
    *colsA = extractInputValue();
    if (!(*colsA)) {
        return 1;
    }

    *rowsB = *colsA;
    printf("\n NOTE: The number of rows for your right matrix will be %d!\n", *colsA);

    /* Extract Number of Desired Columns For Matrix B */
    printf("\n* Enter the desired number of columns for your right matrix *\n");
    *colsB = extractInputValue();
    if (!(*colsB)) {
        return 1;
    }

    printf("\n Your left matrix will be of size: %d x %d"
        "\n Your right matrix will be of size: %d x %d"
        "\n Your result matrix will be of size: %d x %d\n", 
        *rowsA, *colsA, *rowsB, *colsB, *rowsA, *colsB);

    return 0;
}

/* Function to collect a particular user input value */
int extractInputValue() {
    int val = 0;
    int errorCheck = 0;

    do {  
        /* Extract Value */
        printf("\n Please input a positive integer value"
               "\n (Input 0 to quit the program): ");
        errorCheck = scanf("%d", &val); 

        /* Clearing input buffer */
        while (getchar() != '\n') {
            continue;
        }

        /* Will continue loop until I receive proper input */
    } while (errorCheck != 1 || val < 0);

    if (!val) {
        printf("\n--- Per your request, I will end the program ---\n");
        return 0;
    }
    return val;
}