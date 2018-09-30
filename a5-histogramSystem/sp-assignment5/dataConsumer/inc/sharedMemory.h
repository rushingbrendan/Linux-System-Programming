/*
*  FILE          : sharedMemory.h
*  PROJECT       : PROG1970 - System Programming - Assignment #5
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-08-14
*  DESCRIPTION   :
* 	Histogram System - Shared memory
*
*	Shared memory functions for Histogram system
*
*
*
*/


#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
 #include "../../common/inc/common.h"


key_t getShmemKey(void);
int attachToSharedMemory (key_t shmem_key);






#endif /* SHAREDMEMORY_H */
