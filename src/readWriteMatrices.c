/*
    File Name:      readWriteMatrices.c
    Description:    Implementation File For File I/O Functions
*/

#include "readWriteMatrices.h"

int** readMatrixFromFile(const char* path, int rows, int cols) {
    int** matrix = NULL;
    FILE* filePtr = NULL;
    int errorCheck = 0;
    bool error = false;

    matrix = (int**) calloc(rows, sizeof(int*));
    if (!matrix) {
        printf("\n Could not read matrix into memory! \n");
        return NULL;
    }

    filePtr = fopen(path, "r");
    if (filePtr == NULL) {
        printf("\n Error! Could not open file: %s !", path); 
        return NULL;
    }

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

int writeMatrixToFile(const char* path, int rows, int cols) {
    FILE* filePtr = NULL;
    int errorCheck = 0;
    int error = false;

    filePtr = fopen(path, "w");
    if (filePtr == NULL) {
        printf("\n Error! Could not open file: %s !", path); 
        return 1;
    }

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