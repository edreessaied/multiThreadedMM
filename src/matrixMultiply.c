/*
    File Name:      matrixMultiply.c
    Description:    Implementation File For Matrix Multiplication Operations
    Written By:     Edrees Saied
*/

#include "threads.h"
#include "matrixMultiply.h"
#include <time.h>


/* Function that initiates matrix multiplication and creates/join threads */
int runMultiThreadMatMul() {
    if (!matrixAInfo || !matrixBInfo || !matrixCInfo) {
        printf("\n I've detected a NULL matrix! \n");
        return 1;
    }

    int threadCount = (matrixCInfo->rows > THREADMAX) ? THREADMAX : matrixCInfo->rows;
    pthread_t threads[threadCount];
    threadJob* threadJobInfo = NULL;
    int errorCheck = 0;
    clock_t start, end;

    start = clock(); // Log start time of matrix multiplication 
    /* Started creating and activating threads */
    for (int i = 0; i < threadCount; i++) {
        threadJobInfo = (threadJob*) calloc(1, sizeof(threadJobInfo));
        errorCheck = pthread_create(&threads[i], NULL, assignRow, (void*) threadJobInfo);
        if (errorCheck) {
            printf("\n I could not create thread %d!\n", i);
            return 1;
        }
    }

    /* Join on all created threads */
    for (int i = 0; i < threadCount; i++) {
        errorCheck = pthread_join(threads[i], NULL);
        if (errorCheck) {
            printf("\n I could not join on thread %d !\n", i);
            return 1;
        }
    }
    end = clock(); // Log end time of matrix multiplication
    printf("\n Time taken to complete matrix multiplication: %lfs \n", 
            ((double) (end - start)) / CLOCKS_PER_SEC);
    return 0;
}

/* Frees the matrix allocation in memory */
void freeMatrix(int** matrix, int rows) {
    if (!matrix || rows <= 0) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
