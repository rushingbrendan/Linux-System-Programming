/*  
*  FILE          : srec.h
*  PROJECT       : PROG1970 - System Programming - Assignment #2
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*	This assignment encodes files and stdin to stdout and srec / ASM files
*/

//CONSTANTS

#pragma once

#define SUCCESS 1
#define FAIL 0

//EO CONSTANTS


//PROTOTY
int toSREC(char * FILENAME, char * NEW_FILENAME);
int toSREC_stdin(char * FILENAME);


//EO PROTOTYPES
