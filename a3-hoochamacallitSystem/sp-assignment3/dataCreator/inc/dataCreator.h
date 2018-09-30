/*
*	@file		:	dataCreator.h
*
*	project		:	PROG1970 - System Programming - Assignment #3
* 
*	@author		:	Brendan Rushing & Conor MacPherson
*	
*	@date		:	2018-07-12
*
*	@brief		:	Hoochamacallit System - DataCreator
*					-This program creates a status condition representing the state of the Hoochamacallit machine
*				 	on the shop floor.
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
*				 	 at once with different random seed values.
*
*/


#ifndef DATACREATOR_H
#define DATACREATOR_H

//CONSTANTS


/* some constants to be used in the message passing and handling */
#define TYPE_SERVERMESSAGE		    1

#define OPERATION_ADD			    1
#define OPERATION_DELETE		    2
#define OPERATION_LIST			    3
#define OPERATION_EXIT			    4

#define OPERATION_SUCCESS		    0
#define OPERATION_DBFAILURE		    1
#define OPERATION_INVALIDDATA		2
#define SERVER_EXIT			        10
#define DUMB_CLIENT_ERROR		    999


#define SUCCESS 1
#define FAIL 0

#define MESSAGE_CREATOR_SLEEP 10
#define MESSAGE_QUEUE_ERROR -1

#define MACHINE_STATUS_MIN 0
#define MACHINE_STATUS_MAX 7

#define MESSAGE_CREATOR_DELAY_MIN 10
#define MESSAGE_CREATOR_DELAY_MAX 31


//EO CONSTANTS


//PROTOTYPES

void send_message (int mid, int currentState);

//EO PROTOTYPES


#endif /* DATACREATOR_H */