/*!
 *
 *	@file	:	dataReader.c
 *
 *	project	:	PROG1970 - Systems Programming - The Hoochamacallit System
 *
 *	@author	:	Brendan Rushing & Conor Macpherson
 *
 *	@date	:	2018-07-17
 *
 *	@brief	:	This file contains the main entry point for the dataReader application.
 *				The data reader will create shared memory and a message queue.
 *				
 *				It will then wait 15 seconds after which it will start reading messages
 *				from the message queue and storing the data from each message into the
 *				shared memory.
 *
 *				When a new message is received, the dataReader will check it for the state
 *				of the data creator.
 *				If the creator is offline, it will remove the data creator from the shared
 *				memory.
 *
 *				The dataReader will also check if it hasn't heard from a data creator in the
 *				past 35 seconds. If it hasn't it removes it from the master list.
 *
 *				If a message from a previously unkown data creator is received, the creator is
 *				added to the master list
 *
 *				The dataReader will wait 1.5 after each message before it reads another.
 *				If no messages are received for 35 seconds, then the dataReader will
 *				detach from, and deallocate the shared memory.
 *				Then, it will deallocate the message queue.
 *
 */


#include "../../common/inc/common.h"
#include "../inc/messageQueue.h"
#include "../inc/sharedMemory.h"


#define MAX_TIME_NOT_HEARD_FROM_DC 35
#define DATA_READER_INITIAL_WAIT 15
#define WAIT_AFTER_RECIEVE_NANO_SECONDS 1500000L
#define WAIT_AFTER_RECIEVE_SECONDS 1.5
#define MAX_LOG_STRING_LENGTH 255
#define NUMBER_OF_STATES 8


const char* stateMeanings[NUMBER_OF_STATES] = {

	"Everything Is Okay",
	"Hydraulic Pressure Failure",
	"Safety Button Failure",
	"No Raw Material In Process",
	"Operating Temperature Out of Range",
	"Operator Error",
	"Machine Offline",
	"Unkown State"
};


int main(void) {

	// Get a shared memory ID.
	int sharedMemoryID = getSharedMemoryID();
	int messageQueueID = 0;
	key_t messageQueueKey = 0;
	MasterList* masterList = NULL;
	
	// Check that there was no error while getting the shared memory key.
	if(sharedMemoryID != SHARED_MEMORY_ERROR) {

		// Get a message queue key.
		messageQueueKey = getMessageQueueKey();

		// Check that there was no error getting a message queue key.
		if(messageQueueKey != MESSAGE_QUEUE_ERROR) {

			// Create a message queue.
			messageQueueID = createMessageQueue(messageQueueKey);

			// Create a shared memory block and initialize data.
			masterList = (MasterList*) shmat(sharedMemoryID, NULL, 0);
			masterList->messageQueueID = messageQueueID;	
			masterList->numberOfDataCreators = 0;
			for(int i = 0; i < MAX_DC_ROLES; i++) {

				masterList->dc[i].currentState = 0;
				masterList->dc[i].lastHeard = 0;
				masterList->dc[i].PID = 0;
				masterList->dc[i].type = 0;
			}

			// Sleep so DCs can open.
			sleep(DATA_READER_INITIAL_WAIT);

			// Open the logging file.
			FILE* file = fopen("/tmp/DRLog.log", "a");
			if(file == NULL) {

				printf("\nCannot open DRLog.log.\n");
			}


			// Create a temp DCInfo struct used to receive messages.
			DCInfo receivedMessage = {0, 0, 0, 0};
			double secondsSinceLastMessageReceived = 0;
			do {
				
				char logString[MAX_LOG_STRING_LENGTH]  = {0}; 

				// Get a message and continue if this does not fail.
				if(msgrcv(messageQueueID, &receivedMessage, sizeof(receivedMessage) - sizeof(long), 0, 0) > ZERO_BYTES) {

					// Reset the number of seconds since last receiving a message.
					secondsSinceLastMessageReceived = 0;
					
					int newDCNum = 0;

					for(int i = 0; i < masterList->numberOfDataCreators; i++) {

						if(receivedMessage.PID == masterList->dc[i].PID) {

							newDCNum = i;
							break;
						}
						else {

							newDCNum = masterList->numberOfDataCreators + 1;
						}
					}

					memset(logString, 0, MAX_LOG_STRING_LENGTH);
					sprintf(logString, "DC-%02d [%d] updated in the master list - "
					"MSG RECEIVED - Status %02d (%s)", newDCNum, receivedMessage.PID, receivedMessage.currentState, stateMeanings[receivedMessage.currentState]);
					
					bool DCFound = false;	
					for(int DCIndex = 0; DCIndex < MAX_DC_ROLES; DCIndex++) {

						
						printLogFile(file, logString);

						// Check if the DC is off.
						if(receivedMessage.currentState == MACHINE_OFFLINE) {

							memset(logString, 0, MAX_LOG_STRING_LENGTH);
							sprintf(logString, "DC-%02d [%d] has gone OFFLINE - removing from master-list", DCIndex, receivedMessage.PID);
							printLogFile(file, logString);
						}

						// continue when the iterator reaches the DC that sent the message.
						if(receivedMessage.PID == masterList->dc[DCIndex].PID) {

							// Reset the last time hearing from the DC.
							masterList->dc[DCIndex].lastHeard = 0;
							DCFound = true;
							continue;
						}

						// Check if the last time hearing from the current DC was 35 seconds ago or that the DC is offline.
						// If it is, then remove it from the list.
						if((((masterList->dc[DCIndex].lastHeard) += WAIT_AFTER_RECIEVE_SECONDS) >= MAX_TIME_NOT_HEARD_FROM_DC)
							|| masterList->dc[DCIndex].currentState == OFFLINE) {


							memset(logString, 0, MAX_LOG_STRING_LENGTH);
							sprintf(logString, "DC-%02d [%d] removed from master-list - NON-RESPONSIVE", DCIndex, receivedMessage.PID);
							printLogFile(file, logString);

							// Remove and the inactive DC and shift the masterlist array so that the
							// items in the list are contiguous.
							memmove(masterList->dc + DCIndex, masterList->dc + (DCIndex + 1), MAX_DC_ROLES);

							// Empty the last element in the array.
							masterList->dc[MAX_DC_ROLES - 1].currentState = 0;  
							masterList->dc[MAX_DC_ROLES - 1].lastHeard = 0;
							masterList->dc[MAX_DC_ROLES - 1].type = 0;
							masterList->dc[MAX_DC_ROLES - 1].PID = 0;

							// Decrement the number of data creators.
							--(masterList->numberOfDataCreators);
						}					
					}

					// If the DC that sent the received message was not in the master list,
					// add it to the master list if it is not full.
					if(!DCFound && masterList->numberOfDataCreators < MAX_DC_ROLES) {

						memset(logString, 0, MAX_LOG_STRING_LENGTH);
						sprintf(logString, "DC-%02d [%d] added to the master list - NEW DC -"
						"Status 0 (Everthing is OKAY)", masterList->numberOfDataCreators, receivedMessage.PID);

						printLogFile(file, logString);

						// Add the received data to the next available position of the masterList.
						masterList->dc[masterList->numberOfDataCreators].PID = receivedMessage.PID;
						masterList->dc[masterList->numberOfDataCreators].currentState = receivedMessage.currentState;
						masterList->dc[masterList->numberOfDataCreators].lastHeard = 0;
						masterList->numberOfDataCreators++;
					}
				}

				// Sleep for 1.5 seconds.
				usleep(WAIT_AFTER_RECIEVE_NANO_SECONDS);
				secondsSinceLastMessageReceived += WAIT_AFTER_RECIEVE_SECONDS;

			} while(secondsSinceLastMessageReceived < MAX_TIME_NOT_HEARD_FROM_DC);

			// Close the log file.
			if(fclose(file) == EOF) {

				printf("\nCannot close DRLog.log\n");
			}
		}
	}

	// If masterList is not NULL, then detach and deallocate the shared memory.
	if(masterList != NULL) {

		shmdt(masterList);
		shmctl(sharedMemoryID, IPC_RMID, NULL);
	}
	// If the message queue exists, deallocate it.
	if(msgget(messageQueueKey, 0) != -1){

		deallocateMessageQueue(messageQueueKey);
	}

	return 0;
}
