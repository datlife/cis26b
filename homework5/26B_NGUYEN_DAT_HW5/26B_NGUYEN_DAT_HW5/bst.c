#include "bst.h"
/*===============================================================
* insert()
* ===============================================================
* Insert a new input into Binary Search Tree
* 	Pre: root	 : root of BST
		 target  : input
*	Post: 0 : insert failed //duplicated entry
		  1 : interted into BST
*/
int insert(NODE **root, char *target) {
	NODE **ptr_root = root;
	while (*ptr_root) {
		if (strcmp(target, (*ptr_root)->data) > 0)
			ptr_root = &(*ptr_root)->right;
		else if (strcmp(target, (*ptr_root)->data) < 0)
			ptr_root = &(*ptr_root)->left;
		else {
			return 0; //Duplicate entry
		}
	}
	if (!(*ptr_root = (NODE *)malloc(sizeof(NODE))))
		printf("Fatal malloc error!\n"), exit(1);
	(*ptr_root)->data = target;
	(*ptr_root)->left = (*ptr_root)->right = NULL;
	return 1; // data inserted
}
void printTreeInorder(NODE *root) {

}
/*===============================================================
* build_Tree()
* ===============================================================
* Read input file and sort data while reading input
* 	Pre: filename	 : input file
*	Post: binary search tree
*/
NODE *buildTree(char *filename) {
	FILE  *fp = NULL;
	NODE  *tree = NULL;
	//Open a file
	if (filename == NULL) {
		printf("Input File is not provided. \n\n");
		exit(101);
	}
	fp = fopen(filename, "r");
	if (!fp) {
		printf("\nFile %s was not found.\n\n", filename);
		exit(101);
	}
	int count = 0;  								// store the loop counts = number of lines in file
	rewind(fp); 									// Make sure we are at first pos
													// Initialize a list by allocating a sentinel node
	// Read file
	int	   num_lines = 1;							//included the sentinel node
	char     a_line[MAX_LEN];
	while ((fgets(a_line, MAX_LEN, fp) != NULL)) {   // Stop at the end of file
		printf("%-4d : %s\n", num_lines, a_line);
		//Got a line. Now what?
		//Tokenize line and insert into a tree
		//Look at sample output
		//Dilimiters: [=.!*[]0-9<> ]
		//When to skip? // or /**/

		num_lines++;
	}
	// Close the file
	if (fclose(fp) == EOF) {
		printf("Error closing file %s", filename); exit(201);
	}
	return tree;
}
