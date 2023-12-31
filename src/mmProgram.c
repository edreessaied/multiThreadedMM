/*
    File Name:      mmProgram.c
    Description:    Program Driver | Generates Matrices and Initiaties Matrix Multilpication
    Written By:     Edrees Saied
*/

#include "readWriteMatrices.h"

/* Function that runs menu in program driver */
void runMatrixMultiplyMenu(void);

/* Program Driver */
int main() {
    runMatrixMultiplyMenu();
    return 0;
}

/* Runs Program Menu */
void runMatrixMultiplyMenu() {
    int rowsA, colsA, rowsB, colsB = 0;
    int errorCheck = 0;
    char* pathErrorCheck;
    char path[300];
    int** matrixA = NULL;
    int** matrixB = NULL;
    int** matrixC = NULL;
    matrixAInfo = NULL;
    matrixBInfo = NULL;
    matrixCInfo = NULL;
    
    /* Extract the requested matrix dimensions from the user */
    errorCheck = extractMatrixDimensions(&rowsA, &colsA, &rowsB, &colsB);
    if (errorCheck) {
        printf("\n* Ending program *\n");
        return;
    }

    /* Write sample matrix to matrixA.txt */
    pathErrorCheck = (char*) getcwd(path, 250);
    if (!pathErrorCheck) {
        printf("\n Could not extract your current working directory! \n"
               "\n* Ending program *\n");
        return;
    }
    strncat(path, "/../matrices/matrixA.txt", 30);
    errorCheck = writeMatrixToFile(path, rowsA, colsA);   
    if (errorCheck) {
        printf("\n* Ending program *\n");
        return;
    }  
    printf("\n Matrix A has been written to %s! \n", path);

    /* Read matrix A into memory */
    matrixA = readMatrixFromFile(path, rowsA, colsA);
    if (!matrixA) {
        printf("\n* Ending program *\n");
        return;
    }

    /* Write sample matrix to matrixB.txt */
    path[0] = '\0';
    pathErrorCheck = (char*) getcwd(path, 250);
    if (!pathErrorCheck) {
        printf("\n Could not extract your current working directory! \n"
               "\n* Ending program *\n");
        goto done;
    }
    strncat(path, "/../matrices/matrixB.txt", 30);
    errorCheck = writeMatrixToFile(path, rowsB, colsB);   
    if (errorCheck) {
        printf("\n* Ending program *\n");
        goto done;
    }  
    printf("\n Matrix B has been written to %s! \n", path);

    /* Read matrix B into memory */
    matrixB = readMatrixFromFile(path, rowsB, colsB);
    if (!matrixB) {
        printf("\n* Ending program *\n");
        goto done;
    }

    /* Allocate matrixC */
    matrixC = (int**) calloc(rowsA, sizeof(int*));
    if (!matrixC) {
        printf("\n Could not allocate matrix C!"
                "\n* Ending program *\n");
        goto done;
    }
    for (int i = 0; i < rowsA; i++) {
        matrixC[i] = (int*) calloc(colsB, sizeof(int));
        if (!matrixC[i]) {
            printf("\n Could not allocate row %d for matrix C! \n", i);
            goto done;
        }
    }

    /* Dynammically allocate the structures for each matrix */
    matrixAInfo = (Matrix*) calloc(1, sizeof(Matrix));
    if (!matrixAInfo) {
        printf("\n Could not allocate structure for matrix A!"
                "\n* Ending program *\n");
        goto done;
    }
    matrixAInfo->matrix = matrixA;
    matrixAInfo->rows = rowsA;
    matrixAInfo->cols = colsA;

    matrixBInfo = (Matrix*) calloc(1, sizeof(Matrix));
    if (!matrixBInfo) {
        printf("\n Could not allocate structure for matrix B!"
                "\n* Ending program *\n");
        goto done;
    }
    matrixBInfo->matrix = matrixB;
    matrixBInfo->rows = rowsB;
    matrixBInfo->cols = colsB;

    matrixCInfo = (Matrix*) calloc(1, sizeof(Matrix));
    if (!matrixCInfo) {
        printf("\n Could not allocate structure for matrix C!"
                "\n* Ending program *\n");
        goto done;
    }
    matrixCInfo->matrix = matrixC;
    matrixCInfo->rows = rowsA;
    matrixCInfo->cols = colsB;

    /* Initialize the mutex lock */
    errorCheck = pthread_mutex_init(&cRowNumberLock, NULL);
    if (errorCheck) {
        printf("\n I couldn't initialize the cRowNumberLock! \n");
        goto done;
    }

    /* Initialize the number of unassigned rows to fill in */
    unassignedRowsC = matrixCInfo->rows;

    /* Run the matrix multiplication */
    errorCheck = runMultiThreadMatMul();
    if (errorCheck) {
        printf("\n* Ending program *\n");
        goto done;
    }

    /* Write product matrix to matrixC.txt */
    path[0] = '\0';
    pathErrorCheck = (char*) getcwd(path, 250);
    if (!pathErrorCheck) {
        printf("\n Could not extract your current working directory! \n"
               "\n* Ending program *\n");
        goto done;
    }
    strncat(path, "/../matrices/matrixC.txt", 30);
    errorCheck = writeProductMatrixToFile(path, matrixCInfo);   
    if (errorCheck) {
        printf("\n* Ending program *\n");
        goto done;
    } 
    printf("\n Matrix C has been written to %s! \n", path);

    /* Free all allocations */
    done:
        freeMatrix(matrixA, rowsA);
        freeMatrix(matrixB, rowsB);
        freeMatrix(matrixC, rowsA);
        
        free(matrixAInfo);
        free(matrixBInfo);
        free(matrixCInfo);
}