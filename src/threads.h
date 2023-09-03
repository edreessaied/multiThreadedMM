/*
    File Name:      threads.h
    Description:    Header File File For Thread Work
*/

#include "matrixMultiply.h"
#include "userInput.h"
#include <pthread.h>

#define THREADMAX 500

typedef struct threadJob {
    Matrix* matrixAInfo;
    Matrix* matrixBInfo;
    Matrix* matrixCInfo;
    int assignedRow;
    pthread_t tid;
    int jobCnt;
} threadJob;

pthread_mutex_t cRowNumberLock;
int unassignedRowsC;

void fillInAssignedCRow(threadJob* threadJobInfo);
void* assignRow(void* arg);
