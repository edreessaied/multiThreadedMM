/*
    File Name:      threads.c
    Description:    Implementation File For Thread Work
*/

#include "threads.h"

void fillInAssignedCRow(threadJob* threadJobInfo) {
    /* Perform matrix math and fill in C row */
    int assignedRow = threadJobInfo->currentAssignedRow;

    for (int i = 0; i < matrixBInfo->cols; i++) {
        for (int j = 0; j < matrixAInfo->cols; j++) {
            matrixCInfo->matrix[assignedRow][i] += 
                matrixAInfo->matrix[assignedRow][j] *
                matrixBInfo->matrix[j][i];
        }
    }
}

void* assignRow(void* arg) {
    int errorCheck = 0;
    int currentAssignedRow = 0;
    threadJob* threadJobInfo = (threadJob*) arg;

    while (1) {
        errorCheck = pthread_mutex_lock(&cRowNumberLock);
        if (errorCheck) {
            printf("\n Error while acquiring mutex lock! "
                            "\n Terminating program! \n");
            exit(-1);
        }

        if (unassignedRowsC) {
            unassignedRowsC -= 1;
            threadJobInfo->currentAssignedRow = unassignedRowsC;
            errorCheck = pthread_mutex_unlock(&cRowNumberLock);
            if (errorCheck) {
                printf("\n Error while releasing mutex lock!"
                       "\n Terminating program! \n");
                exit(-1);
            }
            fillInAssignedCRow(threadJobInfo);
        } else {
            errorCheck = pthread_mutex_unlock(&cRowNumberLock);
            if (errorCheck) {
                printf("\n Error while releasing mutex lock!"
                       "\n Terminating program! \n");
                exit(-1);
            }
            break;
        }
    }
    free(threadJobInfo);
    pthread_exit(NULL);
    return NULL;
}
