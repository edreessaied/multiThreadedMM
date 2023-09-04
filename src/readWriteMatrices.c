/*
    File Name:      readWriteMatrices.c
    Description:    Implementation File For File I/O Functions
    Written By:     Edrees Saied
*/

#include "readWriteMatrices.h"

/* Function that reads matrix of size rows x cols from file location at path */
int** readMatrixFromFile(const char* path, int rows, int cols) {
    int** matrix = NULL;
    FILE* filePtr = NULL;
    int errorCheck = 0;
    bool error = false;

    /* Allocate the required matrix */
    matrix = (int**) calloc(rows, sizeof(int*));
    if (!matrix) {
        printf("\n Could not allocate matrix onto the heap! \n");
        return NULL;
    }

    /* Open the file */
    filePtr = fopen(path, "r");
    if (filePtr == NULL) {
        printf("\n Error! Could not open file: %s!", path); 
        return NULL;
    }

    /* Read matrix into memory */
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) calloc(cols, sizeof(int));
        if (!matrix[i]) {
            error = true;
            goto rollback;
        }
        for (int j = 0; j < cols; j++) {
            errorCheck = fscanf(filePtr, "%d", &matrix[i][j]);
            if (!errorCheck) {
                printf("\n Could not scan matrix properly! \n");
                error = true;
                goto rollback; 
            }
        }
        errorCheck = fgetc(filePtr);
        if (errorCheck == EOF && i < rows - 1) {
            printf("\n Could not completely scan the matrix! \n");
            error = true;
            goto rollback;
        }
    }
    
    /* If error occured, roll back all memory allocations */
    rollback:
        errorCheck = fclose(filePtr);
        if (errorCheck) {
            printf("\n Could not close the appropriate file! \n");
            error = true;
        }
        if (error) {
            for (int i = 0; i < rows; i++) {
                if (matrix[i]) {
                    free(matrix[i]);
                    matrix[i] = NULL;
                } else {
                    break;
                }
            }
            free(matrix);
            matrix = NULL;
            return NULL;
        }
    return matrix;
}

/* Function that writes matrix of size rows x cols to file location at path */
int writeMatrixToFile(const char* path, int rows, int cols) {
    FILE* filePtr = NULL;
    int errorCheck = 0;
    int error = false;

    /* Open the file */
    filePtr = fopen(path, "w");
    if (filePtr == NULL) {
        printf("\n Error! Could not open file: %s !", path); 
        return 1;
    }

    /* Fill in the file with random matrix values and appropriate formatting */
    srand(rows + cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            errorCheck = fprintf(filePtr, " %d", rand() % 10);
            if (errorCheck < 0) {
                error = true;
                goto errorHandler;
            }
        }
        errorCheck = fprintf(filePtr, "\n");
        if (errorCheck < 0) {
            error = true;
            goto errorHandler;
        }
    }

    /* Check if error occured in the process */
    errorHandler:
        errorCheck = fclose(filePtr);
        if (errorCheck) {
            printf("\n Could not close the appropriate file! \n");
            error = true; 
        }
        if (error) {
            return 1;
        }
    return 0;
}

/* Function that writes matrix specified by matrixCInfo to file location at path */
int writeProductMatrixToFile(char* path, Matrix* matrixCInfo) {
    FILE* filePtr = NULL;
    int errorCheck = 0;
    int error = false;

    /* Open the file */
    filePtr = fopen(path, "w");
    if (filePtr == NULL) {
        printf("\n Error! Could not open file: %s !", path); 
        return 1;
    }

    /* Write matrix to the file with appropriate formatting*/
    for (int i = 0; i < matrixCInfo->rows; i++) {
        for (int j = 0; j < matrixCInfo->cols; j++) {
            errorCheck = fprintf(filePtr, " %d", matrixCInfo->matrix[i][j]);
            if (errorCheck < 0) {
                printf("\n I could not write to the file! \n");
                error = true;
                goto errorHandler;
            }
        }
        errorCheck = fprintf(filePtr, "\n");
        if (errorCheck < 0) {
            printf("\n I could not write to the file! \n");
            error = true;
            goto errorHandler;
        }
    }

    /* Check if error occured in the process */
    errorHandler:
        errorCheck = fclose(filePtr);
        if (errorCheck) {
            printf("\n Could not close the appropriate file! \n");
            error = true; 
        }
        if (error) {
            return 1;
        }
    return 0;
}