/*
Pointers, Stacks & Queues

There are a number of errors (about 10) in the following program.
Locate all errors, fix them (as shown below), run the program, and save its output.

Here is an example:

int num = 10;
int *ptr;

num = &ptr; // <== Error: Comment the line and write the correct line below

// num = &ptr; // Error #1
ptr = &num;

NAME:
IDE:
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define NUM_STU 3

typedef struct
{
	char  name[31];
	int   midterm[2];
	int   final;
} STUDENT;

typedef struct node NODE;
struct node
{
	STUDENT     data;
//***Error*****: struct node next <-- should be a pointer
	NODE 	    *next;
};

void printStu(const STUDENT *pStu);
NODE *push(NODE *stack, const STUDENT *pStu);
NODE *pop(NODE **stack);
void enqueue(NODE **queue, NODE **rear, const STUDENT *pStu);
NODE *dequeue(NODE **queue, NODE **rear);

int main(void)
{

	STUDENT  stuList[NUM_STU] =
	{
		{ "Taylor, Noah", { 85, 94 }, 92 },
		{ "Smith, Olivia", { 91, 89 }, 86 },
		{ "Brown, Liam", { 87, 88 }, 90 }
		//{ "Davis, Emma", { 96, 88 }, 97 },
		//{ "Garcia, Mason", { 79, 93 }, 92 },
		//{ "Lopez, Sophia", { 83, 78 }, 95 }
	};
//***Error*****: unitialized pointer
	NODE *stack = NULL, *top   = NULL;
//***Error*****: front should be a pointer
	NODE *queue = NULL, *rear = NULL, *front = NULL;

//***Error**** should be = NUM_STU
	int count = NUM_STU;

	// build stack and queue with data from an array of STUDENT structures
	srand((unsigned int)time(NULL));
	// Why do we need to push/enqueue randomly? It coul possibly replicate a same number twice
	int i = rand() % NUM_STU;

	for (int n = 0; n < count; n++){
//***Error*****:  stuList[i] should by passed by reference
		stack = push(stack, &stuList[n]);   
		enqueue(&queue, &rear, &stuList[n]);
	}

	// display stack
	printf("STACK contents from top to bottom:\n");

//***Error**** : no need to allocate memory in heap for top
	//top = (NODE *)malloc(sizeof(NODE));
	//if (!top) printf("... error!\n"), exit(1);

//**Error** : should pass address of stack
	while ((top = pop(&stack))) {
		printStu(&top->data);
//**Error** : memory leak
		free(top);
	}
	printf("\n\n");

	// display queue
	printf("QUEUE contents from front to rear:\n");

//**Error** : queue and rear should be passed by reference
	while ((front = dequeue(&queue, &rear))){ // front != NULL
		printStu(&front->data);
//**Error** : memory leak
		free(front); 
	}
	printf("\n\n");
#ifdef _MSC_VER
	printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

	return 0;
}
/***************************************************
Displays the fileds of a STUDENT structure
Pre   pStu - a pointer to a STUDENT structure
Post
*/
void printStu(const STUDENT *pStu)
{
	printf("%-30s %4d %4d %4d\n",
		pStu->name,
		pStu->midterm[0],
		pStu->midterm[1],
		pStu->final);
}
/***************************************************
Stack Insert: insert in the beginning
*/
NODE *push(NODE *stack, const STUDENT *pStu)
{
	NODE *pnew;
	pnew = (NODE *)malloc(sizeof (NODE));

	if (!pnew){
		printf("... error in push!\n");
		exit(1);
	}
	pnew->data = *pStu;
	pnew->next = stack;
	stack = pnew;
	return stack;
}

/***************************************************
Stack Delete: delete the first node
*/
NODE *pop(NODE **stack)
{
	NODE *first;
	if (*stack == NULL) return NULL;
	first = *stack;
	*stack = (*stack)->next;
	first->next = NULL;

	return first;
}

/***************************************************
Queue Insert: insert at the end
*/
void enqueue(NODE **queue, NODE **rear, const STUDENT *pStu)
{
	NODE *pnew;
	pnew = (NODE *)malloc(sizeof (NODE));
	if (!pnew){
		printf("... error in enqueue!\n");
		exit(1);
	}
	pnew->data = *pStu;
	pnew->next = NULL;
	if (*queue == NULL) *queue = pnew;
	else (*rear)->next = pnew;
	*rear = pnew;
	return;
}

/***************************************************
Queue Delete: remove the first node
*/
NODE *dequeue(NODE **queue, NODE **rear)
{
	NODE *first;
	if (*queue == NULL) return NULL;
	first = *queue;
	*queue = (*queue)->next;
	if (*queue == NULL) *rear = NULL;
	first->next = NULL;

	return first;
}

/*	================= Sample Output ================= */
/*	Results:


*/
