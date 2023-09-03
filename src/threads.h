/*
    File Name:      threads.h
    Description:    Header File File For Thread Work
*/

#include "matrixMultiply.h"
#include "userInput.h"
#include <pthread.h>

#define THREADMAX 500

typedef struct threadJob {
    int currentAssignedRow;
} threadJob;

pthread_mutex_t cRowNumberLock;
int unassignedRowsC;
Matrix* matrixAInfo;
Matrix* matrixBInfo;
Matrix* matrixCInfo;

void fillInAssignedCRow(threadJob* threadJobInfo);
void* assignRow(void* arg);
