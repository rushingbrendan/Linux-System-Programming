/*  
*  FILE          : source.c 
*  PROJECT       : PROG1970 - System Programming - Assignment #2
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*	This assignment encodes files and stdin to stdout and srec / ASM files
*/

//INCLUDE FILES

#include <stdio.h>
#include "../inc/asm.h"
#include "../inc/srec.h"
#include <string.h>
//EO INCLUDE FILES

//CONSTANTS

#define FILE_NAME_LENGTH 200
#define SUCCESS 1
#define FAIL 0


enum { NO_INPUT_FILE, VALID_INPUT_FILE, NO_OUTPUT_FILE, VALID_OUTPUT_FILE };

enum { NONE, ASM, SREC, HELP };


#pragma warning(disable:4996)

//EO CONSTANTS






int main(int argc, char *argv[]) {


	char inputFile[FILE_NAME_LENGTH];
	char outputFile[FILE_NAME_LENGTH];
	char inputFileValid = NO_INPUT_FILE;
	int i = 1;

	char* cPtr = NULL;

	int choice = NONE;

	char isInputFile = NO_INPUT_FILE;
	char isOutputFile = NO_OUTPUT_FILE;


	while(i != (argc)){

	char* cPtr2 = NULL;

		if ((strcmp(argv[i], "-srec") == 0)){

			choice = SREC;

		}//eo if

		if ((strcmp(argv[i], "-h") == 0)){

			choice = HELP;

		}//eo if

		cPtr2 = strchr(argv[i], '-');

		if (cPtr2 != NULL){

			cPtr2++;

			if (*cPtr2 == 'i'){

				cPtr2++;
				sprintf(inputFile, "%s", cPtr2);

				isInputFile = VALID_INPUT_FILE;

			}//eo if (*cPtr2 == 'i'){

			else if(*cPtr2 == 'o'){

				cPtr2++;
				sprintf(outputFile, "%s", cPtr2);

				isOutputFile = VALID_OUTPUT_FILE;

			}//eo else if(*cPtr2 == 'o'){


		}//eo if (cPtr2 != NULL){

		i++;

	}//eo for 




	if (choice != SREC && choice != HELP){
	
		choice = ASM;

	}//eo	if (choice != SREC && choice != HELP){


	else if ((argc > 0) && (choice != SREC) && (choice != HELP) ){

		choice = HELP;

	}//eo 	else if ((argc > 1) && (choice != SREC) && (choice != HELP)){

	else if ((choice == SREC) && (isOutputFile == NO_OUTPUT_FILE)){

		strcpy(outputFile, inputFile);
		strcat(outputFile, ".srec");

	}//eo 	else if ((choice == SREC) && (isOutputFile == NO_OUTPUT_FILE)){





	switch (choice)
	{

	case HELP:

		printf("\n HELP - (usage instructions) for encodeInput Program");
		printf("\n There are 4 available switch statements. They can be entered in any order.");
		printf("\n 1)	-h\thelp information is shown on screen.");
		printf("\n 2)	-srec\t	software will output data into S-Record format");
		printf("\n 3)	-iINPUTFILENAME		text after -i is used for input filename");
		printf("\n 4)	-iOUTPUTFILENAME	text after -o is used for output filename");

		break;


	case ASM:

		if (isInputFile == VALID_INPUT_FILE){


			if (toASM(inputFile, outputFile) == SUCCESS){



			}//eo if (Decrypt(decFile, newdecFile) == SUCCESS){

			else{

				printf("\n ERROR during ASM conversion.\n");

			}	//eo else


		}//eo if (isInputFile == VALID_INPUT_FILE){

		else if(isInputFile == NO_INPUT_FILE && isOutputFile ==VALID_OUTPUT_FILE){

			if (toASMwithSTDin(outputFile) == SUCCESS){


			}//eo if (Decrypt(decFile, newdecFile) == SUCCESS){

			else{

				printf("\n ERROR during ASM conversion.\n");

			}	//eo else

		}//eo else if(isInputFile == NO_INPUT_FILE){

		else if(isOutputFile == NO_OUTPUT_FILE && isInputFile == NO_INPUT_FILE){

			if (toASMwithSTDinAndOut() == SUCCESS){


			}//eo if (Decrypt(decFile, newdecFile) == SUCCESS){

			else{

				printf("\n ERROR during ASM conversion.\n");

			}	//eo else

		}//eo else if(isInputFile == NO_INPUT_FILE){

		

		break;

	case SREC:

		if ((isInputFile == NO_INPUT_FILE) && (isOutputFile == VALID_OUTPUT_FILE)){

			if (toSREC_stdin(outputFile) == SUCCESS){


			}//eo if (Decrypt(decFile, newdecFile) == SUCCESS){

			else{

				printf("\n ERROR during SREC conversion.\n");

			}	//eo else


		}//eo if ((isInputFile = NO_INPUT_FILE) && (isOutputFile == VALID_OUTPUT_FILE)){

		else {
			if (toSREC(inputFile, outputFile) == SUCCESS){


			}//eo if (Decrypt(decFile, newdecFile) == SUCCESS){

			else{

				printf("\n ERROR during SREC conversion.\n");

			}	//eo else

		}//eo else
		break;




	}
	return SUCCESS;

}// eo int main(int argc, char *argv[])
