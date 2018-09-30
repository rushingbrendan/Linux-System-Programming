/*!
 *
 *	@file	:	sharedMemory.c
 *
 *	project	:	PROG1970 - Systems Programming - The Hoochamacallit System
 *
 *	@author	:	Brendan Rushing & Conor Macpherson
 *
 *	@date	:	2018-07-10
 *
 *	@brief	:	This file contains functions for creating shared memory.
 *				The function prototypes for these functions are defined in ../inc/sharedMemory.h
 *
 */

#include "../../common/inc/common.h"
#include "../inc/sharedMemory.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>


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
	key_t sharedMemoryKey = ftok(".", SHARED_MEMORY_KEY_VALUE);
	
	// Preserve errno in the case that it is changed from elsewhere in the system.
	int errnoSave = errno;

	// Check if ftok failed.
	// If it did, output an error. Otherwise, check if shared memory exists for the key produced by ftok.
	if(sharedMemoryKey == FTOK_ERROR) {
		
		printf("\nftok error: %s", strerror(errnoSave));
	}
	if((sharedMemoryID = shmget(sharedMemoryKey, sizeof(MasterList), 0)) == SHARED_MEMORY_DOES_NOT_EXIST) {

		// If there is not shared memory, create it with read/write access to the user and groups.
		sharedMemoryID = shmget(sharedMemoryKey, sizeof(MasterList), IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

		// Preserve errno in the case that it is changed from elsewhere in the system.
		errnoSave = errno;

		// If shmget failed, output an error.
		if(sharedMemoryID == SHMGET_ERROR) {

			printf("\nshmget error: %s\n",strerror(errnoSave));
		}
	}

	return sharedMemoryID;
}