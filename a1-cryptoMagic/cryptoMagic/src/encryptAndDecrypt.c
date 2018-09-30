/*  
*  FILE          : encryptAndDecrypt.c 
*  PROJECT       : PROG1970 - System Programming - Assignment #1
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*    The functions in this file are used to encrypt and decrypt a file.
*/

//INCLUDE FILES

#include <stdio.h>

//EO INCLUDE FILES

//CONSTANTS

#define SUCCESS 1
#define FAIL 0


#pragma warning(disable:4996)

//EO CONSTANTS

//PROTOTYPES

int convertHextoDec(char input);

//EO PROTOTYPES


 /*
 * FUNCTION : Encrypt
 *
 * DESCRIPTION : This function encrypts a file
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int Encrypt(char * FILENAME, char * NEW_FILENAME)
{
	FILE *inFile = NULL;   //Declare inFile
	FILE *outFile = NULL;  //Declare outFile
	int Byte = 0;
	int newByte = 0;
	char hexValue[3] = { 0 };

	inFile = fopen(FILENAME, "rb");
	outFile = fopen(NEW_FILENAME, "w");

	if (inFile == NULL || outFile == NULL) {
		printf("Error in opening file");
		return 1;
	}//eo 	if (inFile == NULL || outFile == NULL)

	else {
	
		while ((Byte = fgetc(inFile)) != EOF) {

			if ((Byte == 10) || (Byte == 13)) {
				newByte = Byte;
			}//eo if ((Byte == 10) || (Byte == 13))

			else if (Byte == 9) {
				//REPLACE WITH TT
				newByte = Byte;
			}//eo if (Byte == '9')

			else {
				newByte = Byte - 16;

				if (newByte < 32) {
					newByte = (newByte + 112);
				}//eo if (newByte < 32) {
			}//eo else

			sprintf(hexValue, "%X", newByte);
			

			if ((newByte == 10) || (newByte == 13)) {

				if (fputc(newByte, outFile) == EOF) {

					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(newByte, outFile) == EOF)
			}//eo if ((Byte == 10) || (Byte == 13))

			else if (newByte == 9) {
				if (fputc('T', outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc('T', outFile) == EOF) {

				if (fputc('T', outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc('T', outFile) == EOF) {
			}//eo else if (newByte == 9)

			else {
				if (fputc(hexValue[0], outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				if (fputc(hexValue[1], outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[1], outFile) == EOF) {
			}//eo else
		}//eo while ((Byte = fgetc(inFile)) != EOF) 

		fclose(inFile);
		fclose(outFile);

		return SUCCESS;
	}//eo else
}//eo int Encrypt(char * FILENAME, char * NEW_FILENAME)


 /*
 * FUNCTION : Decrypt
 *
 * DESCRIPTION : This function decrypts a file that has been encrypted
 *		 with the encryption function.
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int Decrypt(char *FILENAME, char *NEW_FILENAME)
{
	FILE *inFile = NULL; //Declare inFile
	FILE *outFile = NULL; //Declare outFile

	unsigned int Byte = 0;
	unsigned int newByte = 0;
	unsigned char decValue[3] = { 0 };
	unsigned char firstChar = 0;
	unsigned char secondChar = 0;
	unsigned char index = 0;
	int result = 0;

	inFile = fopen(FILENAME, "rb");
	outFile = fopen(NEW_FILENAME, "w");

	if (inFile == NULL || outFile == NULL) {
		printf("Error in opening file");
		return FAIL;
	}//eo if (inFile == NULL || outFile == NULL)

	else {

		Byte = 0;
		newByte = 0;

		while ((Byte = fgetc(inFile)) != EOF) {

			if ((Byte == 10) || (Byte == 13)) {

				if (fputc(Byte, outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(Byte, outFile) == EOF)

			}//eo if ((Byte == 10) || (Byte == 13))

			else if (index == 0) {

				decValue[0] = Byte;

				index++;
			}//eo index = 0

			else if (index > 0) {
				
				decValue[1] = Byte;
				decValue[2] = '\0';

			
				if ((decValue[0] == 'T') && (decValue[1] == 'T')) {
					result = 9;
				}//eo if ((decValue[0] == 'T') && (decValue[1] == 'T'))

				else {
					result = (convertHextoDec(decValue[0]) * 16);
					result = result + (convertHextoDec(decValue[1]));
				}//eo else


				if (result == 9) {
					newByte = result;
				}// if (result == 9)

				else if ((result == 10) || (result == 13)) {
					newByte = result;
				}//eo if ((Byte == 10) || (Byte == 13))

				else {
					newByte = result + 16;

					if (newByte > 127) {
						newByte = (newByte - 112);
					}//eo if (newByte > 127)
				}//eo else

				if (fputc(newByte, outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}

				index = 0;
			}//eo index > 0
		}//eo while ((Byte = fgetc(inFile)) != EOF)


		fclose(inFile);
		fclose(outFile);
		return SUCCESS;

	}//eo else
}//eo int Decrypt(char *FILENAME, char *NEW_FILENAME)


/*
 * FUNCTION : convertHextoDec
 *
 * DESCRIPTION : This function converts a hex value into decimal
 *					(capital letters only)
 *
 * PARAMETERS : char input: single hex character
 *
 * RETURNS : int input: single decimal value
 */
int convertHextoDec(char input) {
	if ((input >= '0') && (input <= '9')) {
		input = input - 48;
	}//eo if

	else if ((input >= 'A') && (input <= 'F')) {
		input = input - 55;
	}//eo else if

	return input;
}//eo int convertHextoDec(char input)

