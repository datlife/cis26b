
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_LIGHTS   16
#define TURN_ON_BITS(startbit,  numbits)		(unsigned short)((~(((unsigned short)~0) << (numbits))) << (startbit))		// turn on a range of bits
#define TURN_OFF_BITS(startbit,numbits)			(unsigned short)(~((~(((unsigned short) ~0) << (numbits))) << (startbit)))  //turn off a range of bits
#define TOGGLE_BITS(bits, startbit, numbits)    (unsigned short)( (bits)^TURN_ON_BITS((startbit), (numbits)) )					// toggle a range of bit
#define FLUSH									while(getchar() != '\n')

int main(int args, char argv[])
{
	// ------FUNCTION PROTOTYPES--------
	void menu_driver(unsigned short);
	int  update(unsigned short*, int choice);
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
		if ((isdigit(input[0]) && strlen(input) == 2)) {
			choice = strtol(input, NULL, 0); // Convert to number
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
	case 6:
		*lights &= TURN_OFF_BITS(5, 6);
		break;
	case 7:
		*lights &= TURN_OFF_BITS(11, 5);
		break;
	case 8:
		*lights &= TURN_OFF_BITS(0, 5);
		//*lights = TOGGLE_BITS(*lights, 0, 16);
		break;
	case 9:
		printf("Update a custom configuration (pattern - location to start): ");
		char input[16];
		fgets(input, 16, stdin); // ERROR CHECK HERE
		unsigned short pattern = (unsigned short)strtol(input, NULL, 0);
		overlay(lights, pattern);
		break;
	default:
		break;
	}
	printf("Current light configuration (1-ON / 0-OFF): \n");
	printbits(*lights);
	return okay;
}

void overlay(unsigned short* lights, unsigned short pattern) {

}

/**************************************************************
Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short wrd, int bit_to_test){
	wrd >>= bit_to_test;
	wrd &= 1;
	return wrd;
}
/**************************************************************
This uses a trick to print an unsigned short as a string of
16 bits
*/
void printbits(unsigned short wrd){
	for (int i = 15; i >= 0; i--)
		printf("%1d", testbit(wrd, i));
	printf("\n\n");
	return;
}