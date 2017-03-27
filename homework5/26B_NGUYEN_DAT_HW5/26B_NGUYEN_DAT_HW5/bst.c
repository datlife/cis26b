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
int insert(NODE **root, char *target, int curr_line) {
	NODE **ptr_root = root;
	while (*ptr_root) {
		if (strcmp(target, (*ptr_root)->data) > 0)
			ptr_root = &(*ptr_root)->right;
		else if (strcmp(target, (*ptr_root)->data) < 0)
			ptr_root = &(*ptr_root)->left;
		else {
			//ASSUMPTION: we inserted line in order so I only compare with the last node in queue if
			// it is on the same line.
			enqueue(&(*ptr_root)->front, &(*ptr_root)->rear, curr_line); // Update line number into a queue
			return 0; //Duplicate entry
		}
	}
	if (!(*ptr_root = (NODE *)malloc(sizeof(NODE))))
		printf("Fatal malloc error!\n"), exit(1);

	(*ptr_root)->data = (char *)malloc(strlen(target) + 1);
	if (!((*ptr_root)->data))
		printf("Fatal malloc error!\n"), exit(1);
	strcpy((*ptr_root)->data, target);
	(*ptr_root)->front = (*ptr_root)->rear = NULL;
	(*ptr_root)->right = (*ptr_root)->left = NULL;

	enqueue(&(*ptr_root)->front, &(*ptr_root)->rear, curr_line); // Update line number into a queue
	return 1; // data inserted
}

/*===============================================================
* build_Tree()
* ===============================================================
* Read input file and sort data while reading input
* 	Pre: filename	 : input file
*	Post: binary search tree
*/
NODE *buildTree(char *filename, FILE  *fp) {
	// ASSUMPTION:
	// FILE has been validated in checkArgs()
	NODE  *tree = NULL;
	rewind(fp);
	int	   num_lines = 1;
	char   a_line[MAX_LEN];
	char   comment_flag = 0;
	while ((fgets(a_line, MAX_LEN, fp) != NULL)) {						// Stop at the end of file
		if (comment_flag == 0 && strstr(a_line, "/*") == NULL) { 		// Check if this a start of comment block
			if (strstr(a_line, "//") != NULL) {							// Check if this a comment line.
				num_lines++;
				continue;
			}
			else {
				// printf("Line %d: %s", num_lines, a_line); -- DEBUG
				tokenize_line(a_line, num_lines, &tree);
			}
		}
		else if (strstr(a_line, "*/") != NULL)							// end of block comment
			comment_flag = 0;
		else {
			comment_flag = 1;											// still in comment block
			num_lines++;
			continue;
		}
		num_lines++;
	}
	//FILE will be closed in main.
	return tree;
}
/***************************************************
Extract line into tokens and insert to BST
*/
void tokenize_line(char *a_line, int curr_line, NODE **tree) {
#define DILIMITERS  "#=.!*[]0123456789<>{}();&|+-*\\/, "
	char *tmp = NULL;
	char *token = NULL;
	while (isspace((unsigned char)*a_line)) a_line++;				// Trim leading space
	a_line[strcspn(a_line, "\n")] = '\0';							// Trim new line '\n'
	if (*a_line != 0) {
		if (!(tmp = (char *)malloc(strlen(a_line) + 1)))
			printf("Fatal malloc error!\n"), exit(1);
		strcpy(tmp, a_line);
																	// printf("Tokenized values:%s\n", tmp); --- DEBUG
		remove_pattern(tmp, '"', '"'); 								// Remove "..." or <...>
		remove_pattern(tmp, '<', '>');
		token = strtok(tmp, DILIMITERS);
	}
	while (token != NULL) {
		if (strlen(token) != 0) {
			// printf("%s\n", token); --- DEBUG
			insert(tree, token, curr_line);
		}
		token = strtok(NULL, DILIMITERS);
	}
	if (tmp != NULL)
		free(tmp);
}
/*===============================================================
* printTreeInOrder()
* ===============================================================
* Display Tree in Console output
* 	Pre: root	 : root of BST
*	Post: display to console output
*/
void printTreeInorder(NODE *root) {
	if (root) {
		printTreeInorder(root->left);
		printNode(root);
		printTreeInorder(root->right);
	}
}
/*===============================================================
* printNode()
* ===============================================================
* Display one node in Binary Search Tree
*/
void printNode(NODE *root) {
	printf("%-22s :  ", root->data);
	QueueNode *pwalk = root->front;
	while (pwalk != NULL) {
		printf("%-4d ", pwalk->line_number);
		pwalk = pwalk->next;
	}
	printf("\n");
}
/*===============================================================
* printTreeInOrderToFile()
* ===============================================================
* Save Tree into an ouputfile
* 	Pre: root	 : root of BST
*	Post: save BST to outputfile
*/
void  printTreeInorderToFile(NODE *root, FILE *output) {
	if (root) {
		printTreeInorderToFile(root->left, output);
		printNodeToFile(root, output);
		printTreeInorderToFile(root->right, output);
	}
}
/*===============================================================
* printNodeToFile()
* ===============================================================
* Save node into an outputfile
pre : BST, outputfile
post: save a node in BST into an outputfile
*/
void  printNodeToFile(NODE *root, FILE *output) {
	fprintf(output, "%-22s :  ", root->data);
	QueueNode *pwalk = root->front;
	while (pwalk != NULL) {
		fprintf(output, "%-4d ", pwalk->line_number);
		pwalk = pwalk->next;
	}
	fprintf(output, "\n");
}

void   destroyTree(NODE *root) {
	if (root) {
		destroyTree(root->left);
		destroyTree(root->right);
		destroyNode(root);
	}
}
void destroyNode(NODE *node) {
		// delete queue
		QueueNode *ptr = node->front;
		QueueNode *ptr2 = ptr->next;
		while (ptr != NULL)
		{
			if (ptr != ptr2)
				free(ptr);
			ptr = ptr2;
			if (ptr2 && ptr2->next) ptr2 = ptr2->next;
			else ptr2 = NULL;
		}
		// delete string
		free(node->data);
		// delete node
		free(node);
}
/*===============================================================
* remove_pattern()
* ===============================================================
* Replace library name and string with space
	<..> "..." --> space ' '
* 	Pre: root	 : root of BST
*	Post: removed <..> and ".." out of a line
*/
void remove_pattern(char *curr_line, char start_dilimeter, char end_dilimiter){
	// Iterate through a line and find pattern
	char *curr_pos = strchr(curr_line, start_dilimeter);
	if (curr_pos){
		*curr_pos = ' ';
		curr_pos++;
		if (strchr(curr_pos, end_dilimiter) != NULL) {
			while (*curr_pos != end_dilimiter) {
				*curr_pos = ' ';
				curr_pos++;
			}
			*curr_pos = ' ';
		}
	}
}
