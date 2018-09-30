/*!
 *
 *	@file		:	source.c
 *
 *  project		:	PROG1970 - System Programming - Assignment #3
 *
 *  @author		:	Brendan Rushing & Conor MacPherson
 *
 *  @date		:	2018-07-12
 *
 *  @brief		:	Hoochamacallit System - DataCreator
 *
 *					-This program creates a status condition representing the state of the Hoochamacallit machine
 *					 on the shop floor.
 *
 *					-This program sends messages via a message queue to the DataReader application
 *
 *					-This program will check for a message queue every 10 seconds until it is found.
 *
 *					-This program will send a state (0) Everything is okay is sent first
 *
 *					-This program runs until the state (6) Machine is off-line is generated. Then it will close.
 *					
 *					-This program will be run 10 times with 1 second between iterations to have 10 programs running
 *					 at once with different random seed values.
 */


#include "../inc/dataCreator.h"
#include "../../common/inc/common.h"


#define FILE_NAME_LENGTH 200


int main(void) {


	int randomNumber = 0;
	int currentStatus = 0;
	int messageID = 0;
	int messageQueueFound = false;
	key_t message_key = 0;


	//1. CHECK IF MESSAGE QUEUE EXISTS
	//	 If it does not then sleep for 10 seconds and try again

	while (messageQueueFound != true){

		message_key = ftok (".", 'A');

		if (message_key == -1) {
	  		printf("Data Creator - Cannot create key!\n");
	  		fflush (stdout);
		}	

		//2. get message ID
		messageID = msgget (message_key, 0);

		if (messageID == MESSAGE_QUEUE_ERROR){
			
			sleep(MESSAGE_CREATOR_SLEEP);	//sleep for 10 seconds
		}

		else{

			messageQueueFound = true;
		}

	}

	//SEND MESSA'EVERYTHING - OKAY' - MESSAGE TO QUEUE
	send_message(messageID, currentStatus);
	
	while (currentStatus != MACHINE_OFFLINE){

		randomNumber = RAND(MACHINE_STATUS_MIN,MACHINE_STATUS_MAX);		//random Number 1 to 6 for machine status
		currentStatus = randomNumber;	//currentStatus set
		
		randomNumber = RAND(MESSAGE_CREATOR_DELAY_MIN,MESSAGE_CREATOR_DELAY_MAX);		//random number from 10 to 30 for delay time

		sleep(randomNumber);			//delay for random time

		//SEND MESSAGE
		send_message(messageID, currentStatus);
	}



	return SUCCESS;

}//eo main
