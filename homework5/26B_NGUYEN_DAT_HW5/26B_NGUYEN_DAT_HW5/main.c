#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

int main(int argc, char **argv) {
	void display(NODE *root);
	printf("Input file is :%s\n", argv[1]);
	NODE *tree = buildTree(argv[1]);
	display(tree);
	return 0;
}
void display(NODE *tree){
	time_t time_val;
	time(&time_val); // get current time

	printf("/*************************** Cross Reference Listing ***************************/\n");
	printf("\nCross reference listing made at: %s", asctime(localtime(&time_val)));
	//print BST here
	//print source code here
}
