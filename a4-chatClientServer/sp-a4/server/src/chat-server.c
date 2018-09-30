/*!
 *
 *	@file		:	server.c
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



//INCLUDE FILES
#include "../inc/chat-server.h"
//eo INCLUDE FILES


//PROTOTYPES
void initializeGlobalData(void);
void *listenForConnections(void* inputSockForward);
void *clientData(void* inputSockForward);
int sendMessage(int currentSender, messageParcel_t messageEnvelope);
void removeSwearWords (char* message);
//eo PROTOTYPES


//GLOBAL VARIABLES
serverInfo_t clientInformation;
pthread_t threads[MAX_NUMBER_USERS];
//eo GLOBAL VARIABLES



int main(int argc, char *argv[])
{

    struct sockaddr_in server_addr;
    pthread_t listenThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int sockForward = 0;
    int portNumber = PORT_NUMBER;
    int newSockForward = 0;
    struct sockaddr_in client_addr;
    socklen_t clilen;
    int currentThread = 0;
    int option =1;

    initializeGlobalData();     //initialize global data to 0 


    //1. CREATE A SOCKET WITH SOCKET() SYSTEM CALL    
    sockForward = socket(AF_INET, SOCK_STREAM, 0);
    if (sockForward < SOCK_ERROR){

        return EXIT_FAILURE;
    }

    bzero((char *) &server_addr, sizeof(server_addr)); //zero out serv_addr array

    //variables needed for sock communication
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portNumber);
    
    //CHECK TO MAKE SURE THE SOCKET CAN BE BINDED
    if (setsockopt(sockForward, SOL_SOCKET, (SO_REUSEPORT |SO_REUSEADDR), (char*)&option,sizeof(option)) <0){

        return EXIT_FAILURE;
    }


    //2. BIND THE SOCKET TO THE ADDRESS USING THE BIND() SYSTEM CALL
    if (bind(sockForward, (struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) {

        return EXIT_FAILURE;
    } 
    
    signal(SIGPIPE,SIG_IGN);

    //THREAD --- LISTEN FOR CONNECTIONS
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&listenThread, &attr, listenForConnections, (void *)&sockForward);


    while(1){
        
        while (clientInformation.currentNumberOfUsers == 0);

        //CHECK IF ALL USERS LOGGED OFF
        if (clientInformation.currentNumberOfUsers == 0){

            //kill listening thread
            pthread_cancel(listenThread);

            //CLOSE SYSTEM USING CLOSE() SYSTEM CALL
            close(sockForward);

            break;
        }
    }
    
    //CLOSE THREADS
    for (int i = 0; i < MAX_NUMBER_USERS; i++){

        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
    }

    pthread_join(listenThread, NULL);
    return EXIT_SUCCESS;
}//eo main





 /*
 * FUNCTION : initializeGlobalData
 *
 * DESCRIPTION : This function initializes global variables to 0
 *
 * PARAMETERS : 
 *		
 *
 * RETURNS : 
 */
void initializeGlobalData(void){

    clientInformation.currentNumberOfUsers = 0;

    for (int i = 0; i < MAX_NUMBER_USERS; i++){

        strcpy(clientInformation.clientsOnServer[i].ipAddress, "");
        clientInformation.clientsOnServer[i].socket = 0;

    }//eo for
}//eo void initializeGlobalData(void){





/*
 * FUNCTION : listenForConnections
 *
 * DESCRIPTION : This function listens and accepts new clients
 *
 * PARAMETERS : void* inputsockForward
 *		
 *
 * RETURNS : 
 */
void *listenForConnections(void* inputSockForward){

    int newSockForward = 0;
    struct sockaddr_in client_addr;
    socklen_t clilen;
    pthread_attr_t attr;
    int sockForward = *((int*)inputSockForward);
    int currentThread = 0;

    signal(SIGPIPE,SIG_IGN);

    do{
        //3. LISTEN FOR CONNECTIONS USING LISTEN() SYSTEM CALL
        listen(sockForward,SOCK_BACKLOG);
        clilen = sizeof(client_addr);

        //4. ACCEPT A CONNECTION USING ACCEPT() SYSTEM CALL
        newSockForward = accept(sockForward, (struct sockaddr *) &client_addr, &clilen);

        //increment current users count
        clientInformation.currentNumberOfUsers++;

        //ADD USER TO SERVER DATABASE
        for (int i = 0; i < MAX_NUMBER_USERS; i++){

            if (clientInformation.clientsOnServer[i].socket == 0){

                strcpy(clientInformation.clientsOnServer[i].ipAddress,inet_ntoa(client_addr.sin_addr ));
                clientInformation.clientsOnServer[i].socket = newSockForward;
                currentThread = i;

                break;
            }   

        }//eo for

        //THREAD --- ClientData
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_create(&threads[currentThread], &attr, clientData, (void *)&newSockForward);

    }while (1);
}//eo void *listenForConnections(int sockForward){






/*
 * FUNCTION : clientData
 *
 * DESCRIPTION : This function handles reading client data
 *
 * PARAMETERS : void* inputsockForward
 *		
 *
 * RETURNS : 
 */
void *clientData(void* inputSockForward){
    
    int sockForward = *((int*)inputSockForward);
    char buffer[BUFFER_SIZE] = {0};
    int n = 0;
    messageParcel_t messageEnvelope;
    int retCode = 0;
    int error = 0;
    socklen_t len = sizeof(error);
    char* cPtr = NULL;
    int option = 1;

    signal(SIGPIPE,SIG_IGN);

    while(1){

        //5. RECEIVE DATA USING THE READ() SYSTEM CALL
        bzero(buffer,BUFFER_SIZE);      //zero out buffer

        retCode = getsockopt(sockForward, SOL_SOCKET, SO_ERROR, &error, &len);  //check for errors
            
        if ((retCode == SOCK_OPT_NO_ERROR) && (error == SOCK_OPT_NO_ERROR)){

            //READ DATA FROM SOCKET
            n = read(sockForward, &messageEnvelope, sizeof messageEnvelope);    
        }

        if (n <= SOCK_ERROR){

            break;      //break because server could not read from client so it must be disconnected
        }

        //ADD IP ADDRESS TO CLIENT
        for (int i = 0; i < MAX_NUMBER_USERS; i++){

            if (clientInformation.clientsOnServer[i].socket == sockForward){

                strcpy(messageEnvelope.messageIP,clientInformation.clientsOnServer[i].ipAddress);
                break;
            }   
        }//eo for

        //REMOVE SWEAR WORDS FROM MESSAGE
        removeSwearWords(messageEnvelope.messageText);

        //SEND DATA TO ALL USERS
        n = sendMessage(sockForward, messageEnvelope);

        if (n <= SOCK_ERROR){

          break;     //Break because socket failed the write therefore user must have disconnected.
        } 

        if (strcmp(messageEnvelope.messageText, EXIT_MESSAGE) == 0){

            break;//Break because user entered bye message
        }

    }

    //USER IS SIGNING OFF
    //DECREMENET COUNT
    clientInformation.currentNumberOfUsers--;

    //REMOVE USER FROM DATABASE
    for (int i = 0; i < MAX_NUMBER_USERS; i++){

        if (clientInformation.clientsOnServer[i].socket == sockForward){

            strcpy(clientInformation.clientsOnServer[i].ipAddress,"");  //clear ip address
            clientInformation.clientsOnServer[i].socket = 0;            //clear socket
            
            break;
        }   

    }//eo for

    //CLOSE SOCKET
    close(sockForward);
    pthread_exit(NULL);


}//eo void *clientData(void* sockForward){







/*
 * FUNCTION : sendMessage
 *
 * DESCRIPTION : This function sends message to all users except
 *                the one who sent it.
 *
 * PARAMETERS : void* inputsockForward
 *		
 *
 * RETURNS : 
 */

int sendMessage(int currentSender, messageParcel_t messageEnvelope){

    int n = 0;
    int error = 0;
    socklen_t len = sizeof(error);
    int retCode = 0;
    int option = 1;

    //SEND MESSAGE TO ALL USERS
    for (int i = 0; i < MAX_NUMBER_USERS; i++){

        if (clientInformation.clientsOnServer[i].socket != 0){

            retCode = getsockopt(clientInformation.clientsOnServer[i].socket, SOL_SOCKET, SO_ERROR, &error, &len);
            if ((retCode == SOCK_OPT_NO_ERROR) && (error == SOCK_OPT_NO_ERROR)){

                n = write(clientInformation.clientsOnServer[i].socket,&messageEnvelope,sizeof messageEnvelope);
            }

        }   

    }//eo for

    return n;

}//eo 




/*
 * FUNCTION : removeSwearWords
 *
 * DESCRIPTION : This function replaces swear words found in a char array with *'s
 *
 * PARAMETERS : char* message
 *		
 *
 * RETURNS : 
 */
void removeSwearWords (char* message){

    char* cPtr = NULL;

    for (int i = 0; i < NUMBER_OF_SWEAR_WORDS; i++){

        while ((cPtr = strcasestr(&message[0],  swearWords[i])) != NULL){
            memset(cPtr, REPLACE_SWEAR_WORD_CHAR, ((strlen( swearWords[i]))*sizeof(char)));
        }
    }
}