
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_LIGHTS 16
#define FLUSH     while(getchar() != '\n')
int main(int args, char argv[])
{
	// ------FUNCTION PROTOTYPES--------
	void menu_driver(unsigned short);
	int  update(unsigned short*, int choice);
	void overlay(unsigned short*, unsigned short);
	void print_bit(unsigned short lights);

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
		printf(" 2) Turn on center-stage lights.\n");
		printf(" 3) Turn on left-stage lights.\n");
		printf(" 4) Turn on right-stage lights.\n");
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
			choice = strtol(input, NULL, 0); // Conver ANSCII to number
			printf("OPTION: %d\n\n", choice);
			if (1 <= choice && choice <= 10) {
				int okay = update(&lights, choice);
				okay ? print_bit(lights) : printf("Error updating lighting.\n");
			}
			else {
				printf("\n**Option %d is  an invalid choice, please try again**\n", choice);
			}
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
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
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
void overlay(unsigned short* lights, unsigned short pattern) {

}

void print_bit(unsigned short lights) {
	printf("hello");
}
