/*
*  FILE          : common.h
*  PROJECT       : PROG1970 - System Programming - Assignment #5
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-08-14
*  DESCRIPTION   :
* 	Histogram System - Common
*
*	Common functions, constants and include files for Histogram System
*
*
*
*/

#ifndef COMMON_H
#define COMMON_H

//INCLUDE FILES
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>


#include <signal.h>
#include <errno.h>
//eo INCLUDE FILES


//CONSTANTS

#define MAX_DC_ROLES 10
#define FTOK_FAILURE -1
#define WRITE_OF_ZERO_BYTES 0
#define FILE_TEXT_WIDTH 200
#define SHARED_MEMORY_KEY_VALUE 16535

#define HISTOGRAM_DATA_START 'A'
#define HISTOGRAM_DATA_END	'T'

#define NUMBER_OF_PRODUCERS 2
#define BUFFER_SIZE	256
#define FTOK_KEY 16535
#define DC_LOOP_NUMBER 5
#define DC_ALARM_TIME 2


#define SHMGET_ERROR -1
#define SHARED_MEMORY_DOES_NOT_EXIST -1
#define FTOK_ERROR -1
#define SHARED_MEMORY_ERROR -1
#define FORK_SLEEP_TIME 3

#define SEMAPHORE_ERROR -1
#define SEMAPHORE_INIT 0666


#define SHARED_MEMORY_COUNT_DONE 100
#define SHARED_MEMORY_ID_VALID 0
#define SHARED_MEMORY_ERROR -1
#define SHARED_MEMORY_SUCCESS 0
#define SHARED_MEMORY_SLEEP_TIME 10

typedef struct HistogramData {

	int readIndex;
	int writeIndex;
	char circularBuffer[BUFFER_SIZE];
	int semid;
	
} HistogramData_t;


//eo CONSTANTS


//PROTOTYPES
double RAND(double min, double max);
int getSharedMemoryID();
//eo PROTOTYPES



#endif /* COMMON */






