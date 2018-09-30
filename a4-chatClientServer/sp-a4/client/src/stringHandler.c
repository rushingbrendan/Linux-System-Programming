/*  
*  FILE			 : stringHandler.c 
*  PROJECT		 : PROG1970 - Assignment 4
*  PROGRAMMER	 : Josh Rogers
*  FIRST VERSION : Jul 31, 2018
*  DESCRIPTION	 : 
*   Handles the string formatting and printing portion of the 
*	"Can We Talk" chat client
*/


#include "chatClient.h"


//
// FUNCTION   : printNewMessage 
//
// DESCRIPTION   : 
//  Takes in a message parcel, formats it for output, and prints it to the
//	output window
//
// PARAMETERS   : 
//	messageParcel* toPrint	 - The message parcel that needs formatting
//	sharedInfo* myInfo		 - The shared info struct for the client
//
// RETURNS     : 
//   char*					 - The first half of a split message
//

int printNewMessage(messageParcel* toPrint, sharedInfo* myInfo){
	char* firstMessage = NULL;
	char* secondMessage = NULL;
	char inOut[3] = "<<\0";
	char timeString[10] = { 0 };
	char outputString[MESSAGELENGTH+1];
	int i = 0;

	//Gets the current time for a timestamp
	time_t currTime;
	struct tm * localTime;
	time(&currTime);
	localTime = localtime(&currTime);

	//Converts the tm* struct to a formatted string
	strftime(timeString, sizeof(char)*11, "(%H:%M:%S)", localTime);

	
	//If the received message is the exit message
	//Print [username] disconnected instead of the message contents
	if (strcmp(toPrint->messageText, EXITMESSAGE) == 0) {
		if (strcmp(toPrint->userName, myInfo->name) != 0) {
			sprintf(outputString, "%-15s [%-5s] %s %-40s %s", toPrint->messageIP, toPrint->userName, inOut, "User disconnected.", timeString);
			incrNumMessages(myInfo);
			mvwaddstr(myInfo->outWin, myInfo->numMessages, 1, outputString);
		}
	} else {

		//Parcel the message if necessary
		firstMessage = parcelToString(&secondMessage, toPrint);

		if (firstMessage == NULL) {
			//Message didn't get allocated correctly, so don't try to print it
		} else {

			//If the username on the message matches your own, the message was
			//probably sent by you, so change the directional arrows
			if (strcmp(toPrint->userName, myInfo->name) == 0) {

				strcpy(inOut, ">>");

			}

			//Print the formatted string to outputString
			sprintf(outputString, "%-15s [%-5s] %s %-40s %s", toPrint->messageIP, toPrint->userName, inOut, firstMessage, timeString);

			incrNumMessages(myInfo);

			free (firstMessage);
			
			//Print the string to the output window
			mvwaddstr(myInfo->outWin, myInfo->numMessages, 1, outputString);

		}

		//If there was a second message, format and print it
		if (secondMessage != NULL) {

			if (strcmp(toPrint->userName, myInfo->name) == 0) {
				strcpy(inOut, ">>");
			}

			sprintf(outputString, "%-15s [%-5s] %s %-40s %s", toPrint->messageIP, toPrint->userName, inOut, secondMessage, timeString);
			
			incrNumMessages(myInfo);
			free(secondMessage);

			//Add the string to the output window
			mvwaddstr(myInfo->outWin, myInfo->numMessages, 1, outputString);
		}
	}

	//Move the cursor back to the correct spot on the input window
	wmove(myInfo->inWin, myInfo->cursorY, myInfo->cursorX);

	//Refresh both windows to reflect changes
	wrefresh(myInfo->outWin);
	wrefresh(myInfo->inWin);
}



//
// FUNCTION   : incrNumMessages 
//
// DESCRIPTION   : 
//  Increments the number of messages that are on the screen. If it's equal
//	to the max number of messages, instead scroll the screen (and fix the box,
//	since it scrolls too)
//
// PARAMETERS   : 
//	sharedInfo* myInfo		- The shared info struct for the chat client
//
// RETURNS     : 
//   Nothing
//

void incrNumMessages (sharedInfo* myInfo) {
	int i = 0;

	if (myInfo->numMessages >= MAXMESSAGESINWINDOW) {

		wscrl(myInfo->outWin, 1);
		box(myInfo->outWin, 0, 0);
		for (i = 1; i < WINDOWWIDTH - 1; i++) {
			mvwaddch(myInfo->outWin, OUTPUTWINDOWHEIGHT - 2, i, ' ');
		}

	} else {

		myInfo->numMessages++;

	}
}



//
// FUNCTION   : parcelToString 
//
// DESCRIPTION   : 
//  Converts a message parcel to two messages if it's too long, otherwise
//	just return a pointer to the first message
//
// PARAMETERS   : 
//  char** secondMessage	 - The address of the second half of a split message
//								if there is one, or NULL if there isn't
//	messageParcel* toConvert - The address of the message parcel that's being
//								converted to a string
//
// RETURNS     : 
//   char*					 - The first half of a split message
//

char* parcelToString (char** secondMessage, messageParcel* toConvert) {
	char* firstMessage = NULL;
	char buffer[MESSAGELENGTH+1] = {0};
	int i = 0;
	int splitOnSpace = 0;
	int placeToSplit = 0;

	//If the message is too long to fit in one message
	//Find the best place to split it up
	if (strlen(toConvert->messageText) > 40) {

		//Figure out where to split the message
		placeToSplit = splitMessage(toConvert->messageText);

		if (placeToSplit != MAXPARCELTEXTLENGTH) {

			//If the message wasn't split exactly in the middle, overwrite
			//the whitespace that would otherwise be at the start of line 2
			splitOnSpace = 1;

		}

		//Allocate memory for the second string and copy it into secondMessage
		*secondMessage = malloc(strlen(toConvert->messageText) - placeToSplit + 1);

		if (*secondMessage != NULL) {

			//Make sure secondMessage allocated correctly
			strcpy(*secondMessage, toConvert->messageText+placeToSplit + splitOnSpace);
			toConvert->messageText[placeToSplit] = '\0';

		} else {

			//Otherwise just set it to NULL
			*secondMessage = NULL;

		}


	} else {

		//If the message didn't need to be split, set secondMessage to NULL
		*secondMessage = NULL;

	}

	//Allocate memory for firstMessage and error check it
	firstMessage = malloc (sizeof(char)*MESSAGELENGTH+1);
	if (firstMessage == NULL) {
		return NULL;
	}

	//Copy the message into first message and return it
	strcpy(firstMessage, toConvert->messageText);
	return firstMessage;

}



//
// FUNCTION   : getMessageToSend 
//
// DESCRIPTION   : 
//  Gets a new message from the user input window
//
// PARAMETERS   : 
//  sharedInfo* myInfo		- The client's shared info struct
//
// RETURNS     : 
//   char*					- The message to send to the server
//

char* getMessageToSend (sharedInfo* myInfo) {
	int userKey = ' ';
	char* message = NULL;
	int i = 0;
	int numChars = 0;
	char inputBuffer[81];

	myInfo->cursorY = 1;
	myInfo->cursorX = 2;

	mvwaddch(myInfo->inWin, 1, 1, '>');
	wrefresh(myInfo->inWin);


	do {

		//Get input from the user
		userKey = wgetch(myInfo->inWin);
		
		//Sets the cursorY/X to just after the last character entered
		myInfo->cursorY = numChars/(MAXMESSAGETEXTLENGTH/2) + 1;
		myInfo->cursorX = numChars % (MAXMESSAGETEXTLENGTH/2) + 2;

		if ((userKey == KEY_BACKSPACE) && (numChars > 0)) {

			//If the input key is a backspace, delete the last character from the array
			inputBuffer[numChars-1] = '\0';

			//Decrement the number of characters in the input box
			numChars--;

			if (myInfo->cursorX == 2) {

				//If the cursor is in the wrong place, move it to the end of the current line
				myInfo->cursorY -= 1;
				myInfo->cursorX = MAXPARCELTEXTLENGTH + 2;

			}

			//Replace the last entered character with a space
			mvwaddch(myInfo->inWin, myInfo->cursorY, myInfo->cursorX - 1, ' ');

			//Moves the cursor to the correct writing position (only matters visually)
			wmove(myInfo->inWin, myInfo->cursorY, myInfo->cursorX - 1);

		//Else, if we aren't at the current message length limit
		} else if (numChars < MAXMESSAGETEXTLENGTH) {

			//If the input key is a valid, visible ascii character, print the key
			if ((userKey >= 32) && (userKey <= 126)) {
				
				mvwaddch(myInfo->inWin, myInfo->cursorY, myInfo->cursorX, userKey);
				
				//Add the character to the output array
				inputBuffer[numChars] = userKey;

				//Make the next character in the output array a null terminator (end of output string)
				inputBuffer[numChars+1] = '\0';

				//Increment number of characters in output array
				numChars++;
			}
		}

		//Refresh the screen to display changes
		wrefresh(myInfo->inWin);

		//Loop until the user hits the enter key
	} while ((userKey != '\n') && (myInfo->loop == 1));


	//Clears out the chat box
	for (i = 0; i < WINDOWWIDTH - 1; i++) {
		mvwaddch(myInfo->inWin, i/(MAXMESSAGETEXTLENGTH/2) + 1, i % (MAXMESSAGETEXTLENGTH/2) + 2, ' ');
	}

	//Refresh the input window to reflect changes
	wrefresh(myInfo->inWin);

	//If the user hit enter without adding any characters, return null
	if ((numChars == 0) || (myInfo->loop == 0)){
		return NULL;
	}

	//Malloc space for the output string and error check
	message = malloc (strlen(inputBuffer) * sizeof(char));
	if (message == NULL) {
		return NULL;
	}

	//Copy the output string into the return value
	strcpy(message, inputBuffer);

	//Return the output string
	return message;

}



//
// FUNCTION   : splitMessage 
//
// DESCRIPTION   : 
//  Figured out where to split the input message based on spaces
//
// PARAMETERS   : 
//  char* messageToSplit	- The text portion of the message that needs splitting
//
// RETURNS     : 
//   int					- The index to split the message at
//							  or MAXPARCELTEXTLENGTH, if the message can't be split
//

int splitMessage(char* messageToSplit) {
	int messageLength = strlen(messageToSplit);
	int startPt = MAXPARCELTEXTLENGTH;
	int i = 0;

	//Search backwards from the middle of the message for a space
	//Until either a space is found or the second half of the message
	//would be too long
	for (i = startPt; (messageLength - i) < MAXPARCELTEXTLENGTH; i--) {

		if (messageToSplit[i] == ' ') {

			//Return where to split the message
			return i;

		}

	}

	//If a suitable place to split wasn't found, just return the index of the middle
	return MAXPARCELTEXTLENGTH;

}