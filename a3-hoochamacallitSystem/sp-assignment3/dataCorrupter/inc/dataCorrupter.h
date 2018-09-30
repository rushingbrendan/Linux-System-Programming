/*
*  FILE          : dataCorrupter.h
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

#ifndef DATACORRUPTER_H
#define DATACORRUPTER_H

#define MAX_DC_ROLES 10


#include "../../common/inc/common.h"

//EO INCLUDE FILES

//CONSTANTS



/* some constants to be used in the message passing and handling */
#define TYPE_SERVERMESSAGE		1

#define OPERATION_ADD			1
#define OPERATION_DELETE		2
#define OPERATION_LIST			3
#define OPERATION_EXIT			4

#define OPERATION_SUCCESS		0
#define OPERATION_DBFAILURE		1
#define OPERATION_INVALIDDATA	2
#define SERVER_EXIT				10
#define DUMB_CLIENT_ERROR		999

#define SHARED_MEMORY_COUNT_DONE 100
#define SHARED_MEMORY_ID_VALID 0
#define SHARED_MEMORY_ERROR -1
#define SHARED_MEMORY_SUCCESS 0

#define MESSAGE_QUEUE_ERROR -1

#define INVALID_PID 0

#define DC1 0
#define DC2 1
#define DC3 2
#define DC4 3
#define DC5 4
#define DC6 5
#define DC7 6
#define DC8 7
#define DC9 8
#define DC10 9


#define WOD_SLEEP_MIN 10
#define WOD_SLEEP_MAX 31

#define WOD_MAX_CHOICE 21	
#define WOD_MIN_CHOICE 0


//EO CONSTANTS


//PROTOTYPES
//void wheelOfDestruction (struct MasterList *inputMasterList, int inputValue);
key_t getShmemKey(void);
MasterList *attachToSharedMemory (key_t shmem_key);
int killPID (pid_t inputPID);


//EO PROTOTYPES


#endif /* DATACREATOR_H */
