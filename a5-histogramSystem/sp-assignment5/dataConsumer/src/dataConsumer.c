/*
*  FILE          : dataConsumer.c
*  PROJECT       : PROG1970 - System Programming - Assignment #5
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-08-14
*  DESCRIPTION   :
* 	Histogram System - Consumer
*
*	1. When launched: locate shared memory and semaphore
*
*	2. Read data from circular buffer in shared memory every 2 seconds
*	3. Print histogram graph every 10 seconds
*
*
*
*/

//INCLUDE FILES
#include "../../common/inc/common.h"
#include "../inc/sharedMemory.h"
#include "../../common/inc/semaphoreStruct.h"
//eo INCLUDE FILES


//CONSTANTS
#define ARRAY_SIZE 20
#define READ_AMOUNT 40


typedef struct histoGramDataContents{

char label;
int count;

}histoGramDataContents_t;
//eo CONSTANTS


//GLOBAL VARIABLES
volatile sig_atomic_t programTerminated = false;
volatile sig_atomic_t alarmFlag = false;
//eo GLOBAL VARIABLES




//PROTOTYPES
void printHistogramLine(int inputNumber);
void printHistogram(histoGramDataContents_t inputData[]);
//eo PROTOTYPES




/*
 * FUNCTION : handleAlarm
 *
 * DESCRIPTION : This function is the signal handler for alarm
 *
 * PARAMETERS : int sig
 *		
 *
 * RETURNS : none
 */
void handleAlarm( int sig ) {
    alarmFlag = true;
}



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
	printf("\n data consumer open");

	histoGramDataContents_t histoGramData[ARRAY_SIZE];
	HistogramData_t *ptrHistoGramData = NULL;
	programTerminated = false;
	int displayCount = 0;
	int semid = 0;
	int shmid = 0;
	pid_t pid = 0;
	pid_t ppid = 0;
	printf("\n data consumer open	2: %d	%d	%d",atoi(argv[2]), atoi(argv[3]), atoi(argv[1]));

    //signal(SIGINT, sigintHandler);		//SIGINT HANDLER INITIALIZE
	//signal(SIGALRM, handleAlarm);	//SIGALARM HANDLER INITIALIZE

	//pid = atoi(argv[2]);		//get pid
	//ppid = atoi(argv[3]);		//get ppid

	printf("\n data consumer open^^^^^^^^^^^^^^3");
	//INITIALIZE ARRAY
	char currentLetter = HISTOGRAM_DATA_START;
	for (int i = 0; i < ARRAY_SIZE; i++){

		histoGramData[i].count = 0;
		histoGramData[i].label = currentLetter;
		
		currentLetter++;	//increment current letter
	}

	//SEMAPHORE
	semid = ptrHistoGramData->semid;

	//SHARED MEMORY
	shmid = atoi(argv[1]);
	if (shmid > SHARED_MEMORY_ID_VALID){

		//ATTACH TO SHARED MEMORY WITH MEMORY KEY
		for (int i = 0; i < SHARED_MEMORY_COUNT_DONE; i++){
	
			if ((ptrHistoGramData = (HistogramData_t *)shmat (shmid, NULL, 0)) == NULL){
				//did not connect to shared memory... will try again
			}

		else{

			break;	//connected to shared memory.
		}

		//3. cannot attach to memory -- sleep for 10 seconds
		sleep(SHARED_MEMORY_SLEEP_TIME);
			printf("\n data consumer open3 sleep");

		}//eo for
	}//eo if

			printf("\n data consumer open4 sleep");

    alarm(2); // set up alarm for 2 seconds

	while(!programTerminated){

		for (int i = 0; i < DC_LOOP_NUMBER; i++){

			while (alarmFlag == false){
			}

			displayCount++;			
            alarmFlag = false;		//reset alarm flag
            alarm(DC_ALARM_TIME);	//reset alarm

			//PRINT HISTOGRAM EVERY 10 SECONDS
			if (displayCount == DC_LOOP_NUMBER){

				displayCount = 0;
				printHistogram(histoGramData);	//print histogram graph
			}


			//CONNECT TO SEMAPHORE
			if (semop (semid, &acquire_operation, 1) == SEMAPHORE_ERROR) {
				break;
			}

			//GET DATA WHEN READINDEX IS NOT WRITE INDEX
			while (ptrHistoGramData->readIndex != ptrHistoGramData->writeIndex){

				//READ DATA FROM CIRCULAR BUFFER
				int currentValue = ptrHistoGramData->circularBuffer[ptrHistoGramData->readIndex];
				ptrHistoGramData->circularBuffer[ptrHistoGramData->readIndex]= 0;
				ptrHistoGramData->readIndex++;

				//STORE IN HISTOGRAM DATA ARRAY
				for (int i = 0; i < (ARRAY_SIZE+1); i++){

					if (histoGramData[i].label == currentValue){
						histoGramData[i].count++;
						break;
					}
				}//eo for


				//RESET BUFFER INDEX
				if (ptrHistoGramData->readIndex == (BUFFER_SIZE-1)){
					ptrHistoGramData->readIndex = 0;
				}
			}//eo while
			

			//RELEASE SEMAPHORE
			if (semop (semid, &release_operation, 1) == SEMAPHORE_ERROR) {
				break;			//break and close program
			}
		}//eo for 5
	}//eo while(1)


	//CLEAN UP RESOURCES
	semctl (semid, 0, IPC_RMID, 0);	//disconnect semaphore
	kill(pid, SIGINT);				//send SIGINT to DP-2
	kill(ppid, SIGINT);				//send SIGINT to DP-1
	printf("\nShazam !!");

	return EXIT_SUCCESS;
}





/*
 * FUNCTION : printHistogram
 *
 * DESCRIPTION : This function prints the Histogram graph
 *
 * PARAMETERS : histoGramDataContents_t inputData[])
 *		
 *
 * RETURNS : none
 */
void printHistogram(histoGramDataContents_t inputData[]){

	fflush(stdout);
	printf("\n***********************   HISTOGRAM   ***********************");

	for (int i = 0; i < (ARRAY_SIZE+1); i++){

		printf("\n%c-%03d ", inputData[i].label, inputData[i].count);	//print histogram letter followed by 3 digit integer count
		printHistogramLine(inputData[i].count);			//print symbol line
	}
}//eo printHistogram






/*
 * FUNCTION : printHistogramLine
 *
 * DESCRIPTION : This function prints a line used in the Histogram Graph
 *
 * PARAMETERS : int inputNumber
 *		
 *
 * RETURNS : none
 */
void printHistogramLine(int inputNumber){

	int hundredCount = 0;
	int tenCount = 0;
	int currentCount = 0;


	//PRINT 100 COUNT
	if ((inputNumber/100) > 0){
		hundredCount = inputNumber / 100;

		for (int i = 0; i < hundredCount; i++){
			printf("*");
		}

		currentCount = inputNumber - (hundredCount * 100);
	}

	else{
	currentCount = inputNumber;

	}

	//PRINT 10 COUNT
	if (currentCount > 0){
		if ((currentCount/10) > 0){
			tenCount = currentCount / 10;
			for (int i = 0; i < tenCount; i++){
				printf("+");
			}
		currentCount = currentCount - (tenCount * 10);
		}
	}
	else{

	}
	//PRINT 1 COUNT
	if (currentCount > 0){

		for (int i = 0; i < currentCount; i++){
			printf("-");
		}
	}

}//eo function
