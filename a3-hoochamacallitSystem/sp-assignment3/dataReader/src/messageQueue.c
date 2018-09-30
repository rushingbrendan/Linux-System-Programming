/*!
 *
 *	@file	:	messageQueue.c
 *
 *	project	:	PROG1970 - Systems Programming - The Hoochamacallit System
 *
 *	@author	:	Brendan Rushing & Conor Macpherson
 *
 *	@date	:	2018-07-17
 *
 *	@brief	:	This file contains the function definitions for the function prototypes
 *				defined in ../inc/messageQueue.h
 *
 */


#include "../../common/inc/common.h"
#include "../inc/messageQueue.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


/*!
 *
 *	@brief Get a message queue key.
 *
 *	@return - <b>key_t</b> - A message queues key.
 *	@return - <b>key_t</b> - -1 if ftok fails.
 *
 */
key_t getMessageQueueKey() {

	key_t messageKey = ftok(".", 'A');

	int errnoSave = errno;

	if(messageKey == FTOK_FAILURE) {

		printf("%s", strerror(errnoSave));
	}

	return messageKey;
}


/*!
 *
 *	@brief Locates an existing message queue.
 *
 *	@param[in] - queueKey - <b>key_t</b> - A previously acquired message queue key. 
 *
 *	@return - <b>int</b> - The message queue ID if no errors ocur.
 *	@return - <b>int</b> - -1 if msgget fails.
 *
 */
int createMessageQueue(key_t messageKey) {

	int messageQueueID = 0;

	if((messageQueueID = msgget(messageKey, MESSAGE_QUEUE_EXIST)) == MESSAGE_QUEUE_DOES_NOT_EXISTS) {

		messageQueueID = msgget(messageKey, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

		int errnoSave = errno;

		if(messageQueueID == MSGGET_FAILURE) {
			
			printf("\nmsgget error: %s\n", strerror(errnoSave));
		}
	}

	return messageQueueID;
}


/*!
 *
 *	@brief Deallocates a message queue.
 *
 *	@param[in] - messageQueueID - <b>int</b> - The ID of the message queue to deallocate.
 *
 *	@param[in] - cmd - <b>int</b> - The command
 *
 *	@return - <b>int</b> -
 *
 */
int deallocateMessageQueue(int messageQueueID) {

	int msgctlReturn = 0;

	if((msgctlReturn = msgctl(messageQueueID, IPC_RMID, (struct msqid_ds *) NULL)) == MESSAGE_QUEUE_DEALLOC_FAILURE) {

		int errnoSave = errno;

		printf("\nmsgctl error: %s\n", strerror(errnoSave));
	}

	return msgctlReturn;
}

