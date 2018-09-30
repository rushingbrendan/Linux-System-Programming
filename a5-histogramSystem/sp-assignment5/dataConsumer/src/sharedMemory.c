/*
*  FILE          : sharedMemory.c
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


//INCLUDE FILES
 #include "../../common/inc/common.h"
 #include "../inc/sharedMemory.h"
//eo INCLUDE FILES


 /*
 * FUNCTION : getShmemKey
 *
 * DESCRIPTION : This function gets a shared memory key
 *
 * PARAMETERS : void
 *		
 *
 * RETURNS : key_t
 */
key_t getShmemKey(void){

	key_t shmem_key = 0;

	shmem_key = ftok (".", FTOK_KEY);

	return shmem_key;


}//eo key_t getShmemKey(void){





 /*
 * FUNCTION : attachToSharedMemory
 *
 * DESCRIPTION : This function attaches to the shared memory using the shared memory key
 *
 * PARAMETERS : key_t shmem_key
 *		
 *
 * RETURNS : MasterList*
 */

	int attachToSharedMemory (key_t shmem_key){

		int shmid = 0;
        
        //1. use shared memory
		if ((shmid = shmget (shmem_key, sizeof(HistogramData_t), 0)) == SHARED_MEMORY_ERROR){

		}

        return shmid;

}//eo 
