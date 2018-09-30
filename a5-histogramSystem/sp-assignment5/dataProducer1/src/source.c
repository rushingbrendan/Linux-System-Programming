/*
*  FILE          : source.c
*  PROJECT       : PROG1970 - System Programming - Assignment #5
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-08-14
*  DESCRIPTION   :
* 	Histogram System - Data Producer #1
*
*	1. When launched: setup shared memory and semaphore
*
*	2. Launch DataProducer2
*	3. Generate 20 random letters and write it to the circular buffer
*	4. Sleep for 2 seconds
*
*
*
*/



//INCLUDE FILES
#include "../inc/dataProducer1.h"
#include "../../common/inc/common.h"
#include "../../common/inc/semaphoreStruct.h"
//EO INCLUDE FILES



//CONSTANTS
#define FILE_NAME_LENGTH 200
#define TRUE 1
#define FALSE 0
#define DP1_BUFFER_SIZE 20

#define ARGUMENT_SIZE 25
#define RANDOM_NUMBERS 20
//EO CONSTANTS



//GLOBAL VARIABLES
volatile sig_atomic_t programTerminated = false;
//eo GLOBAL VARIABLES



/*
 * FUNCTION : sigintHandler
 * DESCRIPTION : This function is the signal handler for SIGINT
 *
 * PARAMETERS : int sig
 *		
 *
 * RETURNS : none
 */
void sigintHandler(int sig_num)
{

    signal(SIGINT, sigintHandler);
    fflush(stdout);
	programTerminated = true;
}



int main() {

	HistogramData_t *ptrHistoGramData = NULL;
	int semid = 0;
	char randomNumbers[RANDOM_NUMBERS];
	programTerminated = false;
	char argument[ARGUMENT_SIZE];

	signal(SIGINT, sigintHandler);

	printf("\n DP1 opened...");


	//CREATE SEMAPHORE
	semid = semget (IPC_PRIVATE, 1, IPC_CREAT | SEMAPHORE_INIT);
	if (semid == SEMAPHORE_ERROR)
	{
	  return EXIT_FAILURE;
	}

	if (semctl (semid, 0, SETALL, init_values) == SEMAPHORE_ERROR) 
	{
	  return EXIT_FAILURE;
	}


	//ACQUIRE SEMAPHORE
	if (semop (semid, &acquire_operation, 1) == SEMAPHORE_ERROR) {
	  return EXIT_FAILURE;
	}


	//Get a shared memory ID.
	 int sharedMemoryID = getSharedMemoryID();

	
	// Check that there was no error while getting the shared memory key.
	 if(sharedMemoryID != SHARED_MEMORY_ERROR) {


		// Create a shared memory block and initialize data.
		ptrHistoGramData = (HistogramData_t*) shmat(sharedMemoryID, NULL, 0);
		ptrHistoGramData->readIndex = 0;
		ptrHistoGramData->writeIndex = 0;
		for(int i = 0; i < BUFFER_SIZE; i++) {

			ptrHistoGramData->circularBuffer[i] = 0;

		}
	 }

	 
	//DISCONNECT SEMAPHORE	
	if (semop (semid, &release_operation, 1) == SEMAPHORE_ERROR) {
	    semctl (semid, 0, IPC_RMID);
	    return EXIT_FAILURE;
	  }

	printf("\n DP1 opened... shared memory done");

	ptrHistoGramData->semid = semid;		//store semaphore id


	//FORK & LAUNCH DP-2 APPLICATION	
	sprintf(argument, "%d", sharedMemoryID);		//store shared memory in char array for DP-2
	int pid = fork();	//fork

	if (pid == 0){	//if i am the child then open DP-2

		execl("./dataProducer2", "./dataProducer2", &argument, (char*)NULL);	//open DP-2
		exit(1);
	}

	sleep (FORK_DELAY_TIME);		//sleep for a few seconds to let programs get setup
	 
	printf("\n DP1 after fork");
	
	while(!programTerminated){

		int randomNumber = 0;

		//GET 20 x RANDOM DATA FOR HISTOGRAM
		for (int i = 0; i < DP1_BUFFER_SIZE; i++){

			randomNumber = RAND(HISTOGRAM_DATA_START, (HISTOGRAM_DATA_END+1));	//random number between A and T
			randomNumbers[i] = randomNumber;
		}
			
		sleep(DP1_SLEEP_TIME);		//sleep for 2 seconds

		//CONNECT TO SEMAPHORE
		if (semop (semid, &acquire_operation, 1) == SEMAPHORE_ERROR) {
			break;
		}

		for (int i = 0; i < DP1_BUFFER_SIZE; i++){

			if (!programTerminated){
			ptrHistoGramData->circularBuffer[ptrHistoGramData->writeIndex] = randomNumbers[i];	//write data
			}

			if (!programTerminated){
			ptrHistoGramData->writeIndex++;	//increment write index
			}

			if (ptrHistoGramData->writeIndex == (BUFFER_SIZE-1)){
				ptrHistoGramData->writeIndex = 0;
			}

		}

		//DISCONNECT SEMAPHORE
		if (semop (semid, &release_operation, 1) == SEMAPHORE_ERROR) {
			break;
		}


	}//eo program terminated




	//CLEAN UP RESOURCES
	shmdt (ptrHistoGramData);
	semctl (semid, 0, IPC_RMID, 0);



	return EXIT_SUCCESS;

}// eo main







