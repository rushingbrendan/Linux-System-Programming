/*!
 *
 *	@file		:	server.h
 *
 *  project		:	PROG1970 - System Programming - Assignment #4
 *
 *  @author		:	Brendan Rushing & Josh Rogers
 *
 *  @date		:	2018-08-01
 *
 *  @brief		:	The "Can We Talk" System - Server
 *
 *			- This program is the server for the chat system
 *          - This server receives messages through a socket and sends them to the clients
 *          - The swear words from the messages are replaced with * characters
 *          - The server supports up to 10 users
 *          - The messages are 40 characters max
 *          - The server uses threading to function:
 *                  - 1 thread to monitor system and close when done
 *                  - 1 thread to look for new connections
 *                  - up to 10 threads (1 per user)
 *
 */


//CONSTANTS
#define BUFFER_SIZE 256
#define PORT_NUMBER 9999
#define IP_ADDRESS_LENGTH 20
#define MAX_NUMBER_USERS 10
#define SOCK_ERROR 0
#define SOCK_BACKLOG 5
#define SOCK_OPT_NO_ERROR 0

#define USERNAMEWIDTH 5
#define MAXMESSAGETEXTLENGTH 80
#define MESSAGELENGTH 79

#define NUMBER_OF_SWEAR_WORDS 5
#define REPLACE_SWEAR_WORD_CHAR '*'


#define EXIT_MESSAGE ">>bye<<"

const char* swearWords[] = {"fuck", " ass ", "asshole", "shit", "bitch" };



typedef struct messageParcel{
    char messageIP[16];
    char userName [USERNAMEWIDTH+1];
    char messageText [MAXMESSAGETEXTLENGTH+1];
    unsigned int messageTime;
} messageParcel_t;


typedef struct clientInfo{

int socket;
char ipAddress[IP_ADDRESS_LENGTH];

}clientInfo_t;


typedef struct serverInfo{

int currentNumberOfUsers;
clientInfo_t clientsOnServer[10];

}serverInfo_t;

//eo CONSTANTS


//INCLUDE FILES
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>


#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>

//eo INCLUDE FILES























