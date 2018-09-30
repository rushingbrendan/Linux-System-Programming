/*
*  FILE          : dataProducer1.h
*  PROJECT       : PROG1970 - System Programming - Assignment #5
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-08-14
*  DESCRIPTION   :
* 	Histogram System - Data Producer #1
*
*	1. When launched: setup shared memory and semaphore
*
*	2. Launch DataProducer2
*	3. Generate 20 random letters and write it to the circular buffer
*	4. Sleep for 2 seconds
*
*
*
*/



//INCLUDE FILES
#include "../../common/inc/common.h"
//EO INCLUDE FILES

//CONSTANTS
#define FORK_DELAY_TIME 3
#define DP1_SLEEP_TIME 2
//eo CONSTANTS
