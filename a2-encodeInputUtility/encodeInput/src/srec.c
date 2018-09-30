/*  
*  FILE          : srec.c 
*  PROJECT       : PROG1970 - System Programming - Assignment #2
*  PROGRAMMER    : Brendan Rushing
*  FIRST VERSION : 2018-05-20 
*  DESCRIPTION   : 
*	This assignment encodes files and stdin to stdout and srec / ASM files
*/

//INCLUDE FILES

#include <stdio.h>
#include "../inc/srec.h"

//EO INCLUDE FILES

//CONSTANTS

#define SUCCESS 1
#define FAIL 0
#define LINE_LENGTH_ASM 16
#define ASCII_UPGRADE 48
#define FIRST_RUN 1
#define AFTER_FIRST_RUN 2
#define MAX_NUMBER_OF_CHAR 16
#define COUNT_AND_ADDRESS_FIELD 3
#define AAAA_Address_COUNT 4


#pragma warning(disable:4996)

//EO CONSTANTS

//PROTOTYPES

int printSREChexAddress(FILE *outFile, int inputSREC);
int printScount(FILE *outFile, int inputSREC);
int printCMDcount(FILE *outFile, int inputSREC);


//EO PROTOTYPES






 /*
 * FUNCTION : printSCount
 *
 * DESCRIPTION : This function prints the # of hexadecimal characters in line (CC from example)
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int printScount(FILE *outFile, int inputSREC){

	char srecOutput[2] = {0};


	sprintf(srecOutput, "%d", inputSREC);


	if (inputSREC <= 9){

		if (fputc('0', outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)					

		if (fputc(srecOutput[0], outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)	

	}//eo else if (charCount >= 10){
	
	else {

		if (fputc(srecOutput[0], outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)	

		if (fputc(srecOutput[1], outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)				

					

	}//eo else


}//eo int printScount(FILE *outFile, int inputSREC){







 /*
 * FUNCTION : int printCMDcount(FILE *outFile, int inputSREC){
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int printCMDcount(FILE *outFile, int inputSREC){

	char srecOutput[AAAA_Address_COUNT] = {0};

	sprintf(srecOutput, "%d", inputSREC);


	if (inputSREC < 10){
				
		if (fputc('0', outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)					
					
		if (fputc('0', outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	
				
					
		if (fputc('0', outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	

		if (fputc(srecOutput[0], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	


	}//eo else if (charCount >= 10){
	
	else if (inputSREC < 100){

				
		if (fputc('0', outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)					
					
		if (fputc('0', outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	
				
		if (fputc(srecOutput[0], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)		

		if (fputc(srecOutput[1], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)						

	}//eo if (charCount >= 100){

	else if(inputSREC < 1000){

		if (fputc('0', outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)

		if (fputc(srecOutput[0], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)							
				
		if (fputc(srecOutput[1], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)		

		if (fputc(srecOutput[2], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)							
	}//eo else


	else if(inputSREC < 10000){

		if (fputc(srecOutput[0], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	

		if (fputc(srecOutput[1], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)					
					
		if (fputc(srecOutput[2], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	
				
		if (fputc(srecOutput[3], outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)	
	}//eo if else



}//eo int printCMDcount(FILE *outFile, int inputSREC){





 /*
 * FUNCTION : printSRECcount
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int printSREChexAddress(FILE *outFile, int inputSREC){


	char srecOutput[AAAA_Address_COUNT] = {0};

	sprintf(srecOutput, "%04X", inputSREC);

	fputs(srecOutput, outFile);


}//eo int printSREChexAddress(char * FILENAME, int inputSREC)




 /*
 * FUNCTION : toSREC
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS : char * FILENAME:	Input File
 *		char * NEW_FILENAME	Output File
 *
 * RETURNS : int : SUCCESS or FAIL
 */
int toSREC(char * FILENAME, char * NEW_FILENAME)
{
	FILE *inFile = NULL;   //Declare inFile
	FILE *outFile = NULL;  //Declare outFile
	unsigned int Byte = 0;
	char hexValue[COUNT_AND_ADDRESS_FIELD] = { 0 };
	int srecArray[MAX_NUMBER_OF_CHAR] = {0};
	char headerName[] = "Brendan";
	int charCount = 0;
	int srecCount = 0;
	char* ptr = NULL;
	unsigned char checkSUM = 0;

	inFile = fopen(FILENAME, "rb");
	outFile = fopen(NEW_FILENAME, "wb");

	if (inFile == NULL || outFile == NULL) {
		printf("Error in opening file");
		return 1;
	}//eo 	if (inFile == NULL || outFile == NULL)

	
	//S0 HEADER RECORD
		fputs("S0", outFile);

		ptr = headerName;
		while (*ptr!= '\0'){
			checkSUM = checkSUM + *ptr;
			charCount++;
			ptr++;
		}//eo while (*ptr!= '\0'){

		charCount = charCount+COUNT_AND_ADDRESS_FIELD;	//+1 for checksum count, +2 for address

		checkSUM = checkSUM + charCount;
		checkSUM=~checkSUM & 0xff;

		sprintf(hexValue, "%02d", charCount);

		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)



		if (fputs("0000", outFile) == EOF){
			printf("\n END OF FILE ERROR ");
		}//eo if (fputs("0000", outFile) == EOF){


		ptr = &headerName[0];
		while (*ptr!= '\0'){
			sprintf(hexValue, "%02X", *ptr);

			if (fputs(hexValue, outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)

			ptr++;
		}//eo while (*ptr!= '\0'){


		sprintf(hexValue, "%02X", checkSUM);


		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)



	//EO S0 HEADER RECORD

	charCount = 0;



	while ((Byte = fgetc(inFile)) != EOF) {


		srecArray[charCount] = Byte;
		charCount++;

		if (charCount == MAX_NUMBER_OF_CHAR){

			checkSUM = 0;

			if (fputs("\nS1", outFile) == EOF){
				printf("\n END OF FILE ERROR ");
			}//eo if (fputs("0000", outFile) == EOF){

			printScount(outFile, (charCount-COUNT_AND_ADDRESS_FIELD));
			charCount = 0;

		printSREChexAddress(outFile, srecCount);



			while (charCount != MAX_NUMBER_OF_CHAR){

				checkSUM = checkSUM + srecArray[charCount];
				sprintf(hexValue, "%02X", srecArray[charCount]);
	

				if (fputs(hexValue, outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				charCount++;

			}//eo while
			checkSUM = checkSUM + COUNT_AND_ADDRESS_FIELD + srecCount + MAX_NUMBER_OF_CHAR;	

			

		checkSUM=~checkSUM & 0xFF;

			charCount = 0;

		sprintf(hexValue, "%02X", checkSUM);
		
		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)

			srecCount = srecCount + MAX_NUMBER_OF_CHAR;

			
		}//eo 	while (charCount == 16){

	}//eo while ((Byte = fgetc(inFile)) != EOF) 




	if (charCount > 0){
		int currentCount = 0;
		checkSUM =0;
		if (fputs("\nS1", outFile) == EOF){
			printf("\n END OF FILE ERROR ");
		}//eo if (fputs("S1", outFile) == EOF){

		//printScount(outFile, (charCount));

		
		sprintf(hexValue, "%02X", (charCount+COUNT_AND_ADDRESS_FIELD));
	
		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)


		printSREChexAddress(outFile, srecCount);


		while (currentCount != charCount){

			checkSUM = checkSUM + srecArray[currentCount];
			sprintf(hexValue, "%02X", srecArray[currentCount]);
		
			if (fputs(hexValue, outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)

	
				currentCount++;
		}//eo while while (currentCount != charCount){


		checkSUM = checkSUM + (charCount+COUNT_AND_ADDRESS_FIELD) + srecCount;	//+1 for checksum count, +2 for address
		checkSUM=~checkSUM & 0xFF;

		sprintf(hexValue, "%02X", checkSUM);
		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)

	}//eo if (charCount > 0){

			srecCount = srecCount + MAX_NUMBER_OF_CHAR;

	if (fputs("\nS503", outFile) == EOF){
		printf("\n END OF FILE ERROR ");
	}//eo if (fputs("S1", outFile) == EOF){
	
	printCMDcount(outFile, (srecCount/MAX_NUMBER_OF_CHAR));

	checkSUM = COUNT_AND_ADDRESS_FIELD;
	checkSUM = checkSUM + (srecCount/MAX_NUMBER_OF_CHAR);
	checkSUM=~checkSUM & 0xFF;

	sprintf(hexValue, "%02X", checkSUM);

	if (fputs(hexValue, outFile) == EOF) {
		printf("\n END OF FILE ERROR ");
	}//eo if (fputc(hexValue[0], outFile) == EOF)




	//STARTING ADDRESS
	if (fputs("\nS9030000", outFile) == EOF){
		printf("\n END OF FILE ERROR ");
	}//eo if (fputs("S1", outFile) == EOF){
	
	checkSUM = 0;
	checkSUM = COUNT_AND_ADDRESS_FIELD;
	checkSUM=~checkSUM & 0xFF;


	sprintf(hexValue, "%02X", checkSUM);
	if (fputs(hexValue, outFile) == EOF) {
		printf("\n END OF FILE ERROR ");
	}//eo if (fputc(hexValue[0], outFile) == EOF)



		fclose(inFile);
		fclose(outFile);

		return SUCCESS;
}//eo int toSREC(char * FILENAME, char * NEW_FILENAME)











 /*
 * FUNCTION : toSREC
 *
 * DESCRIPTION : This function converts an input file to asm format
 *
 * PARAMETERS : char * FILENAME:	Input File

 *
 * RETURNS : int : SUCCESS or FAIL
 */
int toSREC_stdin(char * FILENAME)
{

	FILE *outFile = NULL;  //Declare outFile
	unsigned int Byte = 0;
	char hexValue[COUNT_AND_ADDRESS_FIELD] = { 0 };
	int srecArray[MAX_NUMBER_OF_CHAR] = {0};
	char headerName[] = "Brendan";
	int charCount = 0;
	int srecCount = 0;
	char* ptr = NULL;
	unsigned char checkSUM = 0;

	outFile = fopen(FILENAME, "wb");

	if (outFile == NULL) {
		printf("Error in opening file");
		return 1;
	}//eo 	if (inFile == NULL || outFile == NULL)

	
	//S0 HEADER RECORD
		fputs("S0", outFile);

		ptr = headerName;
		while (*ptr!= '\0'){
			checkSUM = checkSUM + *ptr;
			charCount++;
			ptr++;
		}//eo while (*ptr!= '\0'){

		charCount = charCount+COUNT_AND_ADDRESS_FIELD;	//+1 for checksum count, +2 for address

		checkSUM = checkSUM + charCount;
		checkSUM=~checkSUM & 0xff;

		sprintf(hexValue, "%02d", charCount);

		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)



		if (fputs("0000", outFile) == EOF){
			printf("\n END OF FILE ERROR ");
		}//eo if (fputs("0000", outFile) == EOF){


		ptr = &headerName[0];
		while (*ptr!= '\0'){
			sprintf(hexValue, "%02X", *ptr);

			if (fputs(hexValue, outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)

			ptr++;
		}//eo while (*ptr!= '\0'){


		sprintf(hexValue, "%02X", checkSUM);


		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)



	//EO S0 HEADER RECORD

	charCount = 0;



	while ((Byte = fgetc(stdin)) != EOF) {


		srecArray[charCount] = Byte;
		charCount++;

		if (charCount == MAX_NUMBER_OF_CHAR){

			checkSUM = 0;

			if (fputs("\nS1", outFile) == EOF){
				printf("\n END OF FILE ERROR ");
			}//eo if (fputs("0000", outFile) == EOF){

			printScount(outFile, (charCount-COUNT_AND_ADDRESS_FIELD));
			charCount = 0;

		printSREChexAddress(outFile, srecCount);



			while (charCount != MAX_NUMBER_OF_CHAR){

				checkSUM = checkSUM + srecArray[charCount];
				sprintf(hexValue, "%02X", srecArray[charCount]);
	

				if (fputs(hexValue, outFile) == EOF) {
					printf("\n END OF FILE ERROR ");
				}//eo if (fputc(hexValue[0], outFile) == EOF)

				charCount++;

			}//eo while
			checkSUM = checkSUM + COUNT_AND_ADDRESS_FIELD + srecCount + MAX_NUMBER_OF_CHAR;	

			

		checkSUM=~checkSUM & 0xFF;

			charCount = 0;

		sprintf(hexValue, "%02X", checkSUM);
		
		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)

			srecCount = srecCount + MAX_NUMBER_OF_CHAR;

			
		}//eo 	while (charCount == 16){

	}//eo while ((Byte = fgetc(inFile)) != EOF) 




	if (charCount > 0){
		int currentCount = 0;
		checkSUM =0;
		if (fputs("\nS1", outFile) == EOF){
			printf("\n END OF FILE ERROR ");
		}//eo if (fputs("S1", outFile) == EOF){

		//printScount(outFile, (charCount));

		
		sprintf(hexValue, "%02X", (charCount+COUNT_AND_ADDRESS_FIELD));
	
		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)


		printSREChexAddress(outFile, srecCount);


		while (currentCount != charCount){

			checkSUM = checkSUM + srecArray[currentCount];
			sprintf(hexValue, "%02X", srecArray[currentCount]);
		
			if (fputs(hexValue, outFile) == EOF) {
				printf("\n END OF FILE ERROR ");
			}//eo if (fputc(hexValue[0], outFile) == EOF)

	
				currentCount++;
		}//eo while while (currentCount != charCount){


		checkSUM = checkSUM + (charCount+COUNT_AND_ADDRESS_FIELD) + srecCount;	//+1 for checksum count, +2 for address
		checkSUM=~checkSUM & 0xFF;

		sprintf(hexValue, "%02X", checkSUM);
		if (fputs(hexValue, outFile) == EOF) {
			printf("\n END OF FILE ERROR ");
		}//eo if (fputc(hexValue[0], outFile) == EOF)

	}//eo if (charCount > 0){

			srecCount = srecCount + MAX_NUMBER_OF_CHAR;

	if (fputs("\nS503", outFile) == EOF){
		printf("\n END OF FILE ERROR ");
	}//eo if (fputs("S1", outFile) == EOF){
	
	printCMDcount(outFile, (srecCount/MAX_NUMBER_OF_CHAR));

	checkSUM = COUNT_AND_ADDRESS_FIELD;
	checkSUM = checkSUM + (srecCount/MAX_NUMBER_OF_CHAR);
	checkSUM=~checkSUM & 0xFF;

	sprintf(hexValue, "%02X", checkSUM);

	if (fputs(hexValue, outFile) == EOF) {
		printf("\n END OF FILE ERROR ");
	}//eo if (fputc(hexValue[0], outFile) == EOF)




	//STARTING ADDRESS
	if (fputs("\nS9030000", outFile) == EOF){
		printf("\n END OF FILE ERROR ");
	}//eo if (fputs("S1", outFile) == EOF){
	
	checkSUM = 0;
	checkSUM = COUNT_AND_ADDRESS_FIELD;
	checkSUM=~checkSUM & 0xFF;


	sprintf(hexValue, "%02X", checkSUM);
	if (fputs(hexValue, outFile) == EOF) {
		printf("\n END OF FILE ERROR ");
	}//eo if (fputc(hexValue[0], outFile) == EOF)

		fclose(outFile);

		return SUCCESS;
}//eo int Encrypt(char * FILENAME, char * NEW_FILENAME)




