#ifndef _CLIENTHEADER
#define _CLIENTHEADER

/*  
*  FILE          : chatClient.h 
*  PROJECT       : PROG1970 - Assignment 4
*  PROGRAMMER    : Josh Rogers
*  FIRST VERSION : Jul 31, 2018
*  DESCRIPTION   : 
*   Includes and function prototypes for the
*   "Can We Talk" chat client
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <pthread.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define WINDOWWIDTH 81
#define WINDOWHEIGHT 24
#define MAXPARCELTEXTLENGTH 40
#define MAXMESSAGETEXTLENGTH 80
#define MESSAGELENGTH 79
#define MESSAGEBOXHEIGHT 4
#define OUTPUTWINDOWHEIGHT (WINDOWHEIGHT - MESSAGEBOXHEIGHT - 6)

#define USERNAMEWIDTH 5

#define MAXMESSAGESINWINDOW 10
#define MAXIPLENGTH 16

#define EXITMESSAGE ">>bye<<"

#define INVERTEDPAIR 1

#define PORT 9999


//Holds the message parcel information
typedef struct {
    char messageIP[MAXIPLENGTH];
    char userName [USERNAMEWIDTH+1];
    char messageText [MAXMESSAGETEXTLENGTH+1];
    uint messageTime;
} messageParcel;

//Shared info that's needed throughout the client
typedef struct {
    WINDOW* inWin;
    WINDOW* outWin;
    char name[USERNAMEWIDTH+1];
    int loop;
    int sockfd;
    int numMessages;
    int cursorY;
    int cursorX;
    pthread_mutex_t mutexsum;
} sharedInfo;


//String handling functions
int splitMessage(char*);
int printNewMessage(messageParcel*, sharedInfo*);
char* parcelToString (char**, messageParcel*);
char* getMessageToSend (sharedInfo*);
void incrNumMessages (sharedInfo*);


//Client window functions
void closeWindows(sharedInfo*);
void defaultScreen (chtype);
void closeWindows(sharedInfo*);


//Networking-related functions
int setupSockets (sharedInfo*, char*);
void* sendMessage (void*);
void* listener (void*);

#endif
