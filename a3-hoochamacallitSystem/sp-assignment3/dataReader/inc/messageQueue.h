/*!
 *
 *	@file	:	messageQueue.h
 *
 *	project	:	PROG1970 - Systems Programming - The Hoochamacallit System
 *
 *	@author	:	Conor Macpherson
 *
 *	@date	:	2018-07-10
 *
 *	@brief	:	This file contains data and function prototypes for the functions defined in
 *				../src/messageQueue.h.
 *
 */


#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H


#include <sys/types.h>
#include <sys/ipc.h>


#define MSGGET_FAILURE -1
#define MSGRCV_FAILURE -1
#define ZERO_BYTES 0
#define READ_AS_FIFO 0
#define MESSAGE_QUEUE_DOES_NOT_EXISTS -1
#define MESSAGE_QUEUE_DEALLOC_FAILURE -1
#define MESSAGE_QUEUE_EXIST 0
#define MESSAGE_QUEUE_ERROR -1


key_t getMessageQueueKey();

int createMessageQueue(key_t messageKey);
int deallocateMessageQueue(int messageQueueID);

ssize_t receiveMessage(int messageQueueID, void* messageData);


#endif /* MESSAGEQUEUE_H */