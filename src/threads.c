/*
    File Name:      threads.c
    Description:    Implementation File For Thread Work
*/

#include "threads.h"

void fillInAssignedCRow(threadJob* threadJobInfo) {
    /* Perform matrix math and fill in C row */
    int assignedRow = threadJobInfo->assignedRow;

    for (int i = 0; i < threadJobInfo->matrixBInfo->cols; i++) {
        for (int j = 0; j < threadJobInfo->matrixAInfo->cols; j++) {
            threadJobInfo->matrixCInfo->matrix[assignedRow][i] += 
                threadJobInfo->matrixAInfo->matrix[assignedRow][j] *
                threadJobInfo->matrixBInfo->matrix[j][i];
        }
    }
}

void* assignRow(void* arg) {
    threadJob* threadJobInfo = (threadJob*) arg;
    int errorCheck = 0;

    while (1) {
        errorCheck = pthread_mutex_lock(&cRowNumberLock);
        if (errorCheck) {
            /* Error check lock acquire */
        }

        if (unassignedRowsC) {
            unassignedRowsC -= 1;
            threadJobInfo->assignedRow = unassignedRowsC;
            errorCheck = pthread_mutex_unlock(&cRowNumberLock);
            if (errorCheck) {
                /* Error Check lock release */
            }
            threadJobInfo->jobCnt += 1;
            printf("\n Thread %d working %d jobs \n", threadJobInfo->tid, threadJobInfo->jobCnt);
            fillInAssignedCRow(threadJobInfo);
        } else {
            errorCheck = pthread_mutex_unlock(&cRowNumberLock);
            if (errorCheck) {
                /* Error Check */
            }
            break;
        }
    }
    free(threadJobInfo);
    pthread_exit(NULL);
    return NULL;
}
