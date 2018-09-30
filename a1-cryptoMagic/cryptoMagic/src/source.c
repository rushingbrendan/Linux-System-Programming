/*  
*  FILE          : source.c 
*  PROJECT       : PROG1970 - System Programming - Assignment #1
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*	This assignment encrypts a file and saves it with the same name with .crp extension
*	The program can then decrypt the file.	
*/

//INCLUDE FILES

#include <stdio.h>
#include "../inc/encryptAndDecrypt.h"
#include <string.h>
//EO INCLUDE FILES

//CONSTANTS

#define FILE_NAME_LENGTH 200
#define SUCCESS 1
#define FAIL 0


enum { NONE, ENCRYPT, DECRYPT };


#pragma warning(disable:4996)

//EO CONSTANTS






int main(int argc, char *argv[]) {

	char encFile[FILE_NAME_LENGTH];
	char newencFile[FILE_NAME_LENGTH];
	char decFile[FILE_NAME_LENGTH];
	char newdecFile[FILE_NAME_LENGTH];

	char* cPtr = NULL;

	int choice = NONE;


	if (argc == 3) {

		if ((strcmp(argv[1], "-encrypt") == 0)){

			choice = ENCRYPT;

			strcpy(encFile, argv[2]);
			strcpy(newencFile, argv[2]);
			
			cPtr = strchr(newencFile, '.');

			if (cPtr == NULL) {

				strcat(newencFile, ".crp");

			}//eo if (cPtr == NULL)

			else {

				strcpy(cPtr, ".crp");

			}//eo else
			
	
						

		}//eo if (strcmp(argv[1], "-encrypt") == 0))


		else if ((strcmp(argv[1], "-decrypt") == 0)) {

			choice = DECRYPT;
			strcpy(decFile, argv[2]);
			strcpy(newdecFile, argv[2]);

			cPtr = strchr(newdecFile, '.');

			if (cPtr == NULL) {

				strcat(newdecFile, ".txt");

			}//eo if (cPtr == NULL)

			else {

				strcpy(cPtr, ".txt");

			}//eo else



		}//eo if (strcmp(argv[1], "-decrypt") == 0))

		else {

			printf("\n Error - please enter -decrypt or -encrypt");

		}//eo else


	}//eo if

	else if (argc == 2) {

		choice = ENCRYPT;

		strcpy(encFile, argv[1]);
		strcpy(newencFile, argv[1]);

		cPtr = strchr(newencFile, '.');

		if (cPtr == NULL) {
			strcat(newencFile, ".crp");
		}//eo if (cPtr == NULL)

		else {
			strcpy(cPtr, ".crp");
		}//eo else


	}//eo else if

	else if (argc < 1) {

		printf("\n Error no file entered.");

	}//eo else if


	switch (choice)
	{
	case ENCRYPT:

		if (Encrypt(encFile, newencFile) == SUCCESS){

			printf("\n%s has been successfully encrypted to %s \n",encFile, newencFile);

		}//eo if (Encrypt(encFile, newencFile) == SUCCESS){

		else {

			printf("\n ERROR during encryption.\n");

		}//eo else

		break;
	case DECRYPT:
		
		if (Decrypt(decFile, newdecFile) == SUCCESS){

			printf("\n%s has been successfully decrypted to %s\n", decFile, newdecFile);

		}//eo if (Decrypt(decFile, newdecFile) == SUCCESS){

		else{

			printf("\n ERROR during decryption.\n");

		}	//eo else
		break;
	}
	return SUCCESS;

}// eo int main(int argc, char *argv[])
