/*
*  FILE          : common.c
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


//Include files
#include "../inc/common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//EO Include files


/*!
 *
 *	@brief : This function creates a random number from min to max
 *
 *	@param[in] - min - <b>double</b> - The minimum return value.
 *
 *	@param[in] - max - <b>double</b> - The maximum return value.
 *
 *	@return - <b>double</b> - The sudo random number.
 *
 */
double RAND(double min, double max){
	
	srand( time(NULL) * clock() );

	return (double)rand()/(double)RAND_MAX*(max-min) + min;


}//eo double RAND(double min, double max)




/*!
 *
 *	@brief Gets a Shared Memory ID. 
 *
 *	Gets a shared memory ID. If the shared memory already exists, or the
 *	process fails, an error indicator is returned. 
 *
 *	@return - <b>int</b> -	-1 if shared memory already exists for a specific key.
 *	@return - <b>int</b> -	-2 if getting a System V IPC key failed. 
 *	@return - <b>int</b> -	A shared memory ID if the process executed correctly.
 *
 */
int getSharedMemoryID() {

	int sharedMemoryID = -2;

	// Get a System V IPC key for shared memory.
	key_t sharedMemoryKey = ftok(".", 16535);
	
	// Check if ftok failed.
	// If it did, output an error. Otherwise, check if shared memory exists for the key produced by ftok.
	if(sharedMemoryKey == FTOK_ERROR) {
		
	}
	if((sharedMemoryID = shmget(sharedMemoryKey, sizeof(HistogramData_t), 0)) == SHARED_MEMORY_DOES_NOT_EXIST) {

		// If there is not shared memory, create it with read/write access to the user and groups.
		sharedMemoryID = shmget(sharedMemoryKey, sizeof(HistogramData_t), IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

		// If shmget failed, output an error.
		if(sharedMemoryID == SHMGET_ERROR) {

		}
	}

	return sharedMemoryID;
}



