/*
    File Name:      threads.h
    Description:    Header File For Thread Work
    Written By:     Edrees Saied
*/

#include "matrixMultiply.h"
#include "userInput.h"
#include <pthread.h>

#ifndef THREADS_H
#define THREADS_H

/* Maximum amount of threads that I'm willing to create */
#define THREADMAX 500

/* Structure to hold necessary data for a thread to complete its job */
typedef struct threadJob {
    int currentAssignedRow; // Thread's assigned row 
} threadJob;


// Global Variable Declarations

/* Global mutex lock */
pthread_mutex_t cRowNumberLock;

/* Number of unassigned rows in product matrix */
int unassignedRowsC;

/* Structure declarations to contain information about the allocated matrices */
Matrix* matrixAInfo;
Matrix* matrixBInfo;
Matrix* matrixCInfo;

// Function Prototypes

/* Function that thread runs to fill in assigned row */
void fillInAssignedCRow(threadJob* threadJobInfo);

/* Function that thread runs upon creation */
void* assignRow(void* arg);

#endif 