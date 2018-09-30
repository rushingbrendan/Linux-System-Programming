/*  
*  FILE          : client.c 
*  PROJECT       : PROG1970 - Assignment 4
*  PROGRAMMER    : Josh Rogers
*  FIRST VERSION : Jul 31, 2018
*  DESCRIPTION   : 
*   Client window code for the "Can We Talk" internet chat client
*/

#include "chatClient.h"

int main (int argc, char* argv[]) {

    if ((argc != 3) || (strncmp(argv[1], "-user", 5) != 0) || (strncmp(argv[2], "-server", 7) != 0) || (strlen(argv[1]) < 6) || (strlen(argv[2]) < 14)) {
        printf ("USAGE: chat-client -user<userID> -server<server name>\n");
        return 0;
    }

    //Ncurses variables
    WINDOW * outputWindow = NULL;
    WINDOW * inputWindow = NULL;
    messageParcel* myMessage = NULL;

    //Shared info struct to be passed to threads
    //(global variables are scary)
    sharedInfo progInfo;

    //Threading variables
    pthread_t threads[2];
    void *status;
    pthread_attr_t attr;

    strncpy(progInfo.name, argv[1]+5, 5);

    progInfo.name[5] = '\0';

    setupSockets(&progInfo, argv[2]+7);

    //Initialize the screen
    initscr();

    outputWindow = newwin(OUTPUTWINDOWHEIGHT, WINDOWWIDTH, 3, 0);
    inputWindow = newwin(MESSAGEBOXHEIGHT, WINDOWWIDTH, WINDOWHEIGHT - MESSAGEBOXHEIGHT, 0);

    if (has_colors()) {
        //Starts the color and turn off key echoing
        start_color();
        //Changes the default colors
        assume_default_colors(COLOR_WHITE, COLOR_BLACK);

        init_pair(INVERTEDPAIR, COLOR_BLACK, COLOR_WHITE);
    } else {
        init_pair(INVERTEDPAIR, -1, -1);
    }

    //Hide keypresses
    noecho();

    keypad(inputWindow, TRUE);

    //Prints the default UI
    defaultScreen(INVERTEDPAIR);

    //Draws boxes around the input and output screens
    //And enables scroll lock
    box(outputWindow, 0, 0);
    scrollok(outputWindow, TRUE);
    wrefresh(outputWindow);

    box(inputWindow, 0, 0);
    scrollok(inputWindow, TRUE);
    wrefresh(inputWindow);

    //Sets the necessary values in the sharedInfo struct
    progInfo.inWin = inputWindow;
    progInfo.outWin = outputWindow;
    progInfo.loop = 1;
    progInfo.numMessages = 0;

    // Set up threads
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Spawn the listen/receive deamons
    pthread_create(&threads[0], &attr, sendMessage, (void *)&progInfo);
    pthread_create(&threads[1], &attr, listener, (void *)&progInfo);

    // Keep alive until finish condition is done
    while(progInfo.loop);

    mvwaddstr(inputWindow, 1, 2, "Disconnected. Press any key to exit.");
    wrefresh(inputWindow);
    getch();

    //Clean up and return the screen to default
    closeWindows(&progInfo);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}



//
// FUNCTION   : closeWindows 
//
// DESCRIPTION   : 
//  Closes both windows and frees associated memory
//
// PARAMETERS   : 
//  sharedInfo* progInfo    - A pointer to the program's shared info structure
//
// RETURNS     : 
//   nothing
//

void closeWindows(sharedInfo* progInfo) {

    //Closes input and output windows
    delwin(progInfo->outWin);
    delwin(progInfo->inWin);

    //Frees the ncurses struct created by initscr
    endwin();
    return;

}



//  
// FUNCTION   : defaultScreen 
//
// DESCRIPTION   : 
//  Prints out the inout/output headers and text
//
// PARAMETERS   : 
//  chtype invertColour  - A colour pair that's inverted from the default
//
// RETURNS     : 
//   nothing
//

void defaultScreen (chtype invertColour) {
    int i = 0;
    int j = 0;

    //Print the bar on top of the output section
    for (i = 0; i < 3; i++) {
        for (j = 0; j < WINDOWWIDTH; j++) {
            color_set(invertColour, NULL);
            mvaddch(i, j, ' ');
        }
    }

    //Print the bar on the top of the input section
    for (i = WINDOWHEIGHT - MESSAGEBOXHEIGHT - 3; i < WINDOWHEIGHT - MESSAGEBOXHEIGHT; i++) {
        for (j = 0; j < WINDOWWIDTH; j++) {
            color_set(invertColour, NULL);
            mvaddch(i, j, ' ');
        }
    }

    //Add the "Messages" header to the top bar
    mvaddstr(1, WINDOWWIDTH/2 - strlen("Messages")/2, "Messages");

    //Add the "Outgoing Messages" header to the bottom bar
    mvaddstr(WINDOWHEIGHT - MESSAGEBOXHEIGHT - 2, WINDOWWIDTH/2 - strlen("Outgoing Message")/2, "Outgoing Message");

    //Reset to default colours
    color_set(0, NULL);

    //Refresh the screen to display changes
    refresh();
}
