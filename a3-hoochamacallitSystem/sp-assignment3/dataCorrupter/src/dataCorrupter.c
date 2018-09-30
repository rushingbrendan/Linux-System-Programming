/*
*  FILE          : dataCorrupter.c
*  PROJECT       : PROG1970 - System Programming - Assignment #3
*  PROGRAMMER    : Brendan Rushing & Conor MacPherson
*  FIRST VERSION : 2018-07-12
*  DESCRIPTION   :
* 	Hoochamacallit System - DataCorrupter
	-This program gain knowledge of the resources and processes involved in the Hoochamacallit System
	-The program will randomly decided between killing DataCreator processes and deleting the message
	-queue. 
	-The program will log the operations in a log file stored in the /tmp/dataCorrupter.log
*/

//INCLUDE FILES

#include "../inc/dataCorrupter.h"
#include "../../common/inc/common.h"

//EO INCLUDE FILES

//CONSTANTS



//EO CONSTANTS



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

	shmem_key = ftok (".", 16535);

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
//**---------------------------------------------------------------------------------------------------**
	//1. ATTACH TO SHARED MEMORY
	//shmKey = ftok (".", 16535);
	//use this key
	//if it does not exist then sleep for 10 seconds
	//and then try again
	//try until 100 tries OR DR creates the shared memory
	//DX must run in same directory as DR application
	//this list will be implemented as indicated in the Proposed DR Master List defined on last page of document

	MasterList *attachToSharedMemory (key_t shmem_key){

		MasterList *ptrMasterList = NULL;
		int shmid = 0;

		for (int i = 0; i < SHARED_MEMORY_COUNT_DONE; i++){

			//1. use shared memory or allocate a new block
			if ((shmid = shmget (shmem_key, sizeof(MasterList), 0)) == SHARED_MEMORY_ERROR){

			}

			//2. attach to shared memory
			if (shmid > SHARED_MEMORY_ID_VALID){

				if ((ptrMasterList = (MasterList *)shmat (shmid, NULL, 0)) == NULL)
				{

				}

				else{

				//Success -- able to attach to data struct in shared memory with shared memory key and id
				return ptrMasterList;

				}

			}//eo if (shmid > SHARED_MEMORY_ID_VALID){

			//3. cannot attach to memory -- sleep for 10 seconds
			sleep(10);

		}//eo for (int i = 0; i <= SHARED_MEMORY_COUNT_DONE; i++){


		//100 tries and cannot attach to memory
		return NULL;

}//eo 




 /*
 * FUNCTION : killPID
 *
 * DESCRIPTION : This function kills the PID  with the SIGHUP signal
 
 * PARAMETERS : pid_t inputPid
 *		
 *
 * RETURNS : int
 */
int killPID (pid_t inputPID){

//KILL PID WITH SIGHUP SIGNAL
if (inputPID != INVALID_PID){

	kill(inputPID, SIGHUP);

	return EXIT_SUCCESS;

}//eo 

return EXIT_FAILURE;

}//eo int killPID (int inputPID){