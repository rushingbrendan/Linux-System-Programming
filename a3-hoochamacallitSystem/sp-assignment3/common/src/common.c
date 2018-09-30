/*!
 *  
 *	@file		:	common.c
 *
 *	project		:	PROG1970 - System Programming - Assignment #3
 *
 *	@author		:	Brendan Rushing & Conor MacPherson
 *
 *	@date		:	2018-07-12
 *
 *	@brief		:	Hoochamacallit System - Common code used for all 3 programs in Hoochamacallit System:
 *										  - Functions, Include files, Constants, Definitions
 *
 */


//Include files

#include "../inc/common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//EO Include files


/*!
 *
 *	@brief : This function creates a random number from min to max
 *
 *	@param[in] - min - <b>double</b> - The minimum return value.
 *
 *	@param[in] - max - <b>double</b> - The maximum return value.
 *
 *	@return - <b>double</b> - The sudo random number.
 *
 */
double RAND(double min, double max){
	
	srand( time(NULL) * clock() );

	return (double)rand()/(double)RAND_MAX*(max-min) + min;


}//eo double RAND(double min, double max)


/*!
 *
 *	@brief This function prints the time, date, and a string to a log file.
 *
 *	@param[in] - FILENAME - <b>FILE*</b> - The file pointer to print to.
 *
 *	@param[in] - input - <b>char*</b> - The string data to print to the file.
 *
 *	@return - <b>void</b>
 *
 */
void printLogFile(FILE *FILENAME, char* input){

	char outputBuffer[FILE_TEXT_WIDTH] = { 0 };

	time_t T= time(NULL);
    struct  tm tm = *localtime(&T);

	sprintf(outputBuffer, "\n[%04d-%02d-%02d %02d:%02d:%02d]",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcat(outputBuffer, input);


	if (fputs(outputBuffer, FILENAME) == EOF) {

		printf("\n END OF FILE ERROR ");
	}

}//eo void printLogFile(void)



/*!
 *
 *	@brief :  This function prints the time and date to the screen
 *
 *	@param[] - <b>void</b>
 *
 *	@return - <b>void</b>
 *
 */
void printTimeAndDateToScreen(void){

	time_t T= time(NULL);
    struct  tm tm = *localtime(&T);

	printf("\n[%04d-%02d-%02d ",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
    printf("%02d:%02d:%02d] : ",tm.tm_hour, tm.tm_min, tm.tm_sec);


}//eo void printTimeAndDateToScreen(void)


/*!
 *
 *	@brief This function prints the status for the Hoochamacallit machine
 *
 *	@param[in] - input - <b>int</b> - The status of the machine.
 *
 *	@return - <b>void</b>
 *
 */
void printStatus (int input){

	printf("Hoochamacallit Machine Status: #%d --- ", input);

	switch(input){

	case EVERYTHING_OKAY:
		printf("Everything Is Okay");
		break;

	case HYDRAULIC_PRESSURE_FAILURE:
		printf("Hydraulic Pressure Failure");
		break;

	case SAFETY_BUTTON_FAILURE:
		printf("Safety Button Failure");
		break;

	case NO_RAW_MATERIAL_IN_PROCESS:
		printf("No Raw Material In Process");
		break;

	case OPERATING_TEMPERATURE_OUT_OF_RANGE:
		printf("Operating Temperature Out of Range");
		break;

	case OPERATOR_ERROR:
		printf("Operator Error");
		break;

	case MACHINE_OFFLINE:
		printf("Machine Offline");
		break;
		
	default:
		printf("Unkown State");
		break;

	}//eo switch

}//eo void printStatus (int)