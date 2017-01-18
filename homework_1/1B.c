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
#include <string.h>

#define MAX_LEN 25

typedef struct {
	char  name[MAX_LEN];
	int   shares;
} STOCK;

STOCK *read_file(char  *filename, int *arr_size);
void   save_file(char  *filename, STOCK file[]);
void   sortByName(STOCK list[], int size);
void   printList(char title[], const STOCK *list, int size, char format[]);
int    found_duplicate(char stock_name[], const STOCK *list, int size);

int main(void)
{
	int    arr_size = 0;
	char  *input_file = "in.txt";
	char  *output_file = "out.txt";
	STOCK *stock_arr = NULL;
	// Read input file
	stock_arr = read_file(input_file, &arr_size);

	if (stock_arr) {
		// Sort List by Name [Insertion Sort]
		// sortByName(stock_arr, arr_size);
		// Display to screen
		char* format = "%-7s %5d\n";
		printList("Stock Summary", stock_arr, arr_size, format);

		// Save file into output_file
		//save_file(output_file, stock_arr);
	}
	//RELEASE MEMORY
	return 0;
}

/*===============================================================
* read_file()
* ===============================================================
* Read input file
* 	Pre: filename	 : name of current stock
* 	     arr_size    : number of stocks in the list
*
*	Post: return address of dynamically allocated list
*/
STOCK *read_file(char  *filename, int *arr_size) {
	// Declare local variables
	FILE  *fp;
	int    size = 0;
	//Open a file
	fp = fopen(filename, "r+");
	if (!fp) {
		printf("File not found\n");
		exit(101);
	}
	rewind(fp); 									// Make sure we are at first pos
	int count = 0;  								// store the loop counts = number of lines in file
	if (fscanf(fp, "%d", &count) == 0) {
		printf("Cannot get number of lines\n");
		exit(101);
	}
	// Dynamic Allocation arr_stock 
	STOCK *arr_stock = (STOCK*)calloc(count, sizeof(STOCK));
	//temp
	char  stock_name[MAX_LEN];
	int   stock_shares;
	for (int i = 0; i < count; i++) {

		if ((fscanf(fp, "%s %d \n", stock_name, &stock_shares)) != EOF) {
			int pos = found_duplicate(stock_name, arr_stock, size);			// Check if there is a duplicate stock name
			if (pos > -1)
				arr_stock[pos].shares += stock_shares;
			else {
				//perform insertion short here if possible
				strcpy(arr_stock[size].name, stock_name);
				arr_stock[size].shares = stock_shares;
				size++;
			}
		}
		else
			break;
		//Copye size of list to arr_size
		*arr_size = size;
	}
	fclose(fp);
	return arr_stock;
}
/*===============================================================
* save_file()
* ===============================================================
* Create an output file
* 	Pre: filepath	 : full path to outputfile
* 	     file        : array of STOCKs

*	Post: create an ouputfile
*/
void   save_file(char  *filename, STOCK file[]) {
	// Open file in writing mode, remmber using wx
	// copy data to file
}
/*===============================================================
* sortByName()
* ===============================================================
* Sort list by Stock name using Insertion Sort
* 	Pre: list	 : array of STOCKs
* 	     size    : size of array

*	Post: sorted array
*/
void   sortByName(STOCK list[], int size) {

}
/*===============================================================
* printList()
* ===============================================================
* Display an array of Stocks
* 	Pre: title   : title of ouput result
list	 : array of STOCKs
* 	     size    : size of array
format  : format description used in printf(format,..)
*	Post: sorted array
*/
void   printList(char title[], const STOCK *list, int size, char format[]) {
	printf("\n%s\n\n", title);
	for (int i = 0; i < size; i++)
		printf(format, list[i].name, list[i].shares);
	printf("\n");
}
/*===============================================================
* found_duplicate()
* ===============================================================
* check if current stock input has already created before
* 	Pre: name	 : name of current stock
* 	     arr_stock   : list of stocks
* 	     size        : size of list
*	Post: 0 - is Not existed
*	      n - a number - position where existed stock is found
*/
int   found_duplicate(char name[], const STOCK *arrStock, int size) {

	if (size == 0) return -1;
	int found = -1;
	for (int i = 0; i < size; i++) {
		if (strcmp(name, arrStock[i].name) == 0) {
			found = i;
			break;
		}
	}
	return found;
}
