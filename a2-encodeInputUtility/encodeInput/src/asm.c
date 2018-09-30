/*  
*  FILE          : asm.c 
*  PROJECT       : PROG1970 - System Programming - Assignment #2
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*    The functions in this file are used to encrypt and decrypt a file.
*/

//INCLUDE FILES

#include "../inc/asm.h"
#include <stdio.h>

//EO INCLUDE FILES

//CONSTANTS

#define SUCCESS 1
#define FAIL 0
#define LINE_LENGTH_ASM 16
#define ASCII_UPGRADE 48
#define FIRST_RUN 1
#define AFTER_FIRST_RUN 2

enum { S0, S1, S5, S9};

#pragma warning(disable:4996)

//EO CONSTANTS




 /*
 * FUNCTION : toASM
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int toASM(char * FILENAME, char * NEW_FILENAME)
{
	FILE *inFile = NULL;   //Declare inFile
	FILE *outFile = NULL;  //Declare outFile
	int Byte = 0;
	int newByte = 0;
	char hexValue[3] = { 0 };
	char charCount = 0;
	char currentStage = FIRST_RUN;
	char commaStage = FIRST_RUN;

	inFile = fopen(FILENAME, "rb");
	outFile = fopen(NEW_FILENAME, "w");

	if (inFile == NULL || outFile == NULL) {
		printf("Error in opening file");
		return 1;
	}//eo 	if (inFile == NULL || outFile == NULL)

	else {
	
		while ((Byte = fgetc(inFile)) != EOF) {

			if (charCount == 0){


				if (currentStage == FIRST_RUN){

					if (fputs("dc.b\t\t", outFile) == EOF) {
						printf("\n END OF FILE ERROR ");
					}//eo if (fputc(hexValue[0], outFile) == EOF)

					currentStage = AFTER_FIRST_RUN;

				}//eo if (currentStage == FIRST_RUN){

				else{

				if (fputs("\ndc.b\t\t", outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				}//eo else

				charCount = 0;

			}//eo if (charCount >= 16){


			if (charCount == 0){

				if (fputc('$', outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)		

			}//eo if (charCount == 0){

			else{

				if (fputs(",$", outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)	

			}


				charCount++;

			sprintf(hexValue, "%X", Byte);
			
			if (hexValue[1] == '\0'){
				
				hexValue[1] = hexValue[0];
				hexValue[0] = '0';

			}

			
				if (fputc(hexValue[0], outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				if (fputc(hexValue[1], outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[1], outFile) == EOF) {




				
				if (charCount >= 16){

					charCount = 0;
				}

		}//eo while ((Byte = fgetc(inFile)) != EOF) 

		fclose(inFile);
		fclose(outFile);

		return SUCCESS;
	}//eo else
}//eo int Encrypt(char * FILENAME, char * NEW_FILENAME)






 /*
 * FUNCTION : toASMwithSTDin
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS :	
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int toASMwithSTDin(char * NEW_FILENAME)
{
	FILE *outFile = NULL;  //Declare outFile
	int Byte = 0;
	int newByte = 0;
	char hexValue[3] = { 0 };
	char charCount = 0;
	char currentStage = FIRST_RUN;

	outFile = fopen(NEW_FILENAME, "w");

	if (outFile == NULL) {
		printf("Error in opening file");
		return 1;
	}//eo 	if ( outFile == NULL)

	else {
	
		while ((Byte = fgetc(stdin)) != EOF) {

			if (charCount == 0){


				if (currentStage == FIRST_RUN){

					if (fputs("dc.b\t\t", outFile) == EOF) {
						printf("\n END OF FILE ERROR ");
					}//eo if (fputc(hexValue[0], outFile) == EOF)

					currentStage = AFTER_FIRST_RUN;

				}//eo if (currentStage == FIRST_RUN){

				else{

				if (fputs("\ndc.b\t\t", outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				}//eo else

				charCount = 0;

			}//eo if (charCount >= 16){

			if (charCount == 0){

				if (fputc('$', outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)		

			}//eo if (charCount == 0){

			else{

				if (fputs(",$", outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)	

			}


				charCount++;

			sprintf(hexValue, "%X", Byte);
			
			if (hexValue[1] == '\0'){
				
				hexValue[1] = hexValue[0];
				hexValue[0] = '0';

			}//eo if (hexValue[1] == '\0'){
			
				if (fputc(hexValue[0], outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				if (fputc(hexValue[1], outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[1], outFile) == EOF) {

				if (charCount >= 16){

					charCount = 0;
				}

		}//eo while ((Byte = fgetc(inFile)) != EOF) 

		fclose(outFile);

		return SUCCESS;
	}//eo else
}//eo int toASMwithSTDin(char * NEW_FILENAME)




 /*
 * FUNCTION : toASMwithSTDin
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS :	
 *		none
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int toASMwithSTDinAndOut()
{

	int Byte = 0;
	int newByte = 0;
	char hexValue[3] = { 0 };
	char charCount = 0;
	char currentStage = FIRST_RUN;


	
		while ((Byte = fgetc(stdin)) != EOF) {

			if (charCount == 0){


				if (currentStage == FIRST_RUN){

					if (fputs("dc.b\t\t", stdout) == EOF) {
						printf("\n END OF FILE ERROR ");
					}//eo if (fputc(hexValue[0], outFile) == EOF)

					currentStage = AFTER_FIRST_RUN;

				}//eo if (currentStage == FIRST_RUN){

				else{

				if (fputs("\ndc.b\t\t", stdout) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				}//eo else

				charCount = 0;

			}//eo if (charCount >= 16){

			if (charCount == 0){

				if (fputc('$', stdout) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)		

			}//eo if (charCount == 0){

			else{

				if (fputs(",$", stdout) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)	

			}


				charCount++;

			sprintf(hexValue, "%X", Byte);
			
			if (hexValue[1] == '\0'){
				
				hexValue[1] = hexValue[0];
				hexValue[0] = '0';

			}//eo if (hexValue[1] == '\0'){
			
				if (fputc(hexValue[0], stdout) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				if (fputc(hexValue[1], stdout) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[1], outFile) == EOF) {

				if (charCount >= 16){

					charCount = 0;
				}

		}//eo while ((Byte = fgetc(inFile)) != EOF) 


		return SUCCESS;

}//eo int toASMwithSTDin(char * NEW_FILENAME)




