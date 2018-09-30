/*  
*  FILE          : encryptAndDecrypt.h
*  PROJECT       : PROG1970 - System Programming - Assignment #1
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*    The functions in this file are used to encrypt and decrypt a file.
*/

//CONSTANTS

#pragma once

#define SUCCESS 1
#define FAIL 0

//EO CONSTANTS


//PROTOTYPES

int Encrypt(char * FILENAME, char * NEW_FILENAME);
int Decrypt(char *FILENAME, char *NEW_FILENAME);

//EO PROTOTYPES
