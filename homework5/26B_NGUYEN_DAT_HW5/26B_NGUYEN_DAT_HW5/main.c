#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

int main(int argc, char **argv) {
	void display(NODE *root);
	printf("Input file is :%s\n", argv[1]);
	NODE *tree = buildTree(argv[1]);
	return 0;
}
void display(NODE *tree){
	printf("/*************************** Cross Reference Listing ***************************/");
	printf("Cross reference listing made at:");
	//print BST here
	//print source code here

}
