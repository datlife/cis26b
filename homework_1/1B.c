/***
 CIS 26B: Homework 1B
 ********************
 NAME: Dat Nguyen
 IDE (compiler): Vim 8.0 
 *************************************************************************
 
   Review: Functions, Structures, Pointers, Arrays, Sorting, Data Files,
        and Dynamic Allocation of Memory
    
   Create and process a dynamically allocated array of structures
   Save the output as a comment at the end of the program!
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_LEN 25

typedef struct{
    char *name; 
    int   shares;    
} STOCK;

STOCK *read_file (char  *filename, int *arr_size);
void   save_file (char  *filename, STOCK file[]);
void   sortByName(STOCK list[], int size);
void   printList(STOCK list[], char format[]);


int main(void)
{
    char  *input_file  = "in.txt";
    char  *output_file = "out.txt";
    int   *arr_size    =  NULL;    
    STOCK *stock_arr   =  NULL;

    stock_arr = read_file(input_file, arr_size);

    if (stock_arr){
	// Sort List by Name [Insertion Sort]
    	sortByName(stock_arr, *arr_size);

	// Display to screen
	char* format = "%-25s %10d";
	printList(stock_arr, format);

	// Save file into output_file
	save_file(output_file, stock_arr);
    }    
    return 0;
}

STOCK *read_file (char  *filename, int *arr_size){
	
	// Local variables
	FILE *fp;
	STOCK *input = NULL;
	int arr_size = 0;

	//Open a file
	fp = fopen(filename, "r+");
	if (!fp){
		printf("File not found\n");
		return NULL;
	}

    // Make sure we are at first pos
    rewind(fp);
    // Read the first line
    


	return input;
}
void   save_file (char  *filename, STOCK file[]){

}
void   sortByName(STOCK list[], int size){

}
void   printList(STOCK list[], char format[]){

}
