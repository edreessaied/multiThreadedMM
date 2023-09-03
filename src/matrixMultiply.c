/*
    File Name:      matrixMultiply.c
    Description:    Implementation File For Matrix Multiplication
*/

#include "threads.h"
#include "matrixMultiply.h"
#include <time.h>

int runMultiThreadMatMul(Matrix* matrixAInfo, Matrix* matrixBInfo, Matrix* matrixCInfo) {
    if (!matrixAInfo || !matrixBInfo || !matrixCInfo) {
        printf("\n I've detected a NULL matrix! \n");
        return 1;
    }

    int threadCount = (matrixCInfo->rows > THREADMAX) ? THREADMAX : matrixCInfo->rows;
    pthread_t threads[threadCount];
    threadJob* threadJobInfo = NULL;
    int errorCheck = 0;
    clock_t start, end;

    start = clock();

    
    for (int i = 0; i < threadCount; i++) {
        threadJobInfo = (threadJob*) calloc(1, sizeof(threadJob));
        threadJobInfo->matrixAInfo = matrixAInfo;
        threadJobInfo->matrixBInfo = matrixBInfo;
        threadJobInfo->matrixCInfo = matrixCInfo;
        threadJobInfo->tid = (pthread_t) i;
        threadJobInfo->jobCnt = 0;

        pthread_create(&threads[i], NULL, assignRow, (void*)threadJobInfo);
    }


    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }
    end = clock();
    printf("\n Time taken to complete matrix multiplication: %lfs \n", 
            ((double) (end - start)) / CLOCKS_PER_SEC);
    return 0;
}

void freeMatrix(int** matrix, int rows) {
    if (!matrix || rows <= 0) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
