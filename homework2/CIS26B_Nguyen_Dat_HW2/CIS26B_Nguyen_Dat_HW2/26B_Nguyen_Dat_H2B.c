/***
CIS 26B: Homework 2B
********************
NAME: Dat Nguyen
IDE (compiler): Visual Studio 2015
*************************************************************************


*/
#define _CRT_SECURE_NO_WARNINGS			// to avoid using fopen_s and strcpy_s on Visual Studio

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  
#include <string.h>
#include <errno.h>

#define MAX_LEN        25
#define BLOCK_SIZE	   5
#define INPUT_PROMPT   "Enter your input file (or press Enter for default choice):"
#define INPUT_DEFAULT  "./stocks.txt"
#define FORMAT_DESC    "%-7s %5d\n"
#define FLUSH          while(getchar() != '\n')

typedef struct list_node  NODE;
typedef struct stack_node STACK_NODE;

//==========================OBJECT DEFINITIONS============================//
typedef struct{
	char	*name;
	double   price;
}STOCK;

struct stack_node{
	STOCK  data;
	STACK_NODE* next;
};

struct list_node{
	NODE*		forward;
	NODE*		backward;
	STACK_NODE* stack;
	int			stack_size;
};

int main(void){
	//==========================FUNCTION PROTOTYPES==========================//
	NODE  *read_file(char  *filename);
	char  *get_input(char *message);

	//-------------STACK OPERATIONS-----------------//
	STACK_NODE *push(STACK_NODE *stack, STOCK data);
	STACK_NODE *pop(STACK_NODE **stack);

	//------------LINKED-LIST OPERATIONS -----------//
	NODE *get_node(NODE **stack); // could be wrong. watch out stack node
	NODE *init_list(NODE **stack);
	void  insert(NODE *list, STOCK data);
	int   delete(NODE *list, STOCK data);

	NODE* stack = NULL; // keep track of deleted nodes
	NODE* list = NULL;

	char  *input = get_input(INPUT_PROMPT);
	list = init_list(&stack);
	list = read_file(input);
}
/*


*/
NODE *read_file(char  *filename){
	FILE  *fp = NULL;
	//Open a file
	if (strcmp(filename, "") == 0)
		strcpy(filename, INPUT_DEFAULT);  // I assume the maximum buffer is 100
	fp = fopen(filename, "r");

	if (!fp) {
		printf("File %s not found\n", filename); 
		exit(101);
	}

	int count = 0;  								// store the loop counts = number of lines in file
	rewind(fp); 									// Make sure we are at first pos
	printf("%s", filename);

	// MAGIC HERE

	return NULL;
}
char *get_input(char *message){
	char *fname = (char*)malloc(MAX_LEN);
	printf(message);
	fgets(fname, MAX_LEN, stdin);
	fname[strcspn(fname, "\n")] = 0;
	return fname;
}

//-------------STACK OPERATIONS-----------------//
STACK_NODE *push(STACK_NODE *stack, STOCK data){
	return NULL;
}
STACK_NODE *pop(STACK_NODE **stack){
	return NULL;

}

//------------LINKED-LIST OPERATIONS -----------//
NODE *get_node(NODE **stack){
	return NULL;

}
NODE *init_list(NODE **stack){
	return NULL;


}
void  insert(NODE *list, STOCK data){

}