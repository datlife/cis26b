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

#define MAX_LEN 200
#define FLUSH while( getchar()!= '\n') 

typedef struct nodeTag {
	char data;
	struct nodeTag *left;
	struct nodeTag *right;
	int count;
}NODE;

// Function Declarations
NODE *buildTree(char *input_file);
int   insert(NODE **root, char *target);
void  printTreeInorder(NODE *root);

#endif // ! BST_HEADER_