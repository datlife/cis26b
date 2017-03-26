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
	//NODE **ptr_root = root;
	//while (*ptr_root) {
	//	if (strcmp(target, (*ptr_root)->data) > 0)
	//		ptr_root = &(*ptr_root)->right;
	//	else if (strcmp(target, (*ptr_root)->data) < 0)
	//		ptr_root = &(*ptr_root)->left;
	//	else {
	//		return 0; //Duplicate entry
	//	}
	//}
	//if (!(*ptr_root = (NODE *)malloc(sizeof(NODE))))
	//	printf("Fatal malloc error!\n"), exit(1);
	//(*ptr_root)->data = target;
	//(*ptr_root)->left = (*ptr_root)->right = NULL;
	//return 1; // data inserted
	return 0;
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
	rewind(fp); 									
	int	   num_lines = 1;							
	char   a_line[MAX_LEN];
	char   comment_flag = 0;
	while ((fgets(a_line, MAX_LEN, fp) != NULL)) {   // Stop at the end of file

		//Check if this a comment block.
		if (strstr(a_line, "/*") == NULL) {					
			tokenize_line(a_line, &comment_flag);
		}
		//When to skip? // or /**/
		num_lines++;
	}
	// Close the file
	if (fclose(fp) == EOF) {
		printf("Error closing file %s", filename); exit(201);
	}
	return tree;
}

void tokenize_line(char *a_line, char *comment_signal) {
	#define DILIMITERS  "#=.!*[]0123456789<>{}();&|+-*\\/, "
	char *tmp = (char *)malloc(strlen(a_line) + 1);
	char *token = NULL;
	// Trim leading space
	while (isspace((unsigned char)*a_line)) a_line++;

	if (*a_line != 0) {
		strcpy(tmp, a_line);
		printf("Tokenized values:%s\n", tmp);

		// Remove "..." or <...>
		deleteIrrelavantParts(tmp);
		token = strtok(tmp, DILIMITERS);
	}
	while (token != NULL) {
		if (strlen(token) != 0)
			printf("%s\n", token);
			// insert
		else
			printf("Empty\n");
		token = strtok(NULL, DILIMITERS);
	}
	free(tmp);
	//Look at sample output
}

///***************************************************
//Delete library name and string
//  <..> "..." --> space ' '
//*/
void deleteIrrelavantParts(char *curr_line)
{
	//// Case 1: " .... "
	char *ptr;
	ptr = strchr(curr_line, '"');
	if (ptr)
	{
		*ptr = ' ';
		ptr++;
		while (*ptr != '"'){
			*ptr = ' ';
			ptr++;
		}
		*ptr = ' ';
	}
	//// Case 2: < .... >
	ptr = strchr(curr_line, '<');
	if (ptr)
	{
		char *ptr2 = strchr(ptr, '>'); // to check if it's a pair of <>
									   // replace everything in <> (including the signs) with ' ' (space)
		if (ptr2)
		{
			*ptr = ' ';
			ptr++;
			while (*ptr != '>'){
				*ptr = ' ';
				ptr++;
			}
			*ptr = ' ';
		}
	}

}
