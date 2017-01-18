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

#define MAX_LEN 25

typedef struct{
    char *name; 
    int   shares;    
} STOCK;

STOCK *read_file (char  *filename, int *arr_size);
void   save_file (char  *filename, STOCK file[]);
void   sortByName(STOCK list[], int size);
void   printList(const STOCK *list, char format[]);
int    found_duplicate(char stock_name[], const STOCK *list, int size);

int main(void)
{
    char  *input_file  = "in.txt";
    char  *output_file = "out.txt";
    int    arr_size    =  0;    
    STOCK *stock_arr   =  NULL;

    stock_arr = read_file(input_file, &arr_size);

    if (stock_arr){
	// Sort List by Name [Insertion Sort]
    	sortByName(stock_arr, arr_size);

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
	FILE  *fp;
	STOCK *arr_stock = NULL;
	int    size = 0;

	//Open a file
	fp = fopen(filename, "r+");
	
	if (!fp){
	    printf("File not found\n");
       "::exit(101);
    }

    // Make sure we are at first pos
    rewind(fp);

    // Read the first line
    int count = 0;
    if ( fscanf(fp,"%d", &count) == 0){
        printf("Cannot get number of lines\n");
        exit(101);
    }
    for (int i = 0; i < count; i++)
    {
        char  stock_name[MAX_LEN];
        int   stock_shares;
        // %*c to discard \n: end of line
        if ( (fscanf(fp,"%s %d \n", stock_name, &stock_shares)) != EOF)
        {
            // Compare with previous stock
	    printf("%-7s %-5d\n", stock_name, stock_shares);
            // Check if there is a duplicate stock name
	    int dup_pos = found_duplicate(stock_name, arr_stock, size);
	    if (dup_pos > -1)
		arr_stock[dup_pos]->shares += stock_shares;
	    else{
		
	    }
	
            // If found , add num_shares
        }
        else
            break;
    }
    fclose(fp);
    printf("%d", *arr_size);

    return input;
}
void   save_file (char  *filename, STOCK file[]){

}
void   sortByName(STOCK list[], int size){

}
void   printList(STOCK list[], char format[]){

}
/*===============================================================
 * found_duplicate()
 * ==============================================================
 * check if current stock input has already created before
 * 	Pre: name	 : name of current stock
 * 	     arr_stock   : list of stocks
 * 	     size        : size of list
 *	Post: 0 - is Not existed
 *	      n - a number - position where existed stock is found
 */
int   found_duplicate(char name[], const STOCK *arrStock, int size){

	if (size == 0 ) return 0;
	
	int found = -1;
	for (int i = 0; i < size; i++){
	    if ( strcmp(name, arrStock->name) == 0){
		found_duplicate = i;
		break;
	    }
	}
	return found;
}
