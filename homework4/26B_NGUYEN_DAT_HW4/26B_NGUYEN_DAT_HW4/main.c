
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_LIGHTS   16
typedef enum { TURN_ON, TURN_OFF }toggle;

#define CENTER_STAGE	2016   // Binary : 00000 111111 00000
#define LEFT_STAGE		63488  // Binary : 11111 000000 00000
#define RIGHT_STAGE		31     // Binary : 00000 000000 11111
#define FLUSH			while(getchar() != '\n')


int main(int args, char argv[])
{
	// ------FUNCTION PROTOTYPES--------
	void menu_driver(unsigned short);
	int  update(unsigned short*, int choice);
	void set(unsigned short*, int startbit, int endbit, int);
	void overlay(unsigned short*, unsigned short);
	void printbits(unsigned short);

	//------ MAIN PROGRAM --------------
	unsigned short current_lighting = 0; //set all lights to OFF
	menu_driver(current_lighting);
	return 0;
}

void menu_driver(unsigned short lights) {
	char input[3];
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
		printf("Please select an option: ");
		fgets(input, 3, stdin);
		if ((isdigit(input[0]) && strlen(input) == 2)) 
		{
			choice = strtol(input, NULL, 0); // Convert ANSCII to number
			printf("OPTION: %d\n\n", choice);
			if (choice == 10) break;
			if (1 <= choice && choice < 10)
				update(&lights, choice);
			else
				printf("\n**Option %d is  an invalid choice, please try again**\n", choice);
		}
		else {
			printf("\n**Invalid Input, please try again.**\n");
			FLUSH; // @BUG!!!!
		}
	} while (choice != 10);
}
int update(unsigned short* lights, int choice) {
	int okay = 0;
	switch (choice)
	{
	case 1: // Turn all all lights
		set(lights, 0, 16, TURN_ON);
		break;
	case 2: // Turn on center stage
		set(lights, 5, 6, TURN_ON);
		break;
	case 3: // Turn on left stage
		set(lights, 11, 5, TURN_ON);
		break;
	case 4: // Turn on right stage
		set(lights, 0, 5, TURN_ON);
		break;
	case 5: // Turn off all lights
		set(lights, 0, 16, TURN_OFF);
		break;
	case 6:
		set(lights, 5, 6, TURN_OFF);
		break;
	case 7:
		set(lights, 11, 5, TURN_OFF);
		break;
	case 8:
		set(lights, 0, 5, TURN_OFF);
		break;
	case 9:
		printf("Current lighting configuration: \n");
		printf("Update a custom configuration (pattern - location to start): ");
		char input[16];
		fgets(input, 16, stdin); // ERROR CHECK HERE
		unsigned short pattern = strtol(input, NULL, 0);
		overlay(lights, pattern);
		break;
	default:
		break;
	}

	//if okay:
	//print_bit(lights);
	return okay;
}
void set(unsigned short* lights, int startbit, int numbits, int state)
{
	unsigned short mask = (unsigned short)~0;
	mask <<= numbits;
	mask = ~mask;
	mask <<= startbit;
	if (state == TURN_ON)
		*lights |= mask;
	else{					//TURN _OFF
		mask = ~mask;
		*lights &= mask;
	}
	printf("Turn %s %d lights starting at light %d.\n",(state==TURN_ON)?"ON":"OFF", numbits, startbit);
	printf("Current light configuration (1-ON / 0-OFF): \n");
	printbits(*lights);
}
void overlay(unsigned short* lights, unsigned short pattern) {

}

/**************************************************************
Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short wrd, int bit_to_test)
{
	wrd >>= bit_to_test;
	wrd &= 1;
	return wrd;
}

/**************************************************************
This uses a trick to print an unsigned short as a string of
16 bits
*/
void printbits(unsigned short wrd)
{
	for (int i = 15; i >= 0; i--)
		printf("%1d", testbit(wrd, i));
	printf("\n\n");
	return;
}