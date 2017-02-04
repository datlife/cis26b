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
#define INPUT_PROMPT   "Enter your input file (or press Enter for default choice):"
#define INPUT_DEFAULT  "./stocks.txt"
#define FLUSH          while(getchar() != '\n')
#define SENTINEL_NODE  "\177"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

typedef struct list_node  NODE;
typedef struct stack_node STACK_NODE;
typedef enum{ Descending, Ascending }Direction;
enum{ OFF, ON };	// Notify get_node() to free memory

//==========================OBJECT DEFINITIONS============================//
typedef struct {
	char   name[MAX_LEN];
	double quote;
}STOCK;

struct stack_node{
	double		quotes;
	STACK_NODE* next;
};

struct list_node{
	char		name[MAX_LEN];
	int			stack_size;
	STACK_NODE* stack;
	NODE*		next;
	NODE*		prev;
};

typedef struct {
	NODE*  list;
	int    size;
}HEAD;

int main(void){
//==========================FUNCTION PROTOTYPES==========================//
	NODE  *read_file(char  *filename, int *size, NODE **stack);
	char  *get_input(char *message);
	void   display(NODE *list, Direction);
	void   print_manager(NODE *list);
	void   search_manager(NODE *list);
	void   _print(NODE *first, NODE *last, Direction);

//-------------STACK & LINKED LIST OPERATIONS-----------------//
	NODE *get_node(NODE **stack, int kill_signal);
	NODE *init_list(NODE **stack);
	NODE *locate_node(NODE *list, char *name);
	STACK_NODE *push(STACK_NODE *stack, double quote);
	int   insert(STOCK data, NODE *list, NODE **stack);
	void  destroy_list(NODE *list, NODE **stack);

//========================== MAIN FUNCTIONS =============================//
	NODE* stack = NULL; // keep track of deleted nodes - for practice
	HEAD  head;

	char  *input = get_input(INPUT_PROMPT);
	head.list = read_file(input, &head.size, &stack);
	display(head.list, Ascending);	// Display in Ascending Order
	display(head.list, Descending); // Display in Desceding Order
	print_manager(head.list);		// Print sub-list
	search_manager(head.list);		// Search manager

	// Free memory
	destroy_list(head.list, stack);
	free(input);

#ifdef _MSC_VER
	printf(_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Memory Leak\n");
#endif
	system("pause");
	return 0;
}
/*===============================================================
* read_file()
* ===============================================================
* Read input file and sort data while reading input
* 	Pre: filename	 : name of current stock
* 	     list_size   : size of linked list
*		 stack       : stack of available nodes in mem-block
*	Post: address of a linked list
*/
NODE *read_file(char  *filename, int *list_size, NODE **stack){
	FILE  *fp = NULL;
	NODE  *list = NULL;
	//Open a file
	if (strcmp(filename, "") == 0) {
		strcpy(filename, INPUT_DEFAULT);
		printf("File not found. Using default file %s\n\n", INPUT_DEFAULT);

	}
	fp = fopen(filename, "r");
	if (!fp) {
		strcpy(filename, INPUT_DEFAULT);
		printf("\nFile not found. Using default file %s\n\n", INPUT_DEFAULT);
		if (!( fp = fopen(filename, "r"))) {
			printf("File %s not found\n", filename);
			exit(101);
		}
	}
	int count = 0;  								// store the loop counts = number of lines in file
	rewind(fp); 									// Make sure we are at first pos
	// Initialize a list by allocating a sentinel node
	list = init_list(stack);
	// Read file
	int	   size = 1;			//included the sentinel node
	char     stock_name[MAX_LEN];
	double   stock_shares;
	while ((fscanf(fp, "%s  %lf", stock_name, &stock_shares)) != EOF) {   // Stop at the end of file
			STOCK stock = { .quote = stock_shares };
			strcpy(stock.name, stock_name);
			if(insert(stock, list, stack) == 0)
				size++;
	}
	*list_size = size;
	// Close the file
	if (fclose(fp) == EOF) {
		printf("Error closing file %s", filename); exit(201);
	}
	return list;
}
/*=============================================
* locate_node()
* =============================================
* Locate a node in a given link list
* 	Pre:  list    	  : a linked list
* 	      target      : a stock name
*	Post: address of node having the same name
		  NULL if not found
*/
NODE *locate_node(NODE *list, char *target){
	NODE *pWalk = list->next;
	while (strcmp(pWalk->name, SENTINEL_NODE) != 0){
		if (strcmp(pWalk->name, target) == 0)
			return pWalk;
		pWalk = pWalk->next;
	}
	return NULL;
}
/*=============================================
* _print()
* =============================================
* print utility to dispaly a list
* 	Pre:  first    	 : start node 
* 	      last       : end node
		  direction  : ascending/descending
*	Post: display to console output
*/
void   _print(NODE *first, NODE *last, Direction direction){
	switch (direction){
		case Descending:{			//Using p->next			
			NODE *tmp = first;
			while (tmp != last){
				if (strcmp(tmp->name, SENTINEL_NODE) != 0)
					printf("%-6s ",tmp->name);
				tmp = tmp->next;
			}
			printf("%-*s ", MAX_LEN, tmp->name);
		}
		break;
		case Ascending:{			//Using p->prev			
			NODE *tmp = first;
			while (tmp != last){
				if (strcmp(tmp->name, SENTINEL_NODE)!= 0)
					printf("%-6s ", tmp->name);
				tmp = tmp->prev;
			}
			printf("%-*s ", MAX_LEN, tmp->name);
		}
		break;
		default:
			printf("\nWrong Direction EnumType\n");
			break;
	}
	printf("\n");
}
/*================================================
* print_manager()
* ================================================
* Ask user to enter two stocks and display sublist
* 	Pre:  list    	 : a linked list

*	Post: display sublist to screen
*/
void   print_manager(NODE *list){
	char first_stock[MAX_LEN] = { 0 };
	char second_stock[MAX_LEN] = { 0 };
	char print_type[MAX_LEN] = { 0 };
	char condition[MAX_LEN] = { 0 };
	printf("\n\n======================Display Sub-list============================");
	do{
		printf("\n\n");
		// Get user input
		printf("Enter first stock: ");				gets(first_stock);
		printf("Enter second stock: ");				gets(second_stock);
		//Return null if not found
		NODE *start_node = locate_node(list, first_stock);
		NODE *end_node = locate_node(list, second_stock);
		// Display sublist
		if (start_node && end_node){
			printf("\n%s to %s: \n", first_stock, second_stock);
			// Display in four ways
			_print(start_node, end_node, Descending);
			_print(end_node, start_node, Ascending);
			_print(start_node, end_node, Ascending);
			_print(end_node, start_node, Descending); 
		}
		else {		// One of two stock inputs is not found or both 
			if (start_node == NULL)
				printf("%s ", first_stock);
			if (end_node == NULL)
				printf("%s", second_stock);
			printf(" - Not Found\n");
		}		
	} while (printf("\nWould you like to print again? (Y)"), gets(condition),
			 ((toupper(condition[0]) == 'Y') && strlen(condition) == 1));

}
/*===========================================================
* search_manager()
* =========================================================
* Ask user to enter a stock and number of quotes to display
* 	Pre:  list    	 : a linked list

*	Post: display list of n quotes
*/
void search_manager(NODE *list){
	char stock[MAX_LEN];
	char condition[MAX_LEN];
	printf("\n\n====================== Search Manager ============================");
	// Get user input
	while (printf("\n\nEnter a stock name (or QUIT/quit): "), gets(stock), strcmp(stock, "QUIT") && strcmp(stock,"quit")){
		NODE *node = locate_node(list, stock);
		// Display stock
		if (node){
			int size = 0;
			printf("Enter amount of quotes to display: ");
			if (scanf("%d", &size) == 1){
				// Validate size if not exceeding stack size
				if (size > node->stack_size) {
					printf("Please enter smaller amount (max is %d): ", node->stack_size);
					scanf("%d", &size);
				}
				printf("Stock %s : ", node->name);
				STACK_NODE *tmp = node->stack;
				//Traverse through the stack to print
				for (int i = 0; i < size; i++) {
					printf("$%-5.2f   ", tmp->quotes);
					tmp = tmp->next;
				}
				FLUSH;
			}
			else
				printf("\nPlease only enter number\n");	
		}
		else{
			printf("%s - not found\n", stock);
		}
	}
}
/*===========================================================
* display()
* =========================================================
* Print list in Ascending/Descending
* 	Pre:  list    	 : a linked list
		  direction  : Ascending/Descending
*	Post: display list to screen
*/
void  display(NODE *list, Direction direction) {
	NODE *tmp = NULL;
	switch (direction){
		case Ascending:{
			printf("\n-------- Ascending order ----------\n");
			tmp = list->next;
			while (strcmp(tmp->name, SENTINEL_NODE)) {
				printf("%-5s: $%-5.2f\n", tmp->name, tmp->stack->quotes);
				tmp = tmp->next;
				}
		}
		break;
		case Descending:{
			printf("\n-------- Descending order ---------\n");
			tmp = list->prev;
			while (strcmp(tmp->name, SENTINEL_NODE)) {
				printf("%-5s : $%-5.2f\n", tmp->name, tmp->stack->quotes);
				tmp = tmp->prev;
			}
		}
		break;
	}
}
/*===========================================================
* get_input
* =========================================================
* Get user input 
* 	Pre:  message: prompt to display to ask user
*	Post: user input
*/
char *get_input(char *message){
	char *fname = (char*)malloc(MAX_LEN);
	if ( fname == NULL) {
		printf("Fatal malloc error in get_node!\n");
		exit(1);
	}
	printf(message);
	fgets(fname, MAX_LEN, stdin);
	fname[strcspn(fname, "\n")] = 0;
	return fname;
}

//-------------STACK OPERATIONS-----------------//
/*===========================================================
* push()
* =========================================================
* Push operation for Stack
* 	Pre: stack : allocated stack node
		 data  : data
*	Post: push to stack
*/
STACK_NODE *push(STACK_NODE *stack, double data){
	STACK_NODE *pnew;

	pnew = (STACK_NODE *)malloc(sizeof (STACK_NODE));
	if (!pnew){
		printf("... error in push!\n");
		exit(1);
	}
	pnew->quotes = data;
	pnew->next = stack;
	stack = pnew;

	return stack;
}

//------------LINKED-LIST OPERATIONS -----------//
/************************************************
Gets a free node from the free stacl (if not
empty) or from a malloc'ed block of structs
*/
NODE *get_node(NODE **stack,int destroy_signal){
	#define BLOCKSIZE 5
	NODE *first = NULL;
	static NODE *block = NULL, *blockrear;
	static NODE *memstack[20] = { NULL };
	static int  i = 0;

	// Could be a better solution by using node* array to keep track of Block address.
	// However, it requires me to pass that array to every insert/delete call.
	switch (destroy_signal)
	{
		case OFF:
		{
			if (*stack != NULL){			  // pop node off the free stack
				first = *stack;
				*stack = (*stack)->next;
				first->next = NULL;			 // detach from stack
			}
			else if (block != NULL){		 // get node from block
				first = block;
				if (block == blockrear) block = NULL;
				else block++;   // move to the next struct
			}
			else{  // stack and block are NULL!
				if ((block = (NODE *)malloc(BLOCKSIZE * sizeof(NODE))) == NULL){
					printf("Fatal malloc error in get_node!\n");
					exit(1);
				}
				memset(block, 0, BLOCKSIZE * sizeof(NODE)); 
				memstack[i++] = block;
				blockrear = block + BLOCKSIZE - 1;
				first = block;
				block++;
			}
			return first;
		}
			break;
		case ON:{
			char test[sizeof(NODE)] = { 0 };
			for (int i = 0; memstack[i] != NULL; i++){				// GO to first element in each memblock
				for (int s = 0; s < BLOCKSIZE; s++){				// Iterate through block to free stack of each node (if available) before free memblock
					NODE *curr_addr = memstack[i] + s;
					if (memcmp(curr_addr, test, sizeof (NODE)) != 0){ // If block is created (not 0 due to above memset)
						STACK_NODE *curr_stack = curr_addr->stack;
						while (curr_stack){
							STACK_NODE *tmp = curr_stack;
							curr_stack = curr_stack->next;
							free(tmp);
						}
					}			
				}
				free(memstack[i]);									// Free memblock
			}
		}
		break;
	}
	return NULL;
}
/*=========================================================
* init_list()
* =========================================================
* Initialize a Linked-List
* 	Pre: stack : save list of available nodes to use

*	Post: initialize linked list with a sentinel node
*/
NODE *init_list(NODE **stack){
	NODE *list = NULL;
	// Allocate sentinal node
	list = get_node(stack, OFF);
	//Set setinal node
	strcpy(list->name,SENTINEL_NODE);
	list->next = list;
	list->prev = list;
	list->stack_size = -1;
	list->stack = NULL;
	return list;
}
/*=========================================================
* insert()
* =========================================================
* Insert operation for LINKED List Structure
* 	Pre: new_stock: data	
		 list     : linked list to insert
		 stack    : list of available nodes in heap
*	Post: insert a new stock to linkedlist OR add new price
*/
int  insert(STOCK new_stock, NODE *list, NODE **stack){

	NODE *curr = list->next;
	NODE *prev = list;
	NODE *pnew = NULL;
	int   duplicate = 1;
	// search
	while (strcmp(new_stock.name, curr->name) > 0){
		prev = curr;
		curr = curr->next;
	}
	if (strcmp(new_stock.name, curr->name)){
		duplicate = 0;
		pnew = get_node(stack, OFF);
		// Alloclate name for pnew
		strcpy(pnew->name, new_stock.name);
		pnew->stack = push(pnew->stack, new_stock.quote);
		(pnew->stack_size)++;
		// set prev and next
		pnew->next = curr;
		pnew->prev = curr->prev;
		pnew->next->prev = pnew;
		pnew->prev->next = pnew;
	}
	else if (strcmp(new_stock.name, curr->name) == 0) // duplicate 
	{	
		curr->stack = push(curr->stack, new_stock.quote);
		(curr->stack_size)++;
	}
	return duplicate;
}

/*=========================================================
* destroy()
* =========================================================
 Free memory in linkedlist
*/
void  destroy_list(NODE *list, NODE **stack) {
	// Activate kill signal in get node
	get_node(list, ON);
}

/*
Enter your input file (or press Enter for default choice):as

File not found. Using default file ./stocks.txt

-------- Ascending order ----------
AAPL : $119.73
AMZN : $810.11
CSCO : $30.04
EBAY : $30.64
FB   : $127.85
GOOG : $804.46
INTC : $23.94
MSFT : $32.60
NFLX : $139.39
ORCL : $32.78
ZNGA : $2.64

-------- Descending order ---------
ZNGA  : $2.64
ORCL  : $32.78
NFLX  : $139.39
MSFT  : $32.60
INTC  : $23.94
GOOG  : $804.46
FB    : $127.85
EBAY  : $30.64
CSCO  : $30.04
AMZN  : $810.11
AAPL  : $119.73


======================Display Sub-list============================

Enter first stock: AMZN
Enter second stock: AAPL

AMZN to AAPL:
AMZN   CSCO   EBAY   FB     GOOG   INTC   MSFT   NFLX   ORCL   ZNGA   AAPL
AAPL   ZNGA   ORCL   NFLX   MSFT   INTC   GOOG   FB     EBAY   CSCO   AMZN
AMZN   AAPL
AAPL   AMZN

Would you like to print again? (Y)y


Enter first stock: AAPL
Enter second stock: GOOG

AAPL to GOOG:
AAPL   AMZN   CSCO   EBAY   FB     GOOG
GOOG   FB     EBAY   CSCO   AMZN   AAPL
AAPL   ZNGA   ORCL   NFLX   MSFT   INTC   GOOG
GOOG   INTC   MSFT   NFLX   ORCL   ZNGA   AAPL

Would you like to print again? (Y)y


Enter first stock: as
Enter second stock: AMZN
as  - Not Found

Would you like to print again? (Y)n


====================== Search Manager ============================

Enter a stock name (or QUIT/quit): QU
QU - not found

Enter a stock name (or QUIT/quit): FB
Enter amount of quotes to display: 5

Stock FB : $127.85   $27.43   $27.61   $20.72   $26.85

Enter a stock name (or QUIT/quit): AMZN
Enter amount of quotes to display: 100
Please enter smaller amount (max is 2): 2

Stock AMZN : $810.11   $249.74

Enter a stock name (or QUIT/quit): QUIT

No Memory Leak
Press any key to continue . . .
*/