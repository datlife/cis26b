/***************************************************************************
** CIS 26B                                                     Winter, 2017
** Advanced C
******************
** Homework 4:
**        Bit Manipulation
**
***************************************************************************
**  Description: 
**        This program is to control a lighting system with 16 lights. 
***************************************************************************
**  Written By:     Dat Nguyen
**  Date:      6:08 PM 3/5/2017
***************************************************************************/
# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_LIGHTS   16
#define NUMERIC      "0123456789"
#define INPUT_BUFFER 20
#define TURN_ON_BITS(startbit,  numbits)		(unsigned short)((~(((unsigned short)~0) << (numbits))) << (startbit))		// turn on a range of bits
#define TURN_OFF_BITS(startbit,numbits)			(unsigned short)(~((~(((unsigned short) ~0) << (numbits))) << (startbit)))  //turn off a range of bits
#define TOGGLE_BITS(bits, startbit, numbits)    (unsigned short)( (bits)^TURN_ON_BITS((startbit), (numbits)) )					// toggle a range of bit
#define FLUSH									while(getchar() != '\n')

int main(int args, char argv[])
{
	//==========================FUNCTION PROTOTYPES========================//
	void menu_driver(unsigned short);
	void update(unsigned short*, int choice);
	void overlay(unsigned short*);
	void printbits(unsigned short);
	int validate_input(char *, int* startbit, int* numbit, unsigned short* pattern);
	int is_digit(const char*);
	extern int isspace(char);   // avoid warning C4013 on VS 2013, ": undefined; assuming extern returning int"
	extern int isdigit(char);

	//========================== MAIN  =============================//
	unsigned short current_lighting = 0; //set all lights to OFF
	menu_driver(current_lighting);
	return 0;
}
/********************************************
Display menu  for user to select
*/
void menu_driver(unsigned short lights) {
	char input[INPUT_BUFFER];
	int choice = -1;
	do {
		printf("==================== LIGHTING SYSTEM ===================\n");
		printf(" 1) Turn on all lights.\n");
		printf(" 2) Turn on center-stage lights ( 5 - 10)\n");
		printf(" 3) Turn on left-stage lights (11 - 15).\n");
		printf(" 4) Turn on right-stage lights (0 - 4).\n");
		printf(" 5) Turn off all lights.\n");
		printf(" 6) Turn off center-stage lights.\n");
		printf(" 7) Turn off left-stage lights.\n");
		printf(" 8) Turn off right-stage lights.\n");
		printf(" 9) Overlay ON/OFF pattern onto light configuration.\n");
		printf(" 10) Quit.\n");
		printf("=========================================================\n");
		printf("Enter menu choice: ");
		fgets(input, INPUT_BUFFER, stdin);
		strtok(input, "\n");
		if (is_digit(input) == 0) {
			choice = (int)strtol(input, NULL, 0); // Convert to number
			if (choice == 10) break;
			if (1 <= choice && choice < 10)
				update(&lights, choice);
			else {
				printf("Illegal menu selection! Try again!\n");
			}
		}
		else {
			printf("Illegal menu selection! Try again!\n");
		}
	} while (choice != 10);
}
/***********************************************************
Update lighting system
*/
void update(unsigned short* lights, int choice) {
	switch (choice)
	{
	case 1: // Turn all all lights
		*lights = TURN_ON_BITS(0, 16);
		break;
	case 2: // Turn on center stage
		*lights |= TURN_ON_BITS(5, 6);
		break;
	case 3: // Turn on left stage
		*lights |= TURN_ON_BITS(11, 5);
		break;
	case 4: // Turn on right stage
		*lights |= TURN_ON_BITS(0, 5);
		break;
	case 5: // Turn off all lights
		*lights &= TURN_OFF_BITS(0, 16);
		break;
	case 6:	 // Turn off center stage
		*lights &= TURN_OFF_BITS(5, 6);
		break;
	case 7: // Turn off left stage
		*lights &= TURN_OFF_BITS(11, 5);
		break;
	case 8: // Turn off right stage
		*lights &= TURN_OFF_BITS(0, 5);
		break;
	case 9:
		overlay(lights);
		break;
	default:
		break;
	}
	printf("Light settings: ");
	printbits(*lights);
}
/**********************************************************8**
Overlay a bit pattern
*/
void overlay(unsigned short* lights) {
	int okay = -1;
	do {
		printf("Enter starting light number and on/off pattern: ");
		char input[16];		 // why?
		fgets(input, 16, stdin); // ERROR CHECK HERE
		int starting_light;
		int numbits;
		unsigned short pattern;
		okay = validate_input(input, &starting_light, &numbits, &pattern);
		if (okay == 0) {
			//Over lay
			*lights &= ~(~((unsigned short)~0 << numbits) << starting_light);
			pattern <<= starting_light;
			*lights |= pattern;
		}
	} while (okay != 0);
}
/**************************************************************
Return 0 if input is valid,
Otherwise: print error message and return -1
*/
int validate_input(char *input, int *start_bit, int *numbit, unsigned short * pattern) {
	// trimg leading spaces
	while (isspace((unsigned char)*input)) input++;
	if (*input == 0) {// is input has only spaces
		printf("\nYou did not enter anything! Try again!\n");
		return -1;
	}
	char *sbit = strtok(input, " ");
	char *ptrn = strtok(NULL, " ");
	if (strtok(NULL, " ") > 0) {
		printf("Too many entries on line! Try again!\n");
		return -1;
	}
	if (!sbit || !ptrn) {
		if (!sbit)
			printf("You did not enter starting light! Try again!\n");
		if (!ptrn)
			printf("You did not enter light pattern! Try again!\n");
		return -1;
	}
	sbit[strspn(sbit, NUMERIC)] = 0;  // only get numeric values in a string
	ptrn[strspn(ptrn, NUMERIC)] = 0;
	if (*sbit == 0 || *ptrn == 0) {
		printf("Please only enter numeric value (e.g 2 1101)! Try again!\n");
		FLUSH;
		return -1;
	}
	//Convert to number
	*numbit = strlen(ptrn);
	*start_bit = strtol(sbit, NULL, 0);
	*pattern = strtol(ptrn, NULL, 2);

	if ((*start_bit + 1) > NUM_LIGHTS) {
		printf("Invalid starting light number! Try again (max is %d)\n", NUM_LIGHTS - 1);
		return -1;
	}
	if ((NUM_LIGHTS - *start_bit) < *numbit) {
		printf("Invalid light pattern. Number of lights should be less than %d (MAX LIGHTS - starting light)! Try again.\n", NUM_LIGHTS - *start_bit);
		return -1;
	}
	if (*pattern == 0) {
		printf("Illegal on/off pattern! Try again!\n");
		return -1;
	}
	return 0;
}
/**************************************************************
Return 0 is string is digit, else return 1
*/
int is_digit(const char* input) {
	int error = 0;
	for (int i = 0; i < (int)strlen(input); i++) {
		if (!isdigit(input[i])) {
			error = 1;
			break;
		}
	}
	return error;
}
/**************************************************************
Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short wrd, int bit_to_test) {
	wrd >>= bit_to_test;
	wrd &= 1;
	return wrd;
}
/**************************************************************
This uses a trick to print an unsigned short as a string of
16 bits
*/
void printbits(unsigned short wrd) {
	for (int i = 15; i >= 0; i--)
		printf("%1d", testbit(wrd, i));
	printf("\n\n");
	return;
}

/*
SAMPLE OUTPUT


==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: aw51
Illegal menu selection! Try again!
==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: 2
Light settings: 0000011111100000

==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: 4
Light settings: 0000011111111111

==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: 8
Light settings: 0000011111100000

==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: 9
Enter starting light number and on/off pattern:  125as 15151
Invalid starting light number! Try again (max is 15)
Enter starting light number and on/off pattern: 10 1100
Light settings: 0011001111100000

==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: 9
Enter starting light number and on/off pattern: 6 9
Illegal on/off pattern! Try again!
Enter starting light number and on/off pattern: 6
You did not enter light pattern! Try again!
Enter starting light number and on/off pattern: 6 10 foo
Too many entries on line! Try again!
Enter starting light number and on/off pattern: 6 101010
Light settings: 0011101010100000

==================== LIGHTING SYSTEM ===================
1) Turn on all lights.
2) Turn on center-stage lights ( 5 - 10)
3) Turn on left-stage lights (11 - 15).
4) Turn on right-stage lights (0 - 4).
5) Turn off all lights.
6) Turn off center-stage lights.
7) Turn off left-stage lights.
8) Turn off right-stage lights.
9) Overlay ON/OFF pattern onto light configuration.
10) Quit.
=========================================================
Enter menu choice: 10
Press any key to continue . . .

*/
