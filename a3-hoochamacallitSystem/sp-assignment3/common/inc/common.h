/*  
*  FILE          : common.h
*  PROJECT       : PROG1970 - System Programming - Assignment #3
*  PROGRAMMER    : Brendan Rushing & Conor MacPherson
*  FIRST VERSION : 2018-07-12
*  DESCRIPTION   : 
*    Hoochamacallit System - Common code used for all 3 programs in Hoochamacallit System:
						   - Functions, Include files, Constants, Definitions
*/

#ifndef COMMON_H
#define COMMON_H

//INCLUDE FILES
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>


#include <signal.h>
#include <errno.h>
//eo INCLUDE FILES


//defines

#define MAX_DC_ROLES 10
#define FTOK_FAILURE -1
#define WRITE_OF_ZERO_BYTES 0
#define FILE_TEXT_WIDTH 200
#define SHARED_MEMORY_KEY_VALUE 16535

//eo defines

//CONSTANTS

enum Events {
		
	EVERYTHING_OKAY,
	HYDRAULIC_PRESSURE_FAILURE,
	SAFETY_BUTTON_FAILURE,
	NO_RAW_MATERIAL_IN_PROCESS,
	OPERATING_TEMPERATURE_OUT_OF_RANGE,
	OPERATOR_ERROR,
	MACHINE_OFFLINE,
	UNKOWN_STATE
};

enum DCLogTypes { NON_RESPONSIVE, NEW_DC, MSG_RECEIVED, OFFLINE };


typedef struct tagDBMESSAGE 
{
	// the following is a requirement of UNIX/Linux
	long type;

	// now the specifics of our message
	pid_t PID;
    int currentState;
	double lastHeard;

} DCInfo;



typedef struct MasterList {

	int messageQueueID;
	int numberOfDataCreators;
	DCInfo dc[MAX_DC_ROLES];
	
} MasterList;


//eo CONSTANTS


//PROTOTYPES
void printStatus(int input);
void printTimeAndDateToScreen(void);
void printLogFile(FILE *FILENAME, char* input);
double RAND(double min, double max);
FILE* openFile(const char* fileName);
bool appendToFile(FILE* filePtr, char* buffer);
bool closeFile(FILE* filePtr);
bool logEvent(MasterList* masterList, int logType, int DCNum);

//eo PROTOTYPES



#endif /* COMMON */
