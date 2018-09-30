/*!
 *  @file		:	dataCreator.c
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




 /*!
  *
  *	@brief : Sends a message to the message queue.
  *
  * This function sends a message to the message queue
  * The message includes PID, current state and mid.
  *
  * @param[in] - mid - <b>int</b> - The message ID
  * @param[in] - currentState - <b>int</b> - The current state of the data creator.
  *		
  *	@return - <b>int</b> - 1
  */
void send_message (int mid, int currentState)
{
	DCInfo msg;
	int sizeofdata = sizeof (DCInfo) - sizeof (long);

	// indicate message is destined for server
	msg.type = TYPE_SERVERMESSAGE;

	// indicate our returning type, used for filtering the queue
	msg.PID = getpid();

	//add current state to message
	msg.currentState = currentState;

	//last heard initialized as 0
	msg.lastHeard = 0;

	// send the message to server
	msgsnd (mid, (DCInfo*) &msg, sizeofdata, 0);

}
