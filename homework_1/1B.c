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

#define MAX_LEN 25
#define INPUT_PATH  "./in.txt"
#define OUTPUT_PATH "./out.txt"
#define FORMAT_DESC "%-7s %5d\n"
#define FLUSH       while(getchar() != '\n')

typedef struct {
	char  name[MAX_LEN];
	int   shares;
} STOCK;

STOCK *read_file(char  *filename, int *arr_size);
void   save_file(char  *filename, STOCK *file, int size);
void   print_list(char title[], const STOCK *list, int size, char format[]);

// Helper functions
void   sort_by_name(STOCK *new_stock, STOCK *list, int size);
int    found_duplicate(char stock_name[], const STOCK *list, int size);
void   write_data(FILE *fp, char *filename, STOCK* list, int size);

int main(void)
{
	int    arr_size = 0;
	STOCK *arr_stock = NULL;

	arr_stock = read_file(INPUT_PATH, &arr_size);						 // Read input file 
	if (arr_stock) {
		print_list("Stock Summary", arr_stock, arr_size, FORMAT_DESC);   // Display to screen
		save_file(OUTPUT_PATH, arr_stock, arr_size);					 // Save file into output_file
		free(arr_stock);												 // Release memory
	}
	return 0;
}

/*===============================================================
* read_file()
* ===============================================================
* Read input file and sorted data while reading input
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
	if (!(fp = fopen(filename, "r+"))){
		printf("File not found\n");
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
		if ((fscanf(fp, "%s %d \n", stock_name, &stock_shares)) != EOF) {   // Stop at the end of file
			int pos = found_duplicate(stock_name, arr_stock, size);			// Check if there is a duplicate stock name
			if (pos > -1)
				arr_stock[pos].shares += stock_shares;
			else {
				STOCK temp;
				strcpy(temp.name, stock_name); temp.shares = stock_shares;
				// Add new stock to current sorted list.
				sort_by_name(&temp, arr_stock, size);
				size++;
			}
		}
		else
			break;
		//Copy size of list to arr_size
		*arr_size = size;
	}
	if (fclose(fp) == EOF){
		printf("Error closing file %s", filename);
		exit(201);
	}
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
void   save_file(char  *filename, STOCK *file, int size) {
	// Open file in writing mode, remmber using wx
	FILE  *fp;
	//Open a file
	fp = fopen(filename, "r");
	if (!fp) { // File is not created yet
		write_data(fp, filename, file, size);
	}
	else{     // File is existed
		char choice;
		while (1){
			printf("File %s is existed. Do you want to overwrite? (y/n)", filename);
			scanf("%c", &choice);
			if (toupper(choice) == 'Y'){
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
	if (fclose(fp) == EOF){
		printf("Error closing file %s", filename);
		exit(201);
	}
}
/*===============================================================
* write_data()
* ===============================================================
* To avoid write codes twice in save_file().
*	Post: write data to a file
*/
void   write_data(FILE *fp, char *filename, STOCK* file, int size){
	fp = fopen(filename, "w");
	fprintf(fp, "%d\n", size);
	for (int i = 0; i < size; i++){
		fprintf(fp, "%-6s %-4d\n", file->name, file->shares);
		file++;
	}
	printf("\nFile is saved to %s\n", filename);
}

/*===============================================================
* sort_by_name()
* ===============================================================
* Add and new stock to sorted list.
* 	Pre: list	 : array of STOCKs
*	     size    : size of array
*	Post: sorted array
*/
void   sort_by_name(STOCK *new_stock, STOCK *list, int size) {
	if (size == 0){
		strcpy(list[0].name, new_stock->name);
		list[0].shares = new_stock->shares;
	}
	else{
		STOCK *p_walk = list;
		while(p_walk != (list + size)){
			if (strcmp(new_stock->name, p_walk->name) <= 0){
				STOCK p_prev;
				strcpy(p_prev.name, p_walk->name); p_prev.shares = p_walk->shares;
				// Shift array by one element
				for (STOCK *p_curr = p_walk + 1; p_curr != (list + size + 1); p_curr++){
					// Swapping
					STOCK temp;
					strcpy(temp.name, p_curr->name);   temp.shares = p_curr->shares;	
					strcpy(p_curr->name, p_prev.name); p_curr->shares = p_prev.shares;
					strcpy(p_prev.name, temp.name);    p_prev.shares = temp.shares;   											
				}
				// Copy new stock
				strcpy(p_walk->name, new_stock->name);
				p_walk->shares = new_stock->shares;
				break;
			}
			p_walk++;			
		}
		if (p_walk == list + size){
			// Copy new stock
			strcpy(p_walk->name, new_stock->name);
			p_walk->shares = new_stock->shares;
		}
	}
}
/*===============================================================
* print_list()
* ===============================================================
* Display an array of Stocks
* 	Pre: title   : title of ouput result
list	 : array of STOCKs
* 	     size    : size of array
format  : format description used in printf(format,..)
*	Post: sorted array
*/
void   print_list(char title[], const STOCK *list, int size, char format[]) {
	printf("\n%s\n\n", title);
	for (int i = 0; i < size; i++)
		printf(format, list[i].name, list[i].shares);
	printf("\n");
}
/*===============================================================
* found_duplicate()
* ===============================================================
* Validate if stock input has already created before.

* 	Pre: name		 : name of current stock
* 	     arr_stock   : list of stocks
* 	     size        : size of list

*	Post: 0 - is Not existed
*	      n - position where existed stock is found
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
