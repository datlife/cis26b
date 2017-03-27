/*
Binary Search Tree header file
*/
#ifndef  BST_HW5_H_
#define  BST_HW5_H_

#if _MSC_VER > 1700		//If compiler is Visual Studio 2012 or later, disable safety warning
	#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"

#define MAX_LEN 200
#define FLUSH while( getchar()!= '\n') 

typedef struct nodeTag {
	char *data;
	QueueNode *front, *rear;
	struct nodeTag *left, *right;
	int count;
}NODE;

// Function Declarations
NODE *buildTree(char *input_file, FILE *fp);
int   insert(NODE **root, char *target, int curr_line);
void  printTreeInorder(NODE *root);
void  printNode(NODE *);
void  printTreeInorderToFile(NODE *root, FILE *);
void  printNodeToFile(NODE *, FILE *);

void  destroyTree(NODE *root);
void  destroyNode(NODE *node);

// Helper functions to build a trees
void  tokenize_line(char *a_line, int curr_line, NODE **tree);
void  remove_pattern(char *curr_line, char start_dilimeter, char end_dilimiter);  //remove "..." and <...>
#endif // ! BST_HEADER_