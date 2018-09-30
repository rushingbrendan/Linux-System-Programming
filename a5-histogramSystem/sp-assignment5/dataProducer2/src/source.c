/*
*  FILE          : source.c
*  PROJECT       : PROG1970 - System Programming - Assignment #5
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-08-14
*  DESCRIPTION   :
* 	Histogram System - Data Producer #2
*
*	1. When launched: locate shared memory and semaphore
*
*	2. Launch DataConsumer application
*	3. Generate one random letter and write it to the circular buffer
*	4. Sleep for 1/20 of a second
*
*
*
*/

//INCLUDE FILES
#include "../inc/dataProducer2.h"
#include "../../common/inc/common.h"
#include "../../common/inc/semaphoreStruct.h"
#include "../../dataConsumer/inc/sharedMemory.h"
//eo INCLUDE FILES


//GLOBAL VARIABLES
volatile sig_atomic_t programTerminated = false;
//eo GLOBAL VARIABLES



/*
 * FUNCTION : sigintHandler
 *
 * DESCRIPTION : This function is the signal handler for sigint
 *
 * PARAMETERS : int sig_num
 *		
 *
 * RETURNS : none
 */
void sigintHandler(int sig_num)
{

    signal(SIGINT, sigintHandler);
	programTerminated = true;
}







int main(int argc, char* argv[]) {

	int semid = 0;
	int shmid = 0;
	HistogramData_t *ptrHistoGramData = NULL;
	pid_t pid = 0;
	pid_t ppid =0;
	char argShmid[ARGUMENT_STRING_SIZE];
	char argPid[ARGUMENT_STRING_SIZE];
	char argPPid[ARGUMENT_STRING_SIZE];

	printf("\n dp2 opened");


    signal(SIGINT, sigintHandler);		//SIGINT HANDLER INITIALIZE

	pid = getpid();			//get process id
	ppid = getppid();		//get parent process id


	//SHARED MEMORY
	shmid = atoi(argv[1]);
	if (shmid > SHARED_MEMORY_ID_VALID){

		//ATTACH TO SHARED MEMORY WITH MEMORY KEY
		for (int i = 0; i < SHARED_MEMORY_COUNT_DONE; i++){
	
			if ((ptrHistoGramData = (HistogramData_t *)shmat (shmid, NULL, 0)) == NULL){
			}

		else{

			break;
		}

		//3. cannot attach to memory -- sleep for 10 seconds
		sleep(SHARED_MEMORY_SLEEP_TIME);
		}//eo for
	}//eo if


	//SEMAPHORE
	semid = ptrHistoGramData->semid;



	//LAUNCH DC
	sprintf(argShmid, "%d", shmid);		//char array strings for data arguments
	sprintf(argPid, "%d", pid);
	sprintf(argPPid, "%d", ppid);

	int newPid = fork();

	if (newPid == 0){	// i am the child, open program.

		printf("\ndp2 before exec");
		execl("./dataConsumer", "./dataConsumer", &argShmid, &argPid, &argPPid, (char*)NULL);
		printf("\ndp2 after exec");
	}

	sleep (FORK_SLEEP_TIME);


	
	while (programTerminated == false){
		
		int randomNumber = 0;
		randomNumber = RAND(HISTOGRAM_DATA_START, (HISTOGRAM_DATA_END+1));	//random number between A and T


		//CONNECT TO SEMAPHORE
		if (semop (semid, &acquire_operation, 1) == SEMAPHORE_ERROR) {
			break;
		}

		//WRITE DATA TO SHARED MEMORY
		ptrHistoGramData->circularBuffer[ptrHistoGramData->writeIndex] = randomNumber;	//write data
		ptrHistoGramData->writeIndex++;	//increment write index

		if (ptrHistoGramData->writeIndex == (BUFFER_SIZE-1)){
			ptrHistoGramData->writeIndex = 0;

		}


		//DISCONNECT SEMAPHORE
		if (semop (semid, &release_operation, 1) == SEMAPHORE_ERROR) {
			break;
		}

		usleep(DP2_SLEEP_TIME);	//SLEEP FOR 1/20 SECOND

	}


	//CLEAN UP RESOURCES
	shmdt (ptrHistoGramData);
	semctl (semid, 0, IPC_RMID, 0);
	return SUCCESS;

}//eo main




