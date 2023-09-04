/*
    File Name:      threads.c
    Description:    Implementation File For Thread Work
    Written By:     Edrees Saied
*/

#include "threads.h"

/* Function for thread to compute assigned row */
void fillInAssignedCRow(threadJob* threadJobInfo) {
    int assignedRow = threadJobInfo->currentAssignedRow;

    /* Perform matrix math and fill in assignedRow row in product matrix */
    for (int i = 0; i < matrixBInfo->cols; i++) {
        for (int j = 0; j < matrixAInfo->cols; j++) {
            matrixCInfo->matrix[assignedRow][i] += 
                matrixAInfo->matrix[assignedRow][j] *
                matrixBInfo->matrix[j][i];
        }
    }
}

/* Function that thread executes upon its creation */
void* assignRow(void* arg) {
    int errorCheck = 0;
    int currentAssignedRow = 0;
    threadJob* threadJobInfo = (threadJob*) arg;

    /* Run infinite loop while there still remains unassigned rows */
    while (1) {
        /* Acquire global lock */
        errorCheck = pthread_mutex_lock(&cRowNumberLock);
        if (errorCheck) {
            printf("\n Error while acquiring mutex lock!"
                   "\n Terminating program! \n");
            exit(-1);
        }

        /* Check if there are any remaining unassigned rows in product matrix */
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

    /* Free thread's allocated structure and terminate */
    free(threadJobInfo);
    pthread_exit(NULL);
}
