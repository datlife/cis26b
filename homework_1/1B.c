/***
CIS 26B: Homework 1B
********************
NAME: Dat Nguyen
IDE (compiler): Visual Studio 2015
*************************************************************************

Review: Functions, Structures, Pointers, Arrays, Sorting, Data Files,
and Dynamic Allocation of Memory

Create and process a dynamically allocated array of structures
Save the output as a comment at the end of the program!
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>   // used in toupper()
#include <string.h>
#include <errno.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define MAX_LEN 25
#define INPUT_PATH   "./in.txt"
#define INPUT_PROMPT "Enter your input file (or press Enter for default choice):"

#define OUTPUT_PATH   "./out.txt"
#define OUTPUT_PROMPT "Enter your output file (or press Enter for default choice):"

#define FORMAT_DESC  "%-7s %5d\n"
#define FLUSH       while(getchar() != '\n')


typedef struct {
	char  name[MAX_LEN];
	int   shares;
} STOCK;

STOCK *read_file(char  *filename, int *arr_size);
void   save_file(char  *filename, STOCK *file, int size);
void   print_list(char title[], const STOCK *list, int size, char format[]);

// Helper functions
char  *get_input(char *message);
void   sort_by_name(STOCK *list, int size);
int    found_duplicate(char stock_name[], const STOCK *list, int size);
void   write_data(FILE *fp, char *filename, STOCK* list, int size);

int main(void)
{
	int    arr_size = 0;
	STOCK *arr_stock = NULL;
	char  *input_file = get_input(INPUT_PROMPT);
	arr_stock = read_file(input_file, &arr_size);						 // Read input file 

	if (arr_stock) {
		sort_by_name(arr_stock, arr_size);								 // Insertion sort

		print_list("Stock Summary", arr_stock, arr_size, FORMAT_DESC);   // Display to screen

		char  *output_file = get_input(OUTPUT_PROMPT);
		save_file(output_file, arr_stock, arr_size);					 // Save file into output_file

		free(arr_stock);												 // Release memory
		free(output_file);
	}
	free(input_file);

#ifdef _MSC_VER
	printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "\nNo Memory Leak\n");
#endif
	return 0;
}

/*===============================================================
* read_file()
* ===============================================================
* Read input file and sort data while reading input
* 	Pre: filename	 : name of current stock
* 	     arr_size    : number of stocks in the list
*
*	Post: return address of dynamically allocated list
*/
STOCK *read_file(char  *filename, int *arr_size) {
	// Declare local variables
	int    size = 0;
	FILE  *fp;
	STOCK *arr_stock = NULL;

	//Open a file
	if (strcmp(filename, "") != 0)
		fp = fopen(filename, "r");
	else
		fp = fopen(INPUT_PATH, "r");

	if (!fp) {
		printf("File %s not found\n", filename);
		exit(101);
	}
	int count = 0;  								// store the loop counts = number of lines in file
	rewind(fp); 									// Make sure we are at first pos
	if (fscanf(fp, "%d", &count) == 0) {
		printf("Cannot get number of lines\n");
		exit(101);
	}
	// Dynamic Allocation arr_stock 
	arr_stock = (STOCK*)calloc(count, sizeof(STOCK));

	// Temp variables
	char  stock_name[MAX_LEN];
	int   stock_shares;

	for (int i = 0; i < count; i++) {
		if ((fscanf(fp, "%s  %d", stock_name, &stock_shares)) != EOF) {   // Stop at the end of file
			// Copy input to array
			strcpy(arr_stock[size].name, stock_name); arr_stock[size].shares = stock_shares;
			size++;
		}
		else
			break;
		*arr_size = size;
	}
	// Close the file
	if (fclose(fp) == EOF) {
		printf("Error closing file %s", filename); exit(201);
	}
	return arr_stock;
}
/*===============================================================
* sort_by_name()
* ===============================================================
* Add new stock to sorted list.
* 	Pre: list	 : array of STOCKs
*	     size    : size of array
*	Post: sorted array
*/
void   sort_by_name(STOCK *list, int size){
	STOCK temp, *p_current, *p_walk;
	for (p_current = list + 1; p_current <= list + size - 1; p_current++){
		temp = *p_current;	// copy current student to temp
		p_walk = p_current - 1; // save previous element
		while (p_walk >= list && (strcmp(temp.name, p_walk->name) <= 0)){
			*(p_walk + 1) = *p_walk;
			*p_walk--;
		}
		*(p_walk + 1) = temp;
	}
}
/*===============================================================
* save_file()
* ===============================================================
* Create an output file
* 	Pre: filepath	 : full path to outputfile
* 	     file        : array of STOCKs
*	Post: create an ouputfile
*/
void   save_file(char  *filename, STOCK *file, int size) {
	// Open file in writing mode, remmber using wx
	FILE  *fp;
	//Open a file
	//Open a file
	if (strcmp(filename, "") != 0) fp = fopen(filename, "r");
	else {
		fp = fopen(OUTPUT_PATH, "r");
		strcpy(filename, OUTPUT_PATH);
	}
	if (!fp) { // File is not created yet
		fp = fopen(filename, "w");
		write_data(fp, filename, file, size);
	}
	else {     // File is existed
		char choice;
		while (1) {
			printf("File %s is existed. Do you want to overwrite? (y/n)", filename);
			scanf("%c", &choice);
			if (toupper(choice) == 'Y') {
				fp = fopen(filename, "w");
				write_data(fp, filename, file, size);
				break;
			}
			else if (toupper(choice) == 'N') break;
			else {
				printf("\nInvalid choice. Please type again\n");
				FLUSH;
			}
		}
	}
	if (fclose(fp) == EOF) {
		printf("Error closing file %s", filename);
		exit(201);
	}
}
/*===============================================================
* write_data()
* ===============================================================
* Helper function for save_file().
* To avoid write codes twice in
*	Post: write data to a file
*/
void   write_data(FILE *fp, char *filename, STOCK* arr, int size) {
	fprintf(fp, "%d\n", size);
	for (int i = 1; i < size; i++) {
		int shares = arr[i - 1].shares;
		while (strcmp(arr[i].name, arr[i - 1].name) == 0) {
			shares += arr[i].shares;
			i++;
		}
		fprintf(fp, "%-6s %-4d\n", arr[i - 1].name, shares);
	}
	printf("\nFile is saved to %s\n", filename);
}
/*===============================================================
* print_list()
* ===============================================================
* Display an array of Stocks
* 	Pre:  title   : title of ouput result
*		  list	 : array of STOCKs
* 	      size    : size of array
*         format  : format description used in printf(format,..)
*	Post: Display array to console screen
*/
void   print_list(char title[], const STOCK *list, int size, char format[]) {
	printf("\n%s\n\n", title);
	for (int i = 1; i < size - 1; i++){
		int shares = list[i - 1].shares;
		while (strcmp(list[i].name, list[i - 1].name) == 0) {
			shares += list[i].shares;
			i++;
		}
		printf(format, list[i - 1].name, shares);
	}
	printf("\n");
}
/*===============================================================
* get_input()
* ===============================================================
* Prompt message and return user input
* 	Pre: message : a message to print
*	Post: char* : address of dynamic allocated string
*/
char *get_input(char *message) {
	char *fname = (char*)malloc(MAX_LEN);
	printf(message);
	fgets(fname, MAX_LEN, stdin);
	fname[strcspn(fname, "\n")] = 0;
	return fname;
}

/*
=============================SAMPLE OUTPUT==============================

Enter your input file (or press Enter for default choice):

Stock Summary

AAL       369
AAPL     2879
BBBY      471
CHTR      423
EBAY      899
GOOG      123
GOOGL     123
MSFT      380
NLFX     1474
SIRI     1908
TSLA     1383
XLNX      350
YHOO      458

Enter your output file (or press Enter for default choice):
File ./out.txt is existed. Do you want to overwrite? (y/n)sdas

Invalid choice. Please type again
File ./out.txt is existed. Do you want to overwrite? (y/n)y

File is saved to ./out.txt

No Memory Leak
Press any key to continue . . .
*/