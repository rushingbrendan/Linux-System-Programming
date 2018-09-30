/*
*  FILE          : source.c
*  PROJECT       : PROG1970 - System Programming - Assignment #3
*  PROGRAMMER    : Brendan Rushing & Conor MacPherson
*  FIRST VERSION : 2018-07-12
*  DESCRIPTION   :
* 	Hoochamacallit System - DataCorrupter
*
*
*	-This program gain knowledge of the resources and processes involved in the Hoochamacallit System
*	-The program will randomly decided between killing DataCreator processes and deleting the message
*	-queue. 
*	-The program will log the operations in a log file stored in the /tmp/dataCorrupter.log
*/



//INCLUDE FILES

#include "../inc/dataCorrupter.h"
#include "../../common/inc/common.h"


//EO INCLUDE FILES

//CONSTANTS

#define FILE_NAME_LENGTH 200
#define TRUE 1
#define FALSE 0


//EO CONSTANTS



int main() {

	FILE *outFile = NULL;
	int randomNumber = 0;
	char outBuffer[FILE_TEXT_WIDTH] = {0};

	key_t message_key = 0;
	key_t shmem_key = 0;
	key_t messageID = 0;
	pid_t DCtoKill = 0;
	MasterList *ptrMasterList = NULL;
	int wheelOfDestructionFinished = false;


	//OPEN LOG FILE
	outFile = fopen("/tmp/dataCorrupter.log", "a");

	if (outFile == NULL){

		printf("\n Error in opening File");
		return EXIT_FAILURE;
	}

	//DataCorrupter has started. 
	//Logfile created.
	printLogFile(outFile, "DX Started");



	//GET SHARED MEMORY KEY
	shmem_key = getShmemKey();

	if (shmem_key == SHARED_MEMORY_ERROR) { 

	  	sprintf(outBuffer,"DX Error - Cannot created shared memory key --- shmem_key = %d", shmem_key);
	  	printLogFile(outFile, outBuffer);
		fflush (stdout);
		return EXIT_FAILURE;

	}//eo 	if (shmem_key == SHARED_MEMORY_ERROR) { 



	//ATTACH TO SHARED MEMORY WITH MEMORY KEY
	ptrMasterList = attachToSharedMemory (shmem_key);
	 if (ptrMasterList == NULL){

	  	sprintf(outBuffer,"DX Error - Cannot attach to shared memory with shmem_key: %d -- Exiting", shmem_key);
	  	printLogFile(outFile, outBuffer);

	 }//eo 	 if (attachToSharedMemory (shmem_key) == SHARED_MEMORY_ERROR){




//**---------------------------------------------------------------------------------------------------**
	//	MAIN LOOP 
	//sleep for random amount of time (10-30 seconds)
	//upon waking....
	//check for existence of message queue (between DC's and DR)	
	//	1. 	If message queue no longer exists, DX assumes that the DC's and DR has shutdown
	// 		DX will log this event as follows, detach itself from shared memory and exit itself
	// 		[2016-01-06 21:05:07] : DX detected that msgQ is gone - assuming DR/DCs done
	//
	//	2.	Get Random Number from 0 to 20 and select task from Wheel of Destruction

	while (wheelOfDestructionFinished == false){


		DCtoKill = 0;	//clear DCtoKill

		//Get Random Number from 10 to 30
		randomNumber = RAND(WOD_SLEEP_MIN,WOD_SLEEP_MAX);		//random Number 10 to 30
		//Sleep
		sleep(randomNumber);		

		//CHECK IF MESSAGE QUEUE EXISTS
		//1. get message_key
		message_key = ftok (".", 'A');
	
		if (message_key == MESSAGE_QUEUE_ERROR) { 
			
			//cANNOT CREATE MESSAGE_KEY
	  		sprintf(outBuffer,"DX Error: cannot create message_key");
	  		printLogFile(outFile, outBuffer);

		}


		//2. get message ID
		messageID = msgget (message_key, 0);

		if (messageID == MESSAGE_QUEUE_ERROR){


			//DATACORRUPTER IS DONE -- MESSAGE QUEUE HAS BEEN KILLED.
	  		sprintf(outBuffer,"DX detected that msgQ is gone - assuming DR/DCs done");
	  		printLogFile(outFile, outBuffer);


			//CLEAN UP RESOURCES
			shmdt (ptrMasterList);
			fclose(outFile);	//close file
			return EXIT_SUCCESS;

		}//eo 	if (messageID == MESSAGE_QUEUE_ERROR){




	//Get Random Number from 0 to 20 for WOD
	randomNumber = RAND(WOD_MIN_CHOICE,WOD_MAX_CHOICE);		//random Number 0 to 20


	//3. WHEEL OF DESTRUCTION
	switch (randomNumber){

		case 0:
		case 8:
		case 19:
			//DO NOTHING
			sprintf(outBuffer, "WOD Action %02d - No Action", randomNumber);
			printLogFile(outFile, outBuffer);
			break;


		case 1:
		case 4:
		case 11:
			//KILL DC-01 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-01  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC1].PID);
			break;	

		case 2:
		case 5:
		case 15:
			//KILL DC-03 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-03  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC3].PID);
			break;	

		case 3:
		case 6:
		case 13:
			//KILL DC-02 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-02  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC2].PID);
			break;	

		case 7:
			//KILL DC-04 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-04  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC4].PID);
			break;	

		case 9:
			//KILL DC-05 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-05  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC5].PID);
			break;	

		case 10:
		case 17:
			//DELETE THE MSG QUEUE  being used between DCs and DR
			msgctl(messageID, IPC_RMID, NULL);
			printLogFile(outFile, "DX deleted the msgQ - the DR/DCs can't talk anymore - exiting");
			wheelOfDestructionFinished = true;
			break;	

		case 12:
			//KILL DC-06 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-06  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC6].PID);
			break;	

		case 14:
			//KILL DC-07 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-07  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC7].PID);
			break;	

		case 16:
			//KILL DC-08 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-08  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC8].PID);
			break;	

		case 18:
			//KILL DC-09 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-09  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC9].PID);
			break;	

		case 20:
			//KILL DC-10 (if exists)
			sprintf(outBuffer, "WOD Action %02d - DC-10  [%d] TERMINATED", randomNumber, DCtoKill);
			printLogFile(outFile, outBuffer);
			killPID(ptrMasterList->dc[DC10].PID);
			break;	

		default:
			break;


		}//eo switch


 
	}//eo while (1)


	//CLEAN UP RESOURCES
	shmdt (ptrMasterList);
	fclose(outFile);	//close file


	return EXIT_SUCCESS;

}// eo main







