/*  
*  FILE			 : messageHandler.c 
*  PROJECT		 : PROG1970 - Assignment 4
*  PROGRAMMER	 : Josh Rogers
*  FIRST VERSION : Jul 31, 2018
*  DESCRIPTION	 : 
*   Handles the networking portion of the "Can We Talk"
*	chat client
*/

#include "chatClient.h"


//
// FUNCTION : setupSockets 
//
// DESCRIPTION : 
//Opens a socket with the server, given the server's IP
//and saves the socket fd in the sharedInfo structure
//
// PARAMETERS : 
//sharedInfo* progInfo		- The client's shared info structure
//char* serverName			- The IP of the server to connect to
//
// RETURNS	 : 
// nothing
//

int setupSockets (sharedInfo* progInfo, char* serverName) {
	int len;
	int result;
	char buf[256];
	struct sockaddr_in address;
	struct termios oldt;
	struct termios newt;

	//printf("%s\n", serverName);

	progInfo->sockfd = 0;
	pthread_mutex_init (&progInfo->mutexsum, NULL);
	//progInfo->mutexsum = PTHREAD_MUTEX_INITIALIZER;

	// save old terminal settings
	tcgetattr ( 0, &oldt );
	newt = oldt;

	// Disable echo and cannon
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr ( 0, TCSANOW, &newt );

	tcsetattr ( 0, TCSANOW, &oldt );

	//Make socket
	progInfo->sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (progInfo->sockfd < 0) {
		return 3;
	}

	//attr
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(serverName);
	address.sin_port = htons(PORT);

	len = sizeof(address);

	// Make connection
	result = connect(progInfo->sockfd, (struct sockaddr *)&address, len);

	if(result == -1)
	{
		perror("Connection failed, try again.\n");
		exit(1);
	}

	return 0;
}



//
// FUNCTION : setupSockets 
//
// DESCRIPTION : 
//The loop to get a message from the user and send it to the server
//
// PARAMETERS : 
//void* myInfo		- A pointer to the client's shared info structure
//
// RETURNS	 : 
// void*		- NULL
//

void *sendMessage (void* myInfo) {
	char* messageText = NULL;
	int numMessages = 0;
	int i;
	int error = 0;
	int returnVal = 0;
	socklen_t length = sizeof(int);
	messageParcel* messageToSend = malloc(sizeof(messageParcel));

	//Make sure that the memory for the parcel was allocated correctly
	if (messageToSend == NULL) {

		return NULL;

	}

	if (messageToSend != NULL) {

		strcpy(messageToSend->userName, ((sharedInfo*)myInfo)->name);
		messageToSend->userName[USERNAMEWIDTH] = '\0';

		do {

			//If there was a message already, free the memory
			if (messageText != NULL) {
				 free (messageText);
			}

			//Get a message
			messageText = getMessageToSend((sharedInfo*)myInfo);

			if (messageText != NULL) {

				//If the input was valid, print it
				//REPLACE THIS WITH ACTUALLY SENDING MESSAGE
				strcpy(messageToSend->messageText, messageText);

					returnVal = getsockopt(((sharedInfo*)myInfo)->sockfd, SOL_SOCKET, SO_ERROR, &error, &length);

					//Make sure the server is still connected
					if (returnVal == 0) {
						if (error == 0) {
							write(((sharedInfo*)myInfo)->sockfd, (void*)messageToSend, sizeof(messageParcel));
						} else {
							closeWindows((sharedInfo*)myInfo);
							exit(1);
						}
					} else {
						closeWindows((sharedInfo*)myInfo);
						exit(1);
					}

				}

			//Move the cursor back to the writing position
			wmove(((sharedInfo*) myInfo)->inWin, 1, 1);

			//Refresh the screen to display changes
			wrefresh(((sharedInfo*) myInfo)->outWin);
			wrefresh(((sharedInfo*) myInfo)->inWin);

			//Loop until the user input the exit message
		} while ((messageText == NULL) || (strcmp(messageText, EXITMESSAGE) != 0));

		free (messageToSend);

	}

	((sharedInfo*)myInfo)->loop = 0;

	if (messageText != NULL) {
		//When exiting, free the last message if there was one
		free (messageText);
	}

	pthread_exit(NULL);

	return NULL;
}

// Listen for messages and display them
void *listener(void* myInfo)
{
	//Create a destination message parcel
	int size = sizeof(messageParcel);
	messageParcel* newMessage = malloc(size);

	int error = 0;

	while(((sharedInfo*) myInfo)->loop == 1)
	{
		error = read(((sharedInfo*)myInfo)->sockfd, newMessage, size);

		//If the error value is 0, the server probably died
		//So tell the program not to loop and exit
		if (error == 0) {
			((sharedInfo*)myInfo)->loop = 0;
			free(newMessage);
			return NULL;
		}

		//Prints the contents of the message package
		printNewMessage(newMessage, (sharedInfo*) myInfo);
	}

	free(newMessage);

	pthread_exit(NULL);

	return NULL;
}

